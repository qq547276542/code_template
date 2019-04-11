# 动态规划解TSP问题（状态压缩dp）

## TSP问题简述

&emsp;&emsp;给定图上若干个点，以及他们之间的距离，求一条距离和最小的回路，使得该回路正好经过每个点一次。TSP也叫旅行商问题、货郎担问题。。。

## 状态转移方程

&emsp;&emsp;用 V’ 表示一个点的集合，假设从顶点 s 出发， d ( i , V’ ) 表示当前到达顶点 i，经过 V’ 集合中所有顶点一次的最小花费。

1.当 V’ 为仅包含起点的集合，也就是：d ( s , { s } ) = 0 ;

2.其他情况，则对子问题求最优解。需在 V’ 这个城市集合中，尝试每一个城市结点，并求出最优解。
$$
d(i,V'+{i})=\min_{k\in V'}\left\{d(k,V')+C_{ki}\right\}
$$
3.最后的求解方式为:
$$
Answer = \min_{i\in S}\left\{ d(i,S)+c_{is} \right\}\quad其中S为所有点的集合
$$
&emsp;&emsp;状态转移方程就是上文所述，但是还有一个问题，我们如何存储点集这个状态？显然是无法用set作为dp数组的下标的。因此，这里我们使用状态压缩，也就是用一个整数来表示一个点集，当(state&(1<<i))为1时表示点i在集合里。

&emsp;&emsp;在存储状态的同时，我们也能够把tsp路径存储起来。过程就是在状态转移的同时附加了路径的传递（用vector实现）

## c++代码

&emsp;&emsp;算法的时间复杂度：$o(n^22^n)$  ，空间复杂度$o(n^22^n)$，如果存储路径的话空间复杂度为$o(n^32^n)$

输入：in.txt  (第一行为点的个数n   后面n行为每个点的id，以及坐标位置。两个点的距离为欧几里得距离)

```
16
A 2.5 4.0
B 1.2 -2.4
C 8.7 1.2
D 3.6 12.1
E -5.5 0.94
F -6.6 -12.6
G 0.18 5.219
H 12.5 14.3609
I 22.5 -5.26
J 1.61 4.5
K 2.1 -5.6
L 0 25
M 9.2 -32
N -1 7
O -5 -8
P 21 35
```

代码：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 18;
const double PI = acos(-1);
const int mod = 1e9 + 7;
using namespace std;
// 定义常量
const int INF = 0x3f3f3f3f;
#define sqr(x) ((x) * (x))
// 定义变量
int type; // type == 1 满秩矩阵格式, type == 2 二维坐标式
int s;
int N; // 城市结点数量
int init_point;
double dp[1 << maxn][maxn];
// 动态规划状态数组dp[i][j]，i表示集合V’，j表示当前到达的城市结点
double dis[maxn][maxn]; // 两个城市结点之间的距离
vector<int> path[1 << maxn][maxn];
double ans;
vector<int> ans_path;
// 定义结构体
struct vertex {
    double x, y; // 城市结点的坐标
    string id;   // 城市结点的id
    void input() {
        cin >> id;
        scanf("%lf %lf", &x, &y);
    }
} node[maxn];

double Dist(const vertex &a, const vertex &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void init() { // 数据初始化
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        node[i].input();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            dis[i][j] = Dist(node[i], node[j]); // 计算城市之间的距离
    }
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j < N; j++)
            dp[i][j] = INF,path[i][j].clear();
    } // 初始化，除了dp[1][0]，其余值都为INF
    ans = INF;
    return;
}
//复杂度 2^N * N^2
void slove() {
    int M = (1 << N);
    // M就是第四部分所说的V’状态总数，1<<N表示2^N，总共有2^N种状态
    dp[1][0] = 0;
    path[1][0].push_back(0);
    // 假设固定出发点为0，从0出发回到0的花费为0。TSP只要求是一个环路，所以出发点可以任选
    for (int i = 1; i < M; i++) {
        // 枚举V’的所有状态
        for (int j = 1; j < N; j++) {
            // 选择下一个加入集合的城市
            if (i & (1 << j))
                continue;
            // 城市已经存在于V’之中
            if (!(i & 1))
                continue;
            // 出发城市固定为0号城市
            for (int k = 0; k < N; k++) {
                // 在V’这个城市集合中尝试每一个结点，并求出最优解
                if (i & (1 << k)) {
                    // 确保k已经在集合之中并且是上一步转移过来的结点
                    if(dp[i][k] + dis[k][j] < dp[(1 << j) | i][j]){
                        dp[(1 << j) | i][j] = dp[i][k] + dis[k][j];
                        path[(1 << j) | i][j] = path[i][k];
                        path[(1 << j) | i][j].push_back(j);
                    }
                    dp[(1 << j) | i][j] = min(dp[(1 << j) | i][j],
                                              dp[i][k] + dis[k][j]); // 转移方程
                } // 将j点加入到i集合中
            }
        }
    }
    for (int i = 0; i < N; i++){
        if(dp[M - 1][i] + dis[i][0]< ans){
            ans=dp[M - 1][i] + dis[i][0];
            ans_path = path[M-1][i];
        }
    }
    // 因为固定了出发点，所以要加上到城市0的距离。另外要从所有的完成整个环路的集合V’中选择，完成最后的转移
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    init();
    slove();
    cout<<"TSP路径长度: "<<ans<<endl<<"TSP回路： ";
    for(int i=0;i<ans_path.size();i++){
        if(i)cout<<' ';
        cout<<node[ans_path[i]].id;
    }cout<<endl;
    return 0;
}
```

输出结果：

```
TSP路径长度: 186.161
TSP回路： A J G N D L P H C I M F O K B E
```



## TSP问题的启发式解法

&emsp;&emsp;不难看出，动态规划解tsp问题得到的一定是最优解，但是该算法的时间复杂度过高，因此当n的规模超过20多的时候，该算法可能就会超时了。解决大规模tsp问题时，我们往往使用的是启发式算法，得到一个比较好的结果。常用的算法有：蒙特卡洛法，模拟退火，消圈法，蚁群算法，遗传算法等。。。