 const int maxnode=100003;
const int sigma_size=26;  //字符集大小,注意idx函数也要随着修改
struct Trie{
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz;
	void init()
	{
			sz=1;memset(ch[0],0,sizeof(ch[0]));
	}
	int idx(char c){ return c-'a';}
	void insert(char *s,int v){
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++){
				int c=idx(s[i]);
				if(!ch[u][c]){
						memset(ch[sz],0,sizeof(ch[sz]));
						val[sz]=0;
						ch[u][c]=sz++;
				}
				u=ch[u][c];
		}
		val[u]=v;
	}
}trie;
