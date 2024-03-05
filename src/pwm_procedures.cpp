#include "pwm_procedures.hpp"


namespace pwmproc{
    void init_pwm(int pwm_channel, int freq, int resolution){
        ledcSetup(pwm_channel, freq, resolution);
        for(uint8_t i=0; i<3;i++){
            ledcAttachPin(pwm_pins[i], pwm_channel);
        }
        res = pow(2, resolution);
    }

    void set_v_out(float voltage){
        if(voltage <= 95){
            float vset = ((voltage - 95.0) * -1)/47;
            int duty_cycle = res * (vset / 3.3);
            ledcWrite(pwm_pins[0], duty_cycle);
        }
    }
    void set_i_out(float curr){
        if(curr <= 26){
            float iset = ((curr - 26.0) * -1)*0.12;
            int duty_cycle = res * (iset/3.3);
            ledcWrite(pwm_pins[1], duty_cycle);
        }
    }
    void set_i_load(float curr){
        if(curr <= 21.5){
            float lset = curr / 6.6;
            int duty_cycle = res * (lset / 3.3);
            ledcWrite(pwm_pins[2], duty_cycle);
        }
    }

};