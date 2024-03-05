#include <Arduino.h>
#include <math.h>

class LM35{
    private:
        uint8_t pin;
        uint8_t resolution;
         uint32_t max_adc_val;
    protected:
        uint16_t readADC();
    public:
        LM35();
        LM35(uint8_t adcPin);
        float getTemperature();
        void setResolution(uint8_t res);
        float convertTemperature(uint32_t adc);
        float convertTemperature(float voltage);
        
}; 