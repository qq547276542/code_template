首先改算法原理是基于费马小定理： 假如p是素数，且gcd(a,p)=1，那么a^(p-1)%p=1

推论：  若p是素数且a是正整数，那么a^p%p=a

定义：令a是一正整数，若n是合数且满足a^n%n=a,则n称为以a为基的伪素数

素数测试原理：取多个a为底，若n都是以a为基的伪素数，则可以近似认为n为素数。取多个底进行试验，次数越多，n为素数的概率就越大

```cpp
typedef long long LL;
/* *************************************************
* Miller_Rabin 算法进行素数测试
* 速度快，可以判断一个 < 2^63 的数是不是素数
*
**************************************************/
const int S = 8; //随机算法判定次数，一般8~10就够了
// 计算ret = (a*b)%c	a,b,c < 2^63
long long mult_mod(long long a,long long b,long long c) {
    a %= c;
    b %= c;
    long long ret = 0;
    long long tmp = a;
    while(b) {
        if(b & 1) {
            ret += tmp;
            if(ret > c)ret -= c;//直接取模慢很多
        }
        tmp <<= 1;
        if(tmp > c)tmp -= c;
        b >>= 1;
    }
    return ret;
}
// 计算 ret = (a^n)%mod
long long pow_mod(long long a,long long n,long long mod) {
    long long ret = 1;
    long long temp = a%mod;
    while(n) {
        if(n & 1)ret = mult_mod(ret,temp,mod);
        temp = mult_mod(temp,temp,mod);
        n >>= 1;
    }
    return ret;
}
 
// 通过 a^(n-1)=1(mod n)来判断n是不是素数
// n-1 = x*2^t 中间使用二次判断
// 是合数返回true, 不一定是合数返回false
bool check(long long a,long long n,long long x,long long t) {
    long long ret = pow_mod(a,x,n);
    long long last = ret;
    for(int i = 1; i <= t; i++) {
        ret = mult_mod(ret,ret,n);
        if(ret == 1 && last != 1 && last != n-1)return true;//合数
        last = ret;
    }
    if(ret != 1)return true;
    else return false;
}
//**************************************************
// Miller_Rabin算法
// 是素数返回true,(可能是伪素数)
// 不是素数返回false
//**************************************************
bool Miller_Rabin(long long n) {
    if( n < 2)return false;
    if( n == 2)return true;
    if( (n&1) == 0)return false;//偶数
    long long x = n - 1;
    long long t = 0;
    while( (x&1)==0 ) {
        x >>= 1;
        t++;
    }
    srand(time(NULL));/* *************** */
    for(int i = 0; i < S; i++) {
        long long a = rand()%(n-1) + 1;
        if( check(a,n,x,t) )
            return false;
    }
    return true;
}
```