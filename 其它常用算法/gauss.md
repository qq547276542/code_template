```cpp
const int maxn=50;
//有equ个方程，var个变元。增广矩阵行数为equ，列数为var+1
int equ,var;
int a[maxn][maxn]; //增广矩阵
int x[maxn];  //解集
int free_x[maxn];
int free_num;
void init(){
    memset(a,0,sizeof(a));
    memset(x,0,sizeof(x));
    equ=30,var=30;
}
//返回-1表示无解，0代表是唯一解,并生成解集x[]，否则返回自由变元个数
int Gauss(){
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0;k<equ&&col<var;k++,col++){
        max_r=k;
        for(int i=k+1;i<equ;i++){
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        }
        if(a[max_r][col]==0){
            k--;
            free_x[free_num++]=col;
            continue;
        }
        if(max_r!=k){
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(int i=k+1;i<equ;i++){
            if(a[i][col]!=0){
                for(int j=col;j<var+1;j++)
                    a[i][j]^=a[k][j];
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;  //无解
    if(k<var) return var-k;  //解不唯一，返回解个数
    //解唯一，生成解集
    for(int i=var-1;i>=0;i--){
        x[i]=a[i][var];
        for(int j=i+1;j<var;j++)
            x[i]^=(a[i][j]&&x[j]);
    }
    return 0;
}
```

**POJ 1222(高斯消元法)**

**题意**：5*6矩阵中有30个灯，操作一个灯，周围的上下左右四个灯会发生相应变化 即由灭变亮，由亮变灭，如何操作使灯全灭？

**分析**：这个问题是很经典的高斯消元问题。同一个按钮最多只能被按一次，因为按两次跟没有按是一样的效果。那么对于每一个灯，用1表示按，0表示没有按，那么每个灯的状态的取值只能是0或1。列出30个方程，30个变元，高斯消元解出即可，因为解只能是0或者1，所以方程组是一定有解。

```cpp
#include<queue>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<set>
using namespace std;
const int maxn=50;
//有equ个方程，var个变元。增广矩阵行数为equ，列数为var+1
int equ,var;
int a[maxn][maxn]; //增广矩阵
int x[maxn];  //解集
int free_x[maxn];
int free_num;
void init(){
    memset(a,0,sizeof(a));
    memset(x,0,sizeof(x));
    equ=30,var=30;
}
//返回-1表示无解，0代表是唯一解,并生成解集x[]，否则返回自由变元个数
int Gauss(){
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0;k<equ&&col<var;k++,col++){
        max_r=k;
        for(int i=k+1;i<equ;i++){
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        }
        if(a[max_r][col]==0){
            k--;
            free_x[free_num++]=col;
            continue;
        }
        if(max_r!=k){
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(int i=k+1;i<equ;i++){
            if(a[i][col]!=0){
                for(int j=col;j<var+1;j++)
                    a[i][j]^=a[k][j];
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;  //无解
    if(k<var) return var-k;  //解不唯一，返回解个数
    //解唯一，生成解集
    for(int i=var-1;i>=0;i--){
        x[i]=a[i][var];
        for(int j=i+1;j<var;j++)
            x[i]^=(a[i][j]&&x[j]);
    }
    return 0;
}
int G[maxn][maxn];
int main() {
    freopen("in.txt","r",stdin);
    int T;
    cin>>T;
    int now=0;
    while(T--){
        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++)
                scanf("%d",&G[i][j]);
        }
        init();
        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                int t=i*6+j;
                a[t][t]=1;
                a[t][30]=G[i][j];
                if(i>0)a[t][(i-1)*6+j]=1;
                if(i<4)a[t][(i+1)*6+j]=1;
                if(j>0)a[t][i*6+j-1]=1;
                if(j<5)a[t][i*6+j+1]=1;
            }
        }
        int k=Gauss();
        printf("PUZZLE #%d\n",++now);
        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                if(j!=0)cout<<" ";
                cout<<x[i*6+j];
            }
            cout<<endl;
        }
    }
    return 0;
}
```

