# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(test_lvgl
    main.cpp
    sdram.cpp
    storage.cpp
    lvgl_interface.cpp
    # lv_screens/ui-v1.cpp
    lv_screens/ui-v2.cpp
    lv_screens/ui_helpers.cpp
    lv_screens/lv_mainscreen.cpp
    lv_screens/ui_img_icn_play_png.c
    lv_screens/ui_img_icn_play_rev_png.c
)

target_link_libraries(test_lvgl 
    mbed-os
    mbed-storage-sdio
    mbed-storage
    mbed-usb-msd
    lvglDriver
)

mbed_set_post_build(test_lvgl) 