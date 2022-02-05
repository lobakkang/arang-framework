cmake_minimum_required(VERSION 3.11)
project("felix kernel")

set(PRODUCT_NAME felix_kernel)

set(F_CPU 16000000UL)
set(MCU atmega328p)
set(BAUD 115200)
set(PROG_TYPE arduino)

set(E_FUSE 0xfd)
set(H_FUSE 0xda)
set(L_FUSE 0xfd)
set(LOCK_BIT 0xff)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(
  -DF_CPU=${F_CPU}
  -DBAUD=${BAUD}
)
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
  -mmcu=${MCU}
  -Os
)

include_directories(include/)
file(GLOB SRC_FILES "src/kernel/*.c")

add_executable(${PRODUCT_NAME} ${SRC_FILES})
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)
add_custom_target(eeprom avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)
add_custom_target(upload avrdude -F -v -V -c ${PROG_TYPE} -p ${MCU} -P /dev/ttyUSB0 -b 115200 -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)
add_custom_target(upload_eeprom avrdude -c ${PROG_TYPE} -p ${MCU} -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)
add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU} -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m)
add_custom_target(usage avr-size -C --mcu=atmega328p ${PRODUCT_NAME}.elf)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")
