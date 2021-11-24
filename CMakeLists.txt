cmake_minimum_required(VERSION 3.12)

project(nrf51_template)

enable_language(CXX)
enable_language(ASM)

if(NOT DEFINED NRF5_SDK_ROOT)
    message(FATAL_ERROR "NRF5_SDK_ROOT not defined")
endif()

set(NRF5_DEVICE             "NRF51822")
set(NRF5_S130_VERSION          "2.0.1")

set(TARGET_CFLAGS_EXTRA     "")
set(TARGET_CXXFLAGS_EXTRA   "")
set(TARGET_LDFLAGS_EXTRA    "-Wl,--print-memory-usage")

# Shared C source code
set(TARGET_C_SOURCES
    "src/main.c"
    "${NRF5_SDK_ROOT}/components/boards/boards.c"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/clock/nrf_drv_clock.c"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/common/nrf_drv_common.c"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/uart/nrf_drv_uart.c"
    "${NRF5_SDK_ROOT}/components/libraries/hardfault/hardfault_implementation.c"
    "${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_serial.c"
    "${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c"
    "${NRF5_SDK_ROOT}/components/libraries/timer/app_timer.c"
    "${NRF5_SDK_ROOT}/components/libraries/util/app_error.c"
    "${NRF5_SDK_ROOT}/components/libraries/util/app_error_weak.c"
    "${NRF5_SDK_ROOT}/components/libraries/util/app_util_platform.c"
    "${NRF5_SDK_ROOT}/components/libraries/util/nrf_assert.c"
    "${NRF5_SDK_ROOT}/components/libraries/util/sdk_errors.c"
    "${NRF5_SDK_ROOT}/components/toolchain/system_nrf51.c"
)

# C source code for applications with SoftDevice
set(TARGET_C_SOURCES_SD
    "${NRF5_SDK_ROOT}/components/softdevice/common/softdevice_handler/softdevice_handler.c"
)

# Assembly source code
set(TARGET_ASM_SOURCES
    "${NRF5_SDK_ROOT}/components/toolchain/gcc/gcc_startup_nrf51.S"
)

# Shared include directories
set(TARGET_C_INCLUDES
    "config"
    "include"
    "${NRF5_SDK_ROOT}/components/boards"
    "${NRF5_SDK_ROOT}/components/device"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/clock"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/common"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/delay"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/hal"
    "${NRF5_SDK_ROOT}/components/drivers_nrf/uart"
    "${NRF5_SDK_ROOT}/components/libraries/log"
    "${NRF5_SDK_ROOT}/components/libraries/log/src"
    "${NRF5_SDK_ROOT}/components/libraries/util"
    "${NRF5_SDK_ROOT}/components/toolchain"
    "${NRF5_SDK_ROOT}/components/toolchain/cmsis/include"
)

# Include directories for applications without SoftDevice
set(TARGET_C_INCLUDES_BLANK
    "${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd"
)

# Include directories for applications with SoftDevice
set(TARGET_C_INCLUDES_SD
    "${NRF5_SDK_ROOT}/components/softdevice/common/softdevice_handler"
    "${NRF5_SDK_ROOT}/components/softdevice/s130/headers"
)

# Shared C/CXX macros
set(TARGET_C_DEFINES
    "NRF51"
    "${NRF5_DEVICE}"
    "BSP_DEFINES_ONLY"
    "BOARD_CUSTOM"
    "SWI_DISABLE0"
    "USE_APP_CONFIG"
)

# C/CXX macros for applications with SoftDevice
set(TARGET_DEFINES_SD
    "S130"
    "SOFTDEVICE_PRESENT"
    "BLE_SUPPORT_REQD"
    "NRF_SD_BLE_API_VERSION=2"
)

# Shared libraries linked with application
set(TARGET_LIBS
)

# Shared library and linker script search paths
set(TARGET_LIB_DIRECTORIES
    "${NRF5_SDK_ROOT}/components/toolchain/gcc"
)

# Device specific settings, goes to C, CXX and ASM flags.
set(TARGET_CFLAGS_HARDWARE "-mcpu=cortex-m0 -mfloat-abi=soft -mthumb")

# Conditional flags
# DEBUG
set(CMAKE_C_FLAGS_DEBUG     "-DDEBUG -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "-DDEBUG -Og -g")
set(CMAKE_ASM_FLAGS_DEBUG   "-DDEBUG -Og -g")

# RELEASE
set(CMAKE_C_FLAGS_RELEASE        "-DNDEBUG -O3 -flto")
set(CMAKE_CXX_FLAGS_RELEASE      "-DNDEBUG -O3 -flto")
set(CMAKE_ASM_FLAGS_RELEASE      "-DNDEBUG -O3 -flto")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-flto")

# Final compiler flags
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${TARGET_CFLAGS_HARDWARE} ${TARGET_CFLAGS_EXTRA} -Wall -fdata-sections -ffunction-sections -fno-strict-aliasing -fno-builtin")
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${TARGET_CFLAGS_HARDWARE} ${TARGET_CXXFLAGS_EXTRA} -Wall -fdata-sections -ffunction-sections -fno-strict-aliasing -fno-builtin")
set(CMAKE_ASM_FLAGS        "${CMAKE_C_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs -Wl,--gc-sections -lc -lm -lnosys ${TARGET_LDFLAGS_EXTRA}")

# Different linker scripts for different flavors.
# Note that SoftDevice requires certain memory ranges reserved for private use.
set(TARGET_LDSCRIPT_BLANK_AA "${NRF5_SDK_ROOT}/components/toolchain/gcc/nrf51_xxaa.ld")       # Blank device
set(TARGET_LDSCRIPT_BLANK_AC "${NRF5_SDK_ROOT}/components/toolchain/gcc/nrf51_xxac.ld")       # Blank device with additional 16KB SRAM
set(TARGET_LDSCRIPT_SD_AA    "${CMAKE_SOURCE_DIR}/components/toolchain/gcc/nrf51_xxaa_sd.ld") # With SoftDevice
set(TARGET_LDSCRIPT_SD_AC    "${CMAKE_SOURCE_DIR}/components/toolchain/gcc/nrf51_xxaa_sd.ld") # With SoftDevice and additional 16KB SRAM

# Add shared includes, defines and libs
include_directories(${TARGET_C_INCLUDES})
add_compile_definitions(${TARGET_C_DEFINES})
link_directories(${TARGET_LIB_DIRECTORIES})
link_libraries(${TARGET_LIBS})

# Main targets are added below

# ============================= AA variant, without SD ============================= #
add_executable("${CMAKE_PROJECT_NAME}_blank_xxaa.elf" ${TARGET_C_SOURCES} ${TARGET_ASM_SOURCES})
target_link_options("${CMAKE_PROJECT_NAME}_blank_xxaa.elf"
    PRIVATE "-T${TARGET_LDSCRIPT_BLANK_AA}"
    PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_blank_xxaa.map,--cref"
)
target_include_directories("${CMAKE_PROJECT_NAME}_blank_xxaa.elf" PRIVATE ${TARGET_C_INCLUDES_BLANK})

# Generate hex
add_custom_command(OUTPUT "${CMAKE_PROJECT_NAME}_blank_xxaa.hex"
    COMMAND ${CMAKE_OBJCOPY} "-O" "ihex" "${CMAKE_PROJECT_NAME}_blank_xxaa.elf" "${CMAKE_PROJECT_NAME}_blank_xxaa.hex"
    DEPENDS "${CMAKE_PROJECT_NAME}_blank_xxaa.elf"
)
add_custom_target("${CMAKE_PROJECT_NAME}_blank_xxaa_hex" DEPENDS "${CMAKE_PROJECT_NAME}_blank_xxaa.hex")
# ================================================================================== #


# ============================= AC variant, without SD ============================= #
add_executable("${CMAKE_PROJECT_NAME}_blank_xxac.elf" ${TARGET_C_SOURCES} ${TARGET_ASM_SOURCES})
target_link_options("${CMAKE_PROJECT_NAME}_blank_xxac.elf"
    PRIVATE "-T${TARGET_LDSCRIPT_BLANK_AC}"
    PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_blank_xxac.map,--cref"
)
target_include_directories("${CMAKE_PROJECT_NAME}_blank_xxac.elf" PRIVATE ${TARGET_C_INCLUDES_BLANK})

# Generate hex
add_custom_command(OUTPUT "${CMAKE_PROJECT_NAME}_blank_xxac.hex"
    COMMAND ${CMAKE_OBJCOPY} "-O" "ihex" "${CMAKE_PROJECT_NAME}_blank_xxac.elf" "${CMAKE_PROJECT_NAME}_blank_xxac.hex"
    DEPENDS "${CMAKE_PROJECT_NAME}_blank_xxac.elf"
)
add_custom_target("${CMAKE_PROJECT_NAME}_blank_xxac_hex" DEPENDS "${CMAKE_PROJECT_NAME}_blank_xxac.hex")
# ================================================================================== #


# =============================== AA variant, with SD =============================== #
add_executable("${CMAKE_PROJECT_NAME}_sd_xxaa.elf" ${TARGET_C_SOURCES} ${TARGET_C_SOURCES_SD} ${TARGET_ASM_SOURCES})
target_link_options("${CMAKE_PROJECT_NAME}_sd_xxaa.elf"
    PRIVATE "-T${TARGET_LDSCRIPT_SD_AA}"
    PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_sd_xxaa.map,--cref"
)
target_include_directories("${CMAKE_PROJECT_NAME}_sd_xxaa.elf" PRIVATE ${TARGET_C_INCLUDES_SD})
target_compile_definitions("${CMAKE_PROJECT_NAME}_sd_xxaa.elf" PRIVATE ${TARGET_DEFINES_SD})

# Generate hex
add_custom_command(OUTPUT "${CMAKE_PROJECT_NAME}_sd_xxaa.hex" "${CMAKE_PROJECT_NAME}_sd_xxaa_full.hex"
    COMMAND ${CMAKE_OBJCOPY} "-O" "ihex" "${CMAKE_PROJECT_NAME}_sd_xxaa.elf" "${CMAKE_PROJECT_NAME}_sd_xxaa.hex"
    COMMAND "${CMAKE_SOURCE_DIR}/scripts/merge_hex.sh"
            "${NRF5_SDK_ROOT}/components/softdevice/s130/hex/s130_nrf51_${NRF5_S130_VERSION}_softdevice.hex"
            "${CMAKE_PROJECT_NAME}_sd_xxaa.hex"
            "${CMAKE_PROJECT_NAME}_sd_xxaa_full.hex"
    DEPENDS "${CMAKE_PROJECT_NAME}_sd_xxaa.elf"
)
add_custom_target("${CMAKE_PROJECT_NAME}_sd_xxaa_hex" DEPENDS "${CMAKE_PROJECT_NAME}_sd_xxaa.hex")
# ================================================================================== #


# =============================== AC variant, with SD =============================== #
add_executable("${CMAKE_PROJECT_NAME}_sd_xxac.elf" ${TARGET_C_SOURCES} ${TARGET_C_SOURCES_SD} ${TARGET_ASM_SOURCES})
target_link_options("${CMAKE_PROJECT_NAME}_sd_xxac.elf"
    PRIVATE "-T${TARGET_LDSCRIPT_SD_AC}"
    PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_sd_xxac.map,--cref"
)
target_include_directories("${CMAKE_PROJECT_NAME}_sd_xxac.elf" PRIVATE ${TARGET_C_INCLUDES_SD})
target_compile_definitions("${CMAKE_PROJECT_NAME}_sd_xxac.elf" PRIVATE ${TARGET_DEFINES_SD})

# Generate hex
add_custom_command(OUTPUT "${CMAKE_PROJECT_NAME}_sd_xxac.hex" "${CMAKE_PROJECT_NAME}_sd_xxac_full.hex"
    COMMAND ${CMAKE_OBJCOPY} "-O" "ihex" "${CMAKE_PROJECT_NAME}_sd_xxac.elf" "${CMAKE_PROJECT_NAME}_sd_xxac.hex"
    COMMAND "${CMAKE_SOURCE_DIR}/scripts/merge_hex.sh"
            "${NRF5_SDK_ROOT}/components/softdevice/s130/hex/s130_nrf51_${NRF5_S130_VERSION}_softdevice.hex"
            "${CMAKE_PROJECT_NAME}_sd_xxac.hex"
            "${CMAKE_PROJECT_NAME}_sd_xxac_full.hex"
    DEPENDS "${CMAKE_PROJECT_NAME}_sd_xxac.elf"
)
add_custom_target("${CMAKE_PROJECT_NAME}_sd_xxac_hex" DEPENDS "${CMAKE_PROJECT_NAME}_sd_xxac.hex")
# ================================================================================== #
