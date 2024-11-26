# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(hello 
    main.cpp
)

target_link_libraries(hello 
    mbed-os
)

mbed_set_post_build(hello) 