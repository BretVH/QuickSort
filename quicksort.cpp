#include <vector>

using namespace std;

template <class Comparable>
void objectSwap(Comparable &lhs, Comparable &rhs) {
	Comparable tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

template <class Comparable>
void choosePivot(vector<Comparable> &a, int first, int last) {
	int middle = (first + last) / 2;
	objectSwap(a[first], a[middle]);
}

template <class Comparable>
void partition(vector<Comparable> &a, int first, int last, int &pivotIndex) {
	// place the pivot in a[first]
	choosePivot(a, first, last);
	Comparable pivot = a[first];
	int lastS1 = first;
	int firstUnknown = first + 1;

	for (; firstUnknown <= last; ++firstUnknown) {
		if (a[firstUnknown] < pivot) {
			++lastS1;
			objectSwap(a[firstUnknown], a[lastS1]);
		}
		// else item from unknown belongs in S2
	}
	// decide a new pivot
	objectSwap(a[first], a[lastS1]);
	pivotIndex = lastS1;
}

template <class Comparable>
void quicksort(vector<Comparable> &a, int first, int last) {
	int pivotIndex;

	if (first < last) {
		partition(a, first, last, pivotIndex);
		quicksort(a, first, pivotIndex - 1);
		quicksort(a, pivotIndex + 1, last);
	}
}

template <class Comparable>
void quicksort(vector<Comparable> &a) {
	quicksort(a, 0, a.size() - 1);
}

// quicksortMedianOf3 implementation is here
/**
* choosePivotMedian
*  chooses pivot, based on the median of 3 values,
*  placing the median in index last, the smallest value in index first,
*  the largest in index middle,
* @param a
* @param first
* @param last
*/
template <class Comparable>
int choosePivotMedian(vector<Comparable> &a, int first, int last)
{
	int middle = (first + last) / 2;
	if (a[first] > a[middle])
		objectSwap(a[first], a[middle]);
	if (a[first] > a[last])
		objectSwap(a[first], a[last]);
	if (a[middle] < a[last])
		objectSwap(a[middle], a[last]);
	return last;
}

/**
* partitionMedian
* calls choosePivotMedian to choose a pivot value, moves data around the pivot value,
* and sets pivotIndex
* @param a
* @param first
* @param list
* @param pivotIndex
*/
template <class Comparable>
void partitionMedian(vector<Comparable> &a, int first, int last, int &pivotIndex)
{
	int median = choosePivotMedian(a, first, last);
	Comparable pivot = a[median];
	int front = first;
	int back = last;

	for (int i = front; i < last; i++)  //traverse array from front to last - 1
	{
		if (a[i] < pivot)   // if item smaller than pivot it belongs in 1st array
		{
			objectSwap(a[i], a[front]);  //swap with front
			front++;                     //increment front
		}
	}									//otherwise it belongs in the 2nd array
	objectSwap(a[front], a[last]);  //swap 1st element in second array with pivot
	pivotIndex = front;             //set pivotIndex to location of pivot
}

/**
* quickSortMedianOf3
* implements the recursive quick sort Median of 3 algorithm as presented in class
* @param a
* @param first
* @param last
*/
template <class Comparable>
void quicksortMedianOf3(vector<Comparable> &a, int first, int last)
{
	int pivotIndex;

	if (first < last)
	{
		partitionMedian(a, first, last, pivotIndex);
		quicksortMedianOf3(a, first, pivotIndex - 1);
		quicksortMedianOf3(a, pivotIndex + 1, last);
	}
}

/**
* Method: quickSortMedianOf3
* calls recursive quickSortMedianOf3
* @param a
*/
template <class Comparable>
void quicksortMedianOf3(vector<Comparable> &a)
{
	quicksortMedianOf3(a, 0, a.size() - 1);
}

// quickinsertionSort implementation
//insertionSortPartial is here
/**
* insertionSortPartial
* implements insertion sort on a given range of an array
* @param a
* @param first
* @param last
*/
template <class Comparable>
void insertionSortPartial(vector<Comparable> &a, int first, int last)
{
	for (int i = first; i <= last; i++)  //traverse array from first to last
	{
		int j = i;
		Comparable test = a[i];
		while (j > 0 && a[j - 1] > test)   //shift elements right
		{
			a[j] = a[j - 1];
			j--;
		}
		a[j] = test;           //insert value into proper place
	}
}

// Then implement the quicksortInsertion
/**
* quickSortInsertion
* implements the recursive quick sort insertion algorithm as presented in class
* @param a
* @param first
* @param last
* @param ssz
*/
template <class Comparable>
void quicksortInsertion(vector<Comparable> &a, int first, int last, int ssz)
{
	int pivotIndex;
	if (first < last)
	{
		if (last - first + 1 <= ssz)  //if size of array < ssz, run insertionSortPartial
			insertionSortPartial(a, first, last);
		else
		{
			partition(a, first, last, pivotIndex);
			quicksortInsertion(a, first, pivotIndex - 1, ssz);
			quicksortInsertion(a, pivotIndex + 1, last, ssz);
		}
	}
}

/**
* quickSortInsertion
* calls the recursive quickSortInsertion
* @param a
* @param ssz
*/
template <class Comparable>
void quicksortInsertion(vector<Comparable> &a, int ssz)
{
	quicksortInsertion(a, 0, a.size() - 1, ssz);
}

//quicksortM3Insertion implementation
/**
* quickSortM3Insertion
* implements the recursive quick sort Median of 3 Insertion algorithm as presented in class
* @param a
* @param first
* @param last
* @param ssz
*/
template <class Comparable>
void quicksortM3Insertion(vector<Comparable> &a, int first, int last, int ssz)
{
	int pivotIndex;
	if (first < last)
	{
		if (last - first + 1 <= ssz)
			insertionSortPartial(a, first, last);
		else
		{
			partitionMedian(a, first, last, pivotIndex);
			quicksortM3Insertion(a, first, pivotIndex - 1, ssz);
			quicksortM3Insertion(a, pivotIndex + 1, last, ssz);
		}
	}
}

/**
* quickSortM3Insertion
* calls the recursive quickSortM3Insertion
* @param a
* @param ssz
*/
template <class Comparable>
void quicksortM3Insertion(vector<Comparable> &a, int ssz)
{
	quicksortM3Insertion(a, 0, a.size() - 1, ssz);
}
