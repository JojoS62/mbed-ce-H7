# mbed-lvgl

set(MICROPY_DIR TRUE)                       # force lvgl to create an interface lib
# set(LV_CONF_INCLUDE_SIMPLE TRUE)

add_subdirectory(lvgl)                      # build lvgl as an interface lib

add_library(lvgl ALIAS lvgl_interface)      # for compatibility with static/interface libs

target_include_directories(lvgl_interface
    INTERFACE
        .
        lvgl
        lvgl/lv_core
        lvgl/lv_draw
        lvgl/lv_font
        lvgl/lv_gpu
        lvgl/lv_hal
        lvgl/lv_misc
        lvgl/lv_objx
        lvgl/lv_themes
        lvgl/lv_widgets
)

target_link_libraries(lvgl_interface
    INTERFACE
        mbed-rtos-flags
)