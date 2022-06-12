/*
 * hamming8.h
 *
 *  Created on: 2022Äê6ÔÂ12ÈÕ
 *      Author: juxin
 */

#ifndef HAMMING8_H_
#define HAMMING8_H_

#include <stdint.h>
#include <stdbool.h>

bool hamming_syndrom(uint8_t data, uint8_t* err_pos);

#define hamming_correct(data, err_pos)  (data ^ (0x01 << err_pos))

uint8_t hamming_enc(uint8_t raw_data);

uint8_t hamming_dec(uint8_t data);

#endif /* HAMMING8_H_ */
