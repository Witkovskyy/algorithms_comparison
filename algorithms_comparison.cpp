#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <stdio.h>

using namespace std;
//Bubble sort
void sortowanie_babelkowe(int tab[],int n)
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
		if(tab[j-1]>tab[j])
			swap(tab[j-1], tab[j]);
}
//Heap sort
void kopiec(int tab[], int n, int i)
{
    int najwieksza = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && tab[l] > tab[najwieksza])
        najwieksza = l;
    if (r < n && tab[r] > tab[najwieksza])
        najwieksza = r;
    if (najwieksza != i) {
        swap(tab[i], tab[najwieksza]);
        kopiec(tab, n, najwieksza);
    }
}
void kopcowanie(int tab[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        kopiec(tab, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(tab[0], tab[i]);
        kopiec(tab, i, 0);
    }
}
//Insertion sort
void sortowanie_przez_wstawianie(int n, int *tab)
{
     int pom, j;
     for(int i=1; i<n; i++)
     {
        pom = tab[i];
        j = i-1;
        while(j>=0 && tab[j]>pom)
             {
                tab[j+1] = tab[j];
                --j;
             }
        tab[j+1] = pom;
     }
}

//Quicksort
void quick_sort(int *tab, int lewy, int prawy)
{
	if(prawy <= lewy) return;
	int i = lewy - 1, j = prawy + 1,
	pivot = tab[(lewy+prawy)/2];
	while(1)
	{
		while(pivot>tab[++i]);
		while(pivot<tab[--j]);
		if( i <= j)
			swap(tab[i],tab[j]);
		else
			break;
	}
	if(j > lewy)
	quick_sort(tab, lewy, j);
	if(i < prawy)
	quick_sort(tab, i, prawy);
}

void merge(int* tab, int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid;    

    int* leftArray = new int[n1];
    int* rightArray = new int[n2];

    for (int i = 0; i < n1; ++i)
        leftArray[i] = tab[left + i];
    for (int i = 0; i < n2; ++i)
        rightArray[i] = tab[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            tab[k] = leftArray[i];
            ++i;
        } else {
            tab[k] = rightArray[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        tab[k] = leftArray[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        tab[k] = rightArray[j];
        ++j;
        ++k;
    }
    delete[] leftArray;
    delete[] rightArray;
}
void mergeSort(int* tab, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(tab, left, mid);
        mergeSort(tab, mid + 1, right);

        merge(tab, left, mid, right);
    }
}

//Main
int main()
{
    int num_of_elems;
    std::cout<<"Podaj liczbe elementow tablicy: ";
    std::cin>>num_of_elems;
    int* tablica = new int[num_of_elems];

    for(int i=0;num_of_elems>i;i++)
    {
    tablica[i]=rand() %1000000+1;
    // std::cout << tablica[i] << " "; 
    }

//Bubble
	int *tab;
	tab = new int [num_of_elems];
	for(int i=0;i<num_of_elems;i++)
		tab[i]=tablica[i];
    auto begin_bubble = std::chrono::high_resolution_clock::now();
	sortowanie_babelkowe(tab,num_of_elems);
	auto end_bubble = std::chrono::high_resolution_clock::now();
    auto elapsed_bubble = std::chrono::duration_cast<std::chrono::nanoseconds>(end_bubble - begin_bubble);
    delete[] tab;

//Quicksort

  	tab = new int [num_of_elems];
  	for(int i=0;i<num_of_elems;i++)
    	tab[i]=tablica[i];
    auto begin_quick = std::chrono::high_resolution_clock::now();
  	quick_sort(tab,0, num_of_elems-1);
  	auto end_quick = std::chrono::high_resolution_clock::now();
    auto elapsed_quick = std::chrono::duration_cast<std::chrono::nanoseconds>(end_quick - begin_quick);
    delete[] tab;

//Insertion

    tab = new int [num_of_elems];
    for(int i=0; i<num_of_elems; i++)
    {
        tab[i]=tablica[i];
    }
    auto begin_insertion = std::chrono::high_resolution_clock::now();
    sortowanie_przez_wstawianie(num_of_elems, tab);
    auto end_insertion = std::chrono::high_resolution_clock::now();
    auto elapsed_insertion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_insertion - begin_insertion);
    delete[] tab;

//Heap sort

    tab = new int [num_of_elems];
    for(int i=0;i<num_of_elems;i++)
    	tab[i]=tablica[i];
    auto begin_heap = std::chrono::high_resolution_clock::now();
    kopcowanie(tab, num_of_elems);
    auto end_heap = std::chrono::high_resolution_clock::now();
    auto elapsed_heap = std::chrono::duration_cast<std::chrono::nanoseconds>(end_heap - begin_heap);
    delete[] tab;

// Merge sort

	tab = new int [num_of_elems];
	for(int i=0;i<num_of_elems;i++)
		tab[i]=tablica[i];
    auto begin_merge = std::chrono::high_resolution_clock::now();
	mergeSort(tab, 0, num_of_elems-1);
	auto end_merge = std::chrono::high_resolution_clock::now();
    auto elapsed_merge = std::chrono::duration_cast<std::chrono::nanoseconds>(end_merge - begin_merge);
    delete[] tab;

//Timers
    printf("Bubble sort: %.9f seconds.\n", elapsed_bubble.count() * 1e-9);
    printf("Quicksortu: %.9f seconds.\n", elapsed_quick.count() * 1e-9);
    printf("Insertion sort: %.9f seconds.\n", elapsed_insertion.count() * 1e-9);
    printf("Heap sort: %.9f seconds.\n", elapsed_heap.count() * 1e-9);
    printf("Merge sort: %.9f seconds.\n", elapsed_merge.count() * 1e-9);

}
