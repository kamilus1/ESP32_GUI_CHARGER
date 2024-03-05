#include "lm35.hpp"


LM35::LM35(){
    this->pin = 2;
}

LM35::LM35(uint8_t adc_pin){
    this->pin = adc_pin;
    
}

uint16_t LM35::readADC(){
    return analogRead(this->pin);
}
float LM35::getTemperature(){
    return this->convertTemperature((uint32_t)this->readADC());
}
float LM35::convertTemperature(uint32_t adc){
    float temp = (float)adc;
    temp /= max_adc_val;
    return temp * 150;
}
float LM35::convertTemperature(float voltage){
    return voltage * 100;
}

void LM35::setResolution(uint8_t res){
    resolution = res;
    max_adc_val = pow(2, res);
}