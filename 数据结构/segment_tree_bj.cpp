# define N 100100
int e;  //记录横坐标个数,注意主函数里不要有同名变量
struct node1
{
	double x,y1,y2;
	int f;
} line[N*2];
struct node2
{
	double rf,lf,cnt,incnt;  //求矩形交可以没有cnt，求矩形并可以没有incnt
	int l,r,c;
} tree[N*5];
double y[N*2];
int cmp1(const void *a,const void *b)
{
	struct node1 *c=(struct node1*)a;
	struct node1 *d=(struct node1*)b;
	if(c->x == d->x) return c->f - d->f;
	return c->x > d->x ? 1 : -1;
}
int cmp2(const void *a,const void *b)
{
	return *(double *)a > *(double *)b ? 1 : -1;
}
void bulid(int t,int l,int r)
{
	int mid;
	tree[t].c=0;
	tree[t].cnt=0;
	tree[t].incnt=0;
	tree[t].l=l;
	tree[t].r=r;
	tree[t].lf=y[l];
	tree[t].rf=y[r];
	if(l+1==r) return;
	mid=(l+r)/2;
	bulid(2*t,l,mid);
	bulid(2*t+1,mid,r);
}
void calen(int t)  //求矩形并才需要加该函数
{
	if(tree[t].c>0)
	{
		tree[t].cnt=tree[t].rf-tree[t].lf;
		return ;
	}
	if(tree[t].l+1==tree[t].r) tree[t].cnt=0;
	else tree[t].cnt=tree[2*t].cnt+tree[2*t+1].cnt;
}
void incalen(int t)  //求矩形交才需要加该函数
{
	if(tree[t].c>=2)
	{
		tree[t].incnt=tree[t].rf-tree[t].lf;
		return;
	}
	if(tree[t].l+1==tree[t].r) tree[t].incnt=0;
	else if(tree[t].c==1)
	{
		tree[t].incnt=tree[2*t].cnt+tree[2*t+1].cnt;
	}
	else tree[t].incnt=tree[2*t].incnt+tree[2*t+1].incnt;
}
void updata(int t,node1 e)
{
	node1 tmp;
	if(e.y1==tree[t].lf && e.y2==tree[t].rf)
	{
		tree[t].c+=e.f;
		calen(t);
		incalen(t);
		return;
	}
	if(e.y2<=tree[2*t].rf) updata(2*t,e);
	else if(e.y1>=tree[2*t+1].lf) updata(2*t+1,e);
	else
	{
		tmp=e;
		tmp.y2=tree[2*t].rf;
		updata(2*t,tmp);
		tmp=e;
		tmp.y1=tree[2*t+1].lf;
		updata(2*t+1,tmp);
	}
	calen(t);
	incalen(t);
}
void init()  //初始化
{
	e=1;
}
void add_rectange(double x1,double y1,double x2,double y2)  //添加矩形的左下角和右上角坐标
{
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
void add_ok()  //添加完所有矩形后执行
{
	qsort(line+1,e-1,sizeof(line[1]),cmp1);
	qsort(y+1,e-1,sizeof(y[1]),cmp2);
	bulid(1,1,e-1);
}
double bin_Area()  //返回矩形并面积
{
	double ans=0;
	for(int i=1; i<e; i++)
	{
		ans+=tree[1].cnt*(line[i].x - line[i-1].x);
		updata(1,line[i]);
	}
	return ans;
}
double jiao_Area()  //返回矩形交面积
{
	double ans=0;
	for(int i=1; i<e; i++)
	{
		ans+=tree[1].incnt*(line[i].x - line[i-1].x);
		updata(1,line[i]);
	}
	return ans;
}
double bin_jian_jiao_Area()  //返回矩形并减矩形交的面积
{
	double ans=0;
	for(int i=1; i<e; i++)
	{
		ans+=tree[1].cnt*(line[i].x - line[i-1].x);
		ans-=tree[1].incnt*(line[i].x - line[i-1].x);
		updata(1,line[i]);
	}
	return ans;
}
