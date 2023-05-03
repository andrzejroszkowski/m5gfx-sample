/* Blink C++ Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <cstdlib>
#include <thread>
#include "esp_log.h"
#include "gpio_cxx.hpp"
#include "M5Unified.hpp"

using namespace idf;
using namespace std;

extern "C" void app_main(void)
{
    try
    {
        GPIOInput gpio(GPIONum(26));
        gpio.set_pull_mode(GPIOPullMode::PULLUP());

        auto cfg = M5.config();
        M5.begin(cfg);
        M5.Lcd.setRotation(3);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0, 4);
        M5.Lcd.println("PIR TEST");

        while (true)
        {
            auto level = gpio.get_level();
            M5.Lcd.setCursor(110, 55, 6);
            M5.Lcd.println(level == GPIOLevel::HIGH ? "1":"0");
        }
    }
    catch (GPIOException &e)
    {
        printf("GPIO exception occurred: %s\n", esp_err_to_name(e.error));
        printf("stopping.\n");
    }
}
