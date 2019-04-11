const int MAXV = 1 << 9;
int d[MAXV],v,w;
int m,n,V;  //背包大小为V，n种物品,每种物品m个
void ZeroOnePack( int* f, int C, int W) {  //01背包
	int v;
	for( v = V; v >= C; v --)
		f[v] = max( f[v], f[v - C] + W);
}
void CompletePack( int* f, int C, int W) {   //完全背包
	int v;
	for( v = C; v <= V; v ++)
		f[v] = max( f[v], f[v - C] + W);
}
void MultiplePack( int* f, int C, int W, int M) {  //多重背包
	int k = 1;
	if( C * M >= V) {
		CompletePack( f, C, W);
		return;
	}
	while( k < M) {
		ZeroOnePack(f, C * k, W * k);
		M = M - k;
		k <<= 1;
	}
	ZeroOnePack( f, C * M, W * M);
}
int main() {
	// freopen("in.txt","r",stdin);
	while(cin>>n>>V) {
		memset(d,0,sizeof(d));
		for(int i=0; i<n; i++) {
			scanf("%d%d%d",&m,&v,&w);
			MultiplePack(d,v,w,m);
		}
		cout<<d[V]<<endl;
	}
	return 0;
}
