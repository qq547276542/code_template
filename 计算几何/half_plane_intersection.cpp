///////////////////////////////////////////////////////////////////////////////////////////////
struct Line {       //定义直线类型
	Point P;    // 直线上任意一点
	Vector v;   // 方向向量
	double ang; // 极角，即从x正半轴旋转到向量v所需要的角（弧度）
	Line() {}
	Line(Point P, Vector v):P(P),v(v){ ang = atan2(v.y, v.x); }
	bool operator < (const Line& L) const {
		return ang < L.ang;
	}
};
 
// 点p在有向直线L的左边（线上不算）
bool OnLeft(const Line& L, const Point& p) {
	return Cross(L.v, p-L.P) > 0;
}
 
// 二直线交点，假定交点惟一存在
Point GetLineIntersection(const Line& a, const Line& b) {
	Vector u = a.P-b.P;
	double t = Cross(b.v, u) / Cross(a.v, b.v);
	return a.P+a.v*t;
}
 
const double INF = 1e8;
// 半平面交主过程
Point ansPoly[maxn];  //半平面交的多边形点集
int HalfplaneIntersection(vector<Line> L) {   //L为切割平面的直线集合，求半平面交，返回点的个数，点存在anspoly数组中
	int n = L.size();
	sort(L.begin(), L.end()); // 按极角排序
	int first, last;         // 双端队列的第一个元素和最后一个元素的下标
	vector<Point> p(n);      // p[i]为q[i]和q[i+1]的交点
	vector<Line> q(n);       // 双端队列
	q[first=last=0] = L[0];  // 双端队列初始化为只有一个半平面L[0]
	for(int i = 1; i < n; i++) {
		while(first < last && !OnLeft(L[i], p[last-1])) last--;
		while(first < last && !OnLeft(L[i], p[first])) first++;
		q[++last] = L[i];
		if(fabs(Cross(q[last].v, q[last-1].v)) < eps) { // 两向量平行且同向，取内侧的一个
			last--;
			if(OnLeft(q[last], L[i].P)) q[last] = L[i];
		}
		if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
	}
	while(first < last && !OnLeft(q[first], p[last-1])) last--; // 删除无用平面
	if(last - first <= 1) return 0; // 空集，0个点
	p[last] = GetLineIntersection(q[last], q[first]); // 计算首尾两个半平面的交点
	// 从deque复制到输出中
	int index=0;
	for(int i = first; i <= last; i++) ansPoly[index++]=p[i];
	return index;
}
