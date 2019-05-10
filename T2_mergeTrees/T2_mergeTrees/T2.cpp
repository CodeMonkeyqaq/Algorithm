/*
Author:1652977����������
FileName:T2_MergeTrees
Method:Recursive
*/

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

//���Ľ��ṹ��
struct TreeNode 
{ 
	//����ֵ
	int val;
	//�����ӽڵ�
	TreeNode *left;
	TreeNode *right;
	//��㹹�캯��
	TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

/*
�ϲ����ķ���
������TreeNode* TreeNode*
����ֵ��TreeNode*
���������ĸ��ڵ㴫�룬����������ĸ��ڵ�
*/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2);
/*
���ַ���ת��Ϊ��
����:string
����ֵ��TreeNode *
�����ַ�������һ��������������ڵ�
*/
TreeNode* stringToTreeNode(string input);
/*
�����
����:TreeNode*
����ֵ��void
���ݵ�ǰ���������ӡ
*/
void printTreeNode(TreeNode *tree);
/*
ɾ���ַ����ж����nullֵ
����:string
����ֵ��void
���ַ����ж������nullɾ������֤�ɶ���
*/
void deleteUnusedNull(string& s);

//������
int main()
{
	//����������ַ���
	string line;
	cout << "����ذ�������˵���������룺" << endl;
	cout << "1.�����������֣��ֱ��ʾ��������" << endl;
	cout << "2.ÿ�����Ľ�㰴�սڵ���˳�����룬�ÿո�ָ���Ϊ�յ�λ������null��0��" << endl;
	cout << "3.����ֵӦΪ��������" << endl;
	cout << "4.����Ӧ�ý�ֹ�ڸò�Ҷ�ӽ��������ϡ�" << endl;
	cout << "5.����������null��\n" << endl;
	getline(cin, line);
	//���ݽ�����
	TreeNode* t1 = stringToTreeNode(line);
	getline(cin, line);
	TreeNode* t2 = stringToTreeNode(line);
	//���������ϲ�
	TreeNode* ret = mergeTrees(t1, t2);
	//��������
	printTreeNode(ret);

	system("pause");
	return 0;
}


TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
	//���ý�㶼Ϊ��
	if ((!t1) && (!t2))
	{
		return nullptr;
	}
	//����һ�����Ϊ��
	else if (!t1)
	{
		return t2;
	}
	else if (!t2)
	{
		return t1;
	}
	//������㶼��ֵ
	else
	{
		//�������ֵ��ӣ����ݹ���õ��������ӽ��
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);
		t1->right = mergeTrees(t1->right, t2->right);

		return t1;
	}
}


TreeNode* stringToTreeNode(string input) {
	//���ղ𿪵��ַ���
	string node;
	//�������ڵ��ֵ
	int value;
	//���������
	stringstream ss;
	//�����У����ڽ���
	queue<TreeNode*> nodeQueue;
	//���ַ�������ֵ����
	ss.str(input);
	//������ȡ���ո��ַ�֮ǰ�ĵ�һ���ָ��ַ���
	ss >> node;
	//����ַ���Ϊnull
	if (node == "null"|| node == "Null"||node == "NULL")
	{
		return nullptr;
	}
	//�ַ�����Ϊnullʱ������ת��Ϊ������Ϊvalue��ֵ
	value = stoi(node);
	//��ֵ���������
	TreeNode* root = new TreeNode(value);
	//�������
	nodeQueue.push(root);

	while (true)
	{
		//ȡ�������е�һ�����
		TreeNode* parentNode = nodeQueue.front();
		nodeQueue.pop();
		//����û��ʣ���ַ���ʱ����
		if (!(ss>>node)) 
		{
			break;
		}
		//Ϊ�ڵ�������ӽڵ�
		if (node != "null" && node != "Null" && node != "NULL") 
		{
			int leftNumber = stoi(node);
			parentNode->left = new TreeNode(leftNumber);
			nodeQueue.push(parentNode->left);
		}
		//��������Ƿ����ַ�
		if (!(ss >> node)) 
		{
			break;
		}
		//Ϊ�ڵ�������ӽڵ�
		if (node != "null" && node != "Null" && node != "NULL") 
		{
			int rightNumber = stoi(node);
			parentNode->right = new TreeNode(rightNumber);
			nodeQueue.push(parentNode->right);
		}
	}
	//���ظ����
	return root;
}


void printTreeNode(TreeNode* tree) 
{
	//���Ϊ����
	if (tree == nullptr)
	{
		cout << "����Ϊ����" << endl;
		return;
	}
	else
	{
		//����ַ���
		string result;
		//������
		queue<TreeNode*> q;
		//�����ڵ�������
		q.push(tree);
		//�����зǿ�ʱ
		while (!q.empty()) {
			//ȡ����һ�����
			TreeNode* node = q.front();
			q.pop();
			//����ýڵ�Ϊ�գ����������null
			if (node == nullptr) {
				result += "null ";
				continue;
			}
			//�����Ϊ�գ���������Ӹý���valueֵ
			result += to_string(node->val) + " ";
			//���ý��������ӽ��������
			q.push(node->left);
			q.push(node->right);
		}
		//ȥ������ж����null
		deleteUnusedNull(result);
		//��ӡ
		cout << "���Ϊ:" << endl;
		cout << result << endl;
	}
	return;
}


void deleteUnusedNull(string& s)
{
	//ѭ�����Ʊ���
	int i = 0;
	//Ѱ�����һ�����ֵ�λ��
	int position = 0;
	while (i < s.size())
	{
		//������ַ�Ϊ���֣���Ϊposition����ǰλ��
		if (s[i] >= '0' && s[i] <= '9')
		{
			position = i;
		}
		i++;
	}
	//��position+1��λ��һֱ��������β
	s.erase(position + 1, s.size() - position);
}