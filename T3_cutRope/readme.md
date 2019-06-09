# T3 剪绳子

作者：1652977——王星洲

算法第三次作业程序设计 CutRope

语言：`C++`

IDE: `Visual Studio 2019`



## 题目要求

给你一根长度为n的绳子，请把绳子剪成 m 段(m,n 都是整数，n>1 并且 m>1)，每段绳子的长度记为 k[0], k[1], …, k[m]。请问 k[0] k[1] … k[m]可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2，3，3的三段，此时得到的最大乘积是18。



## 需求分析

1. 本题的算法设计考虑**动态规划**的思想，因为该问题中为了求给出绳长对应的乘积最大值可以划分为将绳长分为两段，这两段绳长成绩最大值的乘积，并且依此划分为更小的子问题，具有**最优子结构性质**；同时，子问题的解确定后，就不会再改变，满足了**无后效性**，在计算时，要多次使用子问题的结果，满足了**子问题的重叠性**，因此考虑动态规划算法。按照绳长从2增长到*length*的每个取值的最大乘积作为惩罚因子依次计算，求得的最大值即为最优解。

2. 由于1的结果可以得到对应的贪心算法，作为第二种解法说明。



## 主要函数

|   函数名    | 参数 | 返回值 |                   说明                   |
| :---------: | :--: | :----: | :--------------------------------------: |
| solution()  | int  |  int   |  （dp）将绳子长度作为参数，返回最大乘积  |
| solution2() | int  |  int   | （贪心）将绳子长度作为参数，返回最大乘积 |

## 动态规划求解的方法

当绳子长度为 2 的时候，只能剪成两段长度为 1，所以 solution(2)=1；当绳子长度为 3 的时候，有两种剪法，其中最大的 solution(3)=2。

那么当 n>4 的时候，我们要求出把长度为 length 的绳子剪成若干段之后各段长度乘积的最大值，即求 solution(length)，而4<=length<=n，即要求出所有子问题的最优解。那么对于每个子问题 solution(i)，由于可以有 length/2 种切法，所以我们应该遍历每种切法，并计算出乘积最大的那种切法。当切点在 j(0<j<=i/2) 处时，子问题 solution(i)=max(solution(j)*solution(i-j)),其中 solution(j),solution(i-j)，都可以从数组中查询得到。

#### 流程

```flow
st=>start: 开始
ed=>end: 结束
op1=>operation: 查看参数length
c1=>condition: length=2或3
op2=>operation: 对应返回1或2
op3=>operation: 设置长度为1|2|3的绳子
的结果因子为1|2|3
op4=>operation: 从绳长为4开始计算结果因子
c2=>condition: 绳长达到要求
op5=>operation: 将绳长分为所有可能两
段，计算所有可能结果
因子的最大乘积
op6=>operation: 将该结果作为对应
长度的结果因子
op7=>operation: 绳长+1
op8=>operation: 返回对应绳长结果因子，
即为所求
st->op1->c1(yes,right)->op2->ed
c1(no)->op3->op4->c2(yes)->op8->ed
c2(no,left)->op5->op6->op7->c2
```



#### 具体实现

```c++
/*
计算最大乘积的函数
参数:int
返回值：int
将绳子长度作为参数，返回最大乘积
*/
int solution(int length)
{
	//根据绳子长度选择结果
	switch (length)
	{
		//长度为2，至少剪一刀，乘积为1
	case 2:
		return 1;
		break;
		//长度为3，至少剪一刀，乘积为2
	case 3:
		return 2;
		break;
		//长度为4及以上，使用动态规划
	default:
	{
		//储存各个长度乘积最大值的数组
		vector<int> result(length + 1);
		//长度为1，不需要剪，乘积因子为1
		result[1] = 1;
		//长度为2，不需要剪，乘积因子为2
		result[2] = 2;
		//长度为3，不需要剪，乘积因子为3
		result[3] = 3;
		//计算从4到length所有长度的乘积因子
		for (int i = 4; i <= length; i++)
		{
			//最大值
			int maxNum = 0;
			//分别将绳子剪为不同长度的两段，得到最大值作为该长度的乘积因子
			for (int j = i / 2; j > 0; j--)
			{
				//获得最大值
				int temp = result[j] * result[i - j];
				if (maxNum < temp)
				{
					maxNum = temp;
				}
			}
			//将该最大值作为该长度对应的乘积因子
			result[i] = maxNum;
		}
		//绳子长度对应的乘积因子即为所求
		return result[length];
		break;
	}	
	}
	return -1;
}
```



## 输入合法性检测

在输入合法性检测中，我对非法输入进行了筛选，为了降低实现函数出错的风险，同时增加了程序的健壮性。

方案如下：

```c++
//储存绳子长度
	int length;
	cout << "请输入绳子的长度" << endl;
	//判断输入合法性
	while (true)
	{
		//输入非数字
		if (!(cin >> length))
		{
			cout << "您输入的数据非法" << endl;
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		//输入非大于1的正整数
		else if (length <= 1)
		{
			cout << "请输入大于1的正整数" << endl;
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		//输入正确
		else
		{
			break;
		}
	}
```



## 另一种思路（贪心）

在计算的过程之中发现规律：在绳长为2/3/4时对应的结果为1/2/4，然而在5及以上时，所有结果满足规律：

* 尽可能多的剪成长度为**3**的段
* 不应存在长度为1的段
* 长度为4的段可以分为两段长度为2的段(也可以不分)

这样的规律也就实现了对应的贪心算法。将动态规划算法$ O(n^2) $的时间复杂度以及$O(n)$的空间复杂度有效降低，变为了$O(1)$与$O(1)$，可以考虑如下实现：

```c++
/*
贪心算法计算最大乘积的函数
参数:int
返回值：int
将绳子长度作为参数，返回最大乘积
*/
int solution2(int length)
{
	switch (length)
	{
	case 2:
		return 1;
		break;
	case 3:
		return 2;
		break;
	case 4:
		return 4;
		break;
	default:
		int result = 1;
		int remainder = length % 3;
		if (remainder == 1)
		{
			int times = length / 3 - 1;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
			result *= 4;
		}
		else if(remainder == 0)
		{
			int times = length / 3;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
		}
		else
		{
			int times = length / 3;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
			result *= 2;
		}
		return result;
		break;
	}
	return -1;
}
```



## 说明

值得一提的是：当绳长超过58时，结果的值也超过了 int 计量范围，可以扩大为 long long 或者 double ，不过两个算法得到的值也出现了差别，因为动态规划计算最大值，当结果越界变为负数，得到的解仍然为某个最大值，然而贪心算法不会如此，它的结果就是变为负数之后的值。