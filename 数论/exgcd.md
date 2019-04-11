```cpp
typedef long long LL;
LL exgcd(LL a,LL b,LL &x,LL &y){
     if(a==0&&b==0) return -1;
     if(b==0) { x=1;y=0; return a;  }
     LL d=exgcd(b,a%b,y,x);
     y-=a/b*x;
     return d;
}
LL MLE(LL a,LL b,LL mod){  // 返回(a*x)%mod=b 的最小正整数解
    LL x,y;
    LL gcd=exgcd(a,mod,x,y);
    if(b%gcd!=0) return -1;  //若返回-1，则该方程无解
    x*=b/gcd;
    mod/=gcd;
    if(mod<0) mod=-mod;
    LL ans=x%mod;
    if(ans<=0) ans+=mod;  //其他解为： ans+i*mod （i为整数）
    return ans;
}
LL x0,y0,kx,ky;
bool LE(LL a,LL b,LL c){   //解线性方程ax+by=c
    LL x1,y1;
    LL gcd=exgcd(a,b,x1,y1);
    if(c%gcd)return false;  //无整数解
    x0=x1*c/gcd,y0=y1*c/gcd;
    kx=b/gcd,ky=-a/gcd;
    return true;   //有解，解集为：（x0+kx*t,y0+ky*t） t为整数
}
```

**用扩展欧几里德算法求解模线性方程的方法**：

同余方程 ax≡b (mod n)对于未知数 x 有解，当且仅当 gcd(a,n) | b。且方程有解时，方程有 gcd(a,n) 个解。

求解方程 ax≡b (mod n) 相当于求解方程 ax+ ny= b, (x, y为整数)

设 d= gcd(a,n)，假如整数 x 和 y，满足 d= ax+ ny(用扩展欧几里德得出)。如果 d| b，则方程
a* x0+ n* y0= d， 方程两边乘以 b/ d，(因为 d|b，所以能够整除)，得到 a* x0* b/ d+ n* y0* b/ d= b。
所以 x= x0* b/ d，y= y0* b/ d 为 ax+ ny= b 的一个解，所以 x= x0* b/ d 为 ax= b (mod n ) 的解。
ax≡b (mod n)的一个解为 x0= x* (b/ d ) mod n，且方程的 d 个解分别为 xi= (x0+ i* (n/ d ))mod n {i= 0... d-1}。
设ans=x*(b/d),s=n/d;
方程ax≡b (mod n)的最小整数解为：(ans%s+s)%s;
    
**相关证明**：

证明方程有一解是: x0 = x'(b/d) mod n;
由 a*x0 = a*x'(b/d) (mod n)
     a*x0 = d (b/d) (mod n)   (由于 ax' = d (mod n))
            = b (mod n)
    
证明方程有d个解: xi = x0 + i*(n/d)  (mod n);
由 a*xi (mod n) = a * (x0 + i*(n/d)) (mod n)
                            = (a*x0+a*i*(n/d)) (mod n)
                            = a * x0 (mod n)             (由于 d | a)
                            = b


     

**首先看一个简单的例子**：

5x=4(mod3)

解得x = 2,5,8,11,14.......

由此可以发现一个规律，就是解的间隔是3.

那么这个解的间隔是怎么决定的呢？

如果可以设法找到第一个解，并且求出解之间的间隔，那么就可以求出模的线性方程的解集了.

我们设解之间的间隔为dx.

那么有

a*x = b(mod n);

a*(x+dx) = b(mod n);

两式相减，得到:

a*dx(mod n)= 0;

也就是说a*dx就是a的倍数，同时也是n的倍数，即a*dx是a 和 n的公倍数.为了求出dx,我们应该求出a 和 n的最小公倍数,此时对应的dx是最小的.

设a 和 n的最大公约数为d,那么a 和 n 的最小公倍数为(a*n)/d.

即a*dx = a*n/d;

所以dx = n/d.

因此解之间的间隔就求出来了.