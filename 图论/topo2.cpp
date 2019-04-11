const int maxn=1e3+7;
struct Topo {
	int indeg[maxn],n;
	vector<int> G[maxn],path;
	void init(int n) {
		this->n=n;
		for(int i=0; i<=n; i++)
			G[i].clear();
		memset(indeg,0,sizeof(indeg));
		path.clear();
	}
	void addEdge(int u,int v) {   //添加有向边
		G[u].push_back(v);
		indeg[v]++;
	}
	int topoSort() { //1 代表有topo序列   0代表序列不存在  -1代表序列不唯一
		queue<int> que;
		for(int i=1; i<=n; i++) {  //注意结点下标从1开始
			if(indeg[i]==0) {
				que.push(i);
			}
		}
		int sum=0,flag=0;
		while(!que.empty()) {
			int cur=que.front();
			path.push_back(cur);
			if(que.size()>1)flag=1;
			que.pop();
			sum++;
			for(int j=0; j<G[cur].size(); j++) {
				int id=G[cur][j];
				indeg[id]--;
				if(indeg[id]==0)
					que.push(id);
			}
		}
		if(sum<n)  return 0;
		if(flag)  return -1;
		return 1;
	}
} topo;

