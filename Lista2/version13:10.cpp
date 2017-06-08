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


void merge_sort(vector<int>& array) {
    if (1 < array.size()) {
        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1);
        vector<int> array2(array.begin() + array.size() / 2 , array.end());
        merge_sort(array2);
        merge(array, array1, array2);
	//printf ("compares: %d \n", compares);	
    }
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
    if(p<r)
    {
        q=rand_part(A, p,r);
        quickSort(A,p,q-1);  
        quickSort(A,q+1,r);
    }
}

// * MERGE-INSERTION SORT  * //

void mergein_sort(vector<int>& array) {
//    int i = array.size();
//    int j = array.begin();
    if (array.size() <= 43) {
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

int main()
{    
    int collection, size, sort, stats, log;
    
    cout << "Podaj zbiór jaki mam wygenerować [1 - jeśli ma być ciąg losowy lub 2 - jeśli ciąg malejący ]:";
    cin >> collection;
    cout << "Wpisz wielkość zbioru:";
    cin >> size;
    cout << "Jakie sortowanie zastosować? [0 jeśli Insertion Sort, 1 jeśli Merge Sort, 2 jeśli Quick Sort]";
    cin >> sort;
    cout << "Czy wygenerować logi? [1 jeśli wygenerować logi, 0 gdy nie generować] :";
    cin >> log;
    cout << "Czy wygenerować statystyki? [1 jeśli wygenerować statystyki, 0 gdy nie generować] :";
    cin >> stats;
    //cout << collection<< endl;
   // printf("%d  %d  %d  %d  %d", collection, size, sort, stats, log);
    
    switch(stats){
    case 0:
	    switch(collection)
	    {
	    case 1:
		arr= generate_list_random(size);
		break;
	    case 2:
		arr = generate_list_descending(size);
		break;
	    }

	    switch (sort)
	    {
	    case 0:
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr [g];
		    	printf("%d, ", a);
		    }
		}
		printf("\n");
	
		insertion_sort(&arr , log);
		printf("Insertion Sort \n");
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr[g];
			printf("%d, ", a);
		    }
		}
	    	printf("\n");
		break;

	    case 1:
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr [g];
		    	printf("%d, ", a);
		    }
		}
		printf("\n");
		start = clock();

		mergein_sort(arr);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

		printf("time: %f \n", total);
	
		printf("Merge Sort \n");
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr[g];
			printf("%d, ", a);
		    }
		}
		cout <<"swaps:"<< swaps << endl;
	    	cout <<"compares:"<< compares << endl;
	    	printf("\n");
		break;

	    case 2:
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr [g];
		    	printf("%d, ", a);
		    }
		}
		printf("\n");
		start = clock();
		quickSort2(arr, 0, arr.size()-1);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		
		printf("Quick Sort zrandomizowany: %f \n", total);
		printf("swaps:%ld compares: %ld", swaps, compares);

//			    switch(collection)
//	    {
//	    case 1:
//		arr= generate_list_random(size);
//		break;
//	    case 2:
//		arr = generate_list_descending(size);
//		break;
//	    }

//		start = clock();
//		quickSort2(arr, 0, arr.size()-1);
//		stop = clock();
//		total = (double)(stop- start) /CLOCKS_PER_SEC;
//		
//		printf("Quick Sort nieHoare: %f \n", total);
		if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr[g];
			printf("%d, ", a);
		    }
		}
	    	printf("\n");
		break;
	    }
	    break;
    case 1:
	    switch (sort)
	    {
	    case 0:	    
		FILE * fp;
		FILE * times;
		fp = fopen ("insertion.txt", "w+");
		times= fopen("insertionTimes.txt", "w+");
		   
		for (int i = 1; i<= 100; i++){
		compares= 0;
		swaps = 0;
		switch(collection)
	    	{
	    	case 1:
		    arr= generate_list_random(i*100);
		    break;
	    	case 2:
		    arr = generate_list_descending(i*100);
		    break;
	   	}


		start = clock();
		insertion_sort(&arr, 0);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'insertion.txt' using 1:2 with dots, 'insertion.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'insertionTimes.txt' using 1:2 with points\"");
	    break;

	    case 1:	    

		fp = fopen ("merge.txt", "w+");
		times= fopen("mergeTimes.txt", "w+");
		   
		for (int i = 1; i<= 100; i++){
		    compares= 0;
		    swaps = 0;
		    switch(collection)
	    	    {
	    	    case 1:
		    	arr= generate_list_random(i*100);
		    	break;
	    	    case 2:
		    	arr = generate_list_descending(i*100);
		    	break;
	   	    }


		start = clock();

		merge_sort(arr);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'merge.txt' using 1:2 with dots, 'merge.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'mergeTimes.txt' using 1:2 with points\"");
	    break;

	    case 2:	    
		//FILE * fp;
		//FILE * times;
		fp = fopen ("quick.txt", "w+");
		times= fopen("quickTimes.txt", "w+");
		   
		for (int i = 1; i<= 100; i++){
		compares= 0;
		swaps = 0;
		switch(collection)
	    	{
	    	case 1:
		    arr= generate_list_random(i*100);
		    break;
	    	case 2:
		    arr = generate_list_descending(i*100);
		    break;
	        }


		start = clock();
		quickSort(arr, 0, arr.size()-1);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'quick.txt' using 1:2 with dots, 'quick.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'quickTimes.txt' using 1:2 with points\"");
	    break;

	    case 3:	    

		fp = fopen ("mergein.txt", "w+");
		times= fopen("mergeinTimes.txt", "w+");
		   
		for (int i = 1; i<= 100; i++){
		    compares= 0;
		    swaps = 0;
		    switch(collection)
	    	    {
	    	    case 1:
		    	arr= generate_list_random(i*100);
		    	break;
	    	    case 2:
		    	arr = generate_list_descending(i*100);
		    	break;
	   	    }


		start = clock();

		mergein_sort(arr);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'mergein.txt' using 1:2 with dots, 'mergein.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'mergeinTimes.txt' using 1:2 with points\"");
	    break;



	break;
	}
}

    



return 0; 
}

