# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(test_display 
    main.cpp
    sdram.cpp
    lcd_fonts.cpp
    display_ltdc.cpp
    storage.cpp
)

target_link_libraries(test_display 
    mbed-os
    mbed-storage-sdio
    mbed-storage
)

mbed_set_post_build(test_display) 