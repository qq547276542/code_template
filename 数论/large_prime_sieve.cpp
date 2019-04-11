//POJ2689. 给出一个区间[L, R]，找出区间内容、相邻的距离最近的两个素数和距离最远的两个素数。
//
//我们可以通过2次筛法，第一次先筛选出素数表，第二次通过素数表再筛选出[L,R]之间的素数
//
//注意因为L和R的值非常大，但是R-L是小于1e6的，所以我们可以开一个vis2数组，然后将存放区间是否为合数的vis[L,R]映射到vis2[0,R-L](也就是向左偏移L个单位)

#include<vector>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 1000010;
const int maxp=100010;
int vis[maxn];
int prime[maxp];
int m;
void sieve(int n) {
	int m=(int) sqrt(n+0.5);
	memset(vis,0,sizeof(vis));
	for(int i=2; i<=m; i++) if(!vis[i])
			for(int j=i*i; j<=n; j+=i) vis[j]=1;
}
int gen_primes(int n) {
	sieve(n);
	int c=0;
	for(int i=2; i<=n; i++) if(!vis[i])
			prime[c++]=i;
	return c;
}
int vis2[1000007];
int minn,maxx;
int l1,r1,l2,r2;
bool sieve2(int L,int R) {   //2次筛法，用素数筛区间中的素数
	if(L==1)L++;
	memset(vis2,0,sizeof(vis2));   //vis2[i]=1代表i+L为合数
	for(int i=0; (long long)prime[i]*prime[i]<=R; i++) {
		int k=L/prime[i];
		if(k<=1)k=2;    //j直接从大于等于L的第一个素数开始
		for(long long j=(long long)prime[i]*k; j<=R; j+=prime[i]) {
			vis2[j-L]=1;
		}
	}
	vector<int> vec;
	for(int i=0; i<=R-L; i++) {
		if(!vis2[i])vec.push_back(i+L);
	}
	if(vec.size()<=1) {
		return false;
	}
	for(int i=1; i<vec.size(); i++) {
		int c=vec[i]-vec[i-1];
		if(c>maxx) {
			maxx=c;
			l2=vec[i-1],r2=vec[i];
		}
		if(c<minn) {
			minn=c;
			l1=vec[i-1],r1=vec[i];
		}
	}
	return true;
}
int L,R;
int main() {
	m=gen_primes(maxn-1);
	while(cin>>L>>R) {
		minn=0x7fffffff;
		maxx=0;
		if( sieve2(L,R)) {
			printf("%d,%d are closest, %d,%d are most distant.\n",l1,r1,l2,r2);
		} else {
			printf("There are no adjacent primes.\n");
		}
	}
	return 0;
}

