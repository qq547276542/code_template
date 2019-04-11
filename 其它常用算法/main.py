# encoding: utf-8
'''Python的输入是野生字符串，所以要自己转类型
strip去掉左右两端的空白符，返回str
slipt把字符串按空白符拆开，返回[str]
map把list里面的值映射到指定类型，返回[type]
EOF用抓异常
print后面加逗号就不会换行，否则反之，当然3.x君自行传参
题目细节没看太细，可能有的地方不对，不要在意这些细节啦
'''
 
# 有多组输入数据，但没有具体的告诉你有多少组，只是让你对应每组输入，应该怎样输出。
 
while True:
	try:
		a, b = map(int, input().strip().split())
		print(a + b)
	except EOFError:
		break
	
# 输入一个整数，告诉我们接下来有多少组数据，然后在输入每组数据的具体值。
 
tcase = int(input().strip())
for case in range(tcase):
	a, b = map(int, input().strip().split())
	print(a + b)
	
# 有多组输入数据，没有具体的告诉你有多少组,但是题目却告诉你遇见什么结束
 
while True:
	a, b = map(int, input().strip().split())
	if a == 0 and b == 0:
		break
	print(a + b)
	
# 输入有多组，并却题目告诉你每组输入遇见什么结束，与第三种不同之处在于，每组输入都有相应的细化。
	
tcase = int(input().strip())
for case in range(tcase):
	a, b = map(int, input().strip().split())
	if a == 0 and b == 0:
		break
	print(a + b)
	
# 这次的输入实现输入一个整数，告诉我们有多少行，在输入每一行。对于每一行的输入，有划分为第一个数和其他的数，第一个数代表那一组数据一共有多少输入。
 
tcase = int(input().strip())
for case in range(tcase):
	data = map(int, input().strip().split())
	n, array = data[0], data[1:]
	
	sum = 0
	for i in range(n):
		sum += array[i]
	print(sum)
	
# 有多种输入数据，对于每组输入数据的第一个数代表该组数据接下来要输入数据量
 
while True:
	try:
		data = map(int, input().strip().split())
		n, array = data[0], data[1:]
			
		sum = 0
		for i in range(n):
			sum += array[i]
		print(sum)
	except EOFError:
		raise
	
# 这道题的输出只是简单的在每组输出后边多加一个换行而已！
 
while True:
	try:
		a, b = map(int, input().strip().split())
		print(a + b)
	except EOFError:
		break
	
# 这种类型的输出注意的就是换行，这类题目说在输出样例中，每组样例之间有什么什么，所以我们在对应输出的同时要判断一下是否是最后一组输出，如果不是，就 将题目所说的东西输出（一般是换行或空格），如果是，就直接结束。
 
while True:
	data = input().strip()
	if data.isspace():
		break
	else:
		data = map(int, data)
		n, array = data[0], data[1:]
				
		sum = 0
		for i in range(n):
			sum += array[i]
		print(sum)
