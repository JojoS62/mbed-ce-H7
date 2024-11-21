# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(test_sdio 
    main.cpp
    sdram.cpp
    storage.cpp
)

target_link_libraries(test_sdio 
    mbed-os
    mbed-storage-sdio
    mbed-storage
)

mbed_set_post_build(test_sdio) 