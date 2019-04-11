#define LL long long
int  mod = 1000000007;
int n; //矩阵宽度
const int maxn=100; //maxn不要超过160
struct Mat    //矩阵结构体
{
	LL mat[maxn][maxn];
};
Mat operator * (Mat a, Mat b)  //2个边长为n的正方形矩阵乘法 a*b mod p
{
	Mat c;
	memset(c.mat, 0, sizeof(c.mat));
	int i, j, k;
	for(k = 0; k < n; ++k)
	{
		for(i = 0; i < n; ++i)
		{
			if(a.mat[i][k] <= 0)  continue;   //不要小看这里的剪枝，cpu运算乘法的效率并不是想像的那么理想（加法的运算效率高于乘法，比如Strassen矩阵乘法）
			for(j = 0; j < n; ++j)
			{
				if(b.mat[k][j] <= 0)    continue;    //剪枝
				c.mat[i][j] = (c.mat[i][j]+a.mat[i][k] * b.mat[k][j])%mod;
			}
		}
	}
	return c;
}
 
Mat operator ^ (Mat a, int k)   //宽度为n的矩阵a^k mod p
{
	Mat c;
	int i, j;
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			c.mat[i][j] = (i == j);    //初始化为单位矩阵
	for(; k; k >>= 1)
	{
		if(k&1) c = c*a;
		a = a*a;
	}
	return c;
}
void display(Mat a)  //打印矩阵
{
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
		 printf("%8d  ",a.mat[i][j]);cout<<endl;
	}
}
Mat a,b; //最好把矩阵开在外面，防止爆栈
 
int main()
{
	cin>>n;   //必须先输入矩阵宽度
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		   a.mat[i][j]=b.mat[i][j]=i*j+2;
	display(a);
	display(a*b);
	display(a^2333);
	return 0;
}
