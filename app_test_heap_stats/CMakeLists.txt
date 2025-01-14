# Copyright (c) 2021 Arm Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(test_heap_stats 
    main.cpp
)

target_link_libraries(test_heap_stats 
    mbed-os
)

mbed_set_post_build(test_heap_stats) 