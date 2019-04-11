题目大意：给定一个字符串，问有多少字符串满足UVU的形式，要求U非空，V的长度为g。

思路：首先，很容易想到用后缀数组求LCP，能够在O(1)的时间求任意2点的lcp。

一开始我想的是枚举v的起点，然后在v的左侧枚举左端u的起点，设左端u的起点为i，那么u_len等于v的起点减i,然后右端起点固定为j=i+u_len+v_len,那么只要lcp(i,j)为u_len，则ans++。  很可惜，这个思路时间复杂度为 O(N2).

然后我上网搜了题解，发现有一个枚举u_len的做法，能够将时间复杂度优化为O(nlogn).具体思路如下：

首先枚举U_len,然后字符串会被划分成len-u_len段，每段的起点为0，u_len,2*uLen....... 对于每个uvu串，其左端的u必定只覆盖一个起点，这样我们对于每个起点，计算左侧U覆盖该点的UVU串有多少个。

这样说可能还有点抽象，那么以下图为例，若我们要求串 aabaabaaaa ，设u_len枚举到了2，v_len=1,则串被划分为aa|ba|ab|aa|aa  

假设我们现在求左侧U覆盖第二个起点（即下标为2的点）的uvu串有几个 ,设该起点为i，则很容易求出，该串也必须覆盖点j=i+u_len+v_len。那么对i和j向右求LCP，向左求反向LCP。

为什么要这样做呢？因为我们要得到一个u的可行区间，在该区间内，左侧u和右侧u一定相等，且中间相隔v。而向右求lcp能求出区间右端点，向左求lcp能求出区间左端点。（认真思考）

但是左右端点到i的距离不能大于u_len，因为如果取了大于u_len的值，那么左侧u就会覆盖下一个分隔段的起点，会产生重复答案（认真思考）

![](https://i.loli.net/2019/04/11/5caeddd5d8108.jpg)

（红色字符为分隔段首字符，括号内为经过第二个首字符（str[2]）的左侧u的可取区间，因为u的长度枚举到了2，所以经过str[2]的u可以取str[1~2]和str[2~3]，每对相同颜色的下划线代表左侧的u和同一个uvu串中右侧的u）

最后对于每个u_len的每个分隔段起点，ans+=区间长度-u_len+1。

下面附上ac代码：

```cpp
#include<queue>
#include<cstring>
#include<string>
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int MAXN=100010;
int t1[MAXN],t2[MAXN],c[MAXN];//求SA数组需要的中间变量，不需要赋值
//待排序的字符串放在s数组中，从s[0]到s[n-1],长度为n,且最大值小于m,
//除s[n-1]外的所有s[i]都大于0，r[n-1]=0
//函数结束以后结果放在sa数组中,sa数组下标范围1~n
bool cmp(int *r,int a,int b,int l) {
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int str[],int sa[],int rank1[],int height[],int n,int m) {   //n是串长度，m是字符集大小，一般128
    n++;
    int i, j, p, *x = t1, *y = t2;
    //第一轮基数排序，如果s的最大值很大，可改为快速排序
    for(i = 0; i < m; i++)c[i] = 0;
    for(i = 0; i < n; i++)c[x[i] = str[i]]++;
    for(i = 1; i < m; i++)c[i] += c[i-1];
    for(i = n-1; i >= 0; i--)sa[--c[x[i]]] = i;
    for(j = 1; j <= n; j <<= 1) {
        p = 0;
        //直接利用sa数组排序第二关键字
        for(i = n-j; i < n; i++)y[p++] = i;//后面的j个数第二关键字为空的最小
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        //这样数组y保存的就是按照第二关键字排序的结果
        //基数排序第一关键字
        for(i = 0; i < m; i++)c[i] = 0;
        for(i = 0; i < n; i++)c[x[y[i]]]++;
        for(i = 1; i < m; i++)c[i] += c[i-1];
        for(i = n-1; i >= 0; i--)sa[--c[x[y[i]]]] = y[i];
        //根据sa和x数组计算新的x数组
        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        for(i = 1; i < n; i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p >= n)break;
        m = p;//下次基数排序的最大值
    }
    int k = 0;
    n--;
    for(i = 0; i <= n; i++)rank1[sa[i]] = i;
    for(i = 0; i < n; i++) {
        if(k)k--;
        j = sa[rank1[i]-1];
        while(str[i+k] == str[j+k])k++;
        height[rank1[i]] = k;
    }
}
int rank1[MAXN],height[MAXN];
int RMQ[MAXN];
int mm[MAXN];
int best[20][MAXN];
void initRMQ(int n) {     //调用da后，初始化RMQ（求LCP用）
    for(int i=1; i<=n; i++)RMQ[i]=height[i];
    mm[0]=-1;
    for(int i=1; i<=n; i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(int i=1; i<=n; i++)best[0][i]=i;
    for(int i=1; i<=mm[n]; i++)
        for(int j=1; j+(1<<i)-1<=n; j++) {
            int a=best[i-1][j];
            int b=best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b])best[i][j]=a;
            else best[i][j]=b;
        }
}
int askRMQ(int a,int b) {
    int t;
    t=mm[b-a+1];
    b-=(1<<t)-1;
    a=best[t][a];
    b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b) {
    a=rank1[a];
    b=rank1[b];
    if(a>b)swap(a,b);
    return height[askRMQ(a+1,b)];
}
char str[MAXN];
int r[MAXN];  //把字符串存到这个数组里
int sa[MAXN];   //后缀数组
int n;
int main() {
    //freopen("in.txt","r",stdin);
    int t,now=0;
    cin>>t;
    while(t--) {
        int gn;
        scanf("%d%s",&gn,str);
        n=strlen(str);
        for(int i=0; i<n; i++) {
            r[2*n-i]=r[i]=str[i]-'a'+1;
        }
        r[n]=29;
        int len=2*n+1;
        r[len]=0;
        da(r,sa,rank1,height,len,30);
        initRMQ(len);
        long long ans=0;
        int r;
        for(int U=1;2*U+gn<=n;U++){
            for(int l=0;(r=l+U+gn)<n;l+=U){
                 int width=min(U,lcp(l,r))+min(U,lcp(2*n-l,2*n-r))-1;  
                 if(width>=U){
                     ans+=width-U+1;
                 }
            }
        }
        printf("Case %d: %d\n",++now,ans);
    }
    return 0;
}
```