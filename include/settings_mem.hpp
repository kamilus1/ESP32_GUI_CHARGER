#include <EEPROM.h>
#include <map>


typedef union{
    float value;
    uint8_t value_bytes[4];
} mem_float;

typedef union{
    uint16_t value;
    uint8_t value_bytes[2];
}mem_uint16;
typedef union{
    int value;
    uint8_t value_bytes[4];
} mem_int;

class MemManager{
    static const std::map<std::string, std::pair<uint8_t, uint8_t>>memory_map; 
    static const uint16_t mem_size;
    uint8_t adbms_quantity, cut_temp;
    mem_float vov, vuv, chg_curr, dischg_curr, chg_volt;
    mem_float store_volt, cut_volt;
    mem_uint16 safety_timer, rest_time, dV_min;
    bool values_read;
    protected:
        void read(uint8_t addr, uint8_t *dst, uint16_t len);
        void write(uint8_t addr, uint8_t *data, uint16_t len);
    public:
        MemManager();
        void updateValues();
        bool firstUse();
        void clear(); 
        uint8_t getADBMSQuantity();
        float getVOV();
        float getVUV();
        float getChgCurr();
        float getDischgCurr();
        float getChgVolt();
        float getStoreVolt();
        float getCutVolt();
        uint8_t getCutTemp();
        uint16_t getSafetyTimer();
        uint16_t getRestTime();
        uint16_t getdVMin();
        void setADBMSQuantity(uint8_t data);
        void setVOV(float data);
        void setVUV(float data);
        void setChgCurr(float curr);
        void setDischgCurr(float curr);
        void setChgVolt(float voltage);
        void setStoreVolt(float voltage);
        void setCutVolt(float voltage);
        void setCutTemp(uint8_t temp);
        void setSafetyTimer(uint16_t timestamp);
        void setRestTime(uint16_t timestamp);
        void setdVMin(uint16_t dV);
        void setDefaultSettings();

};