#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

vector<int> arr;

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

void merge(vector<int>& array, vector<int>& array1, vector<int>& array2) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
        if(array1.at(i) <= array2.at(j)){
            array.push_back(array1.at(i));
            i++;
        }else if(array1.at(i) > array2.at(j)){
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
}


void merge_sort(std::vector<int>& array) {
    if (1 < array.size()) {
        std::vector<int> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1);
        std::vector<int> array2(array.begin() + array.size() / 2, array.end());
        merge_sort(array2);
        merge(array, array1, array2);
    }
}



int partition(vector<int>& A, int p,int q)
{
    int x= A[p];
    int i=p;
    int j;

    for(j=p+1; j<q; j++)
    {
        if(A[j]<=x)
        {
            i=i+1;
            swap(A[i],A[j]);
        }

    }

    swap(A[i],A[p]);
    return i;
}

void quickSort(vector<int>& A, int p,int q)
{
    int r;
    if(p<q)
    {
        r=partition(A, p,q);
        quickSort(A,p,r);  
        quickSort(A,r+1,q);
    }
}

//void quickSort(vector<int> A){
//quickSort(A, A.begin(), A.end() );
//}



int main(){
arr = generate_list_random(5,5);

for(int i = 0; i < arr.size(); i++)
{
int a = arr [i];
printf("%d, ", a);
} printf("\n");
quickSort(arr, 0,arr.size());
for(int i = 0; i < arr.size(); i++)
{
int a = arr [i];
printf("%d, ", a);
} printf("\n");


return 0;
}
