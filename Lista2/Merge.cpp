#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;
vector <int> arr;
vector <int> tmp;
clock_t start, stop;
double total;
long swaps = 0;
long compares = 0;




/* Generators of lists*/
vector<int> generate_list_random(int size)
{
    vector<int> arr;
    /* initialize random seed: */
    srand (time(NULL));
    for(int i = 0; i < size; i++)
    {
        if(rand()%512 > 255)
            arr.push_back(rand()%(size+1));
        else
            arr.push_back(rand()%(size+1));
    }
    return arr;
}

vector<int> generate_list_descending(int size)
{
    vector<int> arr;
    /* initialize random seed: */
    srand (time(NULL));
    for(int i = 0; i < size; i++)
    {
	arr.push_back(size- i);
    }
    return arr;
}


/* INSERTION SORT*/
void insertion_sort (vector <int> *array, int log)
{	
    int key;
    int j;
	
    if (log > 0)
    {
        printf("wielkość tablicy: %ld ", array->size());
    }
    	
    for(int i=1; i<array-> size(); i++)
    {
	key = (*array)[i];
	if (log > 0)
    	{
    	printf("\nkey: %d\n", key);
    	}

    	j = i-1;

    
    	while ( j >= 0 && (*array)[j] > key)
   	{	
	    compares ++;
	    if (log > 0)
	    {
	        printf("compare: %d@[%0d], %d\n", (*array)[j], j, key);
	       	printf("swaps: %d , %d \n ", (*array)[j], key);
	    }	
	    (*array)[j+1] = (*array)[j];
			
	    //printf("swaps: %d , %d \n ", (*array)[j+1], (*array)[j]); // zamiana klucza na swoje miejsce
	    swaps ++;
	    j--;
    	}
		
        (*array)[j+ 1]= key;	
    }
    //for(int i=1; i<array-> size(); i++)
    //cout <<"swaps:"<< swaps << endl;
    //cout <<"compares:"<< compares << endl;
    //printf ("swap: %ld \n", swaps);
    //printf ("compares: %d \n", compares);	

}

/* MERGE SORT*/

void merge(vector<int>& array, vector<int>& array1, vector<int>& array2) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
	//printf("compare: %d, %d\n", (array1)[i], array2[j]);
	compares ++ ;
        if(array1.at(i) <= array2.at(j)){
		compares ++ ;
		
		
            array.push_back(array1.at(i));
            i++;
        }else if(array1.at(i) > array2.at(j)){
		 swaps ++ ;
		//printf("swaps: %d , %d \n ", array1[i], array2[j]);
            array.push_back(array2.at(j));
            j++;
        }
        k++;
    }

    while(i < array1.size()){
        array.push_back(array1.at(i));
        i++;
    }

    while(j < array2.size()){
        array.push_back(array2.at(j));
        j++;
    }
	//printf ("compares: %d \n", compares);	
}


void mergein_sort(vector<int>& array) {
//    int i = array.size();
//    int j = array.begin();
    if (array.size() <= 10) {
    insertion_sort(&array,0);
    }


    else{




        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1);
        vector<int> array2(array.begin() + array.size() / 2 , array.end());
        merge_sort(array2);
        merge(array, array1, array2);
	//printf ("compares: %d \n", compares);	
    }
}

void merge_sort2(vector<int>& array) {
    if (1 < array.size()) {
        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1);
        vector<int> array2(array.begin() + array.size() / 2 , array.end());
        merge_sort(array2);
        merge(array, array1, array2);
	//printf ("compares: %d \n", compares);	
    }
}

int main()
{ 
arr= generate_list_descending(10000);
//for(int g = 0; g < arr.size(); g++)
//{
//int a = arr [g];
//printf("%d, ", a);
//}
//printf("\n");


		start = clock();
		merge_sort(arr);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		printf("mergeint: %f", total);
		printf("compares: %ld swaps: %ld", compares, swaps);
arr= generate_list_descending(10000);

		start = clock();
		merge_sort2(arr);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		printf("mergesort: %f", total);
		printf("compares: %ld swaps: %ld", compares, swaps);
//for(int g = 0; g < arr.size(); g++)
//{
//int a = arr [g];
//printf("%d, ", a);
//}
//printf("\n");

return 0;

}


















