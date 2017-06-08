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
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;
int counter = 0;
clock_t start, stop;
double total;
vector <int> arr;
vector <int> tmp;

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

void countingSortToRadix2(vector <int> *givenArray, vector <int> *sortedArray, int * counterMove, int exp) 
{
	vector <int> positionArray(10 , 0);

	for (int i = 0; i < givenArray->size(); i++) {
		positionArray[((*givenArray)[i] / (int)pow(10,exp)) % 10] += 1; //count how many times element from givenArray[i] appears
	}
	
	for (int i = 1; i < 10; i++) {
		positionArray[i] += positionArray[i-1]; // after this loop in positionArray we have number of elements less or equal of i element
		(*counterMove) += 1;
	}
	
	for (int i = (givenArray->size() - 1); i >= 0; i--) {
		(*sortedArray)[(positionArray[((*givenArray)[i] / (int)pow(10,exp)) % 10] )-1] = (*givenArray)[i] ;
		positionArray[((*givenArray)[i] / (int)pow(10,exp)) % 10] -= 1;
		(*counterMove) += 1;
	}

}

void radixSort(vector <int> *givenArray, vector <int> *sortedArray, int * counterMove, int log) {
	int rest = 0;
	int exp = 6; //in variable exp number of positions to compare will be held

	while ( rest == 0 ) {
		exp -= 1;
		rest = givenArray->size() / ((int)pow(10,exp));
	}

	exp += 1;

	for (int i = 0; i < exp; i++) {
	    countingSortToRadix2(givenArray, sortedArray, counterMove, i);
	
	    (*givenArray) = (*sortedArray);
		
	    if(log == 1){
	        cout << "po counting sort nr " << i <<": "<< endl;
                for(int g = 0; g < arr.size(); g++)
	        {
	       	    int a = arr [g];
	    	    printf("%d, ", a);
	        }
    	    	printf("\n");
	    }

	} 
}

int main()
{    
    int log, stats, collection,elements;
    FILE * times;
    cout << "Czy chcesz drukować logi?[1 jeśli tak]";
    cin >> log;
    cout << "Ile chcesz elementów?";
    cin >> elements;
    cout << "Podaj zbiór jaki mam wygenerować [1 - jeśli ma być ciąg losowy lub 2 - jeśli ciąg malejący ]:";
    cin >> collection;
    cout << "Czy wygenerować statystyki? [1 jeśli tak]";
    cin >> stats;

    switch(collection)
    {
    case 1:
	arr= generate_list_random(elements, elements);
	break;
    case 2:
	arr = generate_list_descending(elements);
	break;
    }

    //arr= generate_list_random(elements,elements);

   tmp = arr;  //

   if(log == 1){    
      cout <<"Przed sortowaniem tablica: \n";
      for(int g = 0; g < arr.size(); g++)
	    {
	        int a = arr [g];
	    	printf("%d, ", a);
	    }
    }
	
	printf("\n");
	
     	start = clock();
	radixSort(&arr , &tmp, &counter, log);
	stop = clock();
	total = (double)(stop- start) /CLOCKS_PER_SEC;

    if(log == 1){
	    cout <<"Po sortowaniu tablica: \n";	
	    for(int g = 0; g < arr.size(); g++)
	    {
	        int a = arr[g];
	        printf("%d, ", a);
	    }
    }
    printf("\n");
	
    if (stats == 1){
		
	times= fopen("radixTimes.txt", "w+");
		   
	for (int i = 1; i<= 100; i++){
			
	    switch(collection)
	    {
	    case 1:
	         arr= generate_list_random(i*100, i*100);
		 break;
	    case 2:
		 arr = generate_list_descending(i*100);
		 break;
	    }

	    tmp = arr;
	    start = clock();

	    radixSort(&arr , &tmp, &counter, log);
	    stop = clock();
	    total = (double)(stop- start) /CLOCKS_PER_SEC;

	

		
	    fprintf(times, "%d %f \n",i*100, total);

	}

	fclose(times);
	
	system("gnuplot -p -e \"plot 'radixTimes.txt' using 1:2 with points\"");
    }





}



