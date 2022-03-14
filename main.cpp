#include "functions.h"

int main() {
    int n = 10000000, nd = 10;
    cout << n << endl;
    // auto start1 = high_resolution_clock::now();
    // generate(n, nd);
    // auto stop1 = high_resolution_clock::now();
    // auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
    // cout << "Failo kurimas uztruko: " << duration1.count() * 1e-9 << "s\n";

    auto start = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    vector<data> arr;
    read_data1(arr, "test_output.txt");
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
    cout << "Duomenu nuskaitymas is failo uztruko: " << duration2.count() * 1e-9 << "s\n";

    split(arr, &average);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Programos veikimo laikas: " << duration.count() * 1e-9 << "s\n";
}