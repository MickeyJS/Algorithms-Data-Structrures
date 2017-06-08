#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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
#include <algorithm>

using namespace std;
int compares;

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




void swap(vector<int> &a, int x, int y)
{
    int t = a[x];
    a[x] = a[y];
    a[y] = t;
}

int randomized_partition(vector<int> &a, int left, int right)
{
    int i, j;
    int p = random() % (right - left + 1) + left;
    int pv = a[p];
    swap(a, p, right);
    i = left - 1;
    for (j = left; j < right; j++){
	compares++;
        if (a[j] < pv) {
            i++;
            swap(a, i, j);
        }
    }
    swap(a, i + 1, right);
    return i + 1;
}

int randomized_select(vector<int> &a, int n, int i)
{
    int left = 0, right = n-1;
    //cout << i << "-i-ty el \n";
    while (left < right) {
        int q = randomized_partition(a, left, right);
        int k = q - left + 1;
	compares++;
        if (k == i)
            return a[q];
        else if (k > i)
            right = q - 1;
        else {
            left = q + 1;
            i -= k;
        }
    }
    return a[left];
}




int main()
{
	FILE * times;
	vector <int> *compareCount = new vector <int>;
	int elements, choice, stats, logs;
	vector <int> arr;
	cout << "Ile elementów ma mieć tablica?";
	cin >> elements;
	cout << "Wybierz: \n ------Losowy ciąg elementów wybierz 1------\n ------Losowa permutacja wybierz 2------\n";
	cin >> choice;
	cout << "Czy chcesz statystyki? \n ------TAK wybierz 1------\n ------NIE wybierz 0------\n";
	cin >> stats;
	cout << "Czy chcesz logi? \n ------TAK wybierz 1------\n ------NIE wybierz 0------\n";
	cin >> logs;

	// compares= 0;	
	switch(choice)
	{
	case 1:
    	arr= generate_list_random(elements);
    	break;
	case 2:
    		arr = generate_list_descending(elements);
    		random_shuffle(arr.begin(), arr.end());
    		break;
	}
	if (logs ==1){
	printf("Wylosowana tablica: \n");
	for(int g = 0; g < arr.size(); g++)
	{

	 	printf("%d, ", arr[g]);
	}
	printf("\n");
	}
    	int i;

	cout << "Którego elementu szukasz? \n";
    	cin >> i;
	//print_array(a, n);
    
   
        printf("%d elementem statystyki pozycyjnej jest: %d\n", i, randomized_select(arr, elements, i));
	printf("%d - liczba porównań \n", compares);
	if (logs ==1){
		for(int g = 0; g < arr.size(); g++)
		{
			if (g+1 == i)
			{
				//printf("%d \n", i);
				printf("%d, ", arr[g]);
			}
			else
				printf("-, ");
		}
		printf("\n");
	}
	if (logs ==1){	
		cin.ignore(1024, '\n');
		cout << "Wciśnij coś, żeby dosortować elementy tablicy ...";
		cin.get(); 
		sort(arr.begin(), arr.end());
		for(int g = 0; g < arr.size(); g++)
		{

			printf("%d, ", arr[g]);
		}
	}
	
	if (stats == 1){
		
	//times= fopen("randomizedSelectTimes.txt", "w+");
		   
    		for (int i = 1; i<= 100; i++){
	// compares= 0;	
		    switch(choice)
	    	    {
	    	    case 1:
		    	arr= generate_list_random(i*100);
		    	break;
	    	    case 2:
		    	arr = generate_list_descending(i*100);
			random_shuffle(arr.begin(), arr.end());
		    	break;
	   	    }

    	    
    	

			for (int j = 0; j < 100; j++) {
			    compares= 0;
		 	   // cout << compares << "-przed \n";
			    int g = i*100;
			    int random= rand() % g;
		      	    randomized_select(arr, g, random);
			    //cout << w << "wyszukany element \n";
			   // cout << compares << "-po \n";
			    compareCount->push_back(compares);
			}




		
	    //fprintf(times, "%d %f \n",i*100, compares);

	}


	ofstream myfile;
	myfile.open ("plot.txt");
	for (int i = 0; i < 10000; i++) {
		myfile << i << " " << (*compareCount)[i] << endl ;
	}
	myfile.close();


	system("gnuplot -p -e \"plot 'plot.txt' using 1:2 with dots\"");
	auto biggest = std::max_element(std::begin((*compareCount)), std::end((*compareCount)));
	std::cout << "Max liczba porównań: " << *biggest << endl;

	auto smallest = std::min_element(std::begin((*compareCount)), std::end((*compareCount)));
	std::cout << "Min liczba porównań: " << *smallest << endl;

	float avg = accumulate( (*compareCount).begin(), (*compareCount).end(), 0.0)/(*compareCount).size(); 
	std::cout << "Avg liczba porównań: " << avg << endl;


	//fclose(times);
	
	//system("gnuplot -p -e \"plot 'randomizedSelectTimes.txt' using 1:2 with points\"");
   	 }






}
