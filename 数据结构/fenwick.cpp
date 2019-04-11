const int maxn = 1e5 + 7;
struct BIT {
	int C[maxn];
	int n;
	void init(int n) {
		this->n = n;
		memset(C, 0, sizeof(maxn));
	}
	int lowbit(int x) { return x & -x; }
	int sum(int x) {
		int ret = 0;
		while (x > 0) {
			ret += C[x];
			x -= lowbit(x);
		}
		return ret;
	}
	void add(int x, int d) {
		while (x <= n) {
			C[x] += d;
			x += lowbit(x);
		}
	}
} bit;

