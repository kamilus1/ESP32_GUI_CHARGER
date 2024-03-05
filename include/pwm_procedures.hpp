#include <Arduino.h>
#include <math.h>


namespace pwmproc{
    static const uint8_t pwm_pins[3]{25, 26, 27};
    static float res;
    void init_pwm(int pwm_channel=0, int freq=10000, int resolution=12);
    void set_v_out(float voltage);
    void set_i_out(float curr);
    void set_i_load(float curr);

};