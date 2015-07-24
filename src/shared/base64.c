/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

#include "util.h"
#include "base64.h"

static char key_space[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t base64_encoded_size(size_t len) {
        assert(len < (SIZE_MAX / 4 - 2));

        // ceil(4/3 * len)
        return ((4 * (len + 2)) / 3 + 1);
}

char * base64_encode(char *dest,
                     size_t *dest_len,
                     const uint8_t *src,
                     size_t src_len) {
        size_t si, di;
        int pad;

        assert(dest);
        assert(dest_len);
        assert(*dest_len >= base64_encoded_size(src_len));

        *dest_len = base64_encoded_size(src_len);

        for (si = 0, di = 0; si < src_len; si += 3, di += 4) {
                uint32_t block = (((si < src_len ? src[si + 0] : 0) << 16) |
                                  ((si < src_len ? src[si + 1] : 0) <<  8) |
                                  ((si < src_len ? src[si + 2] : 0) <<  0));

                dest[di + 0] = key_space[(block >> 18) & 0x3F];
                dest[di + 1] = key_space[(block >> 12) & 0x3F];
                dest[di + 2] = key_space[(block >>  6) & 0x3F];
                dest[di + 3] = key_space[(block >>  0) & 0x3F];
        }

        pad = ((3 - (src_len % 3)) % 3);
        if (pad > 1)
                dest[*dest_len - 3] = '=';
        if (pad > 0)
                dest[*dest_len - 2] = '=';
        dest[*dest_len - 1] = '\0';

        return dest;
}
