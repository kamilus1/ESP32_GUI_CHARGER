#include "ADBMS1818Class.hpp"

const float ADBMS1818Class::vcell_min_exist = 1000.0;
const float ADBMS1818Class::vcell_max = 4250.0;

void ADBMS1818Class::start_all_conversions(){
    this->start_cv_adc_conversion();
    while(!this->pladc_rdy());
    this->start_open_wire_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_conversion();
    while(!this->pladc_rdy());
    this->start_overlap_conversion();
    while(!this->pladc_rdy());
    this->start_gpio_adc_conversion();
    while(!this->pladc_rdy());
    this->start_gpio_adc_conversion_dr();
    while(!this->pladc_rdy());
    this->start_gpio_open_wire_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_gpio_conversion();
    while(!this->pladc_rdy());
    this->start_status_adc_conversion();
    while(!this->pladc_rdy());
    this->start_status_adc_dr_conversion();
    while(!this->pladc_rdy());
    this->start_self_test_conversion();
    while(!this->pladc_rdy());
    this->start_cv_gpio12_conversion();
    while(!this->pladc_rdy());
    this->start_cv_sc_conversion();
    while(!this->pladc_rdy());
}

bool ADBMS1818Class::cell_detect(){
    this->adbms_status = COMM_ACTIVE;
    for(uint8_t i=0; i<this->n;i++){
        this->cell_qnt[i]  = 0;
    }
    this->tot_cell_qnt = 0;
    this->start_cv_sc_conversion();
    this->read_cv_adc();
    for(uint8_t i=0; i<this->n; i++){
        uint8_t j = 0;
        while(j<18&&(this->convert_voltage(this->cells_value[i][j])*1000.0)>=this->vcell_min_exist){
            j++;
        }
        this->cell_qnt[i] = j;
        this->tot_cell_qnt += j;
        while(j<18){
            if(this->convert_voltage(this->cells_value[i][j])*1000.0 >= this->vcell_min_exist){
                this->adbms_status = COMM_STOPPED;
                return false;
            }
            j++;
        }
    }
    return true;
}

uint32_t ADBMS1818Class::get_tot_cell_qnt(){
    return this->tot_cell_qnt;
}

uint8_t ADBMS1818Class::get_cell_qnt(uint8_t id){
    return (id >= this->n)? this->cell_qnt[0]: this->cell_qnt[id];
}

uint8_t ADBMS1818Class::get_status(){
    return this->adbms_status;
}

float ADBMS1818Class::get_sum_cell_voltage(){
    this->start_cv_sc_conversion();
    if(this->pladc_rdy()){
        
        this->read_cv_adc();
        float voltage_sum = 0;
        for(uint8_t i=0; i<this->n; i++){
            for(uint8_t j=0; j<this->cell_qnt[i]; j++){
                voltage_sum += this->convert_voltage(this->cells_value[i][j]);
            }
        }
        return voltage_sum;
    }else{
        return 0;
    }
}

int ADBMS1818Class::voltage_percent(float voltage_value){
    voltage_value -= this->vcell_min_exist;
    if(voltage_value <= 0){
        return 0;
    }
    voltage_value /= (this->vcell_max - this->vcell_min_exist);
    voltage_value *= 100;
    if(voltage_value >= 100){
        return 100;
    }
    return (int) voltage_value;
}

void ADBMS1818Class::start_cell_ballancing(uint8_t value){
    this->cell_detect(); 
    for(uint8_t i=0; i<this->n;i++){
        for(uint8_t j=0; j<this->cell_qnt[i]; j++){
            this->set_sct_pin_value(value, (j+1), i);
        }
        for(uint8_t j=this->cell_qnt[i]; j<18; j++){
            this->set_sct_pin_value(0, (j+1), i);
        }
    }
    this->write_sct_reg();
}