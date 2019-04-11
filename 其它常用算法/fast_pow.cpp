int pow_mod(int a, int n, int m)
{
	long long ans = 1;
	while(n){
		if(n&1){
			ans = (ans * a) % m;
		}
		a = (a * a) % m;
		n >>= 1;
	}
	return ans;
}