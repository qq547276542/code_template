 const int hashsize = 1000003;
const int maxstate = 1000000;
typedef int State;
int head[hashsize],Next[maxstate];
State st[maxstate];//需要定义一个状态数组
int id=0;//状态数组的下标，访问状态
void init(){memset(head,0,sizeof(head));}
int Hash(State& s){
	int v=0;
		 //哈希函数
	return v%hashsize;
}
int try_to_insert(int s){//s带入id
		int h=Hash(st[s]);
		int u=Head[h];
		while(u){
				if(st[u]==st[s]) 
				{
						return 0;//找到了，插入失败
				}
				u=next[u];
		}
		next[s]=head[h];
		head[h]=s;
		return 1;  //插入到链表中
}
