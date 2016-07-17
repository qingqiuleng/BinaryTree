#pragma once 
#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key,const V& value)
	:_bf(0)
	, _left(NULL)
	, _right(NULL)
	, _parent(NULL)
	, _key(key)
	, _value(value)
	{}
	int _bf;
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;
	K _key;
	V _value;
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{
	}

	~AVLTree()
	{}

	bool Insert(const K& key,const V& value)//插入
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)//找到要插入的位置
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		cur = new Node(key, value);
		if (key < parent->_key)//将节点插在左树
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else//将节点插在右树
		{
			parent->_right = new Node(key, value);
			cur->_parent = parent;
		}

		//调整平衡因子
		while (cur)
		{
			cur->_bf = _Height(cur->_right) - _Height(cur->_left);//从当前节点开始调节平衡因子
			if (cur->_bf != 0 && cur->_bf != 1 && cur->_bf != -1)
			{
				if (cur->_bf == 2 && cur->_right->_bf == 1)//左单旋
				{
					_RotateL(cur);
				}
				else if (cur->_bf==-2&&cur->_left->_bf==-1)//右单旋
				{
					_RotateR(cur);
				}
				else if (cur->_bf==-2&&cur->_left->_bf==1)//左右双旋
				{
					_RotateLR(cur);
				}
				else if (cur->_bf == 2 && cur->_right->_bf == -1)//右左双旋
				{
					_RotateRL(cur);
				}
			}
			cur = cur->_parent;//往上调整
		}
	}
	Node* Find(const K& key)//查找
	{
		return _Find(_root, key);
	}

	bool IsBlance()//检查是否合格（每个节点因子是否大于2或小于-2）
	{
		return _IsBlance(_root);
	}

protected:
	bool _IsBlance(Node* root)
	{
		if (root == NULL)
			return true;
	
		int factor = _Height(root->_right) - _Height(root->_left);
		if (factor > 1 || factor < -1)
			return false;
		if (factor != root->_bf)
		{
			cout << "平衡因子出错" << endl;
			cout << root->_key << endl;
			return false;
		}
		return _IsBlance(root->_left) && _IsBlance(root->_right);
	}

	Node* _Find(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key == key)
			return root;
		_Find(root->_left,key);
		_Find(root->_right,key);
	}

	void _RotateL(Node*& parent)//左单旋,传引用，因为parent会被改变
	{
		Node* sonR = parent->_right;
		Node* sonRL = sonR->_left;

		parent->_right = sonRL;
		sonR->_parent = parent->_parent;
		sonR->_left = parent;
		parent->_parent = sonR;
		if (sonRL)
		{
			sonRL->_parent = parent;
		}
		parent->_bf = sonR->_bf = 0;//将平衡因子调整

		if (sonR->_parent == NULL)
			_root = sonR;
		else
		{
			if (sonR->_parent->_key > sonR->_key)
				sonR->_parent->_left = sonR; // 链接到左路
			else
				sonR->_parent->_right = sonR;//链接到右路
		}
		parent = sonR;
	}

	void _RotateR(Node*& parent)//右单旋，传引用，因为parent会被改变
	{
		Node* sonL = parent->_left;
		Node* sonLR = sonL->_right;
		
		parent->_left = sonLR;
		sonL->_parent = parent->_parent;
		sonL->_right = parent;
		parent->_parent = sonL;
		if (sonLR)
		{
			sonLR->_parent = parent;
		}
		parent->_bf = sonL->_bf = 0;

		//对sonL的父亲节点进行链接
		if (sonL->_parent == NULL)//父亲节点为空
			_root = sonL;
		else//父亲节点不为空
		{
			if (sonL->_parent->_key > sonL->_key)//链接到左路
				sonL->_parent->_left = sonL;
			else
				sonL->_parent->_right = sonL;//链接右路
		}
		parent = sonL;
	} 

	void _RotateLR(Node*& parent)//左右双旋
	{
		Node* pNode = parent;
		Node* sonL = parent->_left;
		Node* sonLR = sonL->_right;
		_RotateL(parent->_left);
		_RotateR(parent);
		//在进行左右旋之后，平衡因子有问题，需要从新调整
		//sonLR平衡因子有3中情况，分别是0，1，-1
		if (sonLR->_bf == 1)
		{
			pNode->_bf = 1;
			sonL->_bf = 0;
		}
		else if (sonLR->_bf == -1)
		{
			pNode->_bf = 0;
			sonL->_bf = -1;
		}
		else
		{
			parent->_bf = 0;
			sonL->_bf = 0;
		}

	}

	void _RotateRL(Node*& parent)//右左双旋
	{
		Node* pNode = parent;
		Node* sonR = parent->_right;
		Node* sonRL = sonR->_left;
		_RotateR(parent->_right);
		_RotateL(parent);
		//在进行左右旋之后，平衡因子有问题，需要从新调整
		if (sonRL->_bf == 1)
		{
			pNode->_bf = -1;
			sonR= 0;
		}
		else if (sonRL->_bf == -1)
		{
			pNode->_bf = 0;
			sonR->_bf = 1;
		}
		else
		{
			pNode->_bf = 0;
			sonR->_bf = 0;
		}
	}

	int _Height(Node* parent)//高度
	{
		int left, right;
		if (parent == NULL)
			return 0;
		left = _Height(parent->_left);
		right = _Height(parent->_right);
		return left > right ? left + 1 : right + 1;
	}
private:
	Node* _root;
};











