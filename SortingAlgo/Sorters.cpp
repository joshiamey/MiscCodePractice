/*
 * Sorters.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: ameya
 */
#include <algorithm>
#include "Sorters.h"

namespace Sorters
{
	namespace
	{
		void doMerge(std::vector<int>& arr, int start, int mid, int end)
		{
			auto sizel = mid - start + 1;
			auto sizer = end - mid;

			std::vector<int> left;
			std::vector<int> right;

			for(auto i = 0 ; i < sizel; ++i)
			{
				left.push_back(arr[start + i]);
			}

			for(auto j = 0 ; j < sizer; ++j)
			{
				right.push_back(arr[mid + j]);
			}

			auto i = 0;
			auto j = 0;

			for(auto k = 0; k < end; ++k)
			{
				if(left[i] <= right[j])
				{
					arr[k] = left[i];
					++i;
				}
				else
				{
					arr[k] = right[j];
					++j;
				}
			}
		}

		void doMergeSort(std::vector<int>& arr, int start, int end)
		{
			if(start < end)
			{
				auto mid = (end + start)/2;

				doMergeSort(arr,start, mid);
				doMergeSort(arr,mid+1,end);

				doMerge(arr,start,mid,end);

			}
		}
	}

	void selectionSort(std::vector<int>& arr)
	{
		if(arr.size() > 1)
		{
			for(auto i = 0; i < arr.size(); ++i)
			{
				auto min = i;
				for(auto j = i + 1; j < arr.size(); ++j)
				{
					if(arr[j] < arr[min])
					{
						min = j;
					}
				}

				std::swap(arr[i], arr[min]);
			}

		}
	}

	void insertionSort(std::vector<int>& arr)
	{


	}


	void mergeSort(std::vector<int>& arr)
	{
		if(arr.size() <= 1)
			return;

		doMergeSort(arr,0,arr.size() - 1);
	}

}
