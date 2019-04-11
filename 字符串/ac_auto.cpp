 
#include<queue>
#include<cstring>
#include<string>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxnode=1000007;
const int SIGMA_SIZE=26;   //若字符串可能出现所有字符，则要将该值改为128，并且将idx函数中“ -‘a’ "去掉
//给定多个模板，一个文本，能够找出模板在文本中的位置与附加信息val
//该模板默认输入都为小写字母，若题目字符集不是小写字母，需要改动SIGMA_SIZE和idx（）函数 
struct AC {
		int ch[maxnode][SIGMA_SIZE];  //trie树
		int val[maxnode];   //结点附加信息，默认0为该节点不是单词
		int last[maxnode];   //后缀链接
		int f[maxnode];  //失配函数
		int sz;
		void init(){sz=1;memset(ch[0],0,sizeof(ch[0]));}
		void print(int i,int j) {    //匹配成功时自动调用该函数，打印信息
				if(j) {
					//  printf("在%d位置匹配到模板，该模板附加信息val为: %d\n",i,val[j]);
					//在此处打印信息或修改信息
						print(i,last[j]);
				}
		}
		int idx(char c) {
				return c-'a';     //此处要根据字符集的范围来确定
		}
 
		void insert(char *s,int v){  //插入模板字符串，v是该模板的附加信息
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
				val[u]=v;     //此时的u为该字符串s的结点值，会把原先该处结点值覆盖
		}
 
		void getFail() {    //构造失配函数,在添加完所有模板后调用（注意不要漏了这个函数）
				queue<int> q;
				f[0]=0;
				for(int c=0; c<SIGMA_SIZE; c++) {
						int u=ch[0][c];
						if(u) {
								f[u]=0;
								q.push(u);
								last[u]=0;
						}
				}
				while(!q.empty()) {
						int r=q.front();
						q.pop();
						for(int c=0; c<SIGMA_SIZE; c++) {
								int u=ch[r][c];
								if(!u) {
										ch[r][c]=ch[f[r]][c];
										continue;
								}
								q.push(u);
								int v=f[r];
								while(v&&!ch[v][c])v=f[v];
								f[u]=ch[v][c];
								last[u]=val[f[u]]?f[u]:last[f[u]];
						}
				}
		}
 
		void find(char *T) {   //寻找文本T中寻找模板
				int n=strlen(T);
				int j=0;
				for(int i=0; i<n; i++) {
						int c=idx(T[i]);
						j=ch[j][c];
						if(val[j])print(i,j);
						else if(last[j])print(i,last[j]);
				}
		}
 
};
AC a;
int main() {
		// freopen("in.txt","r",stdin);
		a.init();
		a.insert("a",1);
		a.insert("haha",5);
		a.getFail();
		a.find("ahahahaha");
		return 0;
}
