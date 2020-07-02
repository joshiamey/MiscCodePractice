#pragma once
#include <vector>
#include <iostream>

class Heap
{
private:
    static int parent(int i) { return (i / 2) - 1; }
    static int left(int i) { return (2 * i) + 1; }
    static int right(int i) { return (2 * i) + 2; }

    static void minHeapify(std::vector<int> &arr, int i, int N)
    {
        auto smallest = i;
        auto rightchild = right(i);
        auto leftchild = left(i);

        if (rightchild <= N && arr[rightchild] < arr[smallest])
        {
            smallest = rightchild;
        }

        if (rightchild <= N && arr[leftchild] < arr[smallest])
        {
            smallest = leftchild;
        }

        if (smallest != i)
        {
            std::swap(arr[i], arr[smallest]);
            minHeapify(arr, smallest, N);
        }
    }

    static void maxHeapify(std::vector<int> &arr, int i, int N)
    {
        auto largest = i;
        auto rightchild = right(i);
        auto leftchild = left(i);

        if (rightchild <= N && arr[rightchild] > arr[largest])
        {
            largest = rightchild;
        }

        if (leftchild <= N && arr[leftchild] > arr[largest])
        {
            largest = leftchild;
        }

        if (largest != i)
        {
            std::swap(arr[i], arr[largest]);
            maxHeapify(arr, largest, N);
        }
    }

public:
    Heap(/* args */) = delete;
    ~Heap() = delete;

    static void buildMaxHeap(std::vector<int> &arr)
    {
        int N = arr.size() - 1;

        // The leaf nodes are N/2 to N
        // build the min heap from bottom up manner
        for (auto i = N / 2; i >= 0; --i)
        {
            maxHeapify(arr, i, N);
        }
    }

    static void sort(std::vector<int> &arr)
    {
        // Build a maxheap
        buildMaxHeap(arr);
        int N = arr.size() - 1;

        while (N >= 1)
        {
            std::swap(arr[0], arr[N]);
            N--;
            maxHeapify(arr, 0, N);
        }
    }
};
