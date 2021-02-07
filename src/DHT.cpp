//
// Created by filip on 07.02.2021.
//

#include "DHT.h"

inline uint DHT::readDataUntilTheSame(bool value) const {
    uint count = 0;

    while (gpio_get(PIN_DHT) == value) {
        ++count;
        sleep_us(1);
        if (count > 255) return -1;
    }
    return count;
}

DHT::DHT(const uint pinDht, const short maxTemperature, const short maxHumidity,
         const unsigned short timeBeforeStartTransferringUs, const unsigned short timeSeparateBit0Bit1) : PIN_DHT(
        pinDht), TIME_BEFORE_START_TRANSFERRING_US(timeBeforeStartTransferringUs), TIME_SEPARATE_BIT_0_BIT_1(
        timeSeparateBit0Bit1), MAX_TEMPERATURE(maxTemperature), MAX_HUMIDITY(maxHumidity) {}

bool DHT::measure() {
    int i;
    unsigned short count;
    for (i = 0; i < 5; ++i)
        received_data[i] = 0;

    gpio_set_dir(PIN_DHT, GPIO_OUT);
    gpio_put(PIN_DHT, false);
    sleep_ms(20);
    gpio_set_dir(PIN_DHT, GPIO_IN);
    sleep_us(TIME_BEFORE_START_TRANSFERRING_US);

    if (readDataUntilTheSame(true) == -1) return false;

    //Reading data
    for (i = 0; i < DATA_SIZE; ++i) {
        if (readDataUntilTheSame(false) == -1) return false;

        if ((count = readDataUntilTheSame(true)) == -1) return false;

        received_data[i / DATA_SIZE_PARTS] <<= 1;
        if (count > TIME_SEPARATE_BIT_0_BIT_1) received_data[i / DATA_SIZE_PARTS] |= 1;
    }

    if (received_data[4] == ((received_data[0] + received_data[1] + received_data[2] + received_data[3]) & 0xFF)) {
        humidity = ((received_data[0] * 10) + received_data[1]);
        if (humidity > MAX_HUMIDITY * 10) {
            humidity = received_data[0] * 10;
        }

        temperature = ((received_data[2] & 0x7F) * 10) + (received_data[3] & 0x7F);
        if (temperature > MAX_TEMPERATURE * 10) {
            temperature = received_data[2] * 10;
        }
        if (received_data[2] & 0x80 || received_data[3] & 0x80) {
            temperature = -temperature;
        }
    } else {
        return false;
    }
    return true;
}

int DHT::getTemperatureInt() {
    return temperature / 10;
}

int DHT::getHumidityInt() {
    return humidity / 10;
}

float DHT::getTemperatureFloat() {
    return ((float) temperature) / 10;
}

float DHT::getHumidityFloat() {
    return ((float) humidity) / 10;
}

DHT11::DHT11(const uint pinDht) : DHT(pinDht, 50, 80) {}

DHT11_60::DHT11_60(const uint pinDht) : DHT(pinDht, 60, 95) {}

DHT22::DHT22(uint pinDht) : DHT(pinDht, 80, 100) {}

DHT22_125::DHT22_125(uint pinDht) : DHT(pinDht, 125, 100) {}
