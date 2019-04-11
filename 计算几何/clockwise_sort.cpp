Point center;
bool PointCmp(const Point &a,const Point &b)
{
	if (a.x >= 0 && b.x < 0)
		return true;
	if (a.x == 0 && b.x == 0)
		return a.y > b.y;
	//向量OA和向量OB的叉积
	int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det < 0)
		return true;
	if (det > 0)
		return false;
	//向量OA和向量OB共线，以距离判断大小
	int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	int d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);
	return d1 > d2;
}
bool Cmp(const Point &a,const Point &b){
	return !PointCmp(a,b);
}

Point Gravity(Point *p, int n) {  //返回多边形的重心
    double area = 0;
    Point center;
    center.x = 0;
    center.y = 0;
    for (int i = 0; i < n-1; i++) {
        area += (p[i].x*p[i+1].y - p[i+1].x*p[i].y)/2;
        center.x += (p[i].x*p[i+1].y - p[i+1].x*p[i].y) * (p[i].x + p[i+1].x);
        center.y += (p[i].x*p[i+1].y - p[i+1].x*p[i].y) * (p[i].y + p[i+1].y);
    }
    area += (p[n-1].x*p[0].y - p[0].x*p[n-1].y)/2;
    center.x += (p[n-1].x*p[0].y - p[0].x*p[n-1].y) * (p[n-1].x + p[0].x);
    center.y += (p[n-1].x*p[0].y - p[0].x*p[n-1].y) * (p[n-1].y + p[0].y);
    center.x /= 6*area;
    center.y /= 6*area;
    return center;
}
void ClockwiseSortPoints(Point* vPoints, int n)
{
	//计算重心
	center=Gravity(vPoints,n);
	sort(vPoints,vPoints+n,Cmp);
}

