#include "../functions.h"


void write_students(string filename, vector<data> arr, vector<int> indexes) {
    std::ofstream file (filename);

    // write header line
    file << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < arr[0].grades.size(); i++) {
        file << std::right << setw(5) << "ND" + std::to_string(i+1);
    }
    file << setw(5) << "Egz." << "\n";

    std::stringstream line;
    for(auto i:indexes) {
        line << left << setw(20) << arr[i].name << setw(20) << arr[i].surname;
        for(int j = 0; j < arr[i].grades.size(); j++) {
            line << std::right << setw(5) << arr[i].grades[j];
        }
        line << std::right << setw(5) << arr[i].exam << "\n";
        if (i % 1000 == 0) {
            file << line.rdbuf();
            line.clear();
        }
    }
    file << line.rdbuf();
    file.close();

}

// function to print results
void print(vector<data> arr, int s) {
    // print header line
    cout << "\n";
    cout << left << setw(15) << "Vardas" 
        << left << setw(15) << " Pavarde";
    // print based on s value
    switch(s) {
        case 1:
            cout << left << setw(15) << " Galutinis (vid.)" << "\n";
            cout << std::string(45, '-') << "\n";
            break;
        case 2:
            cout << left << setw(15) << " Galutinis (med.)" << "\n";
            cout << std::string(45, '-') << "\n";
            break;
        case 3:
            cout << left << setw(15) << " Galutinis (vid.)" << left << setw(15) << " Galutinis (med.)" << "\n";
            cout << std::string(60, '-') << "\n";
            break;
    }
    // print all elements of an array
    for(auto i:arr) {
        cout << left << setw(15) << i.name << " " 
            << left << setw(15) << i.surname << " ";
            // calculate final grade using average or median based on s value
            switch(s) {
                case 1:
                    cout << left << setw(20) << setprecision(3) << 0.4 * average(i.grades) + 0.6 * i.exam << "\n";
                    break;
                case 2:
                    cout << left << setw(20) << setprecision(3) << 0.4 * median(i.grades) + 0.6 * i.exam << "\n";
                    break;
                case 3:
                    cout << left << setw(20) << setprecision(3) << 0.4 * average(i.grades) + 0.6 * i.exam 
                        << left << setw(20) << setprecision(3) << 0.4 * median(i.grades) + 0.6 * i.exam << "\n";
                    break;
            }
    }
}