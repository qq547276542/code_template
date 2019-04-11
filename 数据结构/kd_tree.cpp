#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
typedef long long LL;
typedef pair<int, LL> PII;
typedef pair<int, int> pii;
const int maxn = 1000005;   //点的数量
const int maxD = 2;   //维数，根据题目维数修改此处
const int maxM = 12;
const LL INF = 4611686018427387903LL;
int now;
struct TPoint   //maxD维空间中的点
{
	int x[maxD];   //x[i]代表第i维坐标，从0开始
} p[maxn];
bool cmp(const TPoint& a, const TPoint& b)
{
	return a.x[now] < b.x[now];
}
template<typename T> T sqr(T n)
{
	return n * n;
}
struct KDtree  //kd树
{
	int K, n, top,num;
	int split[maxn];
	LL dis2[maxM];
	TPoint stk[maxn];
	TPoint kp[maxn];
	TPoint mp;
	void init_KDtree(){ num=0;}  //初始化
	void add_Point(TPoint p)  //初始化后向kd树中添加点
	{
		kp[num++]=p;
	}
	void build_KDtree()  //添加完所有点后构造kd树
	{
		n=num;  
		K=maxD;    
		build(0,n);
	}
	LL find_nearest(TPoint p)  //构造完kd树后，返回kd树中与点p距离最近的点与点p的距离
	{
		for (int i = 0; i < maxD; ++i)
		{
			dis2[i] = INF;
		}
		mp = p;
		nearest_search(0, n, maxD);
		return dis2[maxD-1];
	}
	void build(int l, int r)
	{
		if (l >= r)
			return;
		int i, j, mid = (l + r) >> 1;
		LL dif[maxD], mx;
		for (i = 0; i < K; ++i)
		{
			mx = dif[i] = 0;
			for (j = l; j < r; ++j)
				mx += kp[j].x[i];
			mx /= r - l;
			for (j = l; j < r; ++j)
				dif[i] += sqr(kp[j].x[i] - mx);
		}
		now = 0;
		for (i = 1; i < K; ++i)
			if (dif[now] < dif[i])
				now = i;
 
		split[mid] = now;
		nth_element(kp + l, kp + mid, kp + r, cmp);
		build(l, mid);
		build(mid + 1, r);
	}
	void update(const TPoint& p, int M)
	{
		int i, j;
		LL tmp = dist(p, mp);
		for (i = 0; i < M; ++i)
			if (dis2[i] > tmp)
			{
				for (j = M - 1; j > i; --j)
				{
					stk[j] = stk[j - 1];
					dis2[j] = dis2[j - 1];
				}
				stk[i] = p;
				dis2[i] = tmp;
				break;
			}
	}
	void nearest_search(int l, int r, int M)
	{
		if (l >= r)
			return;
		int mid = (l + r) >> 1;
		update(kp[mid], M);
		if (l + 1 == r)
			return;
		LL d = mp.x[split[mid]] - kp[mid].x[split[mid]];
		if (d <= 0)
		{
			nearest_search(l, mid, M);
			if (sqr(d) < dis2[M - 1])
				nearest_search(mid + 1, r, M);
		}
		else
		{
			nearest_search(mid + 1, r, M);
			if (sqr(d) < dis2[M - 1])
				nearest_search(l, mid, M);
		}
	}
	LL dist(const TPoint& a, const TPoint& b)
	{
		LL res = 0;
		for (int i = 0; i < K; ++i)
			res += sqr<LL>(a.x[i] - b.x[i]);
		return res;
	}
} KD;
