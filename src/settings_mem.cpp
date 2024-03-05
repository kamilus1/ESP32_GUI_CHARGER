#include "settings_mem.hpp"


const std::map<std::string, std::pair<uint8_t, uint8_t>> MemManager::memory_map = {
    {"FIRST", {0, 1}},
    {"ADBMS_QNT", {1, 1}},
    {"VOV", {2, 4}},
    {"VUV", {6, 4}}, 
    {"CHG_CURR", {10, 4}}, 
    {"DISCHG_CURR", {14, 4}},
    {"CHG_VOLT", {18, 4}},
    {"STORE_VOLT", {22, 4}},
    {"CUT_VOLT", {26, 4}},
    {"CUT_TEMP", {30, 1}},
    {"SAFETY_TIMER", {31, 2}},
    {"REST_TIME", {33, 2}}, 
    {"DV_MIN", {35, 2}}
};

const uint16_t MemManager::mem_size = 64;


MemManager::MemManager(){
    values_read = false;
    EEPROM.begin(this->mem_size);
}
void MemManager::updateValues(){
    values_read = false;
    this->getADBMSQuantity();
    this->getVOV();
    this->getVUV();
    this->getChgCurr();
    this->getDischgCurr();
    this->getChgVolt();
    this->getStoreVolt();
    this->getCutVolt();
    this->getCutTemp();
    this->getSafetyTimer();
    this->getRestTime();
    this->getdVMin();
    values_read = true;
}
bool MemManager::firstUse(){
    return EEPROM.read(std::get<0>(this->memory_map.at("FIRST"))) != 7;
}

void MemManager::read(uint8_t addr, uint8_t *dst, uint16_t len){
    for(uint16_t i=0; i<len;i++){
        dst[i] = EEPROM.read((addr + i));
    }
}

void MemManager::write(uint8_t addr, uint8_t *data, uint16_t len){
    for(uint16_t i=0;i<len;i++){
        EEPROM.write((addr + i), data[i]);
    }
}

void MemManager::clear(){
    uint8_t clear_data[this->mem_size] = {0};
    this->write(0, clear_data, this->mem_size);
}

uint8_t MemManager::getADBMSQuantity(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("ADBMS_QNT")), &this->adbms_quantity, std::get<1>(this->memory_map.at("ADBMS_QNT")));
    }
    return this->adbms_quantity;
}

float MemManager::getVOV(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("VOV")), this->vov.value_bytes, std::get<1>(this->memory_map.at("VOV")));
    }
    return this->vov.value;
}
float MemManager::getVUV(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("VUV")), this->vuv.value_bytes, std::get<1>(this->memory_map.at("VUV")));
    }
    return this->vuv.value;
}
float MemManager::getChgCurr(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("CHG_CURR")), this->chg_curr.value_bytes, std::get<1>(this->memory_map.at("CHG_CURR")));
    }
    return this->chg_curr.value;
}
float MemManager::getDischgCurr(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("DISCHG_CURR")), this->dischg_curr.value_bytes, std::get<1>(this->memory_map.at("DISCHG_CURR")));
    }
    return this->dischg_curr.value;
}

float MemManager::getChgVolt(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("CHG_VOLT")), this->chg_volt.value_bytes, std::get<1>(this->memory_map.at("CHG_VOLT")));
    }
    return this->chg_volt.value;
}

float MemManager::getStoreVolt(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("STORE_VOLT")), this->store_volt.value_bytes, std::get<1>(this->memory_map.at("STORE_VOLT")));
    }
    return this->store_volt.value;
}
float MemManager::getCutVolt(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("CUT_VOLT")), this->cut_volt.value_bytes, std::get<1>(this->memory_map.at("CUT_VOLT")));
    }
    return this->cut_volt.value;
}
uint8_t MemManager::getCutTemp(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("CUT_TEMP")), &this->cut_temp, std::get<1>(this->memory_map.at("CUT_TEMP")));
    }
    return this->cut_temp;
}
uint16_t MemManager::getSafetyTimer(){
    if(!this->values_read){
    this->read(std::get<0>(this->memory_map.at("SAFETY_TIMER")), this->safety_timer.value_bytes, std::get<1>(this->memory_map.at("SAFETY_TIMER")));
    }
    return this->safety_timer.value;
}

uint16_t MemManager::getRestTime(){
    if(!this->values_read){
        this->read(std::get<0>(this->memory_map.at("REST_TIME")), this->rest_time.value_bytes, std::get<1>(this->memory_map.at("REST_TIME")));
    }
    return this->rest_time.value;
}
uint16_t MemManager::getdVMin(){
    if(!this->values_read){
        this->read(std::get<0>(this->memory_map.at("DV_MIN")), this->dV_min.value_bytes, std::get<1>(this->memory_map.at("DV_MIN")));
    }
    return this->dV_min.value;
}

void MemManager::setADBMSQuantity(uint8_t data){
    this->adbms_quantity = data;
    this->write(std::get<0>(this->memory_map.at("ADBMS_QNT")), &this->adbms_quantity, std::get<1>(this->memory_map.at("ADBMS_QNT")));
}

void MemManager::setVOV(float data){
    this->vov.value = data;
    this->write(std::get<0>(this->memory_map.at("VOV")), this->vov.value_bytes, std::get<1>(this->memory_map.at("VOV")));
}
void MemManager::setVUV(float data){
    this->vuv.value = data;
    this->write(std::get<0>(this->memory_map.at("VUV")), this->vuv.value_bytes, std::get<1>(this->memory_map.at("VUV")));
}

void MemManager::setChgCurr(float curr){
    this->chg_curr.value = curr;
    this->write(std::get<0>(this->memory_map.at("CHG_CURR")), this->chg_curr.value_bytes, std::get<1>(this->memory_map.at("CHG_CURR")));
}

void MemManager::setDischgCurr(float curr){
    this->dischg_curr.value = curr;
    this->write(std::get<0>(this->memory_map.at("DISCHG_CURR")), this->dischg_curr.value_bytes, std::get<1>(this->memory_map.at("DISCHG_CURR")));
}

void MemManager::setChgVolt(float voltage){
    this->chg_volt.value = voltage;
    this->write(std::get<0>(this->memory_map.at("CHG_VOLT")), this->chg_volt.value_bytes, std::get<1>(this->memory_map.at("CHG_VOLT")));
}

void MemManager::setStoreVolt(float voltage){
    this->store_volt.value = voltage;
    this->write(std::get<0>(this->memory_map.at("STORE_VOLT")), this->store_volt.value_bytes, std::get<1>(this->memory_map.at("STORE_VOLT")));
}

void MemManager::setCutVolt(float voltage){
    this->cut_volt.value = voltage;
    this->write(std::get<0>(this->memory_map.at("CUT_VOLT")), this->cut_volt.value_bytes, std::get<1>(this->memory_map.at("CUT_VOLT")));
}

void MemManager::setCutTemp(uint8_t temp){
    this->cut_temp = temp;
    this->write(std::get<0>(this->memory_map.at("CUT_TEMP")), &this->cut_temp, std::get<1>(this->memory_map.at("CUT_TEMP")));
}

void MemManager::setSafetyTimer(uint16_t timestamp){
    this->safety_timer.value = timestamp;
    this->write(std::get<0>(this->memory_map.at("SAFETY_TIMER")), this->safety_timer.value_bytes, std::get<1>(this->memory_map.at("SAFETY_TIMER")));
}

void MemManager::setRestTime(uint16_t timestamp){
    this->rest_time.value = timestamp;
    this->write(std::get<0>(this->memory_map.at("REST_TIME")), this->rest_time.value_bytes, std::get<1>(this->memory_map.at("REST_TIME")));
}
void MemManager::setdVMin(uint16_t dV){
    this->dV_min.value = dV;
    this->write(std::get<0>(this->memory_map.at("DV_MIN")), this->dV_min.value_bytes, std::get<1>(this->memory_map.at("DV_MIN")));
}
void MemManager::setDefaultSettings(){
    values_read = true;
    uint8_t val = 7;
    this->write(std::get<0>(this->memory_map.at("FIRST")), &val, std::get<1>(this->memory_map.at("FIRST")));
    this->setADBMSQuantity(1);
    this->setVOV(4.21);
    this->setVUV(1.5);
    this->setChgCurr(10.0);
    this->setDischgCurr(2.5);
    this->setChgVolt(25.0);
    this->setStoreVolt(4.0);
    this->setCutVolt(2.55);
    this->setCutTemp(45);
    this->setSafetyTimer(240);
    this->setRestTime(5);
    this->setdVMin(20);
}