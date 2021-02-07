# Raspberry Pi Pico DHT library

This library helps to connect DHT sensor to Raspberry Pi Pico. There is predefined DHT11, DHT11_60 (with increased 
temperature max temperature to 60°C), DHT22, DHT22_125 (with increased max temperature to 125°C). You can declare 
your own DHT sensor, look at the section [other configuration of DHT sensor](#ocoDHTs).

## How to use

To use it library, you must add it to your project and link header file.

If you connect DHT sensor to pin `0` initializing should look like this:

```c++
DHT dhtSensor = DHT11(0);
```

If you want to use other sensor type, only change class.


| Sensor type                  |  Predefined class           |  Example               |
| ---------------------------  | --------------------------- | ---------------------- |
| DHT11                        | ```DHT11(uint pinDht)```    | ```DHT11(0);```        |
| DHT11 (max temperature 60°C) | ```DHT11_60(uint pinDht)``` | ```DHT11_60(0);```     |
| DHT22                        | ```DHT22(uint pinDht)```    | ```DHT22(0);```        |
| DHT22 (max temperature 128°C)| ```DHT22_125(uint pinDht)```| ```DHT22_125(0);```    |



If you not found sensor that you have or your sensor doesnt work look at section 
[other configuration for DHT sensor](#ocoDHTs).


### Measuring and collecting data

```c++
dhtSensor.measure();
float temperature = dhtSensor.getHumidityFloat();
```

## Example

You can find example use in example directory.

## <a name="ocoDHTs"></a>Other configuration of DHT sensor

You can configure your own DHT sensor, you only need sensor specifications. First you must find max temperature and 
humidity. Next find section with initializing or with described communication. There will be charts showing signal 
send from MTU (our board) and sends from the sensor. Find first low signal sends by sensor and note time. Next find 
other charts with send signal means value 0 and 1 and note both high signal time.

Example data:
* Pin where we connect sensor - 0
* Max temperature - 60°C
* Max humidity - 95%  
* First low signal send by sensor - 80us
* Signal means 0 - 28us
* Signal means 1 - 70us

Recalculate this data, multiply first low signal by 1.9 and signal means 0 by 1.25.
* First low signal send by sensor - 80us * 1.9 = 152us
* Signal means 0 - 28us * 1.25 = 35us

When we have this information, we can initialize sensor using basic constructor:

```c++
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
```

Our code will look like this:

```c++
//(pin, max temperature, max humidity, calculated initializing time, calculated boundary between 1 and 0)
DHT dhtSensor(0, 60, 95, 152, 35);
```



## Troubles

If `measure` function return always false, check connections. If this don't help, find documentation to your sensor 
and look on the section [other configuration for DHT sensor](#ocoDHTs).


## License

Copyright © 2021 Krzysztof Swałdek.

This library is free, you can do everything with it only please mention me.