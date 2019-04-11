//模板
long long dp[1005][1005];
long long f(int n,int m){  //返回和为n，每个数不超过m的划分个数    n,m都不能为0
	if(dp[n][m])
		return dp[n][m];
	if(n==1||m==1) return dp[n][m]=1;
	if(m>n)
		return dp[n][m]=f(n,n);
	else if(m==n)
		return dp[n][m]=f(n,m-1)+1;
	else if(m<n)
		return dp[n][m]=f(n,m-1)+f(n-m,m);
}
void init(){
	memset(dp,0,sizeof(dp));
}
