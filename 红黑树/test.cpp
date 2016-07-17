#include"RBTree.h"

void test()
{
	int arr[9] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> r1;
	
	for (int i = 0; i < 9; i++)
	{
		r1.Insert(arr[i],i);
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}