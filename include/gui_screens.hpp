#include "gui_renders.hpp"
#include "user_defines.h"
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#include "pwm_procedures.hpp"
#include "settings_mem.hpp"
#include "lm35.hpp"
#include <vector>
#include <cstring>
#include <exception>

namespace gui{
    //machine state
    /*STATE DESCRIPTION
    1 -> main screen
    2 -> process screen
    3 -> during process screen
    4 -> data screen
    5 -> start settings screen
    6 -> misc or battery settings screen
    */
    static uint8_t state;
    //energy and cells relate variable
    static uint32_t tot_cell_qnt;
    static uint8_t cells_qnt;
    static float sum_cell_volt;
    static int temperature;
    static float input_voltage;
    static int max_power; //whats the formula of max power? Is it DC input voltage * max_current or is it fixed? 
    static uint8_t process_type_selected;
    static uint8_t data_type_selected;
    static uint8_t current_adbms;
    static uint32_t safety_timer;
    static float capacity;
    static float current_curr;
    static uint16_t dV_max;
    static uint8_t charge_state;

    //styles
    static lv_color_t main_buttons_colors[6] 
        {
        LV_COLOR_MAKE(110,210,70),  // CHARGE button 
        LV_COLOR_MAKE(255,200,80),  // STORE button 
        LV_COLOR_MAKE(255,120,80),  // DISCHG button 
        LV_COLOR_MAKE(140,200,255), // DATA button 
        LV_COLOR_MAKE(188,168,188), // CYCLE button 
        LV_COLOR_MAKE(185,190,155)  // SETTINGS button
        };
    static lv_style_t main_buttons_pr_styles[6];
    static lv_style_t main_buttons_styles[6];
    static lv_style_t black_button_style;
    static lv_style_t black_button_pr_style;
    static lv_style_t main_screen_style;
    static lv_style_t process_label_style;
    static lv_style_t info_cont_style;
    static lv_style_t basic_label_style;
    static lv_style_t error_label_style;
    static lv_style_t process_data_label_style;
    static lv_style_t msg_box_style;
    static lv_style_t msg_box_btn_style;
    static lv_style_t bar_style;
    static lv_style_t green_bar_style;
    static lv_style_t red_bar_style;
    static lv_style_t yellow_bar_style;
    
    void init_styles();
    void init_main_scr_style();
    void init_main_btn_style();
    void init_main_btn_pr_style();
    void init_prc_lbl_style();
    void init_prc_data_lbl_style();
    void init_info_cnt_style();
    void init_msg_box_style();
    void init_msg_box_btn_style();
    void init_basic_label_style();
    void init_error_label_style();
    void init_bars_style();



    //event handlers
    static void settings_scr_switch_handler(lv_event_t *e);
    static void battery_set_scr_switch_handler(lv_event_t *e);
    static void misc_set_scr_switch_handler(lv_event_t *e);
    static void charge_scr_switch_handler(lv_event_t *e);
    static void store_scr_switch_handler(lv_event_t *e);
    static void disch_scr_switch_handler(lv_event_t *e);
    static void cycle_scr_switch_handler(lv_event_t *e);
    static void process_back_handler(lv_event_t *e);
    static void process_start_switch_handler(lv_event_t *e);
    static void process_stop_handler(lv_event_t *e);
    static void process_stop_msgbox_handler(lv_event_t *e);
    static void data_next_adbms_handler(lv_event_t *e);
    static void data_prev_adbms_handler(lv_event_t *e);
    static void data_next_mode_handler(lv_event_t *e);
    static void data_start_switch_handler(lv_event_t *e);
    static void data_process_switch_handler(lv_event_t *e);
    static void data_back_handler(lv_event_t *e);

    //screens
    static lv_obj_t *curr_scr;
    static lv_obj_t *trans_scr;
    static lv_obj_t *label_conv;
    static lv_obj_t *label_cell_qnt;
    static lv_obj_t *label_cell_volt_temp;
    static lv_obj_t *label_input_electricity;
    static lv_obj_t *label_info_cont;
    static lv_obj_t *label_cells_voltage[18];
    static lv_obj_t *bars_cells_voltage[18];
    static lv_obj_t *label_special_symbol;
    static lv_obj_t *label_start_process;
    static lv_obj_t *label_process_data[6];
    void init_start_screen();
    //process screens
    void init_process_screen(uint8_t process_type = CHARGE_PROCESS);
    void init_start_process_screen(uint8_t process_type = CHARGE_PROCESS);

    void init_chg_process_screen(lv_obj_t *cont);
    void init_start_chg_process_screen(lv_obj_t *cont);

    void init_dischg_process_screen(lv_obj_t *cont);
    void init_start_dischg_process_screen(lv_obj_t *cont);

    void init_cycle_process_screen(lv_obj_t *cont);
    void init_start_cycle_process_screen(lv_obj_t *cont);

    void init_store_process_screen(lv_obj_t *cont);
    void init_start_store_process_screen(lv_obj_t *cont);
    //data screens
    void init_data_list_screen();
    void init_data_candles_screen();
    void init_data_process_graph();
    //settings screens
    void init_settings_start_screen();
    void init_settings_battery_screen();
    void init_settings_misc_screen();
    //helper screens;
    void init_transition_screen();
    void load_transition();
    void load_current();

    //tasks
    static lv_timer_t *adbms_read;
    static lv_timer_t *process_task;
    
    void adbms_start_scr_read(lv_timer_t *timer);
    void adbms_data_scr_read(lv_timer_t *timer);
    void adbms_data_candles_scr_read(lv_timer_t *timer);
    void adbms_data_graph_scr_read(lv_timer_t *timer);
    void adbms_process_scr_read(lv_timer_t *timer);
    void adbms_start_process_scr_read(lv_timer_t *timer);
    void adbms_start_process_chg_scr_read(lv_timer_t *timer);
    void adbms_start_process_dsg_scr_read(lv_timer_t *timer);
    void adbms_start_process_store_scr_read(lv_timer_t *timer);
    void adbms_start_process_cycle_scr_read(lv_timer_t *timer);
    void adbms_settings_scr_read(lv_timer_t *timer);

    void process_charge(lv_timer_t *timer);
    void process_store(lv_timer_t *timer);
    void process_discharge(lv_timer_t *timer);
    void process_cycle(lv_timer_t *timer);
    
    void init_adbms_task();
};