#include "../functions.h"

// function to find median of an array
double median(vector<int> arr) {
    // sort an array
    quick_sort(arr, 0, arr.size()-1);
    // std::sort(&arr[0], &arr[arr_length-1]);

    // if array has even number of elements return average of middle elements
    // else return middle element
    if(arr.size() % 2 == 0) {
        return (arr[arr.size()/2] + arr[(arr.size() / 2) - 1]) / 2.0;
    } else  {
        return arr[arr.size()/2];
    }
}

// function to calculate the average of an array
double average(vector<int> arr) {
    // if array is not empty
    // calculate the sum of elements and divide it by the length of an array
    if(arr.size() > 0) {
        return accumulate(arr.begin(), arr.end(), 0.0) / arr.size();
    } else {
        return 0;
    }
}

// function to generate file with random data
void generate(int n, int nd) {
    // initialise random number generator
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt;
    mt.seed(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 10);

    // open output file
    std::ofstream file(std::to_string(n) + "st_" + std::to_string(nd) + "nd.txt");

    // write header line
    file << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < nd; i++) {
        file << std::right << setw(5) << "ND" + std::to_string(i+1);
    }
    file << setw(5) << "Egz." << endl;

    std::stringstream line;
    for (int i = 0; i < n; i++) {
        // write name and surname to stringstream
        line << left << setw(20) << "Vardas" + std::to_string(i + 1) << setw(20) << "Pavarde" + std::to_string(i + 1);
        for (int i = 0; i <= nd; i++)
            // write grades to stringstream
            line << std::right << setw(5) << dist(mt);
        if (i + 1 != n)
            line << endl;
        // every 1000 students copy data from stringstream to file
        if (i % 1000 == 0) {
            file << line.rdbuf();
            line.clear();
        }
    }
    file << line.rdbuf();
    file.close();
}

void split_two_new(vector<data> arr, double (*func)(vector<int>)) {
    auto start = std::chrono::high_resolution_clock::now();
    // calculate final grade and split students
    vector<data> vargsiukai, kietiakai;
    for(auto student:arr) {
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

bool f(data &stud) {
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
    while(it != kietiakai.end()) {
        if (it->final < 5) {
            std::iter_swap(it, kietiakai.end() - 1);
            kietiakai.pop_back();
        } else
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