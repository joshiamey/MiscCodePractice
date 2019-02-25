/*
 * Sorters.h
 *
 *  Created on: Feb 12, 2019
 *      Author: ameya
 */

#ifndef SORTERS_H_
#define SORTERS_H_
#include <vector>

namespace Sorters {
	void insertionSort(std::vector<int>& arr);

	void selectionSort(std::vector<int>& arr);

	void bubbleSort(std::vector<int>& arr);

	void mergeSort(std::vector<int>& arr);
};

#endif /* SORTERS_H_ */
