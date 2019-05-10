/*
Author:1652977——王星洲
FileName:T2_MergeTrees
Method:Recursive
*/

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

//树的结点结构体
struct TreeNode 
{ 
	//结点的值
	int val;
	//左右子节点
	TreeNode *left;
	TreeNode *right;
	//结点构造函数
	TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

/*
合并树的方法
参数：TreeNode* TreeNode*
返回值：TreeNode*
将两个树的根节点传入，传出结果树的根节点
*/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2);
/*
将字符串转换为树
参数:string
返回值：TreeNode *
根据字符串建立一棵树并返回其根节点
*/
TreeNode* stringToTreeNode(string input);
/*
输出树
参数:TreeNode*
返回值：void
根据当前树将结果打印
*/
void printTreeNode(TreeNode *tree);
/*
删除字符串中多余的null值
参数:string
返回值：void
将字符串中多出来的null删除，保证可读性
*/
void deleteUnusedNull(string& s);

//主函数
int main()
{
	//接收输入的字符串
	string line;
	cout << "请务必按照以下说明进行输入：" << endl;
	cout << "1.输入两行数字，分别表示两棵树。" << endl;
	cout << "2.每棵树的结点按照节点编号顺序输入，用空格分隔，为空的位置输入null或0。" << endl;
	cout << "3.结点的值应为正整数。" << endl;
	cout << "4.输入应该截止于该层叶子结点输入完毕。" << endl;
	cout << "5.空树请输入null。\n" << endl;
	getline(cin, line);
	//根据建立树
	TreeNode* t1 = stringToTreeNode(line);
	getline(cin, line);
	TreeNode* t2 = stringToTreeNode(line);
	//将两棵树合并
	TreeNode* ret = mergeTrees(t1, t2);
	//输出结果树
	printTreeNode(ret);

	system("pause");
	return 0;
}


TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
	//两棵结点都为空
	if ((!t1) && (!t2))
	{
		return nullptr;
	}
	//其中一个结点为空
	else if (!t1)
	{
		return t2;
	}
	else if (!t2)
	{
		return t1;
	}
	//两个结点都有值
	else
	{
		//将两结点值相加，并递归调用到其左右子结点
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);
		t1->right = mergeTrees(t1->right, t2->right);

		return t1;
	}
}


TreeNode* stringToTreeNode(string input) {
	//接收拆开的字符串
	string node;
	//接收树节点的值
	int value;
	//输入输出流
	stringstream ss;
	//结点队列，用于建树
	queue<TreeNode*> nodeQueue;
	//将字符串输入值流中
	ss.str(input);
	//从流中取出空格字符之前的第一个分割字符串
	ss >> node;
	//如果字符串为null
	if (node == "null"|| node == "Null"||node == "NULL")
	{
		return nullptr;
	}
	//字符串不为null时，将其转换为数字作为value的值
	value = stoi(node);
	//按值建立根结点
	TreeNode* root = new TreeNode(value);
	//进入队列
	nodeQueue.push(root);

	while (true)
	{
		//取出队列中第一个结点
		TreeNode* parentNode = nodeQueue.front();
		nodeQueue.pop();
		//流中没有剩余字符串时跳出
		if (!(ss>>node)) 
		{
			break;
		}
		//为节点添加左子节点
		if (node != "null" && node != "Null" && node != "NULL") 
		{
			int leftNumber = stoi(node);
			parentNode->left = new TreeNode(leftNumber);
			nodeQueue.push(parentNode->left);
		}
		//检查流中是否有字符
		if (!(ss >> node)) 
		{
			break;
		}
		//为节点添加右子节点
		if (node != "null" && node != "Null" && node != "NULL") 
		{
			int rightNumber = stoi(node);
			parentNode->right = new TreeNode(rightNumber);
			nodeQueue.push(parentNode->right);
		}
	}
	//返回根结点
	return root;
}


void printTreeNode(TreeNode* tree) 
{
	//如果为空树
	if (tree == nullptr)
	{
		cout << "该树为空树" << endl;
		return;
	}
	else
	{
		//结果字符串
		string result;
		//结点队列
		queue<TreeNode*> q;
		//将根节点加入队列
		q.push(tree);
		//当队列非空时
		while (!q.empty()) {
			//取出第一个结点
			TreeNode* node = q.front();
			q.pop();
			//如果该节点为空，输出中增加null
			if (node == nullptr) {
				result += "null ";
				continue;
			}
			//如果不为空，输出中增加该结点的value值
			result += to_string(node->val) + " ";
			//将该结点的左右子结点加入队列
			q.push(node->left);
			q.push(node->right);
		}
		//去除结果中多余的null
		deleteUnusedNull(result);
		//打印
		cout << "结果为:" << endl;
		cout << result << endl;
	}
	return;
}


void deleteUnusedNull(string& s)
{
	//循环控制变量
	int i = 0;
	//寻找最后一个数字的位置
	int position = 0;
	while (i < s.size())
	{
		//如果该字符为数字，则为position赋当前位置
		if (s[i] >= '0' && s[i] <= '9')
		{
			position = i;
		}
		i++;
	}
	//从position+1的位置一直擦除到结尾
	s.erase(position + 1, s.size() - position);
}