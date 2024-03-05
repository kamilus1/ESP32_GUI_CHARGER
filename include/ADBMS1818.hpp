#include <Arduino.h>
#include <SPI.h>
#include <map>
#include <stdlib.h>
#include <vector>

#define DEFAULT_ADC_7kHz 2

#define DISC_PERM 1
#define DISC_NPERM 0

const uint16_t crc15Table[256] {0x0,0xc599, 0xceab, 0xb32, 0xd8cf, 0x1d56, 0x1664, 0xd3fd, 0xf407, 0x319e, 0x3aac,  // precomputed CRC15 Table
                                0xff35, 0x2cc8, 0xe951, 0xe263, 0x27fa, 0xad97, 0x680e, 0x633c, 0xa6a5, 0x7558, 0xb0c1,
                                0xbbf3, 0x7e6a, 0x5990, 0x9c09, 0x973b, 0x52a2, 0x815f, 0x44c6, 0x4ff4, 0x8a6d, 0x5b2e,
                                0x9eb7, 0x9585, 0x501c, 0x83e1, 0x4678, 0x4d4a, 0x88d3, 0xaf29, 0x6ab0, 0x6182, 0xa41b,
                                0x77e6, 0xb27f, 0xb94d, 0x7cd4, 0xf6b9, 0x3320, 0x3812, 0xfd8b, 0x2e76, 0xebef, 0xe0dd,
                                0x2544, 0x2be, 0xc727, 0xcc15, 0x98c, 0xda71, 0x1fe8, 0x14da, 0xd143, 0xf3c5, 0x365c,
                                0x3d6e, 0xf8f7,0x2b0a, 0xee93, 0xe5a1, 0x2038, 0x7c2, 0xc25b, 0xc969, 0xcf0, 0xdf0d,
                                0x1a94, 0x11a6, 0xd43f, 0x5e52, 0x9bcb, 0x90f9, 0x5560, 0x869d, 0x4304, 0x4836, 0x8daf,
                                0xaa55, 0x6fcc, 0x64fe, 0xa167, 0x729a, 0xb703, 0xbc31, 0x79a8, 0xa8eb, 0x6d72, 0x6640,
                                0xa3d9, 0x7024, 0xb5bd, 0xbe8f, 0x7b16, 0x5cec, 0x9975, 0x9247, 0x57de, 0x8423, 0x41ba,
                                0x4a88, 0x8f11, 0x57c, 0xc0e5, 0xcbd7, 0xe4e, 0xddb3, 0x182a, 0x1318, 0xd681, 0xf17b,
                                0x34e2, 0x3fd0, 0xfa49, 0x29b4, 0xec2d, 0xe71f, 0x2286, 0xa213, 0x678a, 0x6cb8, 0xa921,
                                0x7adc, 0xbf45, 0xb477, 0x71ee, 0x5614, 0x938d, 0x98bf, 0x5d26, 0x8edb, 0x4b42, 0x4070,
                                0x85e9, 0xf84, 0xca1d, 0xc12f, 0x4b6, 0xd74b, 0x12d2, 0x19e0, 0xdc79, 0xfb83, 0x3e1a, 0x3528,
                                0xf0b1, 0x234c, 0xe6d5, 0xede7, 0x287e, 0xf93d, 0x3ca4, 0x3796, 0xf20f, 0x21f2, 0xe46b, 0xef59,
                                0x2ac0, 0xd3a, 0xc8a3, 0xc391, 0x608, 0xd5f5, 0x106c, 0x1b5e, 0xdec7, 0x54aa, 0x9133, 0x9a01,
                                0x5f98, 0x8c65, 0x49fc, 0x42ce, 0x8757, 0xa0ad, 0x6534, 0x6e06, 0xab9f, 0x7862, 0xbdfb, 0xb6c9,
                                0x7350, 0x51d6, 0x944f, 0x9f7d, 0x5ae4, 0x8919, 0x4c80, 0x47b2, 0x822b, 0xa5d1, 0x6048, 0x6b7a,
                                0xaee3, 0x7d1e, 0xb887, 0xb3b5, 0x762c, 0xfc41, 0x39d8, 0x32ea, 0xf773, 0x248e, 0xe117, 0xea25,
                                0x2fbc, 0x846, 0xcddf, 0xc6ed, 0x374, 0xd089, 0x1510, 0x1e22, 0xdbbb, 0xaf8, 0xcf61, 0xc453,
                                0x1ca, 0xd237, 0x17ae, 0x1c9c, 0xd905, 0xfeff, 0x3b66, 0x3054, 0xf5cd, 0x2630, 0xe3a9, 0xe89b,
                                0x2d02, 0xa76f, 0x62f6, 0x69c4, 0xac5d, 0x7fa0, 0xba39, 0xb10b, 0x7492, 0x5368, 0x96f1, 0x9dc3,
                                0x585a, 0x8ba7, 0x4e3e, 0x450c, 0x8095
                               };


//use default configuration for now.
class ADBMS1818{
    protected:
   
        SPIClass *spi;
        SPISettings *spi_settings;
        static std::map<std::string, uint16_t> commands;
        static std::map<std::string, uint8_t> commands_bits;
        static void u16_to_u8(uint16_t x, uint8_t *y);
        uint32_t f;
        uint16_t rbuff_size, wbuff_size;
        uint8_t cs, n, byte_reg;
        uint8_t *read_buff;
        uint8_t *write_buff;
        uint16_t **cells_value; 
        uint16_t **aux_value;
        uint8_t pec[2];
        
        //configuration bits for write commands
        uint8_t *sctl, *pwm;
        bool adcopt, refon, dtmen, mute, fdrf;
        unsigned long pladc_timeout;
        uint8_t dcto, ps;
        uint16_t vuv, vov, gpiox;
        uint32_t *dcc;
        void pec_15(uint8_t *tab, uint8_t len);
        void poll_command(uint8_t command[2]);
        void write_command(uint8_t command[2], uint8_t*data);
        bool read_command(uint8_t command[2], uint8_t *data);
        void init();
        uint16_t config_md_bits(uint16_t command);
        uint16_t config_ch_bits(uint16_t command, std::string key="CH");
        uint16_t config_st_bits(uint16_t command);
        uint16_t config_pup_bit(uint16_t command);
        uint16_t config_dcp_bit(uint16_t command);
        uint16_t config_bit(uint16_t command, uint8_t pos, bool bit);
        
    public:
        
        explicit ADBMS1818(uint8_t port,  uint8_t csPin, uint32_t freq= 1000000, uint8_t br = 6);
        explicit ADBMS1818(int8_t spi_pins[4], uint32_t freq= 1000000, uint8_t br = 6);
        explicit ADBMS1818(uint8_t csPin,  uint32_t freq= 1000000, uint8_t br = 6);
        //couple setters
        void set_adbms_qnt(uint8_t n);
        void begin(uint8_t n=1);
        void wake_up(uint32_t dur=300);
        void wake_up_idle();
        void set_config_reg_a();
        void set_config_reg_b();
        void set_dcc(uint8_t n=0, uint32_t val = 0);
        void set_bits(std::string bit_key, uint8_t bit_value);
        void start_cv_adc_conversion(); //for default mode with 7khz  freq it takes about 2.3 ms for all cells conversion. 
        void start_open_wire_conversion();
        void start_self_test_conversion();
        void start_overlap_conversion(); 
        void start_gpio_adc_conversion();
        void start_gpio_adc_conversion_dr();//gpio conversion with digital redundancy. dr == digital redundancy
        void start_gpio_open_wire_conversion();
        void start_self_test_gpio_conversion();
        void start_status_adc_conversion();
        void start_status_adc_dr_conversion();
        void start_self_test_status_conversion();
        void start_cv_gpio12_conversion();
        void start_cv_sc_conversion();
        bool pladc_rdy();
        void set_sct_value(uint8_t *values);
        void set_sct_pin_value(uint8_t value, uint8_t pin, uint8_t n1=0);//n is an index (starting from 0) of ADBMS1818 device connected in daisy chain
        void set_pwm_value(uint8_t *values);                            //pin is an index of 1-18 cells starting from 1
        void set_pwm_pin_value(uint8_t value, uint8_t pin, uint8_t n1=0);
        void write_sct_reg();
        void write_pwm_reg();
        void read_cv_adc();
        void read_aux_adc();
        float convert_voltage(uint16_t voltage);
        uint8_t get_n();
        uint16_t get_aux(uint8_t x, uint8_t y);
        const uint16_t &operator () (uint8_t x, uint8_t y) const{
            if(x < this->n && y < 18){
                return this->cells_value[x][y];
            }else{
                return 0;
            }
        }
};