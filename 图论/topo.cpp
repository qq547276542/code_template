int G[maxn][maxn],indegree[maxn],topo[maxn],n,m;     //topo[]可打印topo排序
void Addedge(int u,int v)    //添加有向边u->v
{
	G[u][v]=1;
	indegree[v]++;    //终点入度+1
}
void init()    //初始化边和入度
{
	memset(G,0,sizeof(G));
	memset(indegree,0,sizeof(indegree));
}
int TopoSort() //拓扑排序    return 1(有确定的topo排序)  -1（有多个topo排序，不确定） 0（存在有向环，不存在topo排序）
{
	int c=0,temp[maxn],loc,k,flag=1,i,j;  ////flag=1:有序 flag=-1:不确定
	for(i=1; i<=n; i++)
		temp[i]=indegree[i];
	for(i=1; i<=n; i++)
	{
		k=0;
		for(j=n; j>=1; j--)
			if(temp[j]==0)
			{
				k++;    //查找入度为零的顶点个数
				loc=j;
			}
		if(k==0) return 0;  //有环
		if(k>1) flag=-1;  // 无序
		topo[c++]=loc;   //入度为零的点入队
		temp[loc]=-1;
		for(j=1; j<=n; j++)
			if(G[loc][j]==1) temp[j]--;
	}
	return flag;
}
