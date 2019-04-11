### 1. 单点覆盖，区间查询
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 100007;
const int INF=0x7fffffff;
int MAX[maxn<<2];
int MIN[maxn<<2];
int SUM[maxn<<2];
void PushUP(int rt) {
    MAX[rt] = max(MAX[rt<<1] , MAX[rt<<1|1]);
    MIN[rt] = min(MIN[rt<<1] , MIN[rt<<1|1]);
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
}
//所有的 l ,r ,rt 参数为 1，n,1   其中n为区间长度
void build(int l,int r,int rt) {   //建树
    if (l == r) {
        MAX[rt] = MIN[rt] =SUM[rt]=0;  //初始化线段树为0的写法
        /*
          //边读入边建树的写法，复杂度O(n)  若执行n次更新来初始化的话复杂度为O（nlogn）
            scanf("%d",&MAX[rt]);
            MIN[rt] = MAX[rt];
            SUM[rt] = MAX[rt];
        */
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUP(rt);
}
void update(int p,int v,int l,int r,int rt) {  //单点替换，把p位置的值置为v
    if (l == r) {
        MAX[rt] = v;
        MIN[rt] = v;
        SUM[rt] = v;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p , v ,lson);
    else update(p , v , rson);
    PushUP(rt);
}
void update1(int p,int addv,int l,int r,int rt) {  //单点增加，把p位置的值增加v
    if (l == r) {
        SUM[rt] = SUM[rt] + addv;
        MIN[rt] = MIN[rt] + addv;
        MAX[rt] =MAX[rt]+addv;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update1(p , addv ,lson);
    else update1(p , addv , rson);
    PushUP(rt);
}
int queryMAX(int L,int R,int l,int r,int rt) {   //求L~R的最大值
    if (L <= l && r <= R) {
        return MAX[rt];
    }
    int m = (l + r) >> 1;
    int ret = -INF;
    if (L <= m) ret = max(ret , queryMAX(L , R , lson));
    if (R > m)  ret =  max(ret , queryMAX(L , R , rson));
    return ret;
}
int queryMIN(int L,int R,int l,int r,int rt) {  //求L~R的最小值
    if (L <= l && r <= R) {
        return MIN[rt];
    }
    int m = (l + r) >> 1;
    int ret = INF;
    if (L <= m) ret = min(ret , queryMIN(L , R , lson));
    if (R > m)  ret =  min(ret , queryMIN(L , R , rson));
    return ret;
}
int querySUM(int L,int R,int l,int r,int rt) {   //求L~R的和
    if (L <= l && r <= R) {
        return SUM[rt];
    }
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += querySUM(L , R , lson);
    if (R > m)  ret +=  querySUM(L , R , rson);
    return ret;
}
int main() {
    int n , m;
    while (~scanf("%d%d",&n,&m)) {
        build(1 , n , 1);
        while (m --) {
            char op[2];
            int a , b;
            scanf("%s%d%d",op,&a,&b);
            if (op[0] == 'Q') { //区间求最大
                printf("%d\n",queryMAX(a , b , 1 , n , 1));
            } else if(op[0]=='U') //单点替换
                update(a , b , 1 , n , 1);
            else if(op[0]=='M') { //区间求最小
                printf("%d\n",queryMIN(a , b , 1 , n , 1));
            } else if(op[0]=='H') { //区间求和
                printf("%d\n",querySUM(a , b , 1 , n , 1));
            } else if(op[0]=='S') { //单点增加
                update1(a , b , 1 , n , 1);
            } else if(op[0]=='E') { //单点减少
                update1(a , -b , 1 , n , 1);
            }
        }
    }
    return 0;
}
```

### 2.区间覆盖，区间查询

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
 
#define max(a,b) (a>b)?a:b
#define min(a,b) (a>b)?b:a
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 100100;
const int INF=0x7fffffff;
using namespace std;
int lazy[maxn<<2];
int MAX[maxn<<2];
int MIN[maxn<<2];
int SUM[maxn<<2];
void PushUp(int rt) { //由左孩子、右孩子向上更新父节点
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
    MAX[rt] = max(MAX[rt<<1],MAX[rt<<1|1]);
    MIN[rt] = min(MIN[rt<<1],MIN[rt<<1|1]);
}
void PushDown(int rt,int m) { //向下更新
    if (lazy[rt]) { //懒惰标记
        lazy[rt<<1] = lazy[rt<<1|1] = lazy[rt];
        SUM[rt<<1] = (m - (m >> 1)) * lazy[rt];
        SUM[rt<<1|1] = ((m >> 1)) * lazy[rt];
        MAX[rt<<1]=MAX[rt<<1|1]=lazy[rt];
        MIN[rt<<1]=MIN[rt<<1|1]=lazy[rt];
        lazy[rt] = 0;
    }
}
//所有的l，r，rt  带入1，n，1
void build(int l,int r,int rt) { //初始化建树
    lazy[rt] = 0;
    if (l== r) {
        SUM[rt]=MAX[rt]=MIN[rt]=0;  //初始化为0的建树
        /*scanf("%d",&SUM[rt]);  //边读入边建树的方法
          MAX[rt]=MIN[rt]=SUM[rt];
        */
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int R,int v,int l,int r,int rt) { //将L~R区间的值置为v
    //if(L>l||R>r) return;
    if (L <= l && r <= R) {
        lazy[rt] = v;
        SUM[rt] = v * (r - l + 1);
        MIN[rt] = v;
        MAX[rt] = v;
        //printf("%d %d %d %d %d\n", rt, sum[rt], c, l, r);
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , v , lson);
    if (R > m) update(L , R , v , rson);
    PushUp(rt);
}
 
int querySUM(int L,int R,int l,int r,int rt) {  //求区间L~R的和
    if (L <= l && r <= R) {
        //printf("%d\n", sum[rt]);
        return SUM[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += querySUM(L , R , lson);
    if (m < R) ret += querySUM(L , R , rson);
    return ret;
}
int queryMIN(int L,int R,int l,int r,int rt) {  //求区间L~R的最小值
    if (L <= l && r <= R) {
        //printf("%d\n", sum[rt]);
        return MIN[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = INF;
    if (L <= m) ret = min(ret, queryMIN(L , R , lson));
    if (m < R) ret = min(ret,queryMIN(L , R , rson));
    return ret;
}
int queryMAX(int L,int R,int l,int r,int rt) {  //求区间L~R的最大值
    if (L <= l && r <= R) {
        //printf("%d\n", sum[rt]);
        return MAX[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = -INF;
    if (L <= m) ret = max(ret, queryMAX(L , R , lson));
    if (m < R) ret = max(ret,queryMAX(L , R , rson));
    return ret;
}
 
int main() {
    int  n , m;
    char str[5];
    while(scanf("%d%d",&n,&m)) {
        build(1 , n , 1);
        while (m--) {
            scanf("%s",str);
            int a , b , c;
            if(str[0]=='T') {
                scanf("%d%d%d",&a,&b,&c);
                update(a , b , c , 1 , n , 1);
            } else if(str[0]=='Q') {
                scanf("%d%d",&a,&b);
                cout<<querySUM(a,b,1,n,1)<<endl;
            } else if(str[0]=='A') {
                scanf("%d%d",&a,&b);
                cout<<queryMAX(a,b,1,n,1)<<endl;
            } else if(str[0]=='I') {
                scanf("%d%d",&a,&b);
                cout<<queryMIN(a,b,1,n,1)<<endl;
            }
        }
    }
    return 0;
}
```

### 3.区间增加，区间查询

```cpp
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define max(a,b) (a>b)?a:b
#define min(a,b) (a>b)?b:a
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 100100;
const int INF=0x7fffffff;
using namespace std;
int lazy[maxn<<2];
int SUM[maxn<<2],MAX[maxn<<2],MIN[maxn<<2];
void putup(int rt) {
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
    MAX[rt] =max(MAX[rt<<1],MAX[rt<<1|1]) ;
    MIN[rt] =min(MIN[rt<<1],MIN[rt<<1|1]);
}
void putdown(int rt,int m) {
    if (lazy[rt]) {
        lazy[rt<<1] += lazy[rt];
        lazy[rt<<1|1] += lazy[rt];
        SUM[rt<<1] += lazy[rt] * (m - (m >> 1));
        SUM[rt<<1|1] += lazy[rt] * (m >> 1);
        MAX[rt<<1]+=lazy[rt];
        MAX[rt<<1|1] +=lazy[rt];
        MIN[rt<<1]+=lazy[rt];
        MIN[rt<<1|1]+=lazy[rt];
        lazy[rt] = 0;
    }
}
//以下的 l,r,rt 都带入 1,n,1
void build(int l,int r,int rt) {  //初始化建树
    lazy[rt] = 0;
    if (l == r) {
        //初始化树为0的写法
        SUM[rt]=MAX[rt]=MIN[rt]=0;
        /*  //边读入边建树的写法
        scanf("%d",&SUM[rt]);
        MAX[rt]=MIN[rt]=SUM[rt];
        */
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    putup(rt);
}
void update(int L,int R,int v,int l,int r,int rt) {  //将区间L~R的值增加v
    if (L <= l && r <= R) {
        lazy[rt] += v;
        SUM[rt] += v * (r - l + 1);
        MAX[rt]+=v;
        MIN[rt]+=v;
        return ;
    }
    putdown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , v , lson);
    if (m < R) update(L , R , v , rson);
    putup(rt);
}
int querySUM(int L,int R,int l,int r,int rt) {  //求区间L~R的和
    if (L <= l && r <= R) {
        return SUM[rt];
    }
    putdown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += querySUM(L , R , lson);
    if (m < R) ret += querySUM(L , R , rson);
    return ret;
}
int queryMAX(int L,int R,int l,int r,int rt) {  //求区间L~R的最大值
    if (L <= l && r <= R) {
        return MAX[rt];
    }
    putdown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = -INF;
    if (L <= m) ret =max(ret,queryMAX(L , R , lson)) ;
    if (m < R) ret =max(ret,queryMAX(L , R , rson)) ;
    return ret;
}
int queryMIN(int L,int R,int l,int r,int rt) {  //求区间L~R的最小值
    if (L <= l && r <= R) {
        return MIN[rt];
    }
    putdown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = INF;
    if (L <= m) ret = min(ret,queryMIN(L , R , lson));
    if (m < R) ret = min(ret,queryMIN(L , R , rson));
    return ret;
}
int main() {
    int n , m;
    int a , b , c;
    char str[5];
    scanf("%d%d",&n,&m);
    build(1 , n , 1);
    while (m--) {
        scanf("%s",str);
        if (str[0] == 'S') {
            scanf("%d%d",&a,&b);
            printf("%d\n",querySUM(a , b , 1 , n , 1));
        } else if(str[0]=='C') {
            scanf("%d%d%d",&a,&b,&c);
            update(a , b , c , 1 , n , 1);
        } else if(str[0]=='A') {
            scanf("%d%d",&a,&b);
            printf("%d\n",queryMAX(a , b , 1 , n , 1));
        } else if(str[0]=='I') {
            scanf("%d%d",&a,&b);
            printf("%d\n",queryMIN(a , b , 1 , n , 1));
        }
    }
    return 0;
}
```

