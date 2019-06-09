/*
Author:1652977����������
FileName:T3_cutRope
Method:DP
*/
#include <iostream>
#include <vector>
using namespace std;

/*
�������˻��ĺ���
����:int
����ֵ��int
�����ӳ�����Ϊ�������������˻�
*/
int solution(int length)
{
	//�������ӳ���ѡ����
	switch (length)
	{
		//����Ϊ2�����ټ�һ�����˻�Ϊ1
	case 2:
		return 1;
		break;
		//����Ϊ3�����ټ�һ�����˻�Ϊ2
	case 3:
		return 2;
		break;
		//����Ϊ4�����ϣ�ʹ�ö�̬�滮
	default:
	{
		//����������ȳ˻����ֵ������
		vector<int> result(length + 1);
		//����Ϊ1������Ҫ�����˻�����Ϊ1
		result[1] = 1;
		//����Ϊ2������Ҫ�����˻�����Ϊ2
		result[2] = 2;
		//����Ϊ3������Ҫ�����˻�����Ϊ3
		result[3] = 3;
		//�����4��length���г��ȵĳ˻�����
		for (int i = 4; i <= length; i++)
		{
			//���ֵ
			int maxNum = 0;
			//�ֱ����Ӽ�Ϊ��ͬ���ȵ����Σ��õ����ֵ��Ϊ�ó��ȵĳ˻�����
			for (int j = i / 2; j > 0; j--)
			{
				//������ֵ
				int temp = result[j] * result[i - j];
				if (maxNum < temp)
				{
					maxNum = temp;
				}
			}
			//�������ֵ��Ϊ�ó��ȶ�Ӧ�ĳ˻�����
			result[i] = maxNum;
		}
		//���ӳ��ȶ�Ӧ�ĳ˻����Ӽ�Ϊ����
		return result[length];
		break;
	}	
	}
	return -1;
}

/*
̰���㷨�������˻��ĺ���
����:int
����ֵ��int
�����ӳ�����Ϊ�������������˻�
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
		//���
		int result = 1;
		//�����������õ�������
		int remainder = length % 3;
		//��һʱ�����һ��3��Ϊ4����
		if (remainder == 1)
		{
			int times = length / 3 - 1;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
			result *= 4;
		}
		//û������
		else if(remainder == 0)
		{
			int times = length / 3;
			for (int i = 0; i < times; i++)
			{
				result *= 3;
			}
		}
		//��2
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
	//�������ӳ���
	int length;
	cout << "���������ӵĳ���" << endl;
	//�ж�����Ϸ���
	while (true)
	{
		//���������
		if (!(cin >> length))
		{
			cout << "����������ݷǷ�" << endl;
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		//����Ǵ���1��������
		else if (length <= 1)
		{
			cout << "���������1��������" << endl;
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		//������ȷ
		else
		{
			break;
		}
	}
	cout << "����ֵΪ: " << endl;
	//��������������
	cout << "��̬�滮���:" << solution(length) << endl;
	cout << "̰���㷨���:" << solution2(length) << endl;
	return 0;
}