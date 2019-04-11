const int MAXN=500010;
int a[MAXN],b[MAXN];

//用二分查找的方法找到一个位置，使得num>b[i-1] 并且num<b[i],并用num代替b[i]

int Search(int num,int low,int high){
	int mid;
	while(low<=high){
		mid=(low+high)/2;
		if(num>=b[mid]) low=mid+1;
		else high=mid-1;
	}
	return low;
}

int DP(int n){
	int i,len,pos;
	b[1]=a[1];
	len=1;
	for(i=2;i<=n;i++){
		if(a[i]>=b[len])//如果a[i]比b[]数组中最大还大直接插入到后面即可
		{
			len=len+1;
			b[len]=a[i];
		}
		else//用二分的方法在b[]数组中找出第一个比a[i]大的位置并且让a[i]替代这个位置
		{
			pos=Search(a[i],1,len);
			b[pos]=a[i];
		}
	}
	return len;
}