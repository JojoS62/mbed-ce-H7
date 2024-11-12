# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(Hello 
    main.cpp
    sdram.cpp
    storage.cpp
)

target_link_libraries(Hello 
    mbed-os
    mbed-storage-sdio
    mbed-storage
)

mbed_set_post_build(Hello) 