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

	bool Insert(const K& key,const V& value)//����
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)//�ҵ�Ҫ�����λ��
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
		if (key < parent->_key)//���ڵ��������
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else//���ڵ��������
		{
			parent->_right = new Node(key, value);
			cur->_parent = parent;
		}

		//����ƽ������
		while (cur)
		{
			cur->_bf = _Height(cur->_right) - _Height(cur->_left);//�ӵ�ǰ�ڵ㿪ʼ����ƽ������
			if (cur->_bf != 0 && cur->_bf != 1 && cur->_bf != -1)
			{
				if (cur->_bf == 2 && cur->_right->_bf == 1)//����
				{
					_RotateL(cur);
				}
				else if (cur->_bf==-2&&cur->_left->_bf==-1)//�ҵ���
				{
					_RotateR(cur);
				}
				else if (cur->_bf==-2&&cur->_left->_bf==1)//����˫��
				{
					_RotateLR(cur);
				}
				else if (cur->_bf == 2 && cur->_right->_bf == -1)//����˫��
				{
					_RotateRL(cur);
				}
			}
			cur = cur->_parent;//���ϵ���
		}
	}
	Node* Find(const K& key)//����
	{
		return _Find(_root, key);
	}

	bool IsBlance()//����Ƿ�ϸ�ÿ���ڵ������Ƿ����2��С��-2��
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
			cout << "ƽ�����ӳ���" << endl;
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

	void _RotateL(Node*& parent)//����,�����ã���Ϊparent�ᱻ�ı�
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
		parent->_bf = sonR->_bf = 0;//��ƽ�����ӵ���

		if (sonR->_parent == NULL)
			_root = sonR;
		else
		{
			if (sonR->_parent->_key > sonR->_key)
				sonR->_parent->_left = sonR; // ���ӵ���·
			else
				sonR->_parent->_right = sonR;//���ӵ���·
		}
		parent = sonR;
	}

	void _RotateR(Node*& parent)//�ҵ����������ã���Ϊparent�ᱻ�ı�
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

		//��sonL�ĸ��׽ڵ��������
		if (sonL->_parent == NULL)//���׽ڵ�Ϊ��
			_root = sonL;
		else//���׽ڵ㲻Ϊ��
		{
			if (sonL->_parent->_key > sonL->_key)//���ӵ���·
				sonL->_parent->_left = sonL;
			else
				sonL->_parent->_right = sonL;//������·
		}
		parent = sonL;
	} 

	void _RotateLR(Node*& parent)//����˫��
	{
		Node* pNode = parent;
		Node* sonL = parent->_left;
		Node* sonLR = sonL->_right;
		_RotateL(parent->_left);
		_RotateR(parent);
		//�ڽ���������֮��ƽ�����������⣬��Ҫ���µ���
		//sonLRƽ��������3��������ֱ���0��1��-1
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

	void _RotateRL(Node*& parent)//����˫��
	{
		Node* pNode = parent;
		Node* sonR = parent->_right;
		Node* sonRL = sonR->_left;
		_RotateR(parent->_right);
		_RotateL(parent);
		//�ڽ���������֮��ƽ�����������⣬��Ҫ���µ���
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

	int _Height(Node* parent)//�߶�
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











