cmake_minimum_required(VERSION 3.16)

add_executable(temp example/Temp.cpp src/DHT.cpp src/DHT.h)

target_link_libraries(temp pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(temp 1)
pico_enable_stdio_uart(temp 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(temp)