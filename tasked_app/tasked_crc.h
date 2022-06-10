
#ifndef TASKED_APP_TASKED_CRC_H_
#define TASKED_APP_TASKED_CRC_H_

#include <stdint.h>

#define CRC_LENGTH          (64)
#define CRC_INIT            (0xFFFF)

#define CRC_CHECK_RLT       32256

const uint16_t CRC_Input[CRC_LENGTH] = {
              0x0fc0, 0x1096, 0x5042, 0x0010,           // 16 random 16-bit numbers
              0x7ff7, 0xf86a, 0xb58e, 0x7651,           // these numbers can be
              0x8b88, 0x0679, 0x0123, 0x9599,           // modified if desired
              0xc58c, 0xd1e2, 0xe144, 0xb691,
              0x0fc0, 0x1096, 0x5042, 0x0010,           // 16 random 16-bit numbers
              0x7ff7, 0xf86a, 0xb58e, 0x7651,           // these numbers can be
              0x8b88, 0x0679, 0x0123, 0x9599,           // modified if desired
              0xc58c, 0xd1e2, 0xe144, 0xb691,
              0x0fc0, 0x1096, 0x5042, 0x0010,           // 16 random 16-bit numbers
              0x7ff7, 0xf86a, 0xb58e, 0x7651,           // these numbers can be
              0x8b88, 0x0679, 0x0123, 0x9599,           // modified if desired
              0xc58c, 0xd1e2, 0xe144, 0xb691,
              0x0fc0, 0x1096, 0x5042, 0x0010,           // 16 random 16-bit numbers
              0x7ff7, 0xf86a, 0xb58e, 0x7651,           // these numbers can be
              0x8b88, 0x0679, 0x0123, 0x9599,           // modified if desired
              0xc58c, 0xd1e2, 0xe144, 0xb691
};


#endif /* TASKED_APP_TASKED_CRC_H_ */
