#include <ImC/analysis/hamming8.h>
#include <msp430.h>
#include <stdio.h>

/*
 * If return value is true and err_pos is 0, no error detected.
 * If return value is true and err_pos is not 0, 2 errors detected and can not correct them.
 * If return value is false, error bit is at position err_pos.
 *
 * More than 2 errors may not be detected.
 */
bool hamming_syndrom(uint8_t data, uint8_t* err_pos)
{
    uint8_t xor_rlt = 0;
    uint8_t global_parity = 0;

    for (uint16_t i = 0; i < 8; ++i) {
        uint8_t mask = 0x01 << i;
        if (data & mask) {
            xor_rlt ^= i;
            global_parity++;
        }
    }

    if ((global_parity & 0x01) != 0)    return false;
    else    return true;
}


uint8_t hamming_enc(uint8_t raw_data)
{
    static uint8_t hamming_lookup_table[] =
        { 0, 15, 51, 60, 85, 90, 102, 105, 150, 153, 165, 170, 195, 204, 240, 255 };

    // Only lower 4 bits take effect.
    return hamming_lookup_table[raw_data & 0x0F];
}

uint8_t hamming_dec(uint8_t data)
{
    return (((data >> 5) << 1) & 0x0E) /* Get bit 7 to 5 */ |
            ((data >> 3) & 0x01)/* Get bit 3 */
            ;
}
