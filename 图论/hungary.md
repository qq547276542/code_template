### 匈牙利算法（邻接矩阵）

```c++
/* ***********************************************************
//二分图匹配（匈牙利算法的DFS实现）(邻接矩阵形式)
//初始化：g[][]两边顶点的划分情况
//建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
//g没有边相连则初始化为0
//uN是匹配左边的顶点数，vN是匹配右边的顶点数
//调用：res=hungary();输出最大匹配数
//优点：适用于稠密图，DFS找增广路，实现简洁易于理解
//时间复杂度:O(VE)
//*************************************************************/
//顶点编号从0开始的
const int MAXN = 510;
int uN,vN;//u,v的数目，使用前面必须赋值
int g[MAXN][MAXN];//邻接矩阵
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)
{
   for(int v = 0; v < vN;v++)
       if(g[u][v] && !used[v])
       {
          used[v] = true;
          if(linker[v] == -1 || dfs(linker[v]))
          {
              linker[v] = u;
              return true;
          }
       }
   return false;
}
int hungary()
{
   int res = 0;
   memset(linker,-1,sizeof(linker));
   for(int u = 0;u < uN;u++)
   {
     memset(used,false,sizeof(used));
     if(dfs(u))res++;
   }
   return res;
}

```

### 匈牙利算法（邻接表）

```c++
/*
 * 匈牙利算法邻接表形式
 * 使用前用init()进行初始化，给uN赋值
 * 加边使用函数addedge(u,v)
 *
 */
const int MAXN = 5010;//点数的最大值
const int MAXM = 50010;//边数的最大值
struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXN],tot;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edge[tot].to = v; edge[tot].next = head[u];
    head[u] = tot++;
}
int linker[MAXN];
bool used[MAXN];
int uN;
bool dfs(int u)
{
    for(int i = head[u]; i != -1 ;i = edge[i].next)
    {
       int v = edge[i].to;
       if(!used[v])
       {
           used[v] = true;
           if(linker[v] == -1 || dfs(linker[v]))
           {
              linker[v] = u;
              return true;
           }
       }
    }
    return false;
}
int hungary()
{
    int res = 0;
    memset(linker,-1,sizeof(linker));
    for(int u = 0; u < uN;u++)//点的编号0~uN-1
    {
	memset(used,false,sizeof(used));
	if(dfs(u))res++;
	}
	return res;
}

```

###  Hopcroft-Carp 算法

```c++
/* *******************************
 * 二分图匹配（Hopcroft-Carp算法）
 * 复杂度O(sqrt(n)*E)
 * 邻接表存图，vector实现
 * vector先初始化，然后假如边
 * uN 为左端的顶点数，使用前赋值(点编号0开始)
 */
const int MAXN = 3000;
const int INF = 0x3f3f3f3f;
vector<int>G[MAXN];
int uN;
int Mx[MAXN],My[MAXN];
int dx[MAXN],dy[MAXN];
int dis;
bool used[MAXN];
bool SearchP()
{
   queue<int>Q;
   dis = INF;
   memset(dx,-1,sizeof(dx));
   memset(dy,-1,sizeof(dy));
   for(int i = 0 ; i < uN; i++)
       if(Mx[i] == -1)
       {
          Q.push(i);
          dx[i] = 0;
       }
   while(!Q.empty())
   {
       int u = Q.front();
       Q.pop();
       if(dx[u] > dis)break;
       int sz = G[u].size();
       for(int i = 0;i < sz;i++)
       {
          int v = G[u][i];
          if(dy[v] == -1)
          {
              dy[v] = dx[u] + 1;
              if(My[v] == -1)dis = dy[v];
              else
              {
                 dx[My[v]] = dy[v] + 1;
                 Q.push(My[v]);
              }
          }
       }
   }
   return dis != INF;
}
bool DFS(int u)
{
   int sz = G[u].size();
   for(int i = 0;i < sz;i++)
   {
       int v = G[u][i];
       if(!used[v] && dy[v] == dx[u] + 1)
       {
          used[v] = true;
          if(My[v] != -1 && dy[v] == dis)continue;
          if(My[v] == -1 || DFS(My[v]))
          {
              My[v] = u;
              Mx[u] = v;
              return true;
          }
       }
   }
   return false;
}
int MaxMatch()
{
   int res = 0;
   memset(Mx,-1,sizeof(Mx));
   memset(My,-1,sizeof(My));
   while(SearchP())
   {
       memset(used,false,sizeof(used));
       for(int i = 0;i < uN;i++)
          if(Mx[i] == -1 && DFS(i))
              res++;
   }
   return res;
}
```

