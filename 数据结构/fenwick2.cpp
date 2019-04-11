const int MAXH=107,MAXW=107;
struct Fenwick {
	int W,H;
	int mat[MAXH][MAXW];
	void init(int w,int h){   //初始化矩阵
		 memset(mat,0,sizeof(mat));
		 W=w,H=h;
	}
	int lowbit(int x) {
		return x&-x;
	}
	void add(int x, int y, int d) {
		for(int i = x; i < W; i += lowbit(i))
			for(int j = y; j < H; j += lowbit(j))
				mat[i][j] += d;
	}
	long long sum(int x, int y) {
		long long res = 0;
		int i, j;
		for(i = x; i > 0; i -= lowbit(i))
			for(j = y; j > 0; j -= lowbit(j))
				res += mat[i][j];
		return res;
	}
}fenwick;
int main() {
	fenwick.init(20,20);
	fenwick.add(2,2,5);
	cout<<fenwick.sum(3,3);
	return 0;
}
