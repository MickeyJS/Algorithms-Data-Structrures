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


// * QUICK SORT  * //

int partition(vector <int> &A, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
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
int partition2(vector <int> &A, int p, int r) { //partition z ksiazki cormena
int x=A[r];
int i= p-1;
for(int j=p; j <= r-1; j++)
{
compares++;
if(A[j]<=x)
{
i++;
int w= A[i];
A[i]=A[j];
A[j]=w;
swaps++;
}
}
int w=A[i+1];
A[i+1]=A[r];
A[r]=w;
swaps++;
return i+1;
}

int rand_part(vector<int>& A,int p,int r) //używam zrandomizowanego partition
 {
    int i=p+rand()%(r-p+1);
    int temp;
   // printf("Pierwszy element %d z pola %d zamieniamy z wylosowanym elementem: %d z pola %d", A[p], p, A[i], i);
    swaps++;
    temp=A[r];		//zamiana losowego elementu z ostatnim
    A[r]=A[i];
    A[i]=temp;
    //printf("Piwot to: %d z pola %d", A[p], i);
    return partition2(A,p,r);
  }

void quickSort(vector<int>& A, int p,int r)
{
    int q;
    if(p<r)
    {
        q=partition(A, p,r);
        quickSort(A,p,q);  
        quickSort(A,q+1,r);
    }
}

void quickSort2(vector<int>& A, int p,int r)
{
    int q;

    if(r-p <= 25){
    insertion_sort(&A,0);
    }

    else
    {
        q=rand_part(A, p,r);
        quickSort2(A,p,q-1);  
        quickSort2(A,q+1,r);
    }
}





int main()
{ 
arr= generate_list_descending(100);
for(int g = 0; g < arr.size(); g++)
{
int a = arr [g];
printf("%d, ", a);
}
printf("\n");




		start = clock();
		quickSort(arr, 0, arr.size()-1);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		printf("mergesort: %f", total);
		printf("compares: %ld swaps: %ld", compares, swaps);
for(int g = 0; g < arr.size(); g++)
{
int a = arr [g];
printf("%d, ", a);
}
printf("\n");

return 0;

}






