
#include <tasked_app/tasked_app.h>
#include <tasked_app/tasked_rsa.h>

__SHARED_VAR(
uint16_t candidate_e;
uint16_t e_number;
uint16_t enc_index;
uint16_t dec_index;

uint16_t public_n;
uint16_t phi_n;
uint16_t sqrt_candidate_e;

uint16_t secret_d[RSA_MSGLENGTH];
uint16_t public_e[RSA_MSGLENGTH];
uint16_t enc_cipher[RSA_MSGLENGTH];
uint16_t dec_plain[RSA_MSGLENGTH];
)

const uint8_t* msgPtr = RSA_MSG;

inline uint16_t RSA_PowerMod(uint16_t a, uint16_t b, uint16_t mod)
{
    uint16_t ans = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            ans = (ans * a) % mod;
        b = b / 2;
        a = (a * a) % mod;
    }
    return ans;
}

/* Square root by Newton's method. This code is from InK */
inline uint16_t RSA_Sqrt16(uint16_t x)
{
    uint16_t hi = 0xffff;
    uint16_t lo = 0;
    uint16_t mid = ((uint32_t)hi + (uint32_t)lo) >> 1;
    uint32_t s = 0;

    while (s != x && hi - lo > 1) {
        mid = ((uint32_t)hi + (uint32_t)lo) >> 1;
        s = (uint32_t)mid* (uint32_t)mid;
        if (s < x)
            lo = mid;
        else
            hi = mid;
    }

    return mid;
}


/* https://www.di-mgt.com.au/euclidean.html#extendedeuclidean */
inline uint16_t RSA_ModInv(uint16_t u, uint16_t v)
{
    uint16_t inv, u1, u3, v1, v3, t1, t3, q;
    int16_t iter;
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    iter = 1;
    while (v3 != 0)
    {
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}

inline uint8_t RSA_isPrime(uint16_t x, uint16_t sqrt_x)
{
    uint16_t i;
    for (i = 3; i <= sqrt_x; i += 2)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}


__TASK_ENTRY(init,

const uint16_t p = 11, q = 13;
__GET(public_n) = p * q;
__GET(phi_n) = (p - 1) * (q - 1);
__GET(candidate_e) = p + q - 1;
__GET(e_number) = 0;
__GET(enc_index) = 0;
__GET(dec_index) = 0;

return 1;

)

__TASK(1, get_e_sqrt,

__GET(sqrt_candidate_e) = RSA_Sqrt16(__GET(candidate_e));
return 2;

)

__TASK(2, e_verify,

if (RSA_isPrime(__GET(candidate_e), __GET(sqrt_candidate_e)))
   __GET(public_e[__GET(e_number)++]) = __GET(candidate_e);

if (__GET(e_number) < RSA_MSGLENGTH)
{
   __GET(candidate_e) += 2;
   return 1;
}

return 3;

)

__TASK(3, enc_main,

uint16_t i = __GET(enc_index)++;
__GET(enc_cipher[i]) =
       RSA_PowerMod(msgPtr[i], __GET(public_e[i]), __GET(public_n));

if (__GET(enc_index) < RSA_MSGLENGTH)
    return 3;
else
    return 4;
)

__TASK(4, calculate_d_main,

uint16_t i = __GET(dec_index);
__GET(secret_d[i]) = RSA_ModInv(__GET(public_e[i]), __GET(phi_n));
return 5;

)

__TASK(5, dec_main,

uint16_t i = __GET(dec_index)++;
__GET(dec_plain[i]) =
       RSA_PowerMod(__GET(enc_cipher[i]), __GET(secret_d[i]), __GET(public_n));

if (__GET(dec_index) < RSA_MSGLENGTH)
   return 4;
else {
    if (TASKED_APP_SELF_CHECK_MODE){
        __GET(dec_index) = 0;
        return 6;
    } else return TASK_FINISH;
}

)

__TASK(6, finish,

while (__GET(dec_index) != RSA_MSGLENGTH) {
    uint16_t expected = msgPtr[__GET(dec_index)] % __GET(public_n);
    if (__GET(dec_plain[__GET(dec_index)]) != expected) {
        error_detected();
        while(1){}
    }
    __GET(dec_index)++;
}

return TASK_FINISH;

)


void rsa_regist()
{

    task_regist(0, init,                false);
    task_regist(1, get_e_sqrt,          false);
    task_regist(2, e_verify,            true );
    task_regist(3, enc_main,            true );
    task_regist(4, calculate_d_main,    false);
    task_regist(5, dec_main,            true );
    task_regist(6, finish,              false);

    WAR_REGIST(4);
}




