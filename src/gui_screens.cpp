#include "gui_screens.hpp"
extern ADBMS1818Class adbms;
extern ina238 ina;
extern MemManager mem_manager;
extern LM35 lm35;

namespace gui{
    void init_styles(){
        dV_max = 0;
        safety_timer = 0;
        state = 1;
        tot_cell_qnt = 0;
        sum_cell_volt = 0.0;
        temperature = 0;
        input_voltage = 0;
        max_power = 0;
        process_type_selected = 0;
        data_type_selected = 0;
        current_adbms = 0;
        current_curr = 0;
        charge_state = 0;
        capacity = 0;
        init_main_scr_style();
        init_main_btn_style();
        init_main_btn_pr_style();
        init_prc_lbl_style();
        init_prc_data_lbl_style();
        init_info_cnt_style();
        init_basic_label_style();
        init_error_label_style();
        init_msg_box_style();
        init_msg_box_btn_style();
        init_bars_style();
    }
    void init_main_scr_style(){
        lv_style_init(&main_screen_style);
        lv_style_set_bg_color(&main_screen_style, LV_COLOR_MAKE(0, 0, 0));
        lv_style_set_bg_grad_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_width(&main_screen_style, 0);    //Serg
        lv_style_set_border_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));   //Serg add
        lv_style_set_text_color(&main_screen_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_pad_all(&main_screen_style, 0);    //Serg. padding all(0)
        lv_style_set_pad_gap(&main_screen_style, 5);    //Serg. padding_gap(5)
    }

    void init_main_btn_style(){
        lv_style_init(&black_button_style);
        lv_style_set_radius(&black_button_style, 0);
        lv_style_set_text_color(&black_button_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_bg_opa(&black_button_style, LV_OPA_100);
        lv_style_set_bg_color(&black_button_style, LV_COLOR_MAKE(0, 0, 0));
        lv_style_set_border_width(&black_button_style, 2);
        lv_style_set_border_color(&black_button_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_opa(&black_button_style, LV_OPA_100);
        lv_style_set_shadow_width(&black_button_style, 0);
        lv_style_set_shadow_ofs_y(&black_button_style, 0);
        lv_style_set_outline_opa(&black_button_style, LV_OPA_COVER);
        lv_style_set_outline_color(&black_button_style, LV_COLOR_MAKE(0, 0, 0));
        lv_style_set_pad_all(&black_button_style, 10);
        for(uint8_t i=0;i<6;i++){
            lv_style_init(&main_buttons_styles[i]);
            lv_style_set_radius(&main_buttons_styles[i], 0);
            lv_style_set_text_color(&main_buttons_styles[i], LV_COLOR_MAKE(0x00, 0x00, 0x00));
            lv_style_set_bg_opa(&main_buttons_styles[i], LV_OPA_100);
            lv_style_set_bg_color(&main_buttons_styles[i], main_buttons_colors[i]);
            lv_style_set_shadow_width(&main_buttons_styles[i], 0);
            lv_style_set_shadow_ofs_y(&main_buttons_styles[i], 0);

            lv_style_set_outline_opa(&main_buttons_styles[i], LV_OPA_COVER);
            lv_style_set_outline_color(&main_buttons_styles[i], main_buttons_colors[i]);
            lv_style_set_pad_all(&main_buttons_styles[i], 10);
        }
    }

    void init_main_btn_pr_style(){
        lv_style_init(&black_button_pr_style);
        lv_style_set_outline_width(&black_button_pr_style, 5);
        lv_style_set_outline_opa(&black_button_pr_style, LV_OPA_TRANSP);
        lv_style_set_translate_y(&black_button_pr_style, 4);
        lv_style_set_shadow_ofs_y(&black_button_pr_style, 3);
        static lv_style_transition_dsc_t trans;
        static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, (lv_style_prop_t)0};
        lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);
        lv_style_set_transition(&black_button_pr_style, &trans);
        for(uint8_t i=0; i < 6 ; i++){
            lv_style_init(&main_buttons_pr_styles[i]);
            lv_style_set_outline_width(&main_buttons_pr_styles[i], 5);
            lv_style_set_outline_opa(&main_buttons_pr_styles[i], LV_OPA_TRANSP);

            lv_style_set_translate_y(&main_buttons_pr_styles[i], 4);
            lv_style_set_shadow_ofs_y(&main_buttons_pr_styles[i], 3);
            
            //lv_style_set_bg_color(&main_buttons_pr_styles[i], main_buttons_colors[i]);
            //lv_style_set_bg_grad_color(&main_buttons_pr_styles[i], lv_palette_darken(main_buttons_colors[i], 4));

            /*Add a transition to the the outline*/
            static lv_style_transition_dsc_t trans;
            static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, (lv_style_prop_t)0};
            lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

            lv_style_set_transition(&main_buttons_pr_styles[i], &trans);
        }
    }

    void init_prc_lbl_style(){
        lv_style_init(&process_label_style);
        lv_style_set_text_color(&process_label_style, lv_palette_main(LV_PALETTE_YELLOW));
        lv_style_set_bg_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
    }

    void init_prc_data_lbl_style(){
        lv_style_init(&process_data_label_style);
        lv_style_set_text_color(&process_data_label_style, LV_COLOR_MAKE(0xff, 0xff, 0xff));
        lv_style_set_bg_color(&process_data_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_color(&process_data_label_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_width(&process_data_label_style, 2);
        lv_style_set_radius(&process_data_label_style, 0);
        lv_style_set_bg_grad_color(&process_data_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_opa(&process_data_label_style, LV_OPA_100);
    }
    void init_info_cnt_style(){             
        lv_style_init(&info_cont_style);
        lv_style_set_radius(&info_cont_style, 0);
       
        /*Make a gradient*/
        lv_style_set_bg_opa(&info_cont_style, LV_OPA_COVER);
        lv_style_set_bg_color(&info_cont_style, LV_COLOR_MAKE(0,0,0));
        lv_style_set_bg_grad_color(&info_cont_style, lv_color_darken(main_buttons_colors[0],100));
        lv_style_set_bg_grad_dir(&info_cont_style, LV_GRAD_DIR_VER);

        /*Shift the gradient to the bottom*/
        lv_style_set_bg_main_stop(&info_cont_style, 150);

        lv_style_set_text_color(&info_cont_style, LV_COLOR_MAKE(255, 255, 255));
    }

    void init_basic_label_style(){
        lv_style_init(&basic_label_style);
        lv_style_set_bg_opa(&error_label_style, LV_OPA_COVER);           
        lv_style_set_bg_grad_dir(&error_label_style, LV_GRAD_DIR_VER);
        lv_style_set_text_color(&basic_label_style, LV_COLOR_MAKE(255, 255, 255));
    }

    void init_error_label_style(){
        lv_style_init(&error_label_style);
        lv_style_set_text_color(&error_label_style, LV_COLOR_MAKE(255, 255, 255));
    }   
    void init_msg_box_style(){
        lv_style_init(&msg_box_style);
        lv_style_set_bg_color(&msg_box_style, LV_COLOR_MAKE(50, 50, 50));
        lv_style_set_border_color(&msg_box_style, LV_COLOR_MAKE(0xff, 0xff, 0xff));
        lv_style_set_text_color(&msg_box_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_radius(&msg_box_style, 0);
        lv_style_set_border_width(&msg_box_style, 3);
    }

    void init_msg_box_btn_style(){
        lv_style_init(&msg_box_btn_style);
        lv_style_set_bg_color(&msg_box_btn_style, LV_COLOR_MAKE(20, 20, 20));
        lv_style_set_border_color(&msg_box_btn_style, LV_COLOR_MAKE(0xff, 0xff, 0xff));
        lv_style_set_radius(&msg_box_btn_style, 0);
        lv_style_set_text_color(&msg_box_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_opa(&msg_box_btn_style, LV_OPA_50);
        lv_style_set_border_width(&msg_box_btn_style, 1);
        
    }

    void init_bars_style(){
        lv_style_init(&bar_style);
        lv_style_set_border_color(&bar_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_width(&bar_style, 2);
        lv_style_set_radius(&bar_style, 0);
        lv_style_set_pad_all(&bar_style, 0);
        lv_style_set_anim_time(&bar_style, 500);

        lv_style_init(&green_bar_style);
        lv_style_init(&red_bar_style);
        lv_style_init(&yellow_bar_style);

        lv_style_set_bg_opa(&green_bar_style, LV_OPA_COVER);
        lv_style_set_bg_opa(&red_bar_style, LV_OPA_COVER);
        lv_style_set_bg_opa(&yellow_bar_style, LV_OPA_COVER);

        lv_style_set_bg_color(&green_bar_style, main_buttons_colors[0]);
        lv_style_set_bg_color(&red_bar_style, main_buttons_colors[2]);
        lv_style_set_bg_color(&yellow_bar_style, main_buttons_colors[1]);

        lv_style_set_radius(&green_bar_style, 2);
        lv_style_set_radius(&red_bar_style, 2);
        lv_style_set_radius(&yellow_bar_style, 2);
    }


    
    static void settings_scr_switch_handler(lv_event_t *e){
        lv_event_code_t code = lv_event_get_code(e);
        if(state == 1 && code == LV_EVENT_CLICKED){
            state = 5;
            load_transition();
            init_settings_start_screen();
            load_current();
            lv_timer_set_cb(adbms_read, adbms_settings_scr_read);
        }else if(state == 5 && code == LV_EVENT_CLICKED){
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
            lv_timer_set_cb(adbms_read, adbms_start_scr_read);
        }
    }
    static void battery_set_scr_switch_handler(lv_event_t *e){
        if(state == 5){
            state = 6;
            load_transition();
            init_settings_battery_screen();
            load_current();
        }else if(state == 6){
            state = 5;
            load_transition();
            init_settings_start_screen();
            load_current();
        }
    }
    static void misc_set_scr_switch_handler(lv_event_t *e){
        if(state == 5){
            state = 6;
            load_transition();
            init_settings_misc_screen();
            load_current();
        }else if(state == 6){
            state = 5;
            load_transition();
            init_settings_start_screen();
            load_current();
        }
    }
    static void charge_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen();
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
        
    }
    static void store_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(STORE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }
    static void disch_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(DISCHARGE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }
    static void cycle_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(CYCLE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }

    static void process_back_handler(lv_event_t *e){
        
        state = 1;
        load_transition();
        init_start_screen();
        load_current();
        lv_timer_set_cb(adbms_read, adbms_start_scr_read);
    }

    static void process_start_switch_handler(lv_event_t *e){
        if(state == 2){
            state = 3;
            capacity = 0;
            temperature = 0;
            uint8_t *process_type = (uint8_t *) lv_event_get_user_data(e);
            switch(*process_type){
                case CHARGE_PROCESS:
                    process_task = lv_timer_create(process_charge, PROCESS_READ_PERIOD, NULL);
                break;
                case STORE_PROCESS:
                    process_task = lv_timer_create(process_store, PROCESS_READ_PERIOD, NULL);
                break;
                case DISCHARGE_PROCESS:
                    process_task = lv_timer_create(process_discharge, PROCESS_READ_PERIOD, NULL);
                break;
                case CYCLE_PROCESS :
                    process_task = lv_timer_create(process_cycle, PROCESS_READ_PERIOD, NULL);
                break;
                default:
                break;
            }
        load_transition();
        init_start_process_screen(*process_type);
        load_current();
        }
        
        
    }

    static void process_stop_handler(lv_event_t *e){
        static const char * btns[] = {"YES", "NO", ""};
        lv_obj_t *stop_mbox = lv_msgbox_create(lv_scr_act(), "STOP", "Stop process?", btns, true);
        lv_obj_add_event_cb(stop_mbox, process_stop_msgbox_handler, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_add_style(stop_mbox, &msg_box_style, LV_STATE_DEFAULT);
        lv_obj_add_style(lv_msgbox_get_close_btn(stop_mbox), &main_buttons_styles[2], LV_STATE_DEFAULT);
        lv_obj_add_style(lv_msgbox_get_close_btn(stop_mbox), &main_buttons_pr_styles[2], LV_STATE_PRESSED);
        lv_obj_add_style(lv_msgbox_get_btns(stop_mbox), &msg_box_btn_style, LV_STATE_DEFAULT);
        lv_obj_center(stop_mbox);
    }

    static void process_stop_msgbox_handler(lv_event_t *e){
        lv_obj_t *obj = lv_event_get_current_target(e);
        if(!strcmp("YES", lv_msgbox_get_active_btn_text(obj))){
            lv_msgbox_close(obj);
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
            lv_timer_del(process_task);
            lv_timer_set_cb(adbms_read, adbms_start_scr_read);
        }else{
            lv_msgbox_close(obj);
        }
    }

    static void data_next_adbms_handler(lv_event_t *e){
        if((current_adbms + 1) >= adbms.get_n()){
            current_adbms = 0;
        }else{
            current_adbms += 1;
        }
        
    }

    static void data_prev_adbms_handler(lv_event_t *e){
        if(current_adbms <= 0){
            current_adbms = (adbms.get_n() - 1);
        }else{
            current_adbms -= 1;
        }
        
    }

    static void data_start_switch_handler(lv_event_t *e){
        
        state = 4;
        data_type_selected = 0;
        load_transition();
        init_data_list_screen();
        load_current();
        lv_timer_set_cb(adbms_read, adbms_data_scr_read);
    }
    static void data_back_handler(lv_event_t *e){
        if(state == 4){
            
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
            lv_timer_set_cb(adbms_read, adbms_start_scr_read);
        }else if(state == 3){
            
            load_transition();
            init_start_process_screen(process_type_selected);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }

    static void data_next_mode_handler(lv_event_t *e){
        switch(data_type_selected){
            case 0:
                data_type_selected += 1;
                load_transition();
                init_data_candles_screen();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_candles_scr_read);
                break;
            case 1:
                data_type_selected += 1;
                load_transition();
                init_data_process_graph();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_graph_scr_read);
                break;
            case 2:
                data_type_selected = 0;
                load_transition();
                init_data_list_screen();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_scr_read);
                break;
            default:
                break;
        }
    }

    void init_transition_screen(){
        trans_scr = lv_obj_create(NULL);
        lv_obj_add_style(trans_scr, &main_screen_style, LV_STATE_DEFAULT);
    }
    void init_start_screen(){
        std::vector<std::string> label_btns_text = {"CHARGE", "STORE", "DISCHARGE", "DATA", "CYCLE", "SETTINGS"};
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        
        //start screen grid 
        static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        static lv_coord_t row_dsc[] = {30, 80, 80, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        
        //container with number of Battery Pack cells detected
        lv_obj_t *info_qnt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_qnt_cont);
        init_cont(info_qnt_cont, &info_cont_style, 0, 3, 3);    //BOTTOM center
        label_cell_qnt = lv_label_create(info_qnt_cont);
        lv_label_set_text_fmt(label_cell_qnt, "%u-s Battery Pack Detected", tot_cell_qnt);
        lv_obj_set_style_text_font(label_cell_qnt, &lv_font_montserrat_20, LV_STATE_DEFAULT);
        lv_obj_align(label_cell_qnt, LV_ALIGN_CENTER, 0, 0);
        
        //container with special_symbol
        lv_obj_t *wifi_symbol = lv_obj_create(cont);
        lv_obj_remove_style_all(wifi_symbol);
        init_cont(wifi_symbol, &basic_label_style, 1, 0, 1);    //TOP center
        label_special_symbol = lv_label_create(wifi_symbol);
        lv_label_set_text(label_special_symbol, LV_SYMBOL_WIFI);
        lv_obj_align(label_special_symbol, LV_ALIGN_CENTER, 0, 0);

        //container with info about temp and voltage.
        lv_obj_t *info_temp_volt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_temp_volt_cont);
        init_cont(info_temp_volt_cont, &basic_label_style, 2, 0, 1);    //TOP right
        label_cell_volt_temp = lv_label_create(info_temp_volt_cont);
        lv_obj_set_style_text_font(label_cell_volt_temp, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_cell_volt_temp,"vBAT:  %.2f v\ntBAT:         %d°c", sum_cell_volt, temperature); // to define Battery's Temp, taken from LM35, applied on 1818's GPIO
        lv_obj_align(label_cell_volt_temp, LV_ALIGN_BOTTOM_LEFT, 0, 0);
        
        //container with info about input electricity
        lv_obj_t *info_input_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_input_cont);
        init_cont(info_input_cont, &error_label_style, 0, 0, 1);    //TOP left
        label_input_electricity = lv_label_create(info_input_cont);
        lv_obj_set_style_text_font(label_input_electricity, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_input_electricity, "INPUT:  %.1f v\ntCHG:     %d°c", input_voltage, temperature); // internal temp in charger, taken from INA
        lv_obj_align(label_input_electricity, LV_ALIGN_BOTTOM_LEFT, 0, 0);

        lv_obj_t *buttons[6];
        lv_obj_t *label_buttons[6];
        
        for(uint8_t i=0; i<6; i++){
            buttons[i] = lv_btn_create(cont);
            lv_obj_add_style(buttons[i], &main_buttons_styles[i], LV_STATE_DEFAULT);
            lv_obj_add_style(buttons[i], &main_buttons_pr_styles[i], LV_STATE_PRESSED);
            lv_obj_set_grid_cell(buttons[i], LV_GRID_ALIGN_STRETCH, (i%3), 1, LV_GRID_ALIGN_STRETCH, ((i+3)/3), 1);
            label_buttons[i] = lv_label_create(buttons[i]);
            lv_label_set_text(label_buttons[i], label_btns_text[i].c_str());
            lv_obj_set_style_text_font(label_buttons[i], &lv_font_montserrat_12, LV_STATE_DEFAULT);
            lv_obj_align(label_buttons[i], LV_ALIGN_BOTTOM_LEFT, -8, 10); 
        }
        lv_obj_add_event_cb(buttons[0], charge_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[1], store_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[2], disch_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[3], data_start_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[4], cycle_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[5], settings_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        
    }

    void init_process_screen(uint8_t process_type){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        lv_obj_t *cont = lv_obj_create(curr_scr);
        uint8_t rows, cols;
        cols = 3;
        switch(process_type){
            case CHARGE_PROCESS:
                init_chg_process_screen(cont);
                rows = 6;
            break;
            case STORE_PROCESS:
                init_store_process_screen(cont);
                rows = 5;
            break;
            case DISCHARGE_PROCESS:
                init_dischg_process_screen(cont);
                rows = 4;
            break;
            case CYCLE_PROCESS:
                init_cycle_process_screen(cont);
                rows = 6;
            break;
            default:
            break;
        }
        std::vector<std::string> process = {"CHARGE", "STORE", "DISCHG", "CYCLE"};
        
        process_type_selected = process_type;
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        init_info_label(cont, label_info_cont, &info_cont_style, (cols+1));
        
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *start_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, rows);
        init_button(start_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 3, rows);
        lv_obj_add_event_cb(back_btn, process_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(start_btn, process_start_switch_handler, LV_EVENT_CLICKED, &process_type_selected);

        lv_obj_t *process_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(process_cont);
        init_cont(process_cont, &process_label_style, 2, rows);
        
        lv_obj_t *label_back_btn = lv_label_create(back_btn);
        lv_obj_t *label_start_btn = lv_label_create(start_btn);
        lv_obj_t *label_process = lv_label_create(process_cont);
        
        lv_obj_set_style_text_font(label_process, &lv_font_montserrat_14, LV_STATE_DEFAULT);

        lv_label_set_text(label_back_btn, "BACK");
        lv_label_set_text(label_start_btn, "START");
        lv_label_set_text(label_process, process[process_type].c_str());
        lv_obj_center(label_back_btn);
        lv_obj_center(label_start_btn);
        lv_obj_center(label_process);
    }
    void init_start_process_screen(uint8_t process_type){
        static lv_coord_t col_dsc[] = {15, 60, 60, 60, 40, 20,15, 30, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 50, 40, 40, 30, LV_GRID_TEMPLATE_LAST};
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        uint8_t cols = 7, rows=5;
        switch(process_type){
            case CHARGE_PROCESS:
                init_start_chg_process_screen(cont);
            break;
            case STORE_PROCESS:
            break;
            case DISCHARGE_PROCESS:
            break;
            case CYCLE_PROCESS:
            break;
            default:
            break;
        }
        std::vector<std::string> process = {"CHARGING IN PROGRESS", "STORING IN PROGRESS", 
        "DISCHARGING IN PROGRESS", "CYCLING IN PROGRESS"};
       
        
        //info container
        init_info_label(cont, label_info_cont, &info_cont_style, 8);
        //buttons
        lv_obj_t *stop_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        init_button(stop_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 5);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 5);
        lv_obj_add_event_cb(stop_btn, process_stop_handler, LV_EVENT_CLICKED, NULL);
        //process cont
        lv_obj_t *process_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(process_cont);
        init_cont(process_cont, &process_label_style, 0, 1, 5);

        lv_obj_t *label_process = lv_label_create(process_cont);
        lv_obj_t *label_stop = lv_label_create(stop_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_set_style_text_font(label_process, &lv_font_montserrat_20, LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label_stop, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label_data, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text(label_process, process[process_type].c_str());
        lv_label_set_text(label_stop, "STOP");
        lv_label_set_text(label_data, "DATA");
        lv_obj_center(label_process);
        lv_obj_center(label_stop);
        lv_obj_center(label_data);
    }
    void init_chg_process_screen(lv_obj_t *cont){
        const char * process_settings[5] = {"CURRENT", "VOLTAGE", "DV MIN", "CUT TEMP",  "SAFETY TIMER"};
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 25, 25, 25, 25, 30,  LV_GRID_TEMPLATE_LAST};
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        uint8_t max_capacity = 100;
        uint8_t settings_cnt = 5;
        //conts
        //settings label conts
        lv_obj_t *settings_label_conts[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_label_conts[i] = lv_obj_create(cont);
            init_cont(settings_label_conts[i], &basic_label_style, 0, (i+1), 2);
        }
        //buttons
        //settings buttons
        lv_obj_t *settings_buttons[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 2, (i+1), 2);
        }
        //labels
        //settings info  labels
        lv_obj_t *settings_labels[settings_cnt];
        for(uint8_t i=0; i<settings_cnt;i++){
            settings_labels[i] = lv_label_create(settings_label_conts[i]);
            lv_label_set_text_fmt(settings_labels[i], "%s", process_settings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0 , 0);
        }
        //settings btn labels
        lv_obj_t *settings_btn_labels[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0 ,0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%.1f", mem_manager.getChgCurr());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.3f", mem_manager.getChgVolt());
        lv_label_set_text_fmt(settings_btn_labels[2], "%u", mem_manager.getdVMin());
        lv_label_set_text_fmt(settings_btn_labels[3], "%u", mem_manager.getCutTemp());
        lv_label_set_text_fmt(settings_btn_labels[4], "%u", mem_manager.getSafetyTimer());
    }

    void init_start_chg_process_screen(lv_obj_t *cont){
        const char* process_values[6] = {"VOLTAGE", "CHG CURR", "BAT TEMP", "CHARGING TIME", "dV MAX", "CHARGED CAPACITY"};
        init_process_data_labels(cont, label_process_data, label_start_process, &process_data_label_style, &basic_label_style, process_values);
    }

    void init_dischg_process_screen(lv_obj_t *cont){
        const char * process_settings[5] = {"CUT VOLTAGE", "DSG CURRENT",  "CUT TEMP"};
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {30, 40, 40, 40, 30,  LV_GRID_TEMPLATE_LAST};
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        uint8_t max_capacity = 100;
        uint8_t settings_cnt = 3;
        //conts
        //settings label conts
        lv_obj_t *settings_label_conts[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_label_conts[i] = lv_obj_create(cont);
            init_cont(settings_label_conts[i], &basic_label_style, 0, (i+1), 2);
        }
        //buttons
        //settings buttons
        lv_obj_t *settings_buttons[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 2, (i+1), 2);
        }
        //labels
        //settings info  labels
        lv_obj_t *settings_labels[settings_cnt];
        for(uint8_t i=0; i<settings_cnt;i++){
            settings_labels[i] = lv_label_create(settings_label_conts[i]);
            lv_label_set_text_fmt(settings_labels[i], "%s", process_settings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0 , 0);
        }
        //settings btn labels
        lv_obj_t *settings_btn_labels[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0 ,0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%.3f", mem_manager.getCutVolt());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.1f", mem_manager.getDischgCurr());
        lv_label_set_text_fmt(settings_btn_labels[2], "%u", mem_manager.getCutTemp());

    }

    void init_start_dischg_process_screen(lv_obj_t *cont){
        const char * process_values[6] = {"VOLTAGE", "DSG CURR", "BAT TEMP", "DSG TIME", "", "DSG CAPACITY"};
        init_process_data_labels(cont, label_process_data, label_start_process, &process_data_label_style, &basic_label_style, process_values);
    }

    void init_cycle_process_screen(lv_obj_t *cont){
        const char * process_settings[5] = {"CHG CURR", "DSG CURR", "DIR", "CUT TEMP",  "REST TIME"};
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 25, 25, 25, 25, 30,  LV_GRID_TEMPLATE_LAST};
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        uint8_t max_capacity = 100;
        uint8_t settings_cnt = 5;
        //conts
        //settings label conts
        lv_obj_t *settings_label_conts[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_label_conts[i] = lv_obj_create(cont);
            init_cont(settings_label_conts[i], &basic_label_style, 0, (i+1), 2);
        }
        //buttons
        //settings buttons
        lv_obj_t *settings_buttons[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 2, (i+1), 2);
        }
        //labels
        //settings info  labels
        lv_obj_t *settings_labels[settings_cnt];
        for(uint8_t i=0; i<settings_cnt;i++){
            settings_labels[i] = lv_label_create(settings_label_conts[i]);
            lv_label_set_text_fmt(settings_labels[i], "%s", process_settings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0 , 0);
        }
        //settings btn labels
        lv_obj_t *settings_btn_labels[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0 ,0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%.1f", mem_manager.getChgCurr());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.1f", mem_manager.getDischgCurr());
        lv_label_set_text_fmt(settings_btn_labels[2], "%s", "UP");
        lv_label_set_text_fmt(settings_btn_labels[3], "%u", mem_manager.getCutTemp());
        lv_label_set_text_fmt(settings_btn_labels[4], "%u", mem_manager.getRestTime());
    }
    void init_start_cycle_process_screen(lv_obj_t *cont){
        const char * process_values[6] = {"VOLTAGE", "CURR", "BAT TEMP", "PROC TIME", "", "DSG CAPACITY"};
        init_process_data_labels(cont, label_process_data, label_start_process, &process_data_label_style, &basic_label_style, process_values);
    }

    void init_store_process_screen(lv_obj_t *cont){
        const char * process_settings[5] = {"CHG CURR", "DSG CURR", "STORE VOLT", "CUT TEMP"};
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 32, 32, 32, 32,  30,  LV_GRID_TEMPLATE_LAST};
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        uint8_t max_capacity = 100;
        uint8_t settings_cnt = 4;
        //conts
        //settings label conts
        lv_obj_t *settings_label_conts[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_label_conts[i] = lv_obj_create(cont);
            init_cont(settings_label_conts[i], &basic_label_style, 0, (i+1), 2);
        }
        //buttons
        //settings buttons
        lv_obj_t *settings_buttons[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 2, (i+1), 2);
        }
        //labels
        //settings info  labels
        lv_obj_t *settings_labels[settings_cnt];
        for(uint8_t i=0; i<settings_cnt;i++){
            settings_labels[i] = lv_label_create(settings_label_conts[i]);
            lv_label_set_text_fmt(settings_labels[i], "%s", process_settings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0 , 0);
        }
        //settings btn labels
        lv_obj_t *settings_btn_labels[settings_cnt];
        for(uint8_t i=0;i<settings_cnt;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0 ,0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%.1f", mem_manager.getChgCurr());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.1f", mem_manager.getDischgCurr());
        lv_label_set_text_fmt(settings_btn_labels[2], "%.3f", mem_manager.getStoreVolt());
        lv_label_set_text_fmt(settings_btn_labels[3], "%u", mem_manager.getCutTemp());
    }

    void init_start_store_process_screen(lv_obj_t *cont){
        const char * process_values[6] = {"VOLTAGE", "CHG CURR", "BAT TEMP", "PROC TIME", "", "CHG CAPACITY"};
        init_process_data_labels(cont, label_process_data, label_start_process, &process_data_label_style, &basic_label_style, process_values);
    }

    void init_data_list_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {60, 60, 60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 15, 15, 15, 15, 15, 15, 15, 15, 15, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 5);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 10);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 10);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 1, 10);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 10);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);


        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);

        //cells data labels & containers;
        lv_obj_t *cells_voltage_conts[18];

        for(uint8_t i=0; i<18;i++){
            cells_voltage_conts[i] = lv_obj_create(cont);
            lv_obj_remove_style_all(cells_voltage_conts[i]);
            init_cont(cells_voltage_conts[i], &basic_label_style, (i/9)*2, 1+i%9, 2);
            label_cells_voltage[i] = lv_label_create(cells_voltage_conts[i]);
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u: 0.000", (i+1));
            lv_obj_align(label_cells_voltage[i], LV_ALIGN_LEFT_MID, 1, 0);
        }
    }

    void init_data_candles_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 20, 120, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 18);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons;
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 3, 4);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 14, 3, 4);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 4, 3, 4);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 3);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);

        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);

        //candles containers

        lv_obj_t *candle_conts[18];
        lv_obj_t *label_conts[18];
        for(uint8_t i=0; i<18;i++){
            //candles
            candle_conts[i] = lv_obj_create(cont);
            init_cont(candle_conts[i], &basic_label_style, i, 2);
            bars_cells_voltage[i] = lv_bar_create(candle_conts[i]);
            init_bar(bars_cells_voltage[i], &green_bar_style, &bar_style);

            label_conts[i] = lv_obj_create(cont);
            init_cont(label_conts[i], &basic_label_style, i, 1);
            label_cells_voltage[i] = lv_label_create(label_conts[i]);
            lv_label_set_text(label_cells_voltage[i], "0.000");
            lv_obj_center(label_cells_voltage[i]);

        }
    }

    void init_data_process_graph(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {60, 60, 60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 140, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        init_info_label(cont, label_info_cont, &info_cont_style, 5);
        //buttons
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 2);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 2);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 1, 2);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 2);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);
        
        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);
    }

    void init_settings_start_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {150, 150, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 135, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        init_info_label(cont, label_info_cont, &info_cont_style, 2);
        //buttons
        //settings type buttons
        lv_obj_t *battery_settings_button = lv_btn_create(cont);
        lv_obj_t *misc_settings_button = lv_btn_create(cont);
        //back button
        lv_obj_t *back_button = lv_btn_create(cont);
        init_button(battery_settings_button, &black_button_style, &black_button_pr_style, 0, 1);
        init_button(misc_settings_button, &black_button_style, &black_button_pr_style, 1, 1);
        init_button(back_button, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 2);
        lv_obj_add_event_cb(back_button, settings_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(battery_settings_button, battery_set_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(misc_settings_button, misc_set_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        //labels
        //button labels
        lv_obj_t *battery_settings_label = lv_label_create(battery_settings_button);
        lv_obj_t *misc_settings_label = lv_label_create(misc_settings_button);
        lv_obj_t *back_label = lv_label_create(back_button);
        lv_obj_set_style_text_font(battery_settings_label, &lv_font_montserrat_18, LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(misc_settings_label, &lv_font_montserrat_18, LV_STATE_DEFAULT);
        lv_label_set_text(battery_settings_label, "Battery\nSettings");
        lv_label_set_text(misc_settings_label, "Misc.\nSettings");
        lv_label_set_text(back_label, "BACK");
        lv_obj_center(battery_settings_label);
        lv_obj_center(misc_settings_label);
        lv_obj_center(back_label);
    }

    void init_settings_battery_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {150, 150, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 27, 27, 27, 27, 27, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 2);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //containers
        //settings name containers
        lv_obj_t *settings_conts[5];
        for(uint8_t i=0; i<5;i++){
            settings_conts[i] = lv_obj_create(cont);
            lv_obj_remove_style_all(settings_conts[i]);
            init_cont(settings_conts[i], &basic_label_style, 0, (i+1));
        }
        //buttons
        //back button
        lv_obj_t *back_button = lv_btn_create(cont);
        init_button(back_button, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 6);
        lv_obj_add_event_cb(back_button, battery_set_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        //settings button
        lv_obj_t *settings_buttons[5];
        for(uint8_t i=0; i<5;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 1, (i+1)); 
        }
        
        
        //labels
        //settings label
        static const char *settings_strings[5] = {"VOV:", "VUV:", "STORE VOLT:", "CUT VOLT:", "CUT TEMP:"};
        lv_obj_t *settings_labels[5], *settings_btn_labels[5];
        for(uint8_t i=0; i<5;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0, 0);
            settings_labels[i] = lv_label_create(settings_conts[i]);
            lv_label_set_text(settings_labels[i], settings_strings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0, 0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%.3f", mem_manager.getVOV());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.3f", mem_manager.getVUV());
        lv_label_set_text_fmt(settings_btn_labels[2], "%.3f", mem_manager.getStoreVolt());
        lv_label_set_text_fmt(settings_btn_labels[3], "%.3f", mem_manager.getCutVolt());
        lv_label_set_text_fmt(settings_btn_labels[4], "%u", mem_manager.getCutTemp());
        //back btn label
        lv_obj_t *back_label = lv_label_create(back_button);
        lv_label_set_text(back_label, "BACK");
        lv_obj_center(back_label);
    }
    void init_settings_misc_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {150, 150, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 25, 25, 25, 25, 25, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 2);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //containers
        //settings name containers
        lv_obj_t *settings_conts[6];
        for(uint8_t i=0; i<6;i++){
            settings_conts[i] = lv_obj_create(cont);
            lv_obj_remove_style_all(settings_conts[i]);
            init_cont(settings_conts[i], &basic_label_style, 0, (i+1));
        }
        //buttons
        //back button
        lv_obj_t *back_button = lv_btn_create(cont);
        init_button(back_button, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 7);
        lv_obj_add_event_cb(back_button, misc_set_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        //settings button
        lv_obj_t *settings_buttons[6];
        for(uint8_t i=0; i<6;i++){
            settings_buttons[i] = lv_btn_create(cont);
            init_button(settings_buttons[i], &black_button_style, &black_button_pr_style, 1, (i+1)); 
        }
        //labels
        //settings labels
        static const char *settings_strings[6] = {"ADBMS QNT:", "CHG CURR:", "DISCHG CURR:", "CHG VOLT:", "SAFETY TIMER:", "REST TIME:"};
        lv_obj_t *settings_labels[6], *settings_btn_labels[6];
        for(uint8_t i=0; i<6;i++){
            settings_btn_labels[i] = lv_label_create(settings_buttons[i]);
            lv_obj_align(settings_btn_labels[i], LV_ALIGN_RIGHT_MID, 0, 0);
            settings_labels[i] = lv_label_create(settings_conts[i]);
            lv_label_set_text(settings_labels[i], settings_strings[i]);
            lv_obj_align(settings_labels[i], LV_ALIGN_LEFT_MID, 0, 0);
        }
        lv_label_set_text_fmt(settings_btn_labels[0], "%u", mem_manager.getADBMSQuantity());
        lv_label_set_text_fmt(settings_btn_labels[1], "%.1f", mem_manager.getChgCurr());
        lv_label_set_text_fmt(settings_btn_labels[2], "%.1f", mem_manager.getDischgCurr());
        lv_label_set_text_fmt(settings_btn_labels[3], "%.3f", mem_manager.getChgVolt());
        lv_label_set_text_fmt(settings_btn_labels[4], "%u", mem_manager.getSafetyTimer());
        lv_label_set_text_fmt(settings_btn_labels[5], "%u", mem_manager.getRestTime());
        //back btn label
        lv_obj_t *back_label = lv_label_create(back_button);
        lv_label_set_text(back_label, "BACK");
        lv_obj_center(back_label);
    }

    void load_transition(){
        lv_scr_load(trans_scr);
        lv_obj_del(curr_scr);
    }
    void load_current(){
        lv_scr_load(curr_scr);
    }

    void adbms_start_scr_read(lv_timer_t *timer){
            adbms.cell_detect();
            tot_cell_qnt = adbms.get_tot_cell_qnt();
            sum_cell_volt = adbms.get_sum_cell_voltage();
            if(ina.device_found()){
                input_voltage = ina.read_voltage();
                temperature = (int)ina.read_temperature();
            }else{
                temperature = 0;
                input_voltage = 0;
            }
            max_power = input_voltage * MAX_CURRENT;
            lv_label_set_text_fmt(label_cell_qnt, "%u-s Battery Pack Detected", tot_cell_qnt);
            lv_label_set_text_fmt(label_cell_volt_temp,"vBAT:  %.2f v\ntBAT:         %d°c", sum_cell_volt, temperature); // to define Battery's Temp, taken from LM35, applied on 1818's GPIO
            lv_label_set_text_fmt(label_input_electricity, "INPUT:  %.1f v\ntCHG:     %d°c", input_voltage, temperature); // internal temp in charger, taken from INA
    }

    void adbms_data_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        cells_qnt = adbms.get_cell_qnt(current_adbms);
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        for(uint8_t i=0; i<cells_qnt;i++){
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u: %.3f", (i+1), adbms.convert_voltage(adbms(current_adbms, i) ));
        }
        for(uint8_t i=cells_qnt; i<18;i++){
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u 0.000", (i+1));
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
        
    }

    void adbms_data_candles_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        cells_qnt = adbms.get_cell_qnt(current_adbms);
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        for(uint8_t i=0; i<cells_qnt;i++){
            lv_label_set_text_fmt(label_cells_voltage[i],  "%.3f", adbms.convert_voltage(adbms(current_adbms, i)));
            lv_bar_set_value(bars_cells_voltage[i], adbms.voltage_percent(adbms.convert_voltage(adbms(current_adbms, i))), LV_ANIM_ON);
        }
        for(uint8_t i=cells_qnt; i<18;i++){
            lv_label_set_text(label_cells_voltage[i], "0.000");
            lv_bar_set_value(bars_cells_voltage[i], 0, LV_ANIM_OFF);
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
        
    }

    void adbms_data_graph_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
    }

    void adbms_process_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected   %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
    }
    void adbms_start_process_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected   %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);

    }

    void adbms_start_process_chg_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        float current;
        if(ina.device_found()){
            current = ina.read_current();
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
            current = 0.0;
        }
        float max_temp = 0.0, temp;
        adbms.start_gpio_adc_conversion();
        if(adbms.pladc_rdy()){
            adbms.read_aux_adc();
            for(uint8_t i=0;i<adbms.get_n();i++){
                for(uint8_t j=0;j<9;j++){
                    temp = lm35.convertTemperature(adbms.convert_voltage(adbms.get_aux(i, j))); 
                    if(max_temp<=temp){
                        max_temp = temp;
                    }
                }
            }
        }
        //assuming that period is 0.5 seconds
        capacity += (current * 5) /36;
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected   %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
        lv_label_set_text_fmt(label_process_data[0], "%.1fV", sum_cell_volt);
        lv_label_set_text_fmt(label_process_data[1], "%.1fA", current);
        lv_label_set_text_fmt(label_process_data[2], "%.1f°C", max_temp);
        lv_label_set_text_fmt(label_process_data[3], "%u mins", (safety_timer/60));
        lv_label_set_text_fmt(label_process_data[4], "%umV", dV_max);
        lv_label_set_text_fmt(label_process_data[5], "%.2fmAh", capacity);
    }
    void adbms_settings_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
    }
    void process_charge(lv_timer_t *timer){
        //read ADC temp and check if not above cut temp
        try{
            if(! (charge_state == ERROR_STATE || charge_state == FINISH_STATE)){
                adbms.start_gpio_adc_conversion();
                adbms.read_aux_adc();
                if(safety_timer == (mem_manager.getSafetyTimer()*60)){
                    throw std::out_of_range("Safety timer reset");
                }if(temperature >= MAX_CHG_TEMP){
                    throw std::out_of_range("Charger temperature above cut temp");
                }
                float cut_temp = mem_manager.getCutTemp();
                float max_chg_curr = mem_manager.getChgCurr();
                float min_volt = mem_manager.getVUV();
                float max_volt = mem_manager.getVOV();
                bool all_cells = charge_state == COV_STATE? true: false;
                bool finish = charge_state == FASTCHARGE_STATE? true: false;
                float maxV=0, minV=50;
                for(uint8_t i=0;i<adbms.get_n();i++){
                    for(uint8_t j=0;j<9;j++){
                        if(lm35.convertTemperature(adbms.convert_voltage(adbms.get_aux(i, j)))>=cut_temp){
                            throw std::out_of_range("Battery temperature above cut temp");
                        }
                    }
                    
                    if(!charge_state){
                        charge_state = FASTCHARGE_STATE;
                    }
                    
                    for(uint8_t j=0;j<adbms.get_cell_qnt(i);j++){
                        float volt = adbms.convert_voltage(adbms(i, j));
                        if(charge_state == FASTCHARGE_STATE &&  volt< min_volt){
                            charge_state = PRECHARGE_STATE;
                        }else if(volt > max_volt){
                            charge_state = COV_STATE;
                        }
                        if(all_cells && volt >= max_volt){
                            all_cells = false;
                        }
                        if(finish && (volt < (max_volt - 0.02))){
                            finish = false;
                        }
                        if(volt<=minV){
                            minV = volt;
                        }
                        if(volt>=maxV){
                            maxV = volt;
                        }
                    }
                }
                    if(all_cells){
                        charge_state = 1;
                    }
                    dV_max = (maxV - minV)*1000;
                    if(finish && dV_max <= mem_manager.getdVMin()){
                        charge_state = FINISH_STATE;
                    }
                    safety_timer += ((float)PROCESS_READ_PERIOD/999.0);
                    switch(charge_state){
                        case PRECHARGE_STATE:
                            //precharge state
                            pwmproc::set_v_out(mem_manager.getChgVolt());
                            pwmproc::set_i_out(IPRE);
                            lv_label_set_text(label_start_process, "PRE-CHARGE");
                            break;
                        case FASTCHARGE_STATE:
                            //fast charge state
                            lv_label_set_text(label_start_process, "FAST CHARGE");
                            pwmproc::set_v_out(mem_manager.getChgVolt());
                            pwmproc::set_i_out(current_curr);
                            if(current_curr < max_chg_curr*0.9){
                                current_curr += max_chg_curr*0.1;
                            }else if(current_curr >= max_chg_curr *0.9 && current_curr <max_chg_curr){
                                current_curr += max_chg_curr*0.01;
                            }
                            if(dV_max > mem_manager.getdVMin()){
                                //start ballancing
                                adbms.start_cell_ballancing(2);
                            }else{
                                adbms.start_cell_ballancing(0);
                            }
                        break;
                        case COV_STATE:
                            //cov state
                            lv_label_set_text(label_start_process, "COV STATE");
                            adbms.start_cell_ballancing(0);
                            pwmproc::set_v_out(mem_manager.getChgVolt());
                            pwmproc::set_i_out(current_curr);
                            if(current_curr >=0){
                                current_curr -= max_chg_curr*0.01;
                            }
                        break;
                        case FINISH_STATE:
                            lv_label_set_text(label_start_process, "FINISH");
                            pwmproc::set_v_out(0);
                            pwmproc::set_i_out(0);
                        break;
                        default:
                        break;
                    }
            }
        }catch(const std::exception &e){
            charge_state = ERROR_STATE;
            lv_label_set_text_fmt(label_start_process, "%s", e.what());
            pwmproc::set_v_out(0);
            pwmproc::set_i_out(0);
        }
    }
    void process_discharge(lv_timer_t *timer){
        try{
            if(! (charge_state == ERROR_STATE || charge_state == FINISH_STATE)){
                float cut_temp = mem_manager.getCutTemp();
                adbms.start_gpio_adc_conversion();
                adbms.read_aux_adc();
                if(temperature >= MAX_CHG_TEMP){
                    throw std::out_of_range("Charger temperature above cut temp");
                }
                charge_state = FINISH_STATE;
                for(uint8_t i=0;i<adbms.get_n();i++){
                    for(uint8_t j=0;j<9;j++){
                        if(lm35.convertTemperature(adbms.convert_voltage(adbms.get_aux(i, j)))>=cut_temp){
                            throw std::out_of_range("Battery temperature above cut temp");
                        }
                    }
                    for(uint8_t j=0;j<adbms.get_cell_qnt(i);j++){
                        
                        if(adbms.convert_voltage(adbms(i, j))>mem_manager.getCutVolt()){
                            charge_state = DISCHARGE_STATE;
                        }
                    }
                }
                switch(charge_state){
                    case DISCHARGE_STATE:
                    pwmproc::set_i_load(mem_manager.getDischgCurr());
                    break;
                    case FINISH_STATE:
                    lv_label_set_text(label_start_process, "FINISH");
                    pwmproc::set_i_load(0);
                    default:
                    break;
                }
            }
            
        }catch(const std::exception &e){
            charge_state = ERROR_STATE;
            lv_label_set_text_fmt(label_start_process, "%s", e.what());
            pwmproc::set_i_load(0);
        }
    }
    void process_store(lv_timer_t *timer){
        try{
            if(! (charge_state == ERROR_STATE || charge_state == FINISH_STATE)){
                float cut_temp = mem_manager.getCutTemp();
                if(temperature >= MAX_CHG_TEMP){
                    throw std::out_of_range("Charger temperature above cut temp");
                }
                adbms.start_gpio_adc_conversion();
                adbms.read_aux_adc();
                for(uint8_t i=0;i<adbms.get_n();i++){
                    for(uint8_t j=0;j<9;j++){
                        if(lm35.convertTemperature(adbms.convert_voltage(adbms.get_aux(i, j)))>=cut_temp){
                            throw std::out_of_range("Battery temperature above cut temp");
                        }
                    }
                    if(charge_state == STORE_START_STATE){
                        charge_state = FINISH_STATE;
                    }else if(charge_state == STORE_DSG_STATE){
                        charge_state = STORE_START_STATE;
                    }
                    for(uint8_t j=0;j<adbms.get_cell_qnt(i);j++){
                        float volt = adbms.convert_voltage(adbms(i, j));
                        if(volt <mem_manager.getVUV() || volt >mem_manager.getVOV()){
                            throw std::out_of_range("Voltage battery out of range");
                        }
                        if(volt>(mem_manager.getStoreVolt()+0.02)){
                                charge_state = STORE_DSG_STATE;
                        }
                        if(charge_state!=STORE_DSG_STATE && volt <(mem_manager.getStoreVolt()-0.02)){
                            charge_state = STORE_CHG_STATE;
                        }
                        if(charge_state == STORE_START_STATE){
                            if(volt<=mem_manager.getVUV() || volt >mem_manager.getStoreVolt()){
                                charge_state = STORE_DSG_STATE;
                            }
                        }else if(charge_state == STORE_CHG_STATE){
                            if(volt >= mem_manager.getStoreVolt()){
                                charge_state = STORE_START_STATE;
                            }
                        }
                    }
                }
                switch (charge_state)
                {
                case STORE_START_STATE:
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_out(0);
                    break;
                case STORE_DSG_STATE:
                    pwmproc::set_i_out(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_load(mem_manager.getDischgCurr());
                    break;
                case STORE_CHG_STATE:
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(mem_manager.getChgVolt());
                    pwmproc::set_i_out(mem_manager.getChgCurr());
                    break;
                case FINISH_STATE:
                    lv_label_set_text(label_start_process,"FINISH");
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_out(0);
                    break;
                default:
                    break;
                }
            }
        }catch(const std::exception &e){
            charge_state = ERROR_STATE;
            lv_label_set_text_fmt(label_start_process, "%s", e.what());
            pwmproc::set_i_load(0);
            pwmproc::set_v_out(0);
            pwmproc::set_i_out(0);
        }
    }
    void process_cycle(lv_timer_t *timer){
        try{
            if(! (charge_state == ERROR_STATE || charge_state == FINISH_STATE)){
                float cut_temp = mem_manager.getCutTemp();
                uint8_t next_state;
                if(temperature >= MAX_CHG_TEMP){
                    throw std::out_of_range("Charger temperature above cut temp");
                }
                adbms.start_gpio_adc_conversion();
                adbms.read_aux_adc();
                for(uint8_t i=0;i<adbms.get_n();i++){
                    for(uint8_t j=0;j<9;j++){
                        if(lm35.convertTemperature(adbms.convert_voltage(adbms.get_aux(i, j)))>=cut_temp){
                            throw std::out_of_range("Battery temperature above cut temp");
                        }
                    }
                    for(uint8_t j=0;j<adbms.get_cell_qnt(i);j++){
                        float volt = adbms.convert_voltage(adbms(i, j));
                        if(volt > mem_manager.getVOV() + 0.02 || volt < mem_manager.getVUV()){
                            throw std::out_of_range("Battery cell voltage out of range");
                        }
                        if(volt >= mem_manager.getVOV()){
                            if(charge_state == CYCLE_CHG_STATE){
                                charge_state = CYCLE_REST_STATE;
                                next_state = CYCLE_DSG_STATE;
                            }else{
                                charge_state = CYCLE_DSG_STATE;
                            }
                        }else if(volt <= mem_manager.getCutVolt()){
                            if(charge_state == CYCLE_DSG_STATE){
                                charge_state = CYCLE_REST_STATE;
                                next_state = CYCLE_CHG_STATE;
                            }else{
                                charge_state = CYCLE_CHG_STATE;
                            }
                        }
                    }
                }
                charge_state = charge_state == CYCLE_START_STATE? CYCLE_CHG_STATE: charge_state;
                switch (charge_state)
                {
                case CYCLE_START_STATE:
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_out(0);
                    break;
                case CYCLE_CHG_STATE:
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(mem_manager.getChgVolt());
                    pwmproc::set_i_out(mem_manager.getChgCurr());
                    break;
                case CYCLE_DSG_STATE:
                    pwmproc::set_i_out(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_load(mem_manager.getDischgCurr());
                    break;
                case CYCLE_REST_STATE:
                    safety_timer += ((float)PROCESS_READ_PERIOD/999.0);
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_out(0);
                    if(safety_timer == (mem_manager.getRestTime()*60)){
                        safety_timer = 0;
                        charge_state = next_state;
                    }
                    break;
                case FINISH_STATE:
                    lv_label_set_text(label_start_process, "FINISH");
                    pwmproc::set_i_load(0);
                    pwmproc::set_v_out(0);
                    pwmproc::set_i_out(0);
                    break;
                default:
                    break;
                }
            }
        }catch(const std::exception &e){
            charge_state = ERROR_STATE;
            lv_label_set_text_fmt(label_start_process, "%s", e.what());
            pwmproc::set_i_load(0);
            pwmproc::set_v_out(0);
            pwmproc::set_i_out(0);
        }
    }
    void init_adbms_task(){
        adbms_read = lv_timer_create(adbms_start_scr_read, ADBMS_READ_PERIOD, NULL);
    }
};