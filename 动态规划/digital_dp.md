**HDU 2089 不要62**

http://acm.hdu.edu.cn/showproblem.php?pid=2089

不能出现4，或者相邻的62，这题可以暴力打表解决

具体的在代码里都有解释

```cpp
#include<iostream>  
#include<cstring>  
#include<queue>  
#include<cstdio>  
#include<cmath>  
#include<algorithm>  
#define N 55  
#define inf 1<<29  
#define MOD 9973  
#define LL long long  
#define eps 1e-7  
#define zero(a) fabs(a)<eps  
#define equal(a,b) zero(a-b)  
using namespace std;  
int dp[10][3];  
//dp[i][0],表示不存在不吉利数字  
//dp[i][1],表示不存在不吉利数字，且最高位为2  
//dp[i][2],表示存在不吉利数字  
void Init(){  
    memset(dp,0,sizeof(dp));  
    dp[0][0]=1;  
    for(int i=1;i<=6;i++){  
        dp[i][0]=dp[i-1][0]*9-dp[i-1][1];  //在最高位加上除了4之外的9个数字，但是可能在2之前加了6  
        dp[i][1]=dp[i-1][0];    //就是在原先不含不吉利数字的最高位加2  
        dp[i][2]=dp[i-1][2]*10+dp[i-1][0]+dp[i-1][1];  //在已经有不吉利数字最高位加任意数字，或者在无吉利数字前加4，或者在2前面加4  
    }  
}  
int slove(int n){  
    int len=0,bit[10];  
    int tmp=n;  
    while(n){  
        bit[++len]=n%10;  
        n/=10;  
    }  
    bit[len+1]=0;  
    int ans=0;  
    bool flag=false;  
    for(int i=len;i;i--){  
        ans+=dp[i-1][2]*bit[i];    
        if(flag)   //高位已经出现4或者62，后面的就随意  
            ans+=dp[i-1][0]*bit[i];  
        if(!flag&&bit[i]>4)  //高位可能出现4的情况  
            ans+=dp[i-1][0];  
        if(!flag&&bit[i+1]==6&&bit[i]>2)  //高位是6，后面一位可能出现2，这步debug了很久  
            ans+=dp[i][1];  
        if(!flag&&bit[i]>6)  //高位可能出现6，要把后面最高位为2计入  
            ans+=dp[i-1][1];  
        if(bit[i]==4||(bit[i+1]==6&&bit[i]==2))  //高位已经出现4或者62  
            flag=true;  
    }  
    return tmp-ans;  
}  
int main(){  
    int l,r;  
    Init();  
    while(scanf("%d%d",&l,&r)!=EOF&&l+r)  
        printf("%d\n",slove(r+1)-slove(l));  
    return 0;  
}  
```

**HDU 3555 BOMB**

http://acm.hdu.edu.cn/showproblem.php?pid=3555

不能出现相邻的49,和上一题类似

```cpp
#include<iostream>  
#include<cstring>  
#include<queue>  
#include<cstdio>  
#include<cmath>  
#include<algorithm>  
#define N 55  
#define inf 1<<29  
#define MOD 9973  
#define LL long long  
#define eps 1e-7  
#define zero(a) fabs(a)<eps  
#define equal(a,b) zero(a-b)  
using namespace std;  
LL dp[21][3],n;   
int len,bit[21];  
//dp[i][0]表示长度为i，包括49的个数  
//dp[i][1]表示长度为i，没有49但是开头为9的个数  
//dp[i][2]表示长度为i，没有49  
void Init(){  
    memset(dp,0,sizeof(dp));  
    dp[0][2]=1;  
    for(int i=1;i<20;i++){  
        dp[i][0]=(LL)dp[i-1][0]*10+dp[i-1][1];  
        dp[i][1]=dp[i-1][2];  
        dp[i][2]=(LL)dp[i-1][2]*10-dp[i-1][1];  
    }  
}  
int main(){  
    Init();  
    int t;  
    scanf("%d",&t);  
    while(t--){  
        scanf("%I64d",&n);  
        len=0;  
        n++;  
        while(n){  
            bit[++len]=n%10;  
            n/=10;  
        }  
        bit[len+1]=0;  
        LL ans=0;  
        bool flag=false;  
        for(int i=len;i;i--){  
            ans+=(LL)dp[i-1][0]*bit[i];  
            if(flag)  
                ans+=(LL)dp[i-1][2]*bit[i];  
            if(!flag&&bit[i]>4)  
                ans+=dp[i-1][1];  
            if(bit[i]==9&&bit[i+1]==4)  
                flag=true;  
        }  
        printf("%I64d\n",ans);  
    }  
    return 0;  
}  
```

**UESTC 1307 WINDY 数**
http://acm.uestc.edu.cn/problem.php?pid=1307
要求相邻的数差大于等于2

```cpp
#include<iostream>  
#include<cstring>  
#include<queue>  
#include<cstdio>  
#include<cmath>  
#include<algorithm>  
#define N 100005  
#define inf 1<<29  
#define MOD 9973  
#define LL long long  
#define eps 1e-7  
#define zero(a) fabs(a)<eps  
#define equal(a,b) zero(a-b)  
using namespace std;  
int dp[15][10];  
//dp[i][j]表示考虑i位的数中，最高为j的windy数  
void Init(){  
    memset(dp,0,sizeof(dp));  
    for(int i=0;i<=9;i++)  
        dp[1][i]=1;  
    for(int i=2;i<=10;i++){  
        for(int j=0;j<10;j++){  
            for(int k=0;k<10;k++)  
                if(abs(j-k)>=2)  
                    dp[i][j]+=dp[i-1][k];  
        }  
    }  
}  
int slove(int n){  
    int len=0,bit[15];  
    while(n){  
        bit[++len]=n%10;  
        n/=10;  
    }  
    bit[len+1]=0;  
    int ans=0;  
    //先把长度为1至len-1计入  
    for(int i=1;i<len;i++)  
        for(int j=1;j<10;j++)  
            ans+=dp[i][j];  
    //确定最高位  
    for(int j=1;j<bit[len];j++)  
        ans+=dp[len][j];  
    for(int i=len-1;i;i--){  
        for(int j=0;j<bit[i];j++)  
            if(abs(j-bit[i+1])>=2)  
                ans+=dp[i][j];  
        //如果高位已经出现非法，直接退出  
        if(abs(bit[i]-bit[i+1])<2)  
            break;  
    }  
    return ans;  
}  
int main(){  
    Init();  
    int l,r;  
    while(scanf("%d%d",&l,&r)!=EOF)  
        printf("%d\n",slove(r+1)-slove(l));  
    return 0;  
}  
```

