#include "functions.h"

// sorting algorythms
// sort grades
void quick_sort(vector<int>& array, int first, int last) {
    if (first < last) {
        // find pivot element that all smaller elements are on the left, greater on the right

        // select last element as pivot
        int pivot = array[last];

        // select first element as greater
        int i = first;

        // compare every element of array with pivot
        for (int j = first; j < last; j++) {
            // if element smaller than pivot is found, swap it with greater element
            if (array[j] <= pivot) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;

                // select next element as greater
                i++;
            }
        }

        // swap pivot with greater element
        int tmp = array[i];
        array[i] = array[last];
        array[last] = tmp;

        // quick sort left and right sides 
        quick_sort(array, first, i - 1);
        quick_sort(array, i + 1, last);
    }
}

// sort students
void quick_sort(vector<data>& array, int first, int last) {
    if (first < last) {
        // find pivot element that all smaller elements are on the left, greater on the right

        // select last element as pivot
        string pivot = array[last].name + array[last].surname;

        // select first element as greater
        int i = first;

        // compare every element of array with pivot
        for (int j = first; j < last; j++) {
            // if element smaller than pivot is found, swap it with greater element
            if (array[j].name + array[j].surname <= pivot) {
                data tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;

                // select next element as greater
                i++;
            }
        }

        // swap pivot with greater element
        data tmp = array[i];
        array[i] = array[last];
        array[last] = tmp;

        // quick sort left and right sides 
        quick_sort(array, first, i - 1);
        quick_sort(array, i + 1, last);
    }
}