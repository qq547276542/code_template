```cpp
typedef long long LL;
const int maxn=10000;
int prime[maxn+7];   //下标从1开始，prime[0]存的是素数个数
int getPrime(){   //求小于maxn的所有素数，返回素数个数
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=maxn;i++){
        if(!prime[i])prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=maxn/i;j++){
            prime[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
    return prime[0];  
}
int p[107],dex[107];
//设最大的素数为t，则x最多能取t*t
int getFactors(LL x){   //将x的唯一分解存在p[]和dex[]中
    int fatcnt=0;   
    LL tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++){  //注意i的初始值取决于素数表的起始下标
        dex[fatcnt]=0;
        if(tmp%prime[i]==0){
            p[fatcnt]=prime[i];
            while(tmp%prime[i]==0){
                dex[fatcnt]++;
                tmp/=prime[i];
            }
            fatcnt++;
        }
    }
    if(tmp!=1){
        p[fatcnt]=tmp;
        dex[fatcnt++]=1;
    }
    return fatcnt;
}
```

**约数和公式**：

对于已经分解的整数A=(p1^k1)*(p2^k2)*(p3^k3)*....*(pn^kn)

有A的所有因子之和为

    S = (1+p1+p1^2+p1^3+...p1^k1) * (1+p2+p2^2+p2^3+….p2^k2) * (1+p3+ p3^3+…+ p3^k3) * .... * (1+pn+pn^2+pn^3+...pn^kn)


用递归二分求等比数列1+pi+pi^2+pi^3+...+pi^n：

（1）若n为奇数,一共有偶数项，则：
      1 + p + p^2 + p^3 +...+ p^n = (1+p^(n/2+1)) + p * (1+p^(n/2+1)) +...+ p^(n/2) * (1+p^(n/2+1))
      = (1 + p + p^2 +...+ p^(n/2)) * (1 + p^(n/2+1))

上式红色加粗的前半部分恰好就是原式的一半，那么只需要不断递归二分求和就可以了，后半部分为幂次式，将在下面第4点讲述计算方法。

（2）若n为偶数,一共有奇数项,则:
      1 + p + p^2 + p^3 +...+ p^n = (1+p^(n/2+1)) + p * (1+p^(n/2+1)) +...+ p^(n/2-1) * (1+p^(n/2+1)) + p^(n/2)
      = (1 + p + p^2 +...+ p^(n/2-1)) * (1+p^(n/2+1)) + p^(n/2);

   上式红色加粗的前半部分恰好就是原式的一半，依然递归求解

```cpp
LL power(LL p,LL n,int mod)  //快速幂
{
    LL sq=1;
    while(n>0)
    {
        if(n%2)
            sq=(sq*p)%mod;
        n/=2;
        p=p*p%mod;
    }
    return sq;
}
LL sum(LL p,LL n,int mod){     //求1+pi+pi^2+pi^3+...+pi^n
    if(n==0)
          return 1;
    if(n%2)  //n为奇数,
        return (sum(p,n/2,mod)*(1+power(p,n/2+1,mod)))%mod;
    else     //n为偶数
        return (sum(p,n/2-1,mod)*(1+power(p,n/2+1,mod))+power(p,n/2,mod))%mod;
}
```

