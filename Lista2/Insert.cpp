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
//#include <chrono>
#include <fstream>

using namespace std;
vector <int> arr;
vector <int> tmp;
clock_t start, stop;
double total;
long swaps = 0;
long compares = 0;

/* Generators of lists*/
vector<int> generate_list_random(int size, int max)
{
    vector<int> arr;
    /* initialize random seed: */
  srand (time(NULL));
    for(int i = 0; i < size; i++)
    {
        if(rand()%512 > 255)
            arr.push_back(rand()%(max+1));
        else
            arr.push_back(rand()%(max+1));
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
void insertion_sort (vector <int> *array)
{	int key;
	int j;
	
	
	//printf("wielkość tablicy: %ld ", array->size());
    	for(int i=1; i<array-> size(); i++)
	{
		key = (*array)[i];
//		printf("\nkey: %d\n", key);
		j = i-1;
		//printf("compare: %d@[%0d], %d\n", (*array)[j], j, key);
		
		while ( j >= 0 && (*array)[j] > key)
		{	
			compares ++;
//			printf("compare: %d@[%0d], %d\n", (*array)[j], j, key);
//			printf("swaps: %d , %d \n ", (*array)[j], key);
			(*array)[j+1] = (*array)[j];
			
			//printf("swaps: %d , %d \n ", (*array)[j+1], (*array)[j]); // zamiana klucza na swoje miejsce
			swaps ++;
			j--;
		}
		
		(*array)[j+ 1]= key;	
	}
	//for(int i=1; i<array-> size(); i++)
	
	//printf ("swap: %ld \n", swaps);
	//printf ("compares: %d \n", compares);	

}


void merge(vector<int>& array, vector<int>& array1, vector<int>& array2) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
	//printf("compare: %d, %d\n", (array1)[i], array2[j]);
	compares ++ ;
        if(array1.at(i) <= array2.at(j)){
		compares ++ ;
		//printf("swaps: %d , %d \n ", (*array)[j], key);
		//compares ++ ;
		swaps ++ ;
            array.push_back(array1.at(i));
            i++;
        }else if(array1.at(i) > array2.at(j)){
		compares +=2 ; swaps ++ ;
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


void merge_sort(vector<int>& array) {
    if (1 < array.size()) {
        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1);
        vector<int> array2(array.begin() + array.size() / 2, array.end());
        merge_sort(array2);
        merge(array, array1, array2);
	//printf ("compares: %d \n", compares);	
    }
}


// * QUICK SORT  * //

int partition(vector<int>& A, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	int x = A[p]; // obieramy x 
	int i = p, j = r, w; // i, j - indeksy w tabeli
	while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (A[j] > x) // dopoki elementy sa wieksze od x 
			j--;
		while (A[i] < x) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = A[i];
			A[i] = A[j];
			A[j] = w;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

int rand_part(vector<int>& A,int p,int r)
 {
        int i=p+rand()%(r-p+1);
        int temp;
        temp=A[r];
        A[r]=A[i];
        A[i]=temp;
        return partition(A,p,r);
  }

void quickSort(vector<int>& A, int p,int r)
{
    int q;
    if(p<r)
    {
        q=rand_part(A, p,r);
        quickSort(A,p,q);  
        quickSort(A,q+1,r);
    }
}



int main()
{
   FILE * fp;
   fp = fopen ("merge.txt", "w+");
   
for (int i = 1; i<= 100; i++){
compares= 0;
swaps = 0;
arr = generate_list_descending(i*100);
//for(int g = 0; g < arr.size(); g++)
//{
//int a = arr [g];
//printf("%d, ", a);
//}
//printf("\n");

start = clock();
//insertion_sort(&arr);
//quickSort(arr, 0, arr.size()-1);
merge_sort(arr);
stop = clock();
total = (double)(stop- start) /CLOCKS_PER_SEC;

//printf("time: %f \n", total);
//printf ("compares: %ld \n", compares);	

fprintf(fp, "%d %ld %ld \n", i*100, compares, swaps);

////arr [0] = 9;
//for(int g = 0; g < arr.size(); g++)
//{
//int a = arr[g];
//printf("%d, ", a);
//}
//printf("\n");
}
fclose(fp);
return 0; 
}

