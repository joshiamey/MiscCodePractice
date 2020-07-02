#include <iostream>
#include "Sorters.h"
#include "Heap.h"
using namespace std;

int main(int argc, char **argv)
{
	std::vector<int> arr = {1, 7, 9, 6, 8, 2, 5, 4, 3, 0};
	//std::vector<int> arr = {1, 4, 3, 7, 8, 9, 10};

	//	std::vector<int> arr= {5,1,8,2,4,3};

	//	std::vector<int> arr= {'E','A','S','Y', 'Q', 'U','E','S','T','I','O','N'};

	//	Sorters::selectionSort(arr);

	//Sorters::mergeSort(arr);
	Heap::sort(arr);

	cout << "After sorting: " << endl;

	for (auto a : arr)
	{
		cout << a << " ";
	}

	cout << endl;
	return 0;
}
