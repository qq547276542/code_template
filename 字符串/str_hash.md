学习地址：[Link](https://blog.csdn.net/pengwill97/article/details/80879387)

## Hash方法

给定一个字符串S=s1s2s3..sn，对字母x，我们规定idx(x)=x−′a′+1。 （当然也可以直接用si的ASCII值）

## 自然溢出法
$$
h a s h[i]=h a s h[i-1] * p+i d(s[i])
$$

利用unsigned long long的范围自然溢出，相当于自动对2^64-1取模

## 单Hash方法

$$
h a s h[i]=(h a s h[i-1]) * p+i d x(s[i]) \% \text { mod }
$$

其中p和mod均为质数，并且有p<mod。

对于此种Hash方法，将p和mod尽量取大即可，这种情况下，冲突的概率很低。

### 举例

如取p=13,mod=101
，对字符串abc
进行Hash 
hash[0] = 1 
hash[1] = (hash[0] * 13 + 2) % 101 = 15 
hash[2] = (hash[1] * 13 + 3) % 101 = 97

这样，我们就认为字符串abc
当做97，即97就是abc
 的hash值。

## 双Hash方法

将一个字符串用不同的mod hash两次，将这两个结果用一个二元组表示，作为Hash结果。
$$
\begin{array}{l}{h a s h 1[i]=(h a s h 1[i-1]) * p+i d x(s[i]) \% \bmod 1} \\ {h a s h 2[i]=(h a s h 2[i-1]) * p+i d x(s[i]) \% \bmod 2}\end{array}
$$
hash结果为<hash1[n],hash2[n]>

这种Hash很安全。

## 获取子串的Hash

如果我们求出一个串的Hash，就可以O(1)求解其子串的Hash值。 
我们先以一个具体的例子来理解。

### 例子

假设有一|S|=5的字符串，设Si为第i个字符，其中1≤i≤5。

根据定义分别求出hash[i]
$$
\begin{aligned} \operatorname{hash}[1] &=s_{1} \\ \operatorname{hash}[2] &=s_{1} * p+s_{2} \\ \operatorname{hash}[3] &=s_{1} * p^{2}+s_{2} * p+s_{3} \\ \operatorname{hash}[4] &=s_{1} * p^{3}+s_{2} * p^{2}+s_{3} * p+s_{4} \\ \operatorname{hash}[5] &=s_{1} * p^{4}+s_{2} * p^{3}+s_{3} * p^{2}+s_{4} * p+s_{5} \end{aligned}
$$
现在我们想求s3s4的hash值，不难得出为s3∗p+s4,并且从上面观察，如果看hash[4]−hash[2]
并将结果种带有s1,s2系数的项全部消掉，就是所求。但是由于p的阶数，不能直接消掉，所以问题就转化成，将hash[2]乘一个关于p的系数，在做差的时候将多余项消除，从而得到结果。

不难发现，对应项系数只差一个p^2，而4 - 3 + 1 = 2(待求hash子串下标相减再加一)，这样就不难推导出来此例题的求解式子。
$$
h a s h[4]-h a s h[2] * p^{4-2+1}
$$
至此，通过对上例的归纳，可以得出如下的公式。

### 公式

若已知一个|S|=n的字符串的hash值，hash[i],1≤i≤n，其子串sl..sr, 1≤l≤r≤n对应的hash值为：
$$
h a s h=h a s h[r]-h a s h[l-1] * p^{r-l+1}
$$
考虑到hash[i]每次对p取模，进一步得到下面的式子：
$$
h a s h=\left(h a s h[r]-h a s h[l-1] * p^{r-l+1}\right) \% M O D
$$
看起来这个式子人畜无害，但是对于取模运算要谨慎再谨慎，注意到括号里面是**减法**，即有可能是负数，故做如下的修正：
$$
h a s h=\left(\left(h a s h[r]-h a s h[l-1] * p^{r-l+1}\right) \% M O D+M O D\right) \% M O D
$$
至此得到求子串hash值公式。

值得一提的是，如果需要反复对子串求解hash值，预处理p的n次方效果更佳。

## Hash素数的选取

为了防止冲突，要选择合适的素数，像1e9+7,1e9+9的一些素数，出题人一般会卡一下下，所以尽量选择其他的素数，防止被卡。下面是一些可供选择的素数。 
上界和下界指的是离素数最近的2n的值。

![](https://i.loli.net/2019/05/15/5cdc08c5c20e224500.jpg)

