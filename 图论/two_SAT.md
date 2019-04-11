在实际问题中，2-SAT问题在大多数时候表现成以下形式：有N对物品，每对物品中必须选取一个，也只能选取一个，并且它们之间存在某些限制关系（如某两个物品不能都选，某两个物品不能都不选，某两个物品必须且只能选一个，某个物品必选）等，这时，可以将每对物品当成一个布尔值（选取第一个物品相当于0，选取第二个相当于1），如果所有的限制关系最多只对两个物品进行限制，则它们都可以转化成9种基本限制关系，从而转化为2-SAT模型。

【建模】
其实2-SAT问题的建模是和实际问题非常相似的。
建立一个2N阶的有向图，其中的点分为N对，每对点表示布尔序列A的一个元素的0、1取值（以下将代表A[i]的0取值的点称为i，代表A[i]的1取值的点称为i'）。显然每对点必须且只能选取一个。然后，图中的边具有特定含义。若图中存在边<i, j>，则表示若选了i必须选j。可以发现，上面的9种限制关系中，后7种二元限制关系都可以用连边实现，比如NOT(A[x] AND A[y])需要连两条边<x, y'>和<y, x'>，A[x] OR A[y]需要连两条边<x', y>和<y', x>。而前两种一元关系，对于A[x]（即x必选），可以通过连边<x', x>来实现，而NOT A[x]（即x不能选），可以通过连边<x, x'>来实现。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int MAXN = 200007;
const int MAXM = 400005; //边的最大数
struct Edge {
    int to, next;
} edge[MAXM];
int head[MAXN], tot;
void init() {  //建图前初始化
    tot = 0;
    memset(head, -1, sizeof(head));
}
//u<<1表示u成立，u<<1|1表示u不成立
void add(int u, int v) {   //若事件u成立则v成立，注意结点下标要从0开始！
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
bool vis[MAXN];   //染色标记，为true表示选择，打印时用
int S[MAXN], top; //栈
bool dfs(int u) {
    if (vis[u ^ 1])
        return false;
    if (vis[u])
        return true;
    vis[u] = true;
    S[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next)
        if (!dfs(edge[i].to))
            return false;
    return true;
}
 
bool Twosat(int n) {  //判断可行性
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i += 2) {
        if (vis[i] || vis[i ^ 1]) 
            continue;
        top = 0;
        if (!dfs(i)) {
            while (top)
                vis[S[--top]] = false;
            if (!dfs(i ^ 1))
                return false;
        }
    }
    return true;
}
 
int main() {
    init();
    int n=3; //事件总数
    int a=0,b=1,c=2; //3个事件的编号
    add(a<<1,b<<1); //如果a发生，那么b发生
    add(a<<1|1,b<<1); //如果a不发生，那么b发生
    add(b<<1,c<<1|1);  //如果b发生，那么c不发生
    if(Twosat(2*n)){  //1个事件分成了发生和不发生，所以乘2
        cout<<"Yes\n";
        for(int i=0;i<2*n;i+=2){ //vis[i]和vis[i+1]只能有一个为1
            if(vis[i])           //前者为1代表i/2发生,后者为1代表i/2不发生
                cout<<i/2<<' ';
        }
    }else{
        cout<<"No\n";
    }
    return 0;
}


```

