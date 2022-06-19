
#include <tasked_app/tasked_app.h>
#include <tasked_app/tasked_crc.h>

__SHARED_VAR(
uint16_t SW_Results;
uint16_t cnt;
)

inline uint16_t CRCheck_CCITT_Update(uint16_t init, uint16_t input)
{
    uint16_t CCITT = (uint8_t) (init >> 8) | (init << 8);
    CCITT ^= input;
    CCITT ^= (uint8_t) (CCITT & 0xFF) >> 4;
    CCITT ^= (CCITT << 8) << 4;
    CCITT ^= ((CCITT & 0xFF) << 4) << 1;
    return CCITT;
}

__TASK_ENTRY(init,

__GET(cnt) = 0;
__GET(SW_Results) = CRC_INIT;
return 1;

)


__TASK(1, main,

__GET(SW_Results) = CRCheck_CCITT_Update(__GET(SW_Results), CRC_Input[__GET(cnt)] & 0xFF);
__GET(SW_Results) = CRCheck_CCITT_Update(__GET(SW_Results), (CRC_Input[__GET(cnt)] >> 8) & 0xFF);
++__GET(cnt);

if(__GET(cnt) < CRC_LENGTH)
   return 1;
else {
    return TASK_FINISH;
}

)


void crc_regist()
{
    task_regist(0, init,       false);
    task_regist(1, main,       true );

    WAR_REGIST(2);
}
