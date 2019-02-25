#include <iostream>
#include <vector>
using std::vector;

using std::cin;

using std::cout;

using std::max;

int MaxPairwiseProductFast2(const vector<int>& numbers) {
	int n = numbers.size();

	if(n <= 0)
	{
		return -1;
	}
	if(n == 1)
	{
		return numbers[0];
	}

	auto maxa = 0;
	auto maxb = 0;
	for (int i = 0; i < n; ++i) {

		if(numbers[i] >= maxa)
		{
			maxb = maxa;
			maxa = numbers[i];
		}
		else if(numbers[i] > maxb)
		{
			maxb = numbers[i];
		}

	}


	return maxa * maxb;
}

int MaxPairwiseProduct(const vector<int>& numbers) {
	int product = 0;
	int n = numbers.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			product = max(product, numbers[i] * numbers[j]);
		}
	}
	return product;
}

int MaxPairWiseProductFast(const vector<int>& numbers)
{
 auto index1 = 0;

 for(auto i = 1 ; i < numbers.size(); ++i)
 {
	 if(numbers[i] > numbers[index1])
	 {
		 index1 = i;
	 }
 }

auto index2 = 0 ;
if(index1 == 0)
{
	index2 = 1;
}
for(auto i = 1 ; i < numbers.size(); ++i)
 {
	 if((numbers[i] >= numbers[index2]))
	 {
		 if(i != index1)
		 {
		  index2 = i;
		 }
	 }
 }

return numbers[index1] * numbers[index2];
}
int main() {
	int n;
	cin >> n;
	vector<int> numbers(n);
	for (int i = 0; i < n; ++i) {
		cin >> numbers[i];
	}
	int product = MaxPairwiseProductFast2(numbers);
	cout << product << "\n";
	return 0;
}
