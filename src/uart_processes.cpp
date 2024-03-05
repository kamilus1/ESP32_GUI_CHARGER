#include "uart_processes.hpp"

extern ADBMS1818Class adbms;
extern ina238 ina;
namespace huart{
   
    void init_tasks(){
        commands_list.insert(std::pair<char*, std::function<void()>>("gd", start_transmitting));
        commands_list.insert(std::pair<char*, std::function<void()>>("sd", stop_transmitting));
        is_transmiting = false;
    }

    void start_transmitting(){
        if(!is_transmiting){
            is_transmiting = true;
            transmit_task = lv_timer_create(transmit_data, 2000, NULL);
        }
    }

    void stop_transmitting(){
        if(is_transmiting){
            is_transmiting = false;
            lv_timer_del(transmit_task);
        }
    }
    
    
    void interpret_command(char *command){
        try{
            std::function<void()> task = commands_list.at(command);
            task();
        }catch (const std::out_of_range& e){
            uart_write_bytes(UART_NUM_0, e.what(), strlen(e.what()));
        }
        
    }

    void transmit_data(lv_timer_t *timer){
        char buffer[256];
        char line_buffer[32];
        adbms.cell_detect();
        sprintf(buffer, "ADBMNS QUANTITY: %u\r\n", (unsigned)adbms.get_n()); 
        sprintf(line_buffer, "TOTAL CELLS QUANTITY: %u\r\n", (unsigned)adbms.get_tot_cell_qnt());
        strcat(buffer, line_buffer);
        sprintf(line_buffer, "ALL CELLS VOLTAGE: %f\r\n", adbms.get_sum_cell_voltage());
        strcat(buffer, line_buffer);
        if(ina.device_found()){
            sprintf(line_buffer, "TEMPERATURE: %f\r\n", ina.read_temperature());
            strcat(buffer, line_buffer);
            sprintf(line_buffer, "CHARGER CURRENT: %f\r\n", ina.read_current());
            strcat(buffer, line_buffer);
            sprintf(line_buffer, "CHARGER VOLTAGE: %f\r\n", ina.read_voltage());
            strcat(buffer, line_buffer);
        }
        for(uint8_t i=0; i<adbms.get_n();i++){
            sprintf(line_buffer, "ADBMS NR: %u\r\n", (unsigned)i);
            strcat(buffer, line_buffer);
            for(uint8_t j=0; j<adbms.get_cell_qnt(i);j++){
                sprintf(line_buffer, "C%u VOLTAGE: %f\r\n", (unsigned)j, adbms(i, j));
            }
        }
        uart_write_bytes(UART_NUM_0,buffer, strlen(buffer));
    }
};