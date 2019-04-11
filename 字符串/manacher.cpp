#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
const int maxn=300007;
char str[maxn];
int p[maxn<<1];
void manacher(char *s){   //求p数组
	int len=strlen(s);
	for(int i=len;i>=0;--i){
		s[i+i+2]=s[i];
		s[i+i+1]='#';   //如果字符串中有*和#，代码中需要替换符号
	}
	s[0]='*';
	int k=1,maxlen=0;
	for(int i=2;i<len+len+1;++i){
		int maxr=k+p[k]-1;
		p[i]=min(p[2*k-i],max(maxr-i+1,1));
		while(s[i-p[i]] == s[i+p[i]])++p[i];
		if(i+p[i]>k+p[k])k=i;
		if(p[i]>maxlen)maxlen=p[i];
	}
}
int getLongestPalindrome(char *s){    //得到p数组后，返回最长回文长度
	int len=strlen(s);
	int ans=0;
	for(int i=0;i<len-1;i++){
		 ans=max(ans,p[i]);
	}
	return ans-1;
}
int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~scanf("%s",str)){
		manacher(str);
		cout<<getLongestPalindrome(str)<<endl;
	}
	return 0;
}

/*
P［id］记录的是以字符str［id］为中心的最长回文串，当以str［id］为第一个字符，这个最长回文串向右延伸了P［id］个字符。
    原串：   waabwswfd
    新串：   # w # a # a # b # w # s # w # f # d #
 辅助数组P：  1 2 1 2 3 2 1 2 1 2 1 4 1 2 1 2 1 2 1
    这里有一个很好的性质，P［id］-1就是该回文子串在原串中的长度（包括‘#’）。*/