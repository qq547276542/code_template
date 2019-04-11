//例题为树链剖分+树状数组区间更新单点查询 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <vector>
using namespace std;
const int MAXN = 50010;
vector<int> G[MAXN];
int top[MAXN];//top[v] 表示v所在的重链的顶端节点
int fa[MAXN];//父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v] 表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v对应的位置
int fp[MAXN];//fp和p数组相反
int son[MAXN];//重儿子
int pos;
void init(int n) {
	for(int i=0; i<=n; i++)G[i].clear();
	pos = 1;//使用树状数组，编号从头1开始
	memset(son,-1,sizeof(son));
}
void dfs1(int u,int pre,int d) {   //第一遍dfs预处理各结点信息
	deep[u] = d;
	fa[u] = pre;
	num[u] = 1;
	for(int i=0; i<G[u].size(); i++) {
		int v = G[u][i];
		if(v != pre) {
			dfs1(v,u,d+1);
			num[u] += num[v];
			if(son[u]==-1||num[v]>num[son[u]])
				son[u] = v;
		}
	}
}
void getpos(int u,int sp) {   //获取p数组
	top[u] = sp;
	p[u] = pos++;
	fp[p[u]] = u;
	if(son[u] == -1) return;
	getpos(son[u],sp);
	for(int i=0; i<G[u].size(); i++) {
		int v = G[u][i];
		if( v != son[u] && v != fa[u])
			getpos(v,v);
	}
}
//树状数组
int lowbit(int x) {
	return x&(-x);
}
int c[MAXN];
int n;
int sum(int i) {
	int s = 0;
	while(i > 0) {
		s += c[i];
		i -= lowbit(i);
	}
	return s;
}
void add(int i,int val) {
	while(i <= n) {
		c[i] += val;
		i += lowbit(i);
	}
}
void Change(int u,int v,int val) { //u->v的路径上点的值改变val
//思路：成段更新每一条u，v之间的树链
	int f1 = top[u], f2 = top[v];
	int tmp = 0;
	while(f1 != f2) {   //不在同一条链上
		if(deep[f1] < deep[f2]) {    //先走顶端最深的链
			swap(f1,f2);
			swap(u,v);
		}
		add(p[f1],val);
		add(p[u]+1,-val);
		u = fa[f1];
		f1 = top[u];
	}
	if(deep[u] > deep[v]) swap(u,v);
	add(p[u],val);
	add(p[v]+1,-val);
}
int a[MAXN];
int main() {
	int M,P;
	while(scanf("%d%d%d",&n,&M,&P) == 3) {
		int u,v;
		int C1,C2,K;
		char op[10];
		init(n);
		for(int i = 1; i <= n; i++) {
			scanf("%d",&a[i]);
		}
		while(M--) {
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs1(1,0,0);
		getpos(1,1);
		memset(c,0,sizeof(c));
		for(int i = 1; i <= n; i++) {
			add(p[i],a[i]);
			add(p[i]+1,-a[i]);
		}
		while(P--) {
			scanf("%s",op);
			if(op[0] == 'Q') {
				scanf("%d",&u);
				printf("%d\n",sum(p[u]));
			} else {
				scanf("%d%d%d",&C1,&C2,&K);
				if(op[0] == 'D')
					K = -K;
				Change(C1,C2,K);
			}
		}
	}
	return 0;
}
