#pragma once 
#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode(const K& key,const V& value)
	:_left(NULL)
	, _right(NULL)
	,_parent(NULL)
	,_key(key)
	, _value(value)
	,_col(RED)
	{
	}
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	K _key;
	V _value;
	Color _col;
};


template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{
	}

	~RBTree()
	{
	}

	bool Insert(const K& key, const V& value)//插入
	{
		if (_root == NULL)//根节点为黑色
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
、
parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}

		cur = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//调整节点颜色
		

		while (cur != _root&&parent->_col==RED)//从这个节点向上调整
		{
			Node* Grandfather = parent->_parent;
			if (parent == Grandfather->_left)//插的节点在左子树上
			{
				Node* Uncle = Grandfather->_right;
				if (Uncle&&Uncle->_col == RED)
				{
					Uncle->_col = BLACK;
					Grandfather->_col = RED;

					cur = Grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						_RotateL(parent);
						swap(cur, parent);
					}
					_RotateR(Grandfather);
					parent->_col = BLACK;
					Grandfather->_col = RED;
				}
			}
			else//插的节点在右子树上
			{
				Node* Uncle = Grandfather->_left;
				if (Uncle&&Uncle->_col == RED)
				{
					Uncle->_col = BLACK;
					Grandfather->_col = RED;

					cur = Grandfather;
					parent = cur->_parent;
				}
				else//叔叔节点不存在
				{
					if (cur == parent->_left)
					{
						_RotateR(parent);
						swap(cur, parent);
					}
					_RotateL(Grandfather);
					parent->_col = BLACK;
					Grandfather->_col = RED;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	Node* Find(const K& key)
	{
		_Find(_root, key);
	}

	protected:
		void _RotateL(Node*& parent)//左旋
		{
			Node* sonR = parent->_right;
			Node* sonRL = sonR->_left;

			if (sonRL)
			{
				parent->_right = sonRL;
				sonRL->_parent = parent;
			}
				
			sonR->_left = parent;
			sonR->_parent = parent->_parent;
			parent->_parent = sonR;
			

			if (sonR->_parent == NULL)//最开始的parent就为根节点
				_root = sonR;
			else//最开始的parent不为根节点 
			{
				if (sonR->_parent->_key > sonR->_key)//链接在左路
				{
					sonR->_parent->_left = sonR;
				}
				else//链接在右路
				{
					sonR->_parent->_right = sonR;
				}
			}
			parent = sonR;
		}
		
		void  _RotateR(Node*& parent)//右旋
		{
			Node* sonL = parent->_left;
			Node* sonLR = sonL->_right;

			if (sonL)
			{
				parent->_left = sonL;
				sonL->_parent = parent;
			}

			sonL->_left = parent;
			sonL->_parent = parent->_parent;
			parent->_parent = sonL;

			if (sonL->_parent == NULL)
				_root = sonL;
			else
			{
				if (sonL->_parent->_key > sonL->_key)
				{
					sonL->_parent->_left = sonL;
				}
				else
				{
					sonL->_parent->_right = sonL;
				}
			}
			parent = sonL;
		}

		Node* _Find(Node* root, const K& key)
		{
			if (root == NULL)
				return NULL;
			if (root->_key == key)
				return root;
			_Find(root->_left,key);
			_Find(_root->_right, key);
		}
private:
	Node* _root;
};
	