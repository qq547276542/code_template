const int maxn=1e5+7;
int ufs[maxn];
int Find(int x) {
	if(ufs[x]<0) return x;
	return ufs[x]=Find(ufs[x]);   //查找根的同时进行路径压缩
}
void init() {
	memset(ufs,-1,sizeof(ufs));
} 
void U(int a, int b) {   //合并
	if((a=Find(a))==(b=Find(b))) return;
	ufs[a]+=ufs[b];
	ufs[b]=a;
}
int getNum(int a){   //并查集元素个数
	return -ufs[Find(a)];
}
