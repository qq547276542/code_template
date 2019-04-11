int Next[100007];   //next 数组
int ans;
void getNext(char *p,int *next)  //构造next数组
{
		int j=0,k=-1;
		next[0]=-1;
		int  len=strlen(p);
		while(j<len)
		{
				if(k==-1||p[j]==p[k])    //匹配的情况下,p[j]==p[k]
				{
						j++;
						k++;
						next[j]=k;
				}
				else                   //p[j]!=p[k]
						k=next[k];
		}
}
int KMPMatch(char *s,char *p)   //返回p在s中第一次出现的位置
{
		int i=0,j=0;
		ans=0;
		getNext(p,Next);
		int len=strlen(s),len1=strlen(p);
		while(i<len)
		{
				if(j==-1||s[i]==p[j])
				{
						i++;
						j++;
				}
				else
				{
						j=Next[j];       //消除了指针i的回溯
				}
				if(j==len1)
				{
							return i-len1;
							// ans++;      若要返回子串出现次数，增加该语句，删除上一行的语句，返回ans既可
				}
 
		}
		return -1;
}
int low_xhj(char *s)   //返回最小循环节循环次数    字符串长度除以该值位最小循环节长度
{
		getNext(s,Next);
		int ln=strlen(s);
		if(ln%(ln-Next[ln])==0)
				return ln/(ln-Next[ln]);
				else
						return 1;
}
 
int d[1000007];
int prefixe_match(char *s,int mod) {                     //返回字符串s的所有前缀子串在字符串s中的出现次数，并与mod取模
		d[0]=0;                             //比如字符串abab  ,a出现2次,ab出现2次 ,aba与abab出现1次,返回6=2+2+1+1
		int sum=0;
		getNext(s,Next);
		int n=strlen(s);
		for(int i=1; i<=n; i++) {
				d[i]=1+d[Next[i]];
				sum=(sum+d[i])%mod;
		}
		return sum;
}
