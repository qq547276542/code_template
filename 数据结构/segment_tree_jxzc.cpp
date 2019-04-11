# define N 5005
int e;
struct node1 {
	int x,y1,y2;
	int f;
} line[2*N];
struct node2 {
	int l,r;
	int lf,rf;/*左右区间所对应的y值*/
	int cnt;/*节点上线段的测度*/
	int count;/*节点被线段完全覆盖的次数*/
	int lines;/*节点上所包含的线段的段数*/
	int lb,rb;/*节点的左右端点是否被覆盖*/
} tree[4*N];
int y[2*N];
int cmp1(const void *a,const void *b) {
	struct node1*c=(struct node1 *)a;
	struct node1*d=(struct node1 *)b;
	if(c->x!=d->x) return c->x - d->x;
	return d->f - c->f;/*先入 再出*/
}
int cmp2(const void *a,const void *b) {
	return *(int *)a - *(int *)b;
}
void bulid(int t,int l,int r) {
	int mid;
	tree[t].lines=0;
	tree[t].cnt=0;
	tree[t].count=0;
	tree[t].lb=tree[t].rb=0;
	tree[t].l=l;
	tree[t].r=r;
	tree[t].lf=y[l];
	tree[t].rf=y[r];
	if(l+1==r) return;
	mid=(l+r)/2;
	bulid(2*t,l,mid);
	bulid(2*t+1,mid,r);
}
void calen(int t) {
	if(tree[t].count>0) {
		tree[t].cnt=tree[t].rf-tree[t].lf;
		tree[t].lines=1;
		return;
	}
	if(tree[t].l+1==tree[t].r) {
		tree[t].cnt=0;
		tree[t].lines=0;
	} else {
		tree[t].cnt=tree[2*t].cnt+tree[2*t+1].cnt;
		tree[t].lines=tree[2*t].lines+tree[2*t+1].lines;
		if(tree[2*t].rb!=0&&tree[2*t+1].lb!=0) tree[t].lines--;
	}
}
void updata(int t,node1 e) {
	node1 tmp;
	if(tree[t].lf==e.y1) tree[t].lb+=e.f;
	if(tree[t].rf==e.y2) tree[t].rb+=e.f;
	if(tree[t].lf==e.y1 && tree[t].rf==e.y2) tree[t].count+=e.f;
	else if(e.y2<=tree[2*t].rf) updata(2*t,e);
	else if(e.y1>=tree[2*t+1].lf) updata(2*t+1,e);
	else {
		tmp=e;
		tmp.y2=tree[2*t].rf;
		updata(2*t,tmp);
		tmp=e;
		tmp.y1=tree[2*t+1].lf;
		updata(2*t+1,tmp);
	}
	calen(t);
}
void init() { //初始化
	e=1;
}
void add_rectangle(double x1,double y1,double x2,double y2) { //添加矩形左下角和右上角
	line[e].x=x1;
	line[e].y1=y1;
	line[e].y2=y2;
	line[e].f=1;
	y[e]=y1;
	e++;
	line[e].x=x2;
	line[e].y1=y1;
	line[e].y2=y2;
	line[e].f=-1;
	y[e]=y2;
	e++;
}
void add_ok() { //添加完毕后调用
	qsort(line+1,e-1,sizeof(line[1]),cmp1);
	qsort(y+1,e-1,sizeof(y[1]),cmp2);
	int ys=2;
	for(int i=2; i<e; i++) {
		if(y[i]!=y[i-1]) {
			y[ys]=y[i];
			ys++;
		}
	}/*去除y坐标相同的*/
	bulid(1,1,ys-1);
}
int perimeter() { //返回矩形周长
	int ans=0,lastlen=0,lines=0;
	for(int i=1; i<e; i++) {

		updata(1,line[i]);
		if(i!=1) ans+=lines*(line[i].x - line[i-1].x)*2;
		ans+=abs(lastlen - tree[1].cnt);
		lastlen=tree[1].cnt;
		lines=tree[1].lines;
	}
	return ans;
}
