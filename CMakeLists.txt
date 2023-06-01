# SPDX-License-Identifier: 0BSD
cmake_minimum_required(VERSION 3.26)
project("cec_filter_clear" VERSION 1.0.0)
set(CMAKE_C_STANDARD 23)

# includes
include(3DS)
include(Platform/Nintendo3DS)

# program
set(CEC_FILTER_CLEAR_SRCS
    "src/cecd.c"
    "src/main.c"
)
add_executable(cec_filter_clear ${CEC_FILTER_CLEAR_SRCS})
ctr_generate_smdh(OUTPUT     "${CMAKE_PROJECT_NAME}.smdh"
                  NAME        "Streetpass Cooldown Reset"
                  AUTHOR      "raisinware"
                  DESCRIPTION "Resets the 8 hour Streetpass cooldown"
                  ICON        "resource/icon.png")
ctr_create_3dsx(cec_filter_clear SMDH "${CMAKE_PROJECT_NAME}.smdh")

