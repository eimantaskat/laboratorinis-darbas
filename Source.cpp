#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::accumulate;
using std::setprecision;
using std::vector;

using namespace std::chrono;
using hrClock = std::chrono::high_resolution_clock;

struct data {
    string name, surname;
    int exam;
    vector<int> grades;
};

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
        file << std::right << setw(5) << "ND" + std::to_string(i + 1);
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
            line.str(string());
        }
    }
    file << line.rdbuf();
    file.close();
}

void write_students(string filename, vector<data> arr, vector<int> indexes) {
    std::ofstream file(filename);

    // write header line
    file << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < arr[0].grades.size(); i++) {
        file << std::right << setw(5) << "ND" + std::to_string(i + 1);
    }
    file << setw(5) << "Egz." << endl;

    std::stringstream line;
    for (auto i : indexes) {
        line << left << setw(20) << arr[i].name << setw(20) << arr[i].surname;
        for (int j = 0; j < arr[i].grades.size(); j++) {
            line << std::right << setw(5) << arr[i].grades[j];
        }
        line << std::right << setw(5) << arr[i].exam << endl;
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
    for (int i = 0; i < arr.size(); i++) {
        if (0.4 * func(arr[i].grades) + 0.6 * arr[i].exam < 5)
            vargsiukai.push_back(i);
        else
            kietiakai.push_back(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Studentu rusiavimas i 2 kategorijas uztruko: " << duration.count() * 1e-9 << "s\n";

    start = high_resolution_clock::now();
    write_students("kietiakai.txt", arr, kietiakai);
    write_students("vargsiukai.txt", arr, vargsiukai);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Surusiotu studentu isvedimas i 2 failus uztruko: " << duration.count() * 1e-9 << "s\n";

    // cout << "Studentai surusiuoti i falus kietiakai.txt ir vargsiukai.txt\n";
}

// function to calculate the average of an array
double average(vector<int> arr) {
    // if array is not empty
    // calculate the sum of elements and divide it by the length of an array
    if (arr.size() > 0) {
        return accumulate(arr.begin(), arr.end(), 0.0) / arr.size();
    }
    else {
        return 0;
    }
}

// function to read data from file
void read_data(vector<data>& arr, string filename) {
    try {
        std::stringstream buffer;
        // open file
        std::ifstream file(filename);
        if (!file) {
            throw(1);
        }
        buffer << file.rdbuf();

        file.close();

        int lines_count = 0;
        string line;
        while (getline(buffer, line)) {
            lines_count++;
        }

        if (lines_count == 0) {
            throw(3);
        }

        buffer.clear();
        buffer.seekg(0, std::ios::beg);

        // read file header
        vector<string> header;
        header.reserve(4);
        while (buffer.peek() != '\n') {
            string data;
            buffer >> data;
            header.push_back(data);
        }

        // get homework count
        int homework_count = header.size() - 3;
        header.clear();

        // arr.reserve(lines_count - 1);
        // read data
        int i = 0;
        while (!buffer.eof()) {
            arr.push_back(data());
            buffer >> arr[i].name >> arr[i].surname;
            for (int j = 0; j < homework_count; j++) {
                arr[i].grades.push_back(int());
                buffer >> arr[i].grades[j];
            }
            buffer >> arr[i].exam;
            if (i > lines_count) {
                throw(2);
            }
            i++;
        }

    }
    catch (int err) {
        switch (err) {
        case 1:
            cout << "Failas neegzistuoja" << endl;
            break;
        case 2:
            arr.clear();
            cout << "Faile yra klaida" << endl;
            break;
        case 3:
            cout << "Failas yra tuscias" << endl;
            break;
        }
    }
}

int main() {
    int n = 1000, nd = 10;
    cout << n << endl;
    auto start1 = high_resolution_clock::now();
    generate(n, nd);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
    cout << "Failo kurimas uztruko: " << duration1.count() * 1e-9 << "s\n";

    auto start = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    vector<data> arr;
    read_data(arr, "test_output.txt");
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
    cout << "Duomenu nuskaitymas is failo uztruko: " << duration2.count() * 1e-9 << "s\n";

    split(arr, &average);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Programos veikimo laikas: " << duration.count() * 1e-9 << "s\n";
}