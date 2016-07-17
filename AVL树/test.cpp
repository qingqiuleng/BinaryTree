#include"AVLtree.h"

void test()
{
	AVLTree<int, int> a1;
	int arr[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (int i = 0; i < 10; i++)
	{
		a1.Insert(arr[i], i);
	}


	//cout << a1.Find(4)->_value << endl;

	cout << a1.IsBlance() << endl;;
}
int main()
{
	test();
	system("pause");
	return 0;
}