#include <vector>


using namespace std;
/** Sorts the items in an array into ascending order.
 * @pre a is an array of n items.
 * @post a is sorted into ascending order; n is unchanged.
 * @param a  The given array.
 * @param n  The size of a. */

template <class Comparable>
void insertionSort(vector<Comparable> &a, int n)
{
	// index = first index of the unsorted region,
	// sortedPosition = index of insertion in the sorted region,
	// nextItem = next item in the index region

	// initially, sorted region is theArray[0],
	// usorted region is theArray[1..n-1];
	// in general, sorted region is
	// theArray[0..index-1],
	// unsorted region is theArray[index..n-1]

	for (int index = 1; index < n; ++index)
	{  // Invariant: theArray[0..index-1] is sorted

	   // find the right position (sortedPosition) in
	   // theArray[0..index] for theArray[index],
	   // which is the first item in the index
	   // region; shift, if necessary, to make room
		Comparable nextItem = a[index];
		int sortedPosition = index;

		for (; (sortedPosition > 0) && (a[sortedPosition - 1] > nextItem);
			--sortedPosition)
			// shift theArray[sortedPosition-1] to the right
			a[sortedPosition] = a[sortedPosition - 1];

		// Assertion: theArray[sortedPosition] is where nextItem
		// belongs

		// insert nextItem into Sorted region
		a[sortedPosition] = nextItem;
	}  // end for
}  // end insertionSort



