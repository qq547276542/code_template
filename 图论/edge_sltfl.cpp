/*去掉桥，其余的连通分支就是边双连通分支了。一个有桥的连通图要变成边双连通图的话，把双连通子图
收缩为一个点，形成一颗树。通过遍历所有桥来统计缩点树的各结点度数，需要加的边为(leaf+1)/2(leaf 为叶子结点个数)*/

const int MAXN = 5010;//点数
const int MAXM = 20010;//边数，因为是无向图，所以这个值要*2
struct Edge {
	int to,next;
	bool cut;    //是否是桥标记*********
} edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong[i]代表i所属双连通块号数组的值是1~block
int Index,top;
int block;  //边双连通块数**********
bool Instack[MAXN];
int bridge;//桥的数目***********

void init() {  //加边前调用
	tot = 0;
	memset(head,-1,sizeof(head));
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	Index = top = block = 0;
}
void addedge(int u,int v) {   //添加无向边，调用一次即可，同时加了2条
	edge[tot].to = v;
	edge[tot].next = head[u];
	edge[tot].cut=false;
	head[u] = tot++;
	edge[tot].to = u;
	edge[tot].next = head[v];
	edge[tot].cut=false;
	head[v] = tot++;
}
void Tarjan(int u,int pre) {
	int v;
	Low[u] = DFN[u] = ++Index;
	Stack[top++] = u;
	Instack[u] = true;
	for(int i = head[u]; i != -1; i = edge[i].next) {
		v = edge[i].to;
		if(v == pre)continue;
		if( !DFN[v] ) {
			Tarjan(v,u);
			if( Low[u] > Low[v] )Low[u] = Low[v];
			if(Low[v] > DFN[u]) {
				bridge++;
				edge[i].cut = true;
				edge[i^1].cut = true;
			}
		} else if( Instack[v] && Low[u] > DFN[v] )
			Low[u] = DFN[v];
	}
	if(Low[u] == DFN[u]) {
		block++;
		do {
			v = Stack[--top];
			Instack[v] = false;
			Belong[v] = block;
		} while( v!=u );
	}
}
int du[MAXN];//缩点后形成树，每个点的度数
void solve(int n) {   //求解
	for(int i=1;i<=n;i++)
	if(!DFN[i])
	Tarjan(i,i);
}
