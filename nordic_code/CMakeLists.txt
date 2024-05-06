#
# Copyright (c) 2021 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(hardware_wallet)

# Incluir directorios
include_directories(include)

target_sources(app PRIVATE
        src/main.c
        src/buttons.c
        src/menu.c
        src/crypto.c
        src/base58.c
        src/privateKey.c
        src/publicKey.c
        src/hex_bytes.c)
