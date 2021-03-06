#include "../functions.h"

// funtion to input homework grades
void input_grades(list<int>& grades) {
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
void input_data(list<data>& arr) {
    int i = 0;
    while (true) {
        // add new element to an array
        data tmp;

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
                    tmp.name = name;
                    break;
                } else {
                    cout << "Vardas: ";
                }
            } else {
                tmp.name = name;
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
                    tmp.surname = surname;
                    break;
                } else {
                    cout << "Pavarde: ";
                }
            } else {
               tmp.surname = surname;
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
            tmp.exam = 1 + rand() % 10;
            
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
                tmp.grades.push_back(1 + rand() % 10);
            }
            arr.push_back(tmp);

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
                        tmp.exam = number;
                        break;
                    }
                }
            }

            // input homework grades
            input_grades(tmp.grades);
            arr.push_back(tmp);
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
void read_data(list<data>& arr, string filename) {
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::stringstream buffer;
        // open file
        std::ifstream file(filename);
        if (!file) {
            throw(1);
        }
        buffer << file.rdbuf();

        file.close();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        cout << "Failo skaitymas uztruko: " << duration.count() * 1e-9 << "s\n";

        start = std::chrono::high_resolution_clock::now();
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
        list<string> header;
        while (buffer.peek() != '\n') {
            string data;
            buffer >> data;
            header.push_back(data);
        }

        // get homework count
        int homework_count = header.size() - 3;
        header.clear();

        // read data
        int i = 0;
        while (!buffer.eof()) {
            data tmp;
            buffer >> tmp.name >> tmp.surname;
            for (int j = 0; j < homework_count; j++) {
                tmp.grades.push_back(int());
                buffer >> tmp.grades[j];
            }
            buffer >> tmp.exam;
            arr.push_back(tmp);
            if (i > lines_count) {
                throw(2);
            }
            i++;
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        cout << "Duomenu paruosimas programos naudojimui uztruko: " << duration.count() * 1e-9 << "s\n";
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