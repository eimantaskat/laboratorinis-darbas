#include "../functions.h"

// funtion to input homework grades
void input_grades(vector<int>& grades) {
    cout << "Iveskite namu darbu rezultatus, norint baigti, iveskite 0: " << endl;
    string input;
    int number = 10;
    while(true) {
        // input and verify grade
        cout << grades.size() + 1 << " pazymys: ";
        if(cin >> input) {
            if(!is_grade(input)) {
                cout << "Pazymys turi buti sveikasis skaicius nuo 1 iki 10" << endl;
            } else {
                number = stoi(input);
                if(number < 0 || number > 10) {
                    cout << "Pazymys turi buti sveikasis skaicius nuo 1 iki 10" << endl;
                } else {
                    // if input is 0 break the loop 
                    // else add grade to an array
                    if(number == 0)
                        break;
                    grades.push_back(number);
                }
            }
        }
    };
}

// function to input data
void input_data(vector<data>& arr) {
    int i = 0;
    while (true) {
        // add new element to an array
        arr.push_back(data());

        // input and verify name
        cout << "Vardas: ";
        string name;
        while(true) {
            cin >> name;
            if(!check_name(name)) {
                cout << "Ar " << name << " tikrai yra mokinio vardas? (y/n): ";
                char confirm;
                cin >> confirm;
                if(confirm == 'y') {
                    arr[i].name = name;
                    break;
                } else {
                    cout << "Vardas: ";
                }
            } else {
                arr[i].name = name;
                break;
            }
        }

        // input and verify surname
        cout << "Pavarde: ";
        string surname;
        while(true) {
            cin >> surname;
            if(!check_name(surname)) {
                cout << "Ar " << surname << " tikrai yra mokinio pavarde? (y/n): ";
                char confirm;
                cin >> confirm;
                if(confirm == 'y') {
                    arr[i].surname = surname;
                    break;
                } else {
                    cout << "Pavarde: ";
                }
            } else {
               arr[i].surname = surname;
                break;
            }
        }

        char random;
        cout << "Ar norite sugeneruoti atsitiktinius balus uz namu darbus ir egzamina? (y/n): ";
        cin >> random;
        if(random == 'y') {
            // intitialise random number generator
            srand(time(NULL));

            // generate exam result
            arr[i].exam = 1 + rand() % 10;
            
            // ask how many grades to generate
            int n;
            cout << "Kiek norite sugeneruoti namu darbu pazymiu? ";
            while(!(cin >> n)) {
                cout << "Iveskite sveikaji skaiciu \n";
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            // generate array of random grades
            for(int j = 0; j < n; j++) {
                arr[i].grades.push_back(1 + rand() % 10);
            }

        } else {
            // input and verify exam result
            string exam;
            while(true) {
                cout << "Egzamino rezultatas: ";
                cin >> exam;
                if(!is_grade(exam)) {
                    cout << "Pazymys turi buti sveikasis skaicius nuo 1 iki 10" << endl;
                } else {
                    int number = stoi(exam);
                    if(number <= 0 || number > 10) {
                        cout << "Pazymys turi buti sveikasis skaicius nuo 1 iki 10" << endl;
                    } else {
                        arr[i].exam = number;
                        break;
                    }
                }
            }

            // input homework grades
            input_grades(arr[i].grades);
        }
        i++;
        // add more students or stop
        char add_more;
        cout << "Ar norite prideti dar vieno mokinio duomenis? (y/n): ";
        cin >> add_more;
        if(add_more != 'y') {
            break;
        }
    }
}

// function to read data from file
void read_data(vector<data>& arr, string filename) {
    try {
        // open file
        std::ifstream file(filename);
        if (!file) {
            throw(1);
        }

        int lines_count = 0;
        string line;
        while (getline(file, line)) {
            lines_count++;
        }
        
        file.close();
        file.open(filename);
        
        // read file header
        vector<string> header;
        header.reserve(4);
        while (file.peek() != '\n') {
            string data;
            file >> data;
            header.push_back(data);
        }

        // get homework count
        int homework_count = header.size() - 3;
        header.clear();

        arr.reserve(lines_count - 1);
        // read data
        data temp;
        int i = 0;
        while (!file.eof()) {
            arr.push_back(data());
            file >> arr[i].name >> arr[i].surname;
            for (int j = 0; j < homework_count; j++) {
                arr[i].grades.push_back(int());
                file >> arr[i].grades[j];
            }
            file >> arr[i].exam;
            if (i > lines_count) {
                throw(2);
            }
            i++;
        }
        // close file
        file.close();

    } catch (int err) {
        switch (err) {
        case 1: 
            cout << "Failas neegzistuoja" << endl;
            break;
        case 2:
            arr.clear();
            cout << "Faile yra klaida" << endl;
        }
    }
}