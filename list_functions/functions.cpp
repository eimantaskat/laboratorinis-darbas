#include "../functions.h"

void split(list<data> arr, double (*func)(vector<int>)) {
    auto start = std::chrono::high_resolution_clock::now();
    // calculate final grade and split students
    list<list<data>::iterator> vargsiukai, kietiakai;
    for(auto ptr = arr.begin(); ptr != arr.end(); ptr++) {
        ptr->final = 0.4 * func(ptr->grades) + 0.6 * ptr->exam;
        if (ptr->final < 5)
            vargsiukai.push_back(ptr);
        else
            kietiakai.push_back(ptr);

    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Studentu skirstymas i vargsiukus ir kietiakus uztruko: " << duration.count() * 1e-9 << "s\n";
    
    start = std::chrono::high_resolution_clock::now();
    write_students("kietiakai.txt", arr, kietiakai);
    write_students("vargsiukai.txt", arr, vargsiukai);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Vargsiuku ir kietiaku rasymas i failus uztruko: " << duration.count() * 1e-9 << "s\n";
    // cout << "Studentai surusiuoti i falus kietiakai.txt ir vargsiukai.txt\n";

    arr.clear();
    vargsiukai.clear();
    kietiakai.clear();
}