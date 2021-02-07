//
// Created by filip on 06.02.2021.
//
#include "pico/stdlib.h"
#include <stdio.h>
#include "../src/DHT.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
const uint PIN_LED = 25;
const uint PIN_DHT = 15;

int main() {
    stdio_init_all();
    gpio_init(PIN_LED);
    gpio_init(PIN_DHT);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    sleep_ms(10000);

    //Initialize sensor
    DHT dhtSensor = DHT11_60(PIN_DHT);

    while (1) {
        if(dhtSensor.measure())
            printf("Humidity = %.1f%%, Temperature = %.1fC\n", dhtSensor.getHumidityFloat(), dhtSensor.getTemperatureFloat());
        else
            printf("Error on read data from sensor!\n");
        sleep_ms(5000);
    }

}


#pragma clang diagnostic