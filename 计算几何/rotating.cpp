////////////////旋转卡壳//////////////////////// 
double Rotating_calipers(Point p[],int n) {      // 旋转卡壳，输入凸多边形,输出最远点对的平方
	if(n==1) return 0;
	if(n==2) return Dist2(p[0], p[1]);
	p[n]=p[0]; // 免得取模
	double ans=0;
	for(int u=0,v=1;u<n;u++){
		for(;;){
			double diff = Cross(p[u+1]-p[u],p[v+1]-p[v]);
			if(diff<=0){
				ans=max(ans,Dist2(p[u],p[v])); // u和v是对踵点
				if(diff==0) ans=max(ans,Dist2(p[u],p[v+1])); // diff == 0时u和v+1也是对踵点
				break;
			}
			v=(v+1)%n;
		}
	}
	return ans;
}
