

#ifndef TASKED_APP_TASKED_RSA_H_
#define TASKED_APP_TASKED_RSA_H_

#include <stdint.h>

// "A bosom friend afar brings a distant land near!"
const uint16_t rsa_msg[38] = {'A', 'b', 'o', 's', 'o', 'm', 'f', 'r', 'i', 'e', 'n', 'd', 'a', 'f', 'a',
                            'r', 'b', 'r', 'i', 'n', 'g', 's', 'a', 'd', 'i', 's', 't', 'a', 'n', 't',
                            'l', 'a', 'n', 'd', 'n', 'e', 'a', 'r'};

const uint16_t p = 11, q = 13;

#define RSA_MSGLENGTH    (30)


#endif /* TASKED_APP_TASKED_RSA_H_ */
