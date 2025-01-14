# mbed-lvgl

set(MICROPY_DIR TRUE)                       # force lvgl to create an interface lib
# set(LV_CONF_INCLUDE_SIMPLE TRUE)

add_subdirectory(lvgl)                      # build lvgl as an interface lib

add_library(lvgl ALIAS lvgl_interface)      # for compatibility with static/interface libs

target_include_directories(lvgl_interface
    INTERFACE
        .
        lvgl
)

# target_compile_options(lvgl_interface INTERFACE -O2)

target_link_libraries(lvgl_interface
    INTERFACE
        mbed-rtos-flags
        )