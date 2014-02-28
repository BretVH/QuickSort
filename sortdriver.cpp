#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "insertionSort.cpp"



using namespace std;

/*The following functions except a main are some utilities*/
// array initialization with random numbers. It generate an array with a random order
void initArray( vector<int> &array, int randMax ) {
  int size = array.size( );

  for ( int i = 0; i < size; ) {
    int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
    bool hit = false;
    for ( int j = 0; j < i; j++ ) {
      if ( array[j] == tmp ) {
        hit = true;
        break;
      }
    }
    if ( hit )
      continue;
    array[i] = tmp;
    i++;
  }
}

// array printing in to console as well as into a file
void printArray( vector<int> &array, char arrayName[],ofstream &myfile) {
  int size = array.size( );

  for ( int i = 0; i < size; i++ ){
      stringstream out;
      out<<array[i];
      myfile<<arrayName<<"["<<i<<"] = "<<out.str()<<"\n";
      cout << arrayName << "[" << i << "] = " << array[i] << endl;
  }
 }

// check if the array is sorted. If it is unsorted return -1, if sorted return 1
int isSorted( vector<int> &array) {
  int size = array.size( );

  for ( int i = 1; i < size; i++ ){
      if (array[i]<array[i-1]) return -1;
  }
  return 1;
}
// performance evaluation: the time is shown as a unit of milliseconds
double elapsed( timeval &startTime, timeval &endTime ) {
        
  return ( endTime.tv_sec - startTime.tv_sec ) * 1000000
    + ( endTime.tv_usec - startTime.tv_usec );
}

//print the string "line" into a console window as well as to a file
void writeOutput(ofstream &myfile, string line){
     myfile<<line<<endl;
     cout<<line<<endl;        
     
}

int main( int argc, char* argv[] ) {
  // verify arguments
  if ( argc != 3 ) {
    cerr << "usage: quicksort filename ssz" << endl;
    return -1;
  }
  
  //get the output file name
  char* filename = argv[1];
  
  //get the ssz 
  int ssz  = atoi( argv[2] );
  if ( ssz <= 0 ) {
    cerr << "ssz must be positive" << endl;
    return -1;
  }
  
   
  // Open a file to write your results
  
  ofstream myfile (filename);
  if(!myfile.is_open()){
      cout << "Unable to open file: Terminate program";
      return -1;       
  }
    
  
  stringstream ss; //This is a string stream variable will be used for a parameter
  // Write the program name
    ss<< "Program 4: Improved Quick Sort Algorithms : output = "<<filename<<"  ssz="<<ssz<<endl;
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse
 
  /*Check the the correctness of your improved function*/  
  // array generation     
  int size = 30;
  srand( 1 ); // give random seed as 1
  vector<int> original( size );
  initArray( original, size );
  
  //copy the original array to other arrays
  vector<int> copy1 = original;
  vector<int> copy2 = original; 
  
  // Check if your quick median of 3 is correct
  writeOutput(myfile, "\nBefore quick median of 3 sort");
  printArray(original, "original", myfile);
  quicksortMedianOf3( original );
  writeOutput(myfile, "\nAfter quick MedianOf 3 sort");
  printArray(original, "items", myfile);
  ss<<"\nis sorted?  "<<((isSorted(original)>0)?"Yes":"No");
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse
  
  
  // Check if your quick insertion is correct
  writeOutput(myfile, "\nBefore quick insertion sort");
  printArray(copy1, "copy1", myfile);  
  quicksortInsertion(copy1, 5);
  writeOutput(myfile, "\nAfter quickinsertionSort");
  printArray(copy1, "copy1", myfile);
  ss<<"\nis sorted?  "<<((isSorted(copy1)>0)?"Yes":"No")<<endl;
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse
  
  // Check if your quick insertion median of 3 is correct  
  writeOutput(myfile, "\nBefore quick insertion median 3 sort");
  printArray(copy2, "copy2", myfile);  
  quicksortM3Insertion(copy2, 5);
  writeOutput(myfile, "\nAfter quicksortM3Insertion");
  printArray(copy2, "items3", myfile);
  ss<<"\nis sorted?  "<<((isSorted(copy2)>0)?"Yes":"No")<<endl;
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse
  
  
  /*Now you will compare the performances of algorithms with very large data*/
  /*Remember all of your sorting algorithm overwrite the unsorted initial array */
  /*with the sorted result. */
  /*So, if you want to compare the performances of each algorithm, */
  /*you need to use the same data*/
  
  struct timeval startTime, endTime;      //Give the time structure to print the elapsed time
  size = 1000; //set the size of array as big
  srand(100); //use different random seed to generate in a different way
  vector<int> items(size);
  initArray( items, size ); // Generate 1000 size of random array
  
  //copy the generated items into different separate arrays. 
  vector<int> items2 = items;
  vector<int> items3 = items;
  vector<int> items4 = items;
  vector<int> items5 = items;
  vector<int> items6 = items;
   
 /*compare the performances of different algorithms*/
  
  // insertion sort
  ss<<"\nINSERTION SORT"<<"\nBefore: is sorted?  "
          <<((isSorted(items)>0)?"Yes":"No")<<endl;
  writeOutput(myfile, ss.str());
  ss.str("");
  gettimeofday( &startTime, 0 );
  insertionSort(items, size );
  gettimeofday( &endTime, 0 );
  ss<<"After: is sorted?  "<<((isSorted(items)>0)?"Yes":"No")<<endl
    <<"Insertion Sort: elapsed time: " << elapsed( startTime, endTime )<<" millisec"<< endl;
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse

  // Merge Sort
  ss<<"\nMERGE SORT"<<"\nBefore: is sorted?  "<<((isSorted(items2)>0)?"Yes":"No")<<endl;
  writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  gettimeofday( &startTime, 0 );
  mergesort(items2 );
  gettimeofday( &endTime, 0 );
  ss <<"After: is sorted?  "<<((isSorted(items2)>0)?"Yes":"No")<<endl
          << "Merge Sort: elapsed time: " << elapsed( startTime, endTime )
          <<" millisec"<< endl;
  writeOutput(myfile, ss.str());
  ss.str(""); //reset the string stream for reuse
   
  //Quick Sort
  ss<<"\nQUICK SORT"
          <<"\nBefore: is sorted?  "<<((isSorted(items3)>0)?"Yes":"No")<<endl;
  writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  gettimeofday( &startTime, 0 );
  quicksort(items3 );
  gettimeofday( &endTime, 0 );
  ss<<"After: is sorted?  "<<((isSorted(items3)>0)?"Yes":"No")<<endl
        << "Quick Sort: elapsed time: " << elapsed( startTime, endTime ) <<" millisec"<< endl;
  writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  
  //Quick Sort Median-3
  ss<<"\nQUICK-Median of 3 Sort"<<endl
  <<"Before: is sorted?  "<<((isSorted(items4)>0)?"Yes":"No")<<endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  gettimeofday( &startTime, 0 );
  quicksortMedianOf3(items4 );
  gettimeofday( &endTime, 0 );
  ss<<"After: is sorted?  "<<((isSorted(items4)>0)?"Yes":"No")<<endl
   << "Quick Sort Median-3: elapsed time: " << elapsed( startTime, endTime ) <<" millisec"<< endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  
  //Quick+Insertion Sort : Give the small size as 16
  
   ss<<"\nQUICK-Insertion Sort"<<endl
  <<"Before: is sorted?  "<<((isSorted(items5)>0)?"Yes":"No")<<endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  gettimeofday( &startTime, 0 );
  quicksortInsertion(items5, ssz);
  gettimeofday( &endTime, 0 );
  ss<<"After: is sorted?  "<<((isSorted(items5)>0)?"Yes":"No")<<endl
  << "Quick-Insertion Sort: elapsed time: " << elapsed( startTime, endTime ) <<" millisec"<< endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  
  
  //Quick-MedianOf3 + Insertion: Give the small size as 16
  ss<<"\nQUICK-Median3-Insertion Sort"<<endl
     <<"Before: is sorted?  "<<((isSorted(items6)>0)?"Yes":"No")<<endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  gettimeofday( &startTime, 0 );
  quicksortM3Insertion(items6, ssz);
  gettimeofday( &endTime, 0 );
  ss<<"After: is sorted?  "<<((isSorted(items6)>0)?"Yes":"No")<<endl
   << "QUICK-Median3-Insertion: elapsed time: " << elapsed( startTime, endTime ) <<" millisec"<< endl;
   writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
     
  /*Compare the 4 algorithms with different data*/
    
 int iter = 1000; // The number of iteration
 size = 1000; // set the size of array
 double sum_q=0.0, sum_qm3 = 0.0, sum_qin = 0.0, sum_qinm3 = 0.0;

 
 for (int i=0; i<iter; i++){
     srand(iter+i); // give different random seed for each iteration
     vector<int> array_q( size );
     initArray(array_q, size);//give initial array
       
     ///Your implementation is here!! You should sum the running time of each algorithm here, so that we can get average of each after this loop
	 vector<int> items7 = array_q;  //copy of current array for quicksortMedianOf3
	 vector<int> items8 = array_q;
	 vector<int> items9 = array_q;
	 gettimeofday( &startTime, NULL);  //get current time
	 quicksort(array_q);              //run quicksort
	 gettimeofday( &endTime, NULL);   //get current time
	 sum_q += elapsed(startTime, endTime); //calculate time elapsed and add it to running sum of quicksort running time for the 1000 iterations of array_q
	 gettimeofday( &startTime, NULL); 
	 quicksortMedianOf3(items7);      //run quicksortMedianOf3 
     gettimeofday( &endTime, NULL );
	 sum_qm3 += elapsed(startTime, endTime);  //add elapsed time to running sum for quicksortMedianOf3
	 gettimeofday( &startTime, NULL );
	 quicksortInsertion(items8, ssz);    //run quicksortInsertion
     gettimeofday( &endTime, NULL );
	 sum_qin += elapsed(startTime, endTime);   //add elapsed time to running sum for quicksortInsertion
     gettimeofday( &startTime, NULL);
     quicksortM3Insertion(items9, ssz);   //run quicksortM3Insertion
     gettimeofday( &endTime, NULL );
	 sum_qinm3 += elapsed(startTime, endTime);   //add elapsed time to running sum for quicksortM3Insertion
  }
 
 // print out the average performace for each algorithm
   
  ss << "\n\nAverage: Quick sort Process took " << sum_q/iter << " millisec" << '\n'
    << "Average: Quick-Medianof3 Process took " << sum_qm3/iter << " millisec" << '\n'
    << "Average: Quick-Insertion sort Process took " << sum_qin/iter << " millisec" << '\n'
    << "Average: Quick-Insertion-Medianof3 Process took " << sum_qinm3/iter << " millisec" << '\n';
 
  writeOutput(myfile, ss.str());  
  ss.str(""); //reset the string stream for reuse
  
  myfile.close(); // close the file
  

  return 0;
}
