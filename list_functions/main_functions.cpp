#include "../functions.h"

void list_data_input() {
    list<data> arr;
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
                    if(!check_select(select)) {
                        cout << "Iveskite 1 arba 2" << endl;
                    } else {
                        int s = stoi(select);
                        
                        // quick_sort(arr, 0, arr.size()-1);
                        switch (s) {
                            case 1:
                                arr.sort(compareByName);
                                break;
                            
                            case 2:
                                arr.sort(compareBySurname);
                                break;
                        }
                        
                        print(arr, 3);
                        break;
                    }
                }
                break;
            }
        }
    } else {
        // input manually
        input_data(arr);

        // ask user how to calculate final grade
        cout << "Pagal ka norite skaiciuoti galutini bala?\n1. Vidurki\n2. Mediana\n";
        string select;

        while (true) {
            cin >> select;

            if(!check_select(select)) {
                cout << "Iveskite 1 arba 2" << endl;
            } else {
                int s = stoi(select);
                // print data
                print(arr, s);
                break;
            }
        }
    }
}

void list_student_sorting() {
    list<data> arr;
    while (true) {
        // read from file
        cout << "Iveskite failo pavadinima su pletiniu: ";
        string filename;
        cin >> filename;
        auto start = std::chrono::high_resolution_clock::now();
        read_data(arr, filename);
        
        auto start5 = std::chrono::high_resolution_clock::now();

        arr.sort(compareByName);

        auto stop5 = std::chrono::high_resolution_clock::now();
        auto duration5 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop5 - start5);
        cout << "Studentu rusiavimas pagal vardus uztruko: " << duration5.count() * 1e-9 << " \n";

        auto pause = std::chrono::high_resolution_clock::now();
        auto cont = std::chrono::high_resolution_clock::now();
        if (arr.size() > 0) {
            // ask user how to calculate final grade
            // cout << "Pagal ka norite skaiciuoti galutini bala?\n1. Vidurki\n2. Mediana\n";
            string select = "1";

            while (true) {
                // cin >> select;

                if(!check_select(select)) {
                    cout << "Iveskite 1 arba 2" << endl;
                } else {
                    cont = std::chrono::high_resolution_clock::now();
                    int s = stoi(select);
                    switch (s) {
                    case 1:
                        split(arr, &average);
                        break;
                    
                    case 2:
                        split(arr, &median);
                        break;
                    }
                    break;
                }
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(pause - start);
            auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - cont);
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration1 + duration2);
            cout << "Programos veikimo laikas: " << duration.count() * 1e-9 << "\n";
            break;
        }

    }
}