/*
Author:1652977——王星洲
FileName:T3_cutRope
Method:DP
*/
#include <iostream>
#include <vector>
using namespace std;

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
		//结果
		int result = 1;
		//绳长除以三得到的余数
		int remainder = length % 3;
		//余一时，最后一个3作为4保留
		if (remainder == 1)
		{
			int times = length / 3 - 1;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
			result *= 4;
		}
		//没有余数
		else if(remainder == 0)
		{
			int times = length / 3;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
		}
		//余2
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

int main()
{
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
	cout << "最大的值为: " << endl;
	//求得所需结果并输出
	cout << "动态规划结果:" << solution(length) << endl;
	cout << "贪心算法结果:" << solution2(length) << endl;
	return 0;
}