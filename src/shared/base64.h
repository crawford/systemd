/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

#pragma once

#include <stdint.h>
#include <stddef.h>

size_t base64_encoded_size(size_t len);

char * base64_encode(char *dest,
                     size_t *dest_len,
                     const uint8_t *src,
                     size_t src_len);
