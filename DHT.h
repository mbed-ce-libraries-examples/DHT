/*
 *  DHT Library for  Digital-output Humidity and Temperature sensors
 *
 *  Works with DHT11, DHT22
 *             SEN11301P,  Grove - Temperature&Humidity Sensor     (Seeed Studio)
 *             SEN51035P,  Grove - Temperature&Humidity Sensor Pro (Seeed Studio)
 *             AM2302   ,  temperature-humidity sensor
 *             HM2303   ,  Digital-output humidity and temperature sensor
 *
 *  Copyright (C)   2014 - Wim De Roeve -   based on DHT22 sensor library by HO WING KIT
 *                                          Arduino DHT11 library
 *                                          (https://os.mbed.com/teams/components/code/DHT/)
 *                  2024 - Jan Kamidra  -   convert for MbedCE
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
/*
 *  Example:
 * @code
 * #include "mbed.h"
 * #include "DHT.h"
 * 
 * DHT sensor(D4, DHT11);
 * 
 * int main()
 * {
 *     printf("MbedCE_lib_example_DHT\n");
 *     int error = 0;
 *     float h = 0.0f, c = 0.0f, f = 0.0f, k = 0.0f, dp = 0.0f, dpf = 0.0f;
 *
 *     while(1) {
 *         error = sensor.readData();
 *         thread_sleep_for(2000); // according to datasheet 
 *         if (0 == error) {
 *             c   = sensor.ReadTemperature(CELCIUS);
 *             f   = sensor.ReadTemperature(FARENHEIT);
 *             k   = sensor.ReadTemperature(KELVIN);
 *             h   = sensor.ReadHumidity();
 *             dp  = sensor.CalcdewPoint(c, h);
 *             dpf = sensor.CalcdewPointFast(c, h);
 *             printf("Temperature in Kelvin: %4.2f, Celcius: %4.2f, Farenheit %4.2f\n", k, c, f);
 *             printf("Humidity is %4.2f, Dewpoint: %4.2f, Dewpoint fast: %4.2f\n", h, dp, dpf);
 *         } else {
 *             printf("Error: %d\n", error);
 *         }
 *     }
 * }
 * @endcode
 */

#ifndef MBED_DHT_H
#define MBED_DHT_H

#include "mbed.h"


typedef enum e_Type {
    DHT11     = 11,
    SEN11301P = 11,
    RHT01     = 11,
    DHT22     = 22,
    AM2302    = 22,
    SEN51035P = 22,
    RHT02     = 22,
    RHT03     = 22
}eType;

typedef enum e_Error {
    ERROR_NONE = 0,
    BUS_BUSY,
    ERROR_NOT_PRESENT,
    ERROR_ACK_TOO_LONG,
    ERROR_SYNC_TIMEOUT,
    ERROR_DATA_TIMEOUT,
    ERROR_CHECKSUM,
    ERROR_NO_PATIENCE
}eError;

typedef enum e_Scale {
    CELCIUS = 0,
    FARENHEIT,
    KELVIN
}eScale;


class DHT
{

public:
    /** Constructor
     * @param PinName   pin         The pin to assign as data pin.
     * @param eType     DHTtype     DHTtype set the type of Sensor.
     * 
     * @note     DHT11, SEN11301P, RHT01, DHT22, AM2302, SEN51035P, RHT02, RHT03 
     * 
    */
    DHT(PinName pin, eType DHTtype);
    ~DHT();
    eError readData(void);
    float ReadHumidity(void);
    float ReadTemperature(eScale const Scale);
    float CalcdewPoint(float const celsius, float const humidity);
    float CalcdewPointFast(float const celsius, float const humidity);

private:
    time_t  _lastReadTime;
    float _lastTemperature;
    float _lastHumidity;
    PinName _pin;
    bool _firsttime;
    eType _DHTtype;
    uint8_t DHT_data[5];
    float CalcTemperature();
    float CalcHumidity();
    float ConvertCelciustoFarenheit(float const);
    float ConvertCelciustoKelvin(float const);
    eError stall(DigitalInOut &io, int const level, int const max_time);

};

#endif
