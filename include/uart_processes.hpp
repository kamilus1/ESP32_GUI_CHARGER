#include "driver/uart.h"
#include "gui_screens.hpp"
#include <map>
#include <string.h>
#include <functional>

namespace huart{
    static lv_timer_t *transmit_task;
    static bool is_transmiting;
    static std::map<char*, std::function<void()>> commands_list;

    void init_tasks();
    void start_transmitting();
    void start_store_process();
    void start_ship_process();
    void start_hardware_test();
    void stop_transmitting();
    void stop_process();
    void stop_hardware_test();
    static void transmit_data(lv_timer_t *timer);
    void interpret_command(char *command);
};