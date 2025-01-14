# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

list(APPEND SOURCEFILES
    main.cpp
    sdram.cpp
    lcd_fonts.cpp
    storage.cpp
)

if("FK743M5_XIH6" IN_LIST MBED_TARGET_LABELS)
    list(APPEND SOURCEFILES
        display_ltdc_XIH6.cpp
    )
endif()

if("FK743M2_IIT6" IN_LIST MBED_TARGET_LABELS)
    list(APPEND SOURCEFILES
        display_ltdc_IIT6.cpp
    )
endif()

add_executable(test_display 
    ${SOURCEFILES}
)

target_link_libraries(test_display 
    mbed-os
    mbed-storage-sdio
    mbed-storage
)

mbed_set_post_build(test_display) 