```cpp
const int maxn = 1024;
struct KM {
	int n;                // X 的大小
	int weight [maxn][maxn];        // X 到 Y 的映射（权重）
	int lx[maxn], ly[maxn];        // 标号
	bool sx[maxn], sy[maxn];    // 是否被搜索过
	int match[maxn];        // Y(i) 与 X(match [i]) 匹配
	void init (int size) {   // 初始化权重
		// 根据实际情况，添加代码以初始化
		n = size;
		memset(weight,0,sizeof(weight));
	}
	void add_edge(int left,int right,int W) {
		weight[left][right]=W;
	}
	bool path (int u) { //从 X(u) 寻找增广道路，找到则返回 true
		sx [u] = true;
		for (int v = 0; v < n; v ++)
			if (!sy [v] && lx[u] + ly [v] == weight [u][v]) {
				sy [v] = true;
				if (match [v] == -1 || path (match [v])) {
					match [v] = u;
					return true;
				}
			}
		return false;
	}
	int bestmatch (bool maxsum) {    // 参数 maxsum 为 true ，返回最大权匹配，否则最小权匹配
		int i, j;
		if (!maxsum) {
			for (i = 0; i < n; i ++)
				for (j = 0; j < n; j ++)
					weight [i][j] = -weight [i][j];
		}
		for (i = 0; i < n; i ++) {  // 初始化标号
			lx [i] = -0x1FFFFFFF;
			ly [i] = 0;
			for (j = 0; j < n; j ++)
				if (lx [i] < weight [i][j])
					lx [i] = weight [i][j];
		}
		memset (match, -1, sizeof (match));
		for (int u = 0; u < n; u ++)
			while (1) {
				memset (sx, 0, sizeof (sx));
				memset (sy, 0, sizeof (sy));
				if (path (u))
					break;
				int dx = 0x7FFFFFFF;    // 修改标号
				for (i = 0; i < n; i ++)
					if (sx [i])
						for (j = 0; j < n; j ++)
							if(!sy [j])
								dx = min (lx[i] + ly [j] - weight [i][j], dx);
				for (i = 0; i < n; i ++) {
					if (sx [i])
						lx [i] -= dx;
					if (sy [i])
						ly [i] += dx;
				}
			}
		int sum = 0;
		for (i = 0; i < n; i ++)
			sum += weight [match [i]][i];
		if (!maxsum) {
			sum = -sum;
			for (i = 0; i < n; i ++)
				for (j = 0; j < n; j ++)
					weight [i][j] = -weight [i][j];         // 如果需要保持 weight [ ][ ] 原来的值，这里需要将其还原
		}
		return sum;
	}
} km;
```

正式的定义，网上一大把，但他们的作用是让人看不懂……
**二分图**：把点分成两个集合X,Y，使得图的边的两个端点总是分别落在X和Y上，不会有X中的点连向X中的点，不会有Y中的点连向Y中的点

**匹配**：实质上是二分图中的一个边集，边集中出现的点不会重合，比如有a-b了，就不会有a-c了，要是有了a就重合了

**最大匹配**：这个边集的数目最大的那个匹配

匈牙利算法——

**增广路**：一条在X和Y之间交错的路径，【这条路上一条是匹配边，一条不是匹配边】，如此相交错，
其中第一条和最后一条边不是匹配边，（所以增广路的长度一定为奇数，不是匹配边的数目比是匹配边的数目多1），

按matrix67的神说法，当我们把这条路上不是匹配边的那些换成要匹配的，原来是匹配的换成不要匹配的，匹配数就+1

所以当有增广路存在时说明匹配数可以再增大

二分图中最小点覆盖等于最大匹配数

**最小点覆盖**：实质是个点集，点集里面的点能覆盖所有的边，最小点覆盖就是满足这个要求的点集中点数最小的那个

证明：所有的边分为匹配的（A）边和不是匹配的边（B），最小点覆盖的点集就是要每条匹配的边两端顶点中的一个，
比如现在有x1-y1属于A，x1-y2属于B，对于x1-y1这条匹配边取x1而不取y1，这样就能覆盖到x1-y2，即B也能覆盖到

**二分图中最小边覆盖=顶点数-最小点覆盖（最大匹配）**

**最小边覆盖**：实质是个边集，这个集合里的边能覆盖所有的点，最小边覆盖是满足这个要求的所有边集中边数最少的一个
这里顶点数等于总的顶点数，是二分图两边的顶点数，不是一边

证明：设最大匹配数为m，总顶点数为n。为了使边数最少，又因为一条边最多能干掉两个点，所以尽量用边干掉两个点
也就是取有匹配的那些边，当然这些边是越多越好，那就是最大匹配了，所以先用最大匹配数目的边干掉大多数点
剩下的解决没有被匹配的点，就只能一条边干掉一个点了，设这些数目为a
显然，2m+a=n，而最小边覆盖=m+a，
所以最小边覆盖=（2m+a）-m=n-m

**最小路径覆盖**

最小路径覆盖(path covering)：是“路径” 覆盖“点”，即用尽量少的不相交简单路径覆盖有向无环图G的所有顶点，即每个顶点严格属于一条路径。路径的长度可能为0(单个点)。

**最小路径覆盖数＝原图G的顶点数－二分图的最大匹配数**