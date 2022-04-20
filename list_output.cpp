#include "functions.h"

// function to print results
void print(list<data> arr, int s) {
    // print header line
    cout << endl;
    cout << left << setw(15) << "Vardas"
        << left << setw(15) << " Pavarde";
    // print based on s value
    switch (s) {
    case 1:
        cout << left << setw(15) << " Galutinis (vid.)" << endl;
        cout << std::string(45, '-') << endl;
        break;
    case 2:
        cout << left << setw(15) << " Galutinis (med.)" << endl;
        cout << std::string(45, '-') << endl;
        break;
    case 3:
        cout << left << setw(15) << " Galutinis (vid.)" << left << setw(15) << " Galutinis (med.)" << endl;
        cout << std::string(60, '-') << endl;
        break;
    }
    // print all elements of an array
    for (auto i : arr) {
        cout << left << setw(15) << i.name << " "
            << left << setw(15) << i.surname << " ";
        // calculate final grade using average or median based on s value
        switch (s) {
        case 1:
            cout << left << setw(20) << setprecision(3) << 0.4 * average(i.grades) + 0.6 * i.exam << endl;
            break;
        case 2:
            cout << left << setw(20) << setprecision(3) << 0.4 * median(i.grades) + 0.6 * i.exam << endl;
            break;
        case 3:
            cout << left << setw(20) << setprecision(3) << 0.4 * average(i.grades) + 0.6 * i.exam
                << left << setw(20) << setprecision(3) << 0.4 * median(i.grades) + 0.6 * i.exam << endl;
            break;
        }
    }
}

void write_students(string filename, list<data> arr) {
    // write student name, surname and final grade to stringstream
    std::stringstream line;
    for (auto student : arr)
        line << left << setw(20) << student.name << setw(20) << student.surname << setw(20) << student.final << '\n';

    std::ofstream file(filename);

    // write header line
    file << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis balas" << endl;

    // write stringstream to file
    file << line.rdbuf();

    file.close();

}