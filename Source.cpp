#include "functions.h"

int main() {
    string container;
    cout << "Koki konteineri norite naudoti?\n1 - std::vector\n2 - std::list\n3 - std::deque\n";
    while (true) {
        cin >> container;
        if (!check_select1(container)) {
            cout << "Iveskite 1, 2 arba 3" << endl;
        }
        else
            break;
    }
    int c = stoi(container);


    // input data
    string select;
    cout << "Ka norite daryti?\n1 - ivesti duomeis\n2 - sugeneruoti duomenis\n3 - surusioti studentus i vargsiukus ir kietiakus\n";

    while (true) {
        cin >> select;
        if (!check_select1(select)) {
            cout << "Iveskite 1, 2 arba 3" << endl;
        }
        else
            break;
    }
    int s = stoi(select);

    switch (s) {
    case 1:
        switch (c) {
        case 1:
            vector_data_input();
            break;
        case 2:
            list_data_input();
            break;
        case 3:
            deque_data_input();
            break;
        }
        break;

    case 2: {
        data_generation();
        break;
    }
    case 3: {
        switch (c) {
        case 1:
            vector_student_sorting();
            break;
        case 2:
            list_student_sorting();
            break;
        case 3:
            deque_student_sorting();
            break;
        }
        break;
    }
    }
}