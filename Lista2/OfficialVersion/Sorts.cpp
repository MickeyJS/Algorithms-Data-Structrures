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

void merge(vector<int>& array, vector<int>& array1, vector<int>& array2, int logs) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
	if (logs == 1)
	{	
		printf("compare: %d, %d\n", (array1)[i], array2[j]);
	}
	compares ++ ;
        if(array1.at(i) <= array2.at(j)){
		compares ++ ;
		
		
            array.push_back(array1.at(i));
            i++;
        }else if(array1.at(i) > array2.at(j)){
		 swaps ++ ;
		if (logs == 1)
		{		
		printf("swaps: %d , %d \n ", array1[i], array2[j]);
		}
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


void merge_sort(vector<int>& array, int logs) {
    if (1 < array.size()) {
        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
   	if(log>0)
	{   printf("Podzieliliśmy tablice na pierwsza połowe:\n");
	    for(int g = 0; g < array1.size(); g++)
	    {
		int a = array1 [g];
		 printf("%d, ", a);
	    }
		printf("\n");
	}
        merge_sort(array1, logs);
        vector<int> array2(array.begin() + array.size() / 2 , array.end());
   	if(log>0)
	{   printf("Podzieliliśmy tablice na drugą połowe:\n");
	    for(int g = 0; g < array2.size(); g++)
	    {
		int a = array2 [g];
		 printf("%d, ", a);
	    }
		printf("\n");
	}
        merge_sort(array2, logs);
        merge(array, array1, array2, logs);
	//printf ("compares: %d \n", compares);	
    }
}


// * QUICK SORT  * //

//int partition(vector <int> &A, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
//{
//int x = A[p]; // obieramy x
//int i = p, j = r, w; // i, j - indeksy w tabeli
//while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
//{
//while (A[j] > x) // dopoki elementy sa wieksze od x
//j--;
//while (A[i] < x) // dopoki elementy sa mniejsze od x
//i++;
//if (i < j) // zamieniamy miejscami gdy i < j
//{
//w = A[i];
//A[i] = A[j];
//A[j] = w;
//i++;
//j--;
//}
//else // gdy i >= j zwracamy j jako punkt podzialu tablicy
//return j;
//}
//}
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

int rand_part(vector<int>& A,int p,int r, int logs) //używam zrandomizowanego partition
 {
    int i=p+rand()%(r-p+1);
    int temp;
   // printf("Pierwszy element %d z pola %d zamieniamy z wylosowanym elementem: %d z pola %d", A[p], p, A[i], i);
    swaps++;
    temp=A[r];		//zamiana losowego elementu z ostatnim
    A[r]=A[i];
    A[i]=temp;
    if(logs==1){
    
    }
    return partition2(A,p,r);
  }

void quickSort(vector<int>& A, int p,int r, int logs)
{
    int q;
    if(p<r)
    {
        q=rand_part(A, p,r, logs);
	printf("Piwot to: %d \n", A[q]);
	if(log>0)
		{   printf("Elementy mniejsze od pivota %d \n", A[q]);
			//printf("\n");
		    for(int g = p; g <= q-1; g++)
		    {
			int a = arr [g];
		    	printf("%d, ", a);
		    }printf("\n");
		}
        quickSort(A,p,q-1, logs); 
	if(log>0)
		{ printf("Elementy wieksze od pivota %d \n", A[q]);
		    for(int g = q+1; g <= r; g++)
		    {
			int a = arr [g];
		    	printf("%d, ", a);
		    } printf("\n");
		} 
        quickSort(A,q+1,r, logs);
    }
}
//QUICK INSERTION SORT//
//void partial_insertion_sort (vector <int> *array, int start, int end, int log)
//{	
//    int key;
//    int j;
//	
//    if (log > 0)
//    {
//        printf("wielkość tablicy: %ld ", array->size());
//    }
//    	
//    for(int i=start; i<end; i++)
//    {
//	key = (*array)[i];
//	if (log > 0)
//    	{
//    	printf("\nkey: %d\n", key);
//    	}

//    	j = i-1;

//    
//    	while ( j >= 0 && (*array)[j] > key)
//   	{	
//	    compares ++;
//	    if (log > 0)
//	    {
//	        printf("compare: %d@[%0d], %d\n", (*array)[j], j, key);
//	       	printf("swaps: %d , %d \n ", (*array)[j], key);
//	    }	
//	    (*array)[j+1] = (*array)[j];
//			
//	    //printf("swaps: %d , %d \n ", (*array)[j+1], (*array)[j]); // zamiana klucza na swoje miejsce
//	    swaps ++;
//	    j--;
//    	}
//		
//        (*array)[j+ 1]= key;	
//    }
//    //for(int i=1; i<array-> size(); i++)
//    //cout <<"swaps:"<< swaps << endl;
//    //cout <<"compares:"<< compares << endl;
//    //printf ("swap: %ld \n", swaps);
//    //printf ("compares: %d \n", compares);	

//}


//QUICKINSERTION SORT!!!




//void quickinSort(vector<int>& A, int p,int r)
//{
//    int q;
//    if(p<r)
//    {
//    if(r-p <= 7){
//    partial_insertion_sort(&A, p, r,0);
//    }

//    else
//    {
//        q=rand_part(A, p,r);
//        quickinSort(A,p,q-1);  
//        quickinSort(A,q+1,r);
//    }
//    }
//}




// -------------QUICK INSERTION HYBRID ------------
    void PartInsertionSort(vector<int>& list, int start, int end)
    {
        for (int x = start + 1; x < end; x++)
        {
            int val = list[x];
            int j = x - 1;
            while (j >= 0 && val < list[j])
            {
                list[j + 1] = list[j];
                j--;
            }
            list[j + 1] = val;
        }
    }


    void quickinSort(vector<int>& list, int start, int end,int logs)
    {
        if (start < end)
        {
            // This is where we switch to Insertion Sort!
            if ((end - start) < 9)
            {
                PartInsertionSort(list, start, end + 1);
            }
            else
            {
                int part = rand_part(list, start, end, logs);
                quickinSort(list, start, part - 1, logs);
                quickinSort(list, part + 1, end, logs);
            }
        }
    }








// * MERGE-INSERTION SORT  * //

void mergein_sort(vector<int>& array,  int logs) {
//    int i = array.size();
//    int j = array.begin();
    if (array.size() <= 7) {
    		if(log>0)
		{   printf("Robimy insertion sort.\n");

		}
    insertion_sort(&array,0);
	
    }


    else{




        vector<int> array1(array.begin(), array.begin() + array.size() / 2);
    		if(log>0)
		{   printf("Podzieliliśmy tablice na pierwsza połowe:\n");
		    for(int g = 0; g < array1.size(); g++)
		    {
			int a = array1 [g];
		    	printf("%d, ", a);
		    }
		printf("\n");
		}	
        mergein_sort(array1, logs);
        vector<int> array2(array.begin() + array.size() / 2 , array.end());
    		if(log>0)
		{   printf("Podzieliliśmy tablice na drugą połowe:\n");
		    for(int g = 0; g < array2.size(); g++)
		    {
			int a = array2 [g];
		    	printf("%d, ", a);
		    }
		printf("\n");
		}
        mergein_sort(array2, logs);
        merge(array, array1, array2, 0);
	//printf ("compares: %d \n", compares);	
    }
}










void swap(vector<int> &a, int x, int y)
{
    int t = a[x];
    a[x] = a[y];
    a[y] = t;
}

void dualPivotQuicksort(vector<int> &a, const int left, const int right, int div, const int limit) {
	int length = right - left;
	//insertion sort dla malych liczb
	if(length < limit) {
		printf("Odpalam insertion sort dla malej liczby!!!\n");
		for(int i = left + 1; i <= right; i++){
			for(int j = i; j > left && a[j] < a[j - 1]; j--){
				swap(a, j, j - 1);
			}
		}
		return;
	}
	
	int third = length / div;   //na ile 
	// podział na trzy podtablice 
	int m1 = left + third;
	int m2 = right - third;
	if(m1 <= left) {
		m1 = left + 1;
	}
	if(m2 >= right) {
		m2 = right - 1;
	}
	if(a[m1] < a[m2]) {
		swap(a, m1, left);
		swap(a, m2, right);
	} else {
		swap(a, m1, right);
		swap(a, m2, left);
	}
	// pivots
	int pivot1 = a[left];
	printf("Pivot1 to: %d \n", a[left]);
	int pivot2 = a[right];
	printf("Pivot2 to: %d \n", a[right]);
	// pointers
	int less = left + 1;
	int great = right - 1;
	
	// sorting
	for(int k = less; k <= great; k++){
		if(a[k] < pivot1) {	
			//printf("Zamiana %d z %d \n", a[k], a[less]);
			swap(a, k, less++);
		} else if(a[k] > pivot2) {
			while(k < great && a[great] > pivot2){
				great--;
			}
			//printf("Zamiana %d z %d \n", a[k], a[great]);
			swap(a, k, great--);
			if(a[k] < pivot1) {

				swap(a, k, less++);
			}
		}
	}
	// swaps
	int dist = great - less;
	if(dist < 13) {
		div++;
	}
	//printf("Zamiana %d z %d \n", a[less-1], a[left]);
	swap(a, less - 1, left);
	//printf("Zamiana %d z %d \n", a[great+1], a[right]);
	swap(a, great + 1, right);
	// odpalamy dualPIVOTA DLA ELEMENTOW MNIEJSZYCH NIŻ PIVOT 1 i WIEKSZYCH NIŻ PIVOT2
	printf("Quicksort dla elementow mniejszych niż Pivot1: "); 
	for(int g = left; g < less-1; g++)
			    {
				int a = arr [g];
			    	printf("%d, ", a);
			    }
	printf("\n");
	dualPivotQuicksort(a, left, less - 2, div, limit);
	printf("Quicksort dla elementow wiekszych niż Pivot2: ");
	 for(int g = great+2; g < right; g++)
			    {
				int a = arr [g];
			    	printf("%d, ", a);
			    }
		printf("\n");
	dualPivotQuicksort(a, great + 2, right, div, limit);
	// equal elements
	if(dist > length - 13 && pivot1 != pivot2) {
		for(int k = less; k <= great; k++){
			if(a[k] == pivot1) {
				swap(a, k, less++);
			} else if(a[k] == pivot2) {
				swap(a, k, great--);
				if(a[k] == pivot1) {
					swap(a, k, less++);
				}
			}
		}
	}
	// subarray
	if(pivot1 < pivot2) {
		printf("Quicksort dla elementow pomiedzy  Pivot1 i Pivot2: ");

	 	for(int g = less -1; g < great+1; g++)
			    {
				int a = arr [g];
			    	printf("%d, ", a);
			    }
		printf("\n");	
		dualPivotQuicksort(a, less, great, div,limit);
	}
	
}








int main()
{    
    int collection, size, sort, stats, log;
    
    cout << "Podaj zbiór jaki mam wygenerować [1 - jeśli ma być ciąg losowy lub 2 - jeśli ciąg malejący ]:";
    cin >> collection;
    cout << "Wpisz wielkość zbioru:";
    cin >> size;
    cout << "Jakie sortowanie zastosować? \n---0 jeśli Insertion Sort\n---1 jeśli Merge Sort\n---2 jeśli Quick Sort\n---3 jeśli MergeInsertion Sort\n---4 jeśli QuickInsertion Sort\n---5 jeśli DualPivot";
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
		//dualPivotQuicksort(arr, 0, arr.size(), 3, 15);
		printf("DualPivot Sort \n");
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

		merge_sort(arr, log);
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
		quickSort(arr, 0, arr.size()-1, log);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		
		printf("Quick Sort zrandomizowany- czas: %f \n", total);
		printf("swaps:%ld compares: %ld \n", swaps, compares);

				if(log>0)
		{
		    for(int g = 0; g < arr.size(); g++)
		    {
			int a = arr[g];
			printf("%d, ", a);
		    }
		}
		break;
	    case 3:
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

		mergein_sort(arr, log);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

		printf("time: %f \n", total);
	
		printf("Merge-Insertion Sort \n");
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

	    case 4:
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

		quickinSort(arr, 0, arr.size()-1, 0);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

		printf("time: %f \n", total);
	
		printf("Quick-Insertion Sort \n");
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
	    case 5:
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
		dualPivotQuicksort(arr, 0, arr.size(), 3, 15);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;
		
		printf("Quick Sort zrandomizowany: %f \n", total);
		//printf("swaps:%ld compares: %ld", swaps, compares);
		break;

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

		merge_sort(arr, 0);
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
		quickSort(arr, 0, arr.size()-1, 0);
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

		mergein_sort(arr,0);
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

	    case 4:	    

		fp = fopen ("quickin.txt", "w+");
		times= fopen("quickinTimes.txt", "w+");
		   
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

		quickinSort(arr, 0, arr.size()-1, 0);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'quickin.txt' using 1:2 with dots, 'quickin.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'quickinTimes.txt' using 1:2 with points\"");
	    break;
	    case 5:	    

		fp = fopen ("doublePivot.txt", "w+");
		times= fopen("doublePivot.txt", "w+");
		   
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

		dualPivotQuicksort(arr, 0, arr.size(), 3, 27);
		stop = clock();
		total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		fprintf(fp, "%d %ld %ld  \n", i*100, compares, swaps);
		fprintf(times, "%d %f \n",i*100, total);

		}
		fclose(fp);
		fclose(times);
		system("gnuplot -p -e \"plot 'doublePivot.txt' using 1:2 with dots, 'doublePivot.txt' using 1:3 with points \"");
		system("gnuplot -p -e \"plot 'doublePivot.txt' using 1:2 with points\"");
	    break;




	break;
	}
}

    



return 0; 
}

