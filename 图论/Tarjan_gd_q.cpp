#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int MAXN=10010,MAXM=100010;
//点的下标切记转换成由1~n
struct Edge{
   int to,next;
   bool cut;  //是否为桥的标记*******
}edge[MAXM];  //边数组
/*    遍历点u的临接边
	for(int i=head[u];i!=-1;i=edge[i].next)
	{   edge[i]      } //edge[i]即为边
*/
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN];
int Index,top;
bool Instack[MAXN];
bool cut[MAXN];    //是否为割点的标记*********
int add_block[MAXN];   //删除一个点后增加的连通块
int bridge;     //记录桥的个数*******
 
void init(){  //加边前先初始化
   memset(DFN,0,sizeof(DFN));
   memset(Instack,false,sizeof(Instack));
   memset(add_block,0,sizeof(add_block));
   memset(cut,false,sizeof(cut));
   memset(head,-1,sizeof(head));
   tot=Index=top=bridge=0;
}
 
void add_edge(int u,int v){  //添加无向边，只需调用一次！！！！！！！！！
	edge[tot].to=v;  edge[tot].next=head[u] ; edge[tot].cut=false;
	head[u]=tot++;
	edge[tot].to=u;  edge[tot].next=head[v] ; edge[tot].cut=false;
	head[v]=tot++;
}
 
void Tarjan(int u,int pre){
	int v;
  //  cout<<u<<" "<<pre<<endl;
	Low[u]=DFN[u]=++Index;
	Stack[top++]=u;
	Instack[u]=true;
	int son=0;
	for(int i=head[u];i!=-1;i=edge[i].next){
		 v=edge[i].to;
		 if(v==pre)continue;
		 if(!DFN[v]){     //如果没有访问过v
			son++;
			Tarjan(v,u);
			if(Low[u]>Low[v])Low[u]=Low[v];
			//判断无向边（u,v）是否是桥
			if(Low[v]>DFN[u]){
				bridge++;
				edge[i].cut=true;
				edge[i^1].cut=true;
			}
			//判断u是否为割点
			if(u!=pre&&Low[v]>=DFN[u]){
				cut[u]=true;
				add_block[u]++;
			}
		 }
		 else if(Low[u]>DFN[v])
			Low[u]=DFN[v];
	}
	if(u==pre&&son>1)cut[u]=true;
	if(u==pre)add_block[u]=son-1;
	Instack[u]=false;
	top--;
}
 
void solve(int N){  //  寻找割顶和桥,N为题目中结点数
	 for(int i=1;i<=N;i++)
	 if(!DFN[i])Tarjan(i,i);     //对于每一个连通分量都调用一次
}