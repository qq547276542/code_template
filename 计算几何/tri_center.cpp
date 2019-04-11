 //过三点求圆心坐标（三角形外心）
Point waixin(Point a,Point b,Point c) {
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1)/2;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2)/2;
	double d = a1*b2 - a2*b1;
	return Point(a.x + (c1*b2 - c2*b1)/d, a.y + (a1*c2 -a2*c1)/d);
}

//两个圆相交的公共部分面积
double Area_of_overlap(Point c1,double r1,Point c2,double r2) {
	double d = dist(c1,c2);
	if(r1 + r2 < d + eps)return 0;
	if(d < fabs(r1 - r2) + eps) {
		double r = min(r1,r2);
		return PI*r*r;
	}
	double x = (d*d + r1*r1 - r2*r2)/(2*d);
	double t1 = acos(x / r1);
	double t2 = acos((d - x)/r2);
	return r1*r1*t1 + r2*r2*t2 - d*r1*sin(t1);
}
 