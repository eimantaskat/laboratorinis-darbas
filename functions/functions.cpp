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
    std::ofstream file("test_output.txt");

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

void split(vector<data> arr, double (*func)(vector<int>)) {
    // calculate final grade and split students
    vector<int> vargsiukai, kietiakai;
    auto start = high_resolution_clock::now();        
    for(int i = 0; i < arr.size(); i++) {
        if (0.4 * func(arr[i].grades) + 0.6 * arr[i].exam < 5)
            vargsiukai.push_back(i);
        else
            kietiakai.push_back(i);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Studentu rusiavimas i 2 kategorijas uztruko: " << duration.count()  * 1e-9 << "s\n";
    
    start = high_resolution_clock::now(); 
    write_students("kietiakai.txt", arr, kietiakai);
    write_students("vargsiukai.txt", arr, kietiakai);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Surusiotu studentu isvedimas i 2 failus uztruko: " << duration.count()  * 1e-9 << "s\n";

    // cout << "Studentai surusiuoti i falus kietiakai.txt ir vargsiukai.txt\n";
}