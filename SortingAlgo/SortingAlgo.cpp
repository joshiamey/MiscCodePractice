#include <iostream>
#include "Sorters.h"
using namespace std;

int main(int argc, char **argv) {
	cout << "Hello world \n";

//	std::vector<int> arr= {1,7,5,6,8,2,5,4,3,0};

	std::vector<int> arr= {1,5,8,2,4,3,10};

//	std::vector<int> arr= {'E','A','S','Y', 'Q', 'U','E','S','T','I','O','N'};

//	Sorters::selectionSort(arr);

	Sorters::mergeSort(arr);

	cout << "After sorting: " << endl;

	for(auto a : arr)
	{
		cout << " " << a;
	}
	return 0;
}
