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
   // unsorted = first index of the unsorted region,
   // loc = index of insertion in the sorted region,
   // nextItem = next item in the unsorted region

   // initially, sorted region is theArray[0],
   //            unsorted region is theArray[1..n-1];
   // in general, sorted region is
   //             theArray[0..unsorted-1],
   // unsorted region is theArray[unsorted..n-1]

   for (int unsorted = 1; unsorted < n; ++unsorted)
   {  // Invariant: theArray[0..unsorted-1] is sorted

      // find the right position (loc) in
      // theArray[0..unsorted] for theArray[unsorted],
      // which is the first item in the unsorted
      // region; shift, if necessary, to make room
      Comparable nextItem = a[unsorted];
      int loc = unsorted;

      for (;(loc > 0) && (a[loc-1 ]> nextItem);
            --loc)
         // shift theArray[loc-1] to the right
         a[loc] = a[loc-1];

      // Assertion: theArray[loc] is where nextItem
      // belongs

      // insert nextItem into Sorted region
      a[loc] = nextItem;
   }  // end for
}  // end insertionSort



