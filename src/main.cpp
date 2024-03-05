#include "main.hpp"

//uart variables and function prototypes
static QueueHandle_t uart0_queue;
static const char * TAG = "";      

static void UART_ISR_ROUTINE(void *pvParameters);


//gui variables

TFT_eSPI tft = TFT_eSPI();


//adbms pins and object
int8_t adbms_pins[4] = {18,19,23,CS};//tab for custom SPI Pins. sck, miso, mosi, cs is a pin order. In this tab i use HSPI port SPI pins
ADBMS1818Class adbms = ADBMS1818Class(adbms_pins); //constructor with modified pins
//ADBMS1818 adbms((uint8_t)FSPI, (uint8_t)CS); //construcot with modified CS pin and spi port
//ADBMS1818 adbms(15); //constructor with default SPI and CS pin modifed
//ina238 driver
//address depends on signals attached to A0 and A1 pins of ina238. 
//https://www.ti.com/lit/ds/symlink/ina238-q1.pdf?ts=1623446444912#page=15
ina238 ina((uint16_t)INA238_ADDR);
//lm35 sensor class
LM35 lm35 = LM35();
//eeprom mem manager class
MemManager mem_manager = MemManager();
//lvgt gui vars
static const uint32_t screenWidth  = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
uint16_t touchX, touchY;





void setup() {
  //configure memory
  if(mem_manager.firstUse()){
    mem_manager.setDefaultSettings();
  }else{
    mem_manager.updateValues();
  }
  //this line should be deleted after
  mem_manager.setDefaultSettings();
  //configure lm35 driver
  lm35.setResolution(ADBMS_ADC_RESOLUTION);
  //configuring UART interrupts 
  uart_config_t uart_0_config = {
    .baud_rate = BAUD_RATE, 
    .data_bits = UART_DATA_8_BITS, 
    .parity = UART_PARITY_DISABLE, 
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  uart_param_config(UART_NUM_0, &uart_0_config);
  esp_log_level_set(TAG, ESP_LOG_INFO);
  uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_0, BUF_SIZE, BUF_SIZE, 20, &uart0_queue, 0);
  xTaskCreate(UART_ISR_ROUTINE, "UART_ISR_ROUTINE", 2048, NULL, 12, NULL);
  //ina238 begin
  ina.begin();
  //adbms begin
  pinMode(CS, OUTPUT);
  adbms.begin(mem_manager.getADBMSQuantity());
  //tft screeen begin
  tft.init();
  tft.setRotation(3);
  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch( calData );
  //init setup of LVGL
  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register( &disp_drv );

   //Initialize the (dummy) input device driver
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init( &indev_drv );
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   indev_drv.read_cb = my_touchpad_read;
   lv_indev_drv_register( &indev_drv );
   //initialize pwm 
   pwmproc::init_pwm();
  //initialize terminal tasks
  huart::init_tasks();
     //Initialize styles
    gui::init_styles();
    gui::init_transition_screen();
   //gui::init_demo_screen();
   gui::init_start_screen();
   gui::load_current();
   //initialize tasks
    gui::init_adbms_task();
    //lv_example_win_1();
    //setup core 0 task
    
}




void loop() {
    lv_timer_handler();
    delay(5);
}




void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
  uint16_t touchX, touchY;
   bool touched = tft.getTouch( &touchX, &touchY, TOUCH_THRESHOLD );
   
   if( !touched )
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;
   }
}

static void UART_ISR_ROUTINE(void *pvParameters){
  uart_event_t event;
  size_t buffered_size;
  bool exit_condition = false;
  while(!exit_condition){
    if(xQueueReceive(uart0_queue, (void *)&event, (portTickType)portMAX_DELAY)){
      if(event.type == UART_DATA){

        uint8_t UART0_data[128];
        int UART0_data_length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t*)&UART0_data_length));
        UART0_data_length = uart_read_bytes(UART_NUM_0, UART0_data, UART0_data_length, 100);
        UART0_data_length -= 2;
        char command[UART0_data_length+1];
        strncpy(command, (char *)UART0_data, UART0_data_length);
        huart::interpret_command(command);
      }
    }
  }
  vTaskDelete(NULL);
}

