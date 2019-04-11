#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
const int INF=1<<30;
const int maxn=2000+10;
struct INtervalTree2D{  //2维线段树x轴y轴的下标均从1开始
	int Max[maxn][maxn],Min[maxn][maxn],Sum[maxn][maxn],n,m;
	int xo,xleaf,x1,y1,x2,y2,x,y,v,vmax,vmin,vsum;
	void query1D(int o,int L,int R){
		if(y1<=L&&R<=y2){
			vmax=max(Max[xo][o],vmax);vmin=min(Min[xo][o],vmin);
			vsum+=Sum[xo][o];
		}else{
			int M=L+(R-L)/2;
			if(y1<=M)query1D(o*2,L,M);
			if(M<y2)query1D(o*2+1,M+1,R);
		}
	}
	void query2D(int o,int L,int R){
		if(x1<=L&&R<=x2){xo=o;query1D(1,1,m);}
		else{
			int M=L+(R-L)/2;
			if(x1<=M)query2D(o*2,L,M);
			if(M<x2)query2D(o*2+1,M+1,R);
		}
	}
	void modify1D(int o,int L,int R){
		if(L==R){
			if(xleaf){Sum[xo][o]=Max[xo][o]=Min[xo][o]=v;return ;}
			Max[xo][o]=max(Max[xo*2][o],Max[xo*2+1][o]);
			Min[xo][o]=min(Min[xo*2][o],Min[xo*2+1][o]);
			Sum[xo][o]=Sum[xo*2][o]+Sum[xo*2+1][o];
		}else {
			int M=L+(R-L)/2;
			if(y<=M){modify1D(o*2,L,M);}
			else {modify1D(o*2+1,M+1,R);}
			Max[xo][o]=max(Max[xo][o*2],Max[xo][o*2+1]);
			Min[xo][o]=min(Min[xo][o*2],Min[xo][o*2+1]);
			Sum[xo][o]=Sum[xo][o*2]+Sum[xo][o*2+1];
		}
	}
	void modify2D(int o,int L,int R){
		if(L==R){xo=o;xleaf=1;modify1D(1,1,m);}
		else{
			int M=L+(R-L)/2;
			if(x<=M)modify2D(o*2,L,M);
			else modify2D(o*2+1,M+1,R);
			xo=o;xleaf=0;modify1D(1,1,m);
		}
	}
	void init_size(int h,int w)//设置矩阵的行数和列数
	{
		n=h;m=w;
	}
	void modify(int x,int y,int v){  //将(x,y)的值修改为v（初始化线段树也是用该函数，调用m*n次）
		this->x=x;this->y=y;this->v=v;
		modify2D(1,1,n);
	}
	void query(int x1,int y1,int x2,int y2){   //询问x1,y1,x2,y2间的最值，调用该函数后，vmax,vmin即为结果
		this->x1=x1;this->y1=y1;this->x2=x2;this->y2=y2;
		vmax=-INF;vmin=INF;vsum=0;
		query2D(1,1,n);
	}
}xdtree;
int main() {
	//  freopen("in.txt","r",stdin);
	int n,m;
	int x,y,v;
	cin>>n>>m;
	xdtree.init_size(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&v);
			xdtree.modify(i,j,v);
		}
		int q,x1,x2,y1,y2;
		cin>>q;
		char cas[3];
		while(q--){
			scanf("%s",cas);
			if(cas[0]=='q'){
				cin>>x1>>y1>>x2>>y2;
				xdtree.query(x1,y1,x2,y2);
				cout<<xdtree.vmax<<' '<<xdtree.vmin<<' '<<xdtree.vsum<<endl;
			}
			else{
				cin>>x>>y>>v;
				xdtree.modify(x,y,v);
			}
		}
		return 0;
}