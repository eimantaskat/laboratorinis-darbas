#include "functions.h"

void split_two_new(vector<data> arr, double (*func)(vector<int>)) {
    auto start = std::chrono::high_resolution_clock::now();
    // calculate final grade and split students
    vector<data> vargsiukai, kietiakai;
    for (auto student : arr) {
        student.final = 0.4 * func(student.grades) + 0.6 * student.exam;
        if (student.final < 5)
            vargsiukai.push_back(student);
        else
            kietiakai.push_back(student);
    }
    arr.clear();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Studentu skirstymas i vargsiukus ir kietiakus uztruko: " << duration.count() * 1e-9 << "s\n";

    start = std::chrono::high_resolution_clock::now();
    write_students("kietiakai.txt", kietiakai);
    kietiakai.clear();
    write_students("vargsiukai.txt", vargsiukai);
    vargsiukai.clear();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Vargsiuku ir kietiaku rasymas i failus uztruko: " << duration.count() * 1e-9 << "s\n";
    // cout << "Studentai surusiuoti i falus kietiakai.txt ir vargsiukai.txt\n";
}

bool f(data& stud) {
    stud.final = 0.4 * average(stud.grades) + 0.6 * stud.exam;
    return stud.final < 5;
}
bool f1(data stud) {
    return stud.final > 5;
}

void split_one_new(vector<data> kietiakai, double (*func)(vector<int>)) {
    auto start = std::chrono::high_resolution_clock::now();

    std::stable_partition(kietiakai.begin(), kietiakai.end(), f);
    auto it = std::find_if(kietiakai.begin(), kietiakai.end(), f1);
    vector<data> vargsiukai(kietiakai.begin(), it);

    it = kietiakai.begin();
    while (it != kietiakai.end()) {
        if (it->final < 5) {
            std::iter_swap(it, kietiakai.end() - 1);
            kietiakai.pop_back();
        }
        else
            it++;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Studentu skirstymas i vargsiukus ir kietiakus uztruko: " << duration.count() * 1e-9 << "s\n";

    auto start5 = std::chrono::high_resolution_clock::now();

    std::sort(kietiakai.begin(), kietiakai.end(), compareByName);
    std::sort(vargsiukai.begin(), vargsiukai.end(), compareByName);

    auto stop5 = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop5 - start5);
    cout << "Studentu rusiavimas pagal vardus uztruko: " << duration5.count() * 1e-9 << " \n";

    start = std::chrono::high_resolution_clock::now();
    write_students("kietiakai.txt", kietiakai);
    kietiakai.clear();
    write_students("vargsiukai.txt", vargsiukai);
    vargsiukai.clear();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Vargsiuku ir kietiaku rasymas i failus uztruko: " << duration.count() * 1e-9 << "s\n";
    // cout << "Studentai surusiuoti i falus kietiakai.txt ir vargsiukai.txt\n";
}