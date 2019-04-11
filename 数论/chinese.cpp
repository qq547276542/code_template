typedef long long LL;
LL exgcd(LL a,LL b,LL &x,LL &y){
	  if(a==0&&b==0) return -1;
	  if(b==0) { x=1;y=0; return a;  }
	  LL d=exgcd(b,a%b,y,x);
	  y-=a/b*x;
	  return d;
}
int m[10],a[10];  //存方程组,模数为m,余数为a,即 X%m=a  (X是我们要求的)
bool solve(int &m0,int &a0,int m,int a){
	  LL y,x;
	  int g=exgcd(m0,m,x,y);
	  if(abs(a-a0)%g) return false;  //注意使用cstdlib中的abs()
	  x*=(a-a0)/g;
	  x%=m/g;
	  a0=(x*m0+a0);
	  m0*=m/g;
	  a0%=m0;
	  if(a0<0)a0+=m0;
	  return true;
}
/*
无解返回false ,有解返回true
解的形式最后为 a0+m0*t (0<=a0<m0)
*/
int m0,a0;
bool MLES(int &m0,int &a0,int n){  //解为 X=a0+m0*k
	bool flag =true;
	m0=1;
	a0=0;
	for(int i=0;i<n;i++){
		 if(!solve(m0,a0,m[i],a[i])){
		  flag=false;
		  break;
		 }
	}
	return flag;
}
