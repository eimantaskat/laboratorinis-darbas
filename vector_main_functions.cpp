#include "functions.h"

void vector_data_input() {
    vector<data> arr;
    string from_file, select;
    cout << "Ar norite nuskaityti duomenis is failo? (y/n): ";
    cin >> from_file;

    if (from_file == "y") {
        while (true) {
            // read from file
            cout << "Iveskite failo pavadinima su pletiniu: ";
            string filename;
            cin >> filename;

            read_data(arr, filename);
            if (arr.size() > 0) {
                cout << "Pagal ka norite rusiuoti studentus?\n1. Varda\n2. Pavarde\n";

                while (true) {
                    cin >> select;
                    if (!check_select(select)) {
                        cout << "Iveskite 1 arba 2" << endl;
                    }
                    else {
                        int s = stoi(select);

                        // quick_sort(arr, 0, arr.size()-1);
                        switch (s) {
                        case 1:
                            std::sort(arr.begin(), arr.end(), compareByName);
                            break;

                        case 2:
                            std::sort(arr.begin(), arr.end(), compareBySurname);
                            break;
                        }

                        print(arr, 3);
                        break;
                    }
                }
                break;
            }
        }
    }
    else {
        // input manually
        input_data(arr);

        // ask user how to calculate final grade
        cout << "Pagal ka norite skaiciuoti galutini bala?\n1. Vidurki\n2. Mediana\n";
        string select;

        while (true) {
            cin >> select;

            if (!check_select(select)) {
                cout << "Iveskite 1 arba 2" << endl;
            }
            else {
                int s = stoi(select);
                // print data
                print(arr, s);
                break;
            }
        }
    }
}

void vector_student_sorting() {
    vector<data> arr;
    while (true) {
        cout << "Kaip norite rusioti studentus?\n1. I du naujus konteinerius\n2. I viena nauja konteineri\n";
        string select;
        while (true) {
            cin >> select;

            if (!check_select(select))
                cout << "Iveskite 1 arba 2" << endl;
            else
                break;
        }

        while (true) {
            // read from file
            cout << "Iveskite failo pavadinima su pletiniu: ";
            string filename;
            cin >> filename;
            auto start = std::chrono::high_resolution_clock::now();

            read_data(arr, filename);

            if (arr.size() > 0) {
                int s = stoi(select);
                switch (s) {
                case 1:
                    split_two_new(arr, &average);
                    break;

                case 2:
                    split_one_new(arr, &median);
                    break;
                }
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                cout << "Programos veikimo laikas: " << duration.count() * 1e-9 << "\n";
                break;
            }
        }
        break;
    }
}