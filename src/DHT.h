//
// Created by filip on 07.02.2021.
//

#ifndef BUTTON_FIRST_DHT_H
#define BUTTON_FIRST_DHT_H

#include <pico/stdlib.h>

/**
 * @author Krzysztof Swałdek
 * @version 1
 * @date 07.02.2021
 */
class DHT {
public:
    /**
     * Initialize object for DHT sensor. If templated class not work use it and declare data from yours sensor specification.
     * @param pinDht pin number where sensor are connected
     * @param maxTemperature max sensor temperature from specification
     * @param maxHumidity max sensor humidity from specification
     * @param timeBeforeStartTransferringUs time of low state on initializing after send low state from MCU. Take a look at the specification. Read it and multiply by 1.9. Eg. 80us (read from sensor specification) * 1.9 = ~150us.
     * @param timeSeparateBit0Bit1 time boundary to separate bit with value 0 and 1 when sensors sends 40bit information. Take a look at the specification. Read it and multiply by 1.25. Eg. 28us (read from sensor specification) * 1.25 = 35us.
     */
    DHT(uint pinDht, short maxTemperature, short maxHumidity, unsigned short timeBeforeStartTransferringUs = 150,
        unsigned short timeSeparateBit0Bit1 = 35);

    /**
     * Measuring temperature and humidity.
     * @return true - all OK, false - error on collecting data
     */
    bool measure();

    /**
     * Get temperature as int (only integer).
     * @return integer temperature
     */
    int getTemperatureInt();

    /**
     * Get temperature as float (integer and decimal).
     * @return temperature with decimal part
     */
    float getTemperatureFloat();

    /**
     * Get humidity as int (only integer)
     * @return integer humidity
     */
    int getHumidityInt();

    /**
     * Get humidity as float (integer and decimal).
     * @return humidity with decimal part
     */
    float getHumidityFloat();

private:
    const uint PIN_DHT;
    const short DATA_SIZE = 40;
    const short DATA_SIZE_PARTS = 8;
    const short MAX_TEMPERATURE;
    const short MAX_HUMIDITY;

    // Time of start signal send by DHT (bit 0) * 1.9
    const unsigned short TIME_BEFORE_START_TRANSFERRING_US;

    // Boundary between bit value 0 and 1. If in documentation is 28 - 29 us boundary should be ~35us (time from documentation * 1.25)
    const unsigned short TIME_SEPARATE_BIT_0_BIT_1;

    short received_data[5];

    int temperature;
    int humidity;

    inline uint readDataUntilTheSame(bool value) const;
};

/**
 * Template for DHT22 with temp max 50°C
 */
class DHT11: public DHT{
public:
    /**
     * Initialize sensor
     * @param pinDht pin number where sensor are connected
     */
    explicit DHT11(uint pinDht);
};

/**
 * Template for DHT22 with temp max 60°C
 */
class DHT11_60: public DHT{
public:
    /**
     * Initialize sensor
     * @param pinDht pin number where sensor are connected
     */
    explicit DHT11_60(uint pinDht);
};

/**
 * Template for DHT22 with temp max 80°C
 */
class DHT22: public DHT{
public:
    /**
     * Initialize sensor
     * @param pinDht pin number where sensor are connected
     */
    explicit DHT22(uint pinDht);
};

/**
 * Template for DHT22 with temp max 125°C
 */
class DHT22_125: public DHT{
public:
    /**
     * Initialize sensor
     * @param pinDht pin number where sensor are connected
     */
    explicit DHT22_125(uint pinDht);
};


#endif //BUTTON_FIRST_DHT_H
