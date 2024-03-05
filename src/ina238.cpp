#include "ina238.hpp"
std::map<std::string, uint8_t> ina238::registers = {
    {"CONFIG_1", 0x00},
    {"ADCCONFIG_2", 0x01},
    {"CURRLSBCALC_3", 0x02},
    {"VSHUNT", 0x04},
    {"VBUS", 0x05},
    {"DIETEMP", 0x06},
    {"CURRENT", 0x07},
    {"POWER", 0x08},
    {"DIAG_ALERT", 0x0b},
    {"SOVL", 0x0c},
    {"SUVL", 0x0d},
    {"BOVL", 0x0e},
    {"BUVL", 0x0f},
    {"TEMP_LIMIT", 0x10},
    {"PWR_LIMIT", 0x11},
    {"MAFUCATURER_ID", 0x3e},
    {"DEVICE_ID", 0x3f}
};
ina238::ina238(uint16_t addr, float r_shunt, uint8_t sda, uint8_t scl, uint32_t freq,  uint8_t i2c_bus): ina_addr(addr), r(r_shunt){
    i2c_wire = new TwoWire(i2c_bus);
    i2c_wire->begin(sda, scl, freq);

}

ina238::ina238(uint16_t addr,  TwoWire *two_wire, float r_shunt): ina_addr(addr), r(r_shunt){
    i2c_wire = two_wire;

}

bool ina238::device_found(){
    i2c_wire->beginTransmission(ina_addr);
    uint8_t error;
    error = i2c_wire->endTransmission();
    return error == 0;
}


void ina238::write_command(uint8_t *data, uint8_t qnt){
    i2c_wire->beginTransmission(this->ina_addr);
    for(uint8_t i=0;i<qnt;i++){
        i2c_wire->write(data[i]);
    }
    i2c_wire->endTransmission();
}

void ina238::read_command(uint8_t *data, uint8_t wqnt, uint8_t rqnt){
    this->write_command(data, wqnt);
    i2c_wire->requestFrom(this->ina_addr, rqnt);
    for(uint8_t i=0;i<rqnt;i++){
        while(!i2c_wire->available());
        this->read_data[i] = i2c_wire->read();
    }
}

void ina238::write_config1(uint8_t rst, uint8_t convdly, uint8_t adcrange){
    for(uint8_t i=0;i<4;i++){
        this->write_data[i] = 0;
    }
    this->adc_range = (adcrange == 1) ? true: false;
    this->write_data[0] = this->registers["CONFIG_1"];
    this->write_data[1] = (rst << 7); 
    this->write_data[1] |= (convdly >> 2);
    this->write_data[2] = (convdly << 6);
    this->write_data[2] |= adcrange << 3;
    this->write_command(this->write_data, 3);
}
void ina238::write_adc_config2(uint8_t mode, uint8_t vcbust, uint8_t vshct, uint8_t vtct, uint8_t avg){
for(uint8_t i=0;i<4;i++){
        this->write_data[i] = 0;
    }
    this->write_data[0] = this->registers["ADCCONFIG_2"];
    this->write_data[1] = (mode << 4);
    this->write_data[1] |= (vcbust << 1);
    this->write_data[1] |= (vshct >> 2);
    this->write_data[2] = (vshct << 6);
    this->write_data[2] |= (vtct << 2);
    this->write_data[2] |= avg;
    this->write_command(this->write_data, 3);
}

void ina238::write_currlsbcalc_3(uint16_t currlsb){
    for(uint8_t i=0;i<4;i++){
        this->write_data[i] = 0;
    }
    this->write_data[0] = this->registers["CURRLSBCALC_3"];
    this->curr_lsb_calc = currlsb;
    this->curr_lsb_calc /= (pow(2, 15));
    float shunt_cal = 819.2 * pow(10, 6) * this->curr_lsb_calc * this->r;
    currlsb = (uint16_t) shunt_cal;
    this->write_data[1] = currlsb >> 8;
    this->write_data[2] = 0x00ff & currlsb;
    this->write_command(this->write_data, 3);
}

float ina238::read_current(){
    this->write_data[0] = this->registers["CURRENT"];
    this->read_command(this->write_data, 1, 2);
    uint16_t curr = this->read_data[0];
    curr <<= 8;
    curr |= this->read_data[1];
    float curr_lsb = this->curr_lsb_calc;
    curr_lsb = this->adc_range == true? curr_lsb*4: curr_lsb;
    return ((float)curr) * curr_lsb;
}

float ina238::read_temperature(){
    this->write_data[0] = this->registers["DIETEMP"];
    this->read_command(this->write_data, 1, 2);
    uint16_t temp_buffer = this->read_data[0];
    temp_buffer <<= 4;
    temp_buffer |= (this->read_data[1] >> 4);
    float temp = 0.125;
    temp *= temp_buffer;
    return temp;
}

float ina238::read_voltage(){
    this->write_data[0] = this->registers["VBUS"];
    this->read_command(this->write_data, 1, 2);
    uint16_t volt_buffer = this->read_data[0];
    volt_buffer <<= 8;
    volt_buffer |= this->read_data[1];
    float voltage = 0.003125;
    voltage *= volt_buffer;
    return voltage;
}

void ina238::begin(){
    if(this->device_found()){
        this->write_config1();
        this->write_adc_config2();
        this->write_currlsbcalc_3();
    }
}