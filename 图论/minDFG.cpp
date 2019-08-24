#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int INF = 2e9;
const int MAXN = 5e2+10;

int uN, vN;
int M[MAXN][MAXN], ulink[MAXN], vlink[MAXN];
bool vis[MAXN], uvis[MAXN], vvis[MAXN];

bool dfs(int u)
{
	for(int i = 1; i<=vN; i++)
	if(M[u][i] && !vis[i])
	{
		vis[i] = true;
		if(vlink[i]==-1 || dfs(vlink[i]))
		{
			vlink[i] = u;
			ulink[u] = i;
			return true;
		}
	}
	return false;
}

int hungary()
{
	int ret = 0;
	memset(ulink, -1, sizeof(ulink));
	memset(vlink, -1, sizeof(vlink));
	for(int i = 1; i<=uN; i++)
	{
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ret++;
	}
	return ret;
}

//从左边的未匹配点走一遍试找增广路的路径，但是却不可能找到增广路，否则最大匹配数会增加。
//路径上的首边必为未匹配边，尾边必为匹配边，且两种边交替出现。
void hungary_tree(int u)
{
	uvis[u] = true;
	for(int i = 1; i<=vN; i++)
	if(M[u][i] && !vvis[i])
	{
		vvis[i] = true;
		hungary_tree(vlink[i]);
	}
}

int main()
{
	int m;
	// uN vN分别为左侧点数和右侧点数
	while(cin>>uN>>m)
	{
		vN = uN;
		memset(M, false, sizeof(M));
		for(int i = 1; i<=m; i++)
		{
			int u, v;
			cin>>u>>v;
			if(u>v)
				swap(u,v);
			v-=uN;
			M[u][v] = true;        //因为u代表横坐标，v代表纵坐标.
			// 边只从左到右加一次
		}

		int cnt = hungary();
		cout<<cnt<<endl;

		memset(uvis, false, sizeof(uvis));
		memset(vvis, false, sizeof(vvis));
		for(int i = 1; i<=uN; i++) 
			if(ulink[i]==-1) 
				hungary_tree(i);
		
		vector<int> ans ;
		for(int i = 1; i<=uN; i++) if(!uvis[i]) ans.push_back(i);
		for(int i = 1; i<=vN; i++) if(vvis[i]) ans.push_back(i+uN);
				for(int i=0;i<ans.size();i++){
					if(i)cout<<' ';
					cout<<ans[i];
				}
		printf("\n");
	}
}