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

void randomPermutationArray(vector <int> &array, size) {
	generate_list_descending(array, size);
	random_shuffle(array.begin(), array.end());
}

int partition(vector <int> &A, int p, int r) {
int x=A[r];
int i= p-1;
for(int j=p; j < r-1; j++)
{
if(A[j]<=x)
{
i++;
int w= A[i];
A[i]=A[j];
A[j]=w;

}
}
int w=A[i+1];
A[i+1]=A[r];
A[r]=w;
return i+1;
}

int rand_part(vector<int>& A,int p,int r)
 {
    srand (time(NULL));
    int i=p+rand()%(r-p+1);
    int temp;
   // printf("Pierwszy element %d z pola %d zamieniamy z wylosowanym elementem: %d z pola %d", A[p], p, A[i], i);
    swaps++;
    temp=A[r];		//zamiana losowego elementu z ostatnim
    A[r]=A[i];
    A[i]=temp;
    //printf("Piwot to: %d z pola %d", A[p], i);
    return partition(A,p,r);
  }

int randomSelect(vector<int> &A, int p, int r, int i)
{

    if(i> A.size()-1){
    cout << "error";
	}
    else{
    if (p == r)
    {
	return A[p];
    }
    int q=rand_part(A,p,r);
    int k= q-p+1;
    if(i == k){
    return A[q];
    }
    else if (i < k){
       return randomSelect(A,p,q-1,i);
    }
    else return randomSelect(A,q+1,r,i-k);
   }
}


int main()
{    
arr = generate_list_descending(10);
random_shuffle(array.begin(), array.end());
for(int g = 0; g < arr.size(); g++)
{
int a = arr [g];
printf("%d, ", a);
}
printf("\n");
int s;
cin >> s;
int wynik = randomSelect(arr,0,arr.size()-1, s);
printf("%d",wynik);
}












