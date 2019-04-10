#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn=1007;
const int INF=0x7fffffff;
struct Edge {
	int from ,to, dist;
	Edge(int u,int v,int d):from(u),to(v),dist(d) {}
};
struct SPFA {
	int n,m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool visit[maxn];
	int d[maxn];
	int p[maxn];
	void init(int n) {
		this->n=n;
		for(int i=0; i<n; i++)G[i].clear();
		edges.clear();
	}
	void AddEdge(int from,int to,int dist) {
		edges.push_back(Edge(from,to,dist));
		m=edges.size();
		G[from].push_back(m-1);
	}
	void spfa(int s) {
		for(int i=1; i<=n; i++) {
			d[i] = INF;
		}
		queue<int> q;
		memset(visit,false,sizeof(visit));
		q.push(s);
		visit[s] = true;
		d[s] = 0;
		while(!q.empty()) {
			int u = q.front();
			visit[u] = false;
			for(int i=0; i<G[u].size(); i++) {
					Edge& e=edges[G[u][i]];
				if (d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					 //p[e.to] = u; 
					if( !visit[e.to] ) {
						visit[e.to] = true;
						q.push(e.to) ;
					}
				}
			}
			q.pop();
		}
	}
}sf;