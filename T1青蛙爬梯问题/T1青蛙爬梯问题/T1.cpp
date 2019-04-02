/*
Question1: FrogJump algorithm
Description:һֻ����һ�ο������� 1 ��̨�ף�Ҳ�������� 2 ��̨�ס�
			����������� 1 �� n ����̨���ܹ��ж�����������
CoreAlgorithm:Matrix quick pow
author:Wang Xingzhou_1652977
contact: mobile:18916111729
		 email:1242532947@qq.com
*/
#include<iostream>
using namespace std;


//define matrix struct
struct Matrix {
	//Int can't hold so large number
	long long mat[2][2];
};

/*matrix multiply 
@brief:multiply two matrix and return result
@parameter:matrix a and matrix b
@return:a new matrix with result
*/
Matrix multiply(Matrix a, Matrix b) {
	Matrix result;
	for (int i = 0; i<2; i++) {
		for (int j = 0; j<2; j++) {
			result.mat[i][j] = 0;
			for (int k = 0; k<2; k++) {
				result.mat[i][j] = result.mat[i][j] + a.mat[i][k] * b.mat[k][j];
			}
		}
	}
	return result;
}

/*matrix quick pow 
@brief:A fast algorithm for calculating the value of another multiplier
@parameter:reference--multiplier n--exponential
@return:the result of reference
*/
Matrix quickPow(Matrix reference, int n) {
	//store the original reference
	Matrix reference1;
	reference1.mat[0][0] = 1;
	reference1.mat[0][1] = 1;
	reference1.mat[1][0] = 1;
	reference1.mat[1][1] = 0;
	if (n == 1)
	{
		return reference1;
	}
	if (n == 2)
	{
		return multiply(reference, reference);
	}
	if (n % 2 == 0)
	{
		reference = multiply(quickPow(reference, n / 2), quickPow(reference, n / 2));
	}
	else
	{
		reference = multiply(quickPow(reference, n / 2), quickPow(reference, n / 2));
		reference = multiply(reference, reference1);
	}
}

int main() {
	//The stairs order 
	int number;
	cout << "������¥�ݵĽ���:" << endl;
	while (1)
	{
		//illegal input
		if (!(cin >> number))
		{
			cout << "��������Ƿ������������롣" << endl;
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		//A negative number
		else if (number < 0)
		{
			cout << "������һ����������" << endl;
		}
		//three special condition
		else if (number == 0)
		{
			cout << "���еķ�����0�֡�" << endl;
			system("pause");
			return 0;
		}
		else if (number == 1)
		{
			cout << "���еķ�����1�֡�" << endl;
			system("pause");
			return 0;
		}
		else if (number == 2)
		{
			cout << "���еķ�����2�֡�" << endl;
			system("pause");
			return 0;
		}
		//usual condition
		else
			break;
	}
	//Initial multiplicand
	Matrix origin;
	origin.mat[0][0] = 2;
	origin.mat[0][1] = 1;
	origin.mat[1][0] = 0;
	origin.mat[1][1] = 0;
	//Initial reference
	Matrix reference;
	reference.mat[0][0] = 1;
	reference.mat[0][1] = 1;
	reference.mat[1][0] = 1;
	reference.mat[1][1] = 0;
	//The calculation results
	Matrix result = multiply(origin, quickPow(reference, number - 2));
	//output
	cout << "���еķ�����" << result.mat[0][0] << "�֡�" << endl;
	system("pause");
	return 0;
}