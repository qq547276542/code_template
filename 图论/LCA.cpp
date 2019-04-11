#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 10010;
int rmq[2*MAXN];//rmq数组，就是欧拉序列对应的深度序列
struct ST {
	int mm[2*MAXN];
	int dp[2*MAXN][20];//最小值对应的下标
	void init(int n) {
		mm[0] = -1;
		for(int i = 1; i <= n; i++) {
			mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
			dp[i][0] = i;
		}
		for(int j = 1; j <= mm[n]; j++)
			for(int i = 1; i + (1<<j) - 1 <= n; i++)
				dp[i][j] = rmq[dp[i][j-1]] <
						   rmq[dp[i+(1<<(j-1))][j-1]]?dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
	}
	int query(int a,int b) { //查询[a,b]之间最小值的下标
		if(a > b)swap(a,b);
		int k = mm[b-a+1];
		return rmq[dp[a][k]] <=
			   rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
	}
};
vector<int> G[MAXN];
int F[MAXN*2];//欧拉序列，就是dfs遍历的顺序，长度为2*n-1,下标从1开始
int P[MAXN];//P[i]表示点i在F中第一次出现的位置
int cnt;
ST st;
void dfs(int u,int pre,int dep) {
	F[++cnt] = u;
	rmq[cnt] = dep;
	P[u] = cnt;
	for(int i=0; i<G[u].size(); i++) {
		int v = G[u][i];
		if(v == pre)continue;
		dfs(v,u,dep+1);
		F[++cnt] = u;
		rmq[cnt] = dep;
	}
}
void LCA_init(int root,int n) { //查询LCA前的初始化
	cnt = 0;
	dfs(root,root,0);
	st.init(2*n-1);
}
int query_lca(int u,int v) { //查询u,v的lca编号
	return F[st.query(P[u],P[v])];
}
int main() {
	for(int i=0; i<10; i++)
		G[i].clear();
	G[1].push_back(2);
	G[2].push_back(1);
	G[1].push_back(3);
	G[3].push_back(1);
	G[2].push_back(4);
	G[4].push_back(2);
	G[5].push_back(2);
	G[2].push_back(5);
	G[4].push_back(6);
	G[6].push_back(4);
	LCA_init(1,7);   
	cout<<query_lca(6,6)<<endl;
	return 0;
}

