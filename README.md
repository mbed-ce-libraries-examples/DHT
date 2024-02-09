# DHT library for MbedCE

Library for interfacing DHT sensors (DHT11, DHT21, DHT22 and more - info in header file) under MbedCE. DHT sensor are popular because are cheap and is working on one data wire.

## How to start
1. Create a new project according to [MbedCE instructions](https://github.com/mbed-ce/mbed-os/wiki)
2. Add this as submodule to zour project via `git submodule add --depth 1 https://github.com/mbed-ce-libraries-examples/DHT DHT`
3. The top level `CMakeList.txt` (in root of your project) should be modified according to [this wiki page](https://github.com/mbed-ce/mbed-os/wiki/MbedOS-configuration#libraries-in-your-application)
4. Create your main.cpp file and copy & Paste example code below.
5. Build the project

## Example code
```
#include "mbed.h"
#include "DHT.h"

DHT sensor(D4, DHT11); // here fill your data pin and type of your sensor

int main()
{
    printf("MbedCE_lib_example_DHT\n");
    int error = 0;
    float h = 0.0f, c = 0.0f, f = 0.0f, k = 0.0f, dp = 0.0f, dpf = 0.0f;

    while(1) {
        error = sensor.readData();
        thread_sleep_for(2000); // according to datasheet
        if (0 == error) {
            c   = sensor.ReadTemperature(CELCIUS);
            f   = sensor.ReadTemperature(FARENHEIT);
            k   = sensor.ReadTemperature(KELVIN);
            h   = sensor.ReadHumidity();
            dp  = sensor.CalcdewPoint(c, h);
            dpf = sensor.CalcdewPointFast(c, h);
            printf("Temperature in Kelvin: %4.2f, Celcius: %4.2f, Farenheit %4.2f\n", k, c, f);
            printf("Humidity is %4.2f, Dewpoint: %4.2f, Dewpoint fast: %4.2f\n", h, dp, dpf);
        } else {
            printf("Error: %d\n", error);
        }
    }
}
```
## Description
![DHT22](https://github.com/mbed-ce-libraries-examples/DHT/assets/23274499/e8a91e1c-c52b-4f45-8490-071bc0db6c3d)

### Status:
This library was tested (02/2024) with Nucleo-F446RE, DHT22 sensor, VS-Code under Win11, GCC 12.3 and MbedCE library
