//**********************************************
// pollard_rho 算法进行质因素分解
// 需要用到Miller-Rabin素数测试的代码
//
//*********************************************
long long factor[100];//质因素分解结果（刚返回时时无序的）
int tol;//质因素的个数，编号0~tol-1
long long gcd(long long a,long long b) {
	long long t;
	while(b) {
		t = a;
		a = b;
		b = t%b;
	}
	if(a >= 0)return a;
	else return -a;
}
 
//找出一个因子
long long pollard_rho(long long x,long long c) {
	long long i = 1, k = 2;
	srand(time(NULL));
	long long x0 = rand()%(x-1) + 1;
	long long y = x0;
	while(1) {
		i ++;
		x0 = (mult_mod(x0,x0,x) + c)%x;
		long long d = gcd(y - x0,x);
		if( d != 1 && d != x)return d;
		if(y == x0)return x;
		if(i == k) {
			y = x0;
			k += k;
		}
	}
}
//对 n进行素因子分解，存入factor. k设置为107左右即可
void findfac(long long n,int k) {
	if(n == 1)return;
	if(Miller_Rabin(n)) {
		factor[tol++] = n;
		return;
	}
 
 
	long long p = n;
	int c = k;
	while( p >= n)
		p = pollard_rho(p,c--);//值变化，防止死循环k
	findfac(p,k);
	findfac(n/p,k);
}
//POJ 1811
//给出一个N(2 <= N < 2^54),如果是素数，输出"Prime",否则输出最小的素因子
int main() {
	int T;
	long long n;
	scanf("%d",&T);
	while(T--) {
		scanf("%I64d",&n);
		if(Miller_Rabin(n))printf("Prime\n");
		else {
			tol = 0;
			findfac(n,107);
			long long ans = factor[0];
			for(int i = 1; i < tol; i++) ans = min(ans,factor[i]);
			printf("%I64d\n",ans);
		}
	}
	return 0;
}

