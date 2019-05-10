

# T2 合并二叉树

作者：1652977——王星洲

算法第二次作业程序设计 MergeTrees

语言：`C++`

IDE: `Visual Studio 2019`



## 题目要求

给出两个二叉树，合并它们并返回合并后的二叉树。合并规则：相同位置的节点值相加；如 果相同位置一个树为 null，一个树值为 A，则设置为 A 。



## 需求分析

本题核心的算法实现十分简单，我主要考虑使用递归的思想，从两棵树的根结点开始，先合并根结点，再分别对其左右子结点进行递归调用，直到两棵树均没有子结点为止。



## 主要函数

|       函数名       |            参数            |  返回值   |                        说明                        |
| :----------------: | :------------------------: | :-------: | :------------------------------------------------: |
|    mergeTrees()    | TreeNode* t1, TreeNode* t2 | TreeNode* | 将两个树的根节点传入，合并两树并传出结果树的根节点 |
| stringToTreeNode() |           string           | TreeNode* |         根据字符串建立一棵树并返回其根节点         |
|  printTreeNode()   |         TreeNode *         |     /     |              根据当前树将结果打印输出              |
| deleteUnusedNull() |          string &          |     /     |       将字符串中多出来的null删除，保证可读性       |



## 合并二叉树的流程

```flow
st=>start: 开始
e=>end: 结束
op1=>operation: 两节点值相加，
对左右子结点递归调用
op2=>operation: 返回t1
op3=>operation: 返回t2
op4=>operation: 返回空结点
c1=>condition: t1为空且t2为空
c2=>condition: t1为空
c3=>condition: t2为空
st->c1(yes)->op4->e
st->c1(no)->c2(yes)->op3->e
c1(no)->c2(no)->c3(yes)->op2->e
c2(no)->c3(no)->op1->e
```

具体代码如下

```c++
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
```



## 树的建立与输出

### 根据字符串建立树

我采用了stringstream流来实现输入字符串的空格分隔以及判空，使用方法如下

```
//接收拆开的字符串
string node;
//输入输出流
stringstream ss;
//将字符串输入值流中
ss.str(input);
//从流中取出空格字符之前的第一个分割字符串
ss >> node;
//输入流判空
if (!(ss>>node)) 
{
	break;
}
```



```flow
st=>start: 开始
e=>end: 结束
c1=>condition: 输入流第一个值为空
c2=>condition: 结点不为空
c3=>condition: 输入流没有剩余字符串
c4=>condition: 输入流没有剩余字符串
op1=>operation: 返回空结点
op2=>operation: 返回根结点
op3=>operation: 建立根结点并加入队列
op4=>operation: 取出队列中第一个结点，
作为父节点，队列中删除该节点
op5=>operation: 取出流中下一个结点
op6=>operation: 将该节点作为父节点的左子节点，
队列中加入该节点
op7=>operation: 取出流中下一个结点
op8=>operation: 将该节点作为父节点的右子节点，
队列中加入该节点
st->c1(yes,right)->op1->e
c1(no)->op3->op4->op5->c3(yes,right)->op2(right)->e
c3(no)->op6->op7->c4(yes,right)->op2
c4(no,right)->op8(top)->op4
```

具体代码如下

```c++
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
```



### 树的输出

主要流程：

```flow
st=>start: 开始
e=>end: 结束
c1=>condition: 该树为空树
c2=>condition: 队列为空
c3=>condition: 该节点为空
op1=>operation: 将根结点加入队列
op2=>operation: 取出第一个结点，
将该节点从队列中删除
op3=>operation: 输出字符串增加null
op4=>operation: 输出字符串增加结点value值
op5=>operation: 把该节点左右子节点加入队列
op6=>operation: 输出字符串删除最后一个
数字之后的null字符串
op7=>operation: 输出空树
st->c1(yes,right)->op7->e
c1(no)->op1->c2(yes,right)->op6->e
c2(no)->op2->c3(yes,right)->op3(top)->c2
c3(no)->op4->op5->c2
```

具体代码如下：

```c++
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
```


