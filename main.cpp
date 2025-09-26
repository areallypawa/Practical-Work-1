#include <iostream>
#include <string>
using namespace std;

const int TASK2 = 127;
const float TASK3 = 3.14;
const double TASK4 = 3.14;

union MyFloatUnion {
    int tool;
    float num;
};
MyFloatUnion myFloatUnion;
union MyDoubleUnion {
    int tool[2];
    double num;
};
MyDoubleUnion myDoubleUnion;

void Algorithm_print_bits(int num) {
    const int BITS = sizeof(num) * 8;
    unsigned int mask = 1 << (BITS - 1);

    for (int i(0); i < BITS; i++) {
        if (((i == 1) || (i % 4 == 0)) && (i != 0)) {
            cout << ' ';
        }
        cout << (num & mask ? '1' : '0');
        mask >>= 1;
    }
    cout << '\n';
}

void Algorithm_print_double() {
    // Bin-Code for tip double 
    const int BITS = sizeof(int) * 8;

    for (int j(1); j > -1; j--) {
        unsigned int mask = 1 << (BITS - 1);
        for (int i(0); i < BITS; i++) {
            if (((i == 1) || (i == 12)) && (i != 0) && (j == 1)) {
                cout << "__";
            }
            else if (i % 4 == 0) {
                cout << ' ';
            }
            cout << (myDoubleUnion.tool[j] & mask ? '1' : '0');
            mask >>= 1;
        }
    }
}

void Algorithm_for_task_5(int number, int flag) {
    cout << "\nВведи индекс бита и значение на которое его поменять\n";
    int idx; bool value;
    cin >> idx >> value;

    int modify_num;
    const int BITS = sizeof(number) * 8;

    if (value) {
        unsigned int mask = (1 << idx);
        modify_num = number | mask;

        switch (flag) {
        case 1:
            cout << "Стало число " << modify_num << " BIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 2:
            myFloatUnion.tool = modify_num;
            cout << "Стало число " << myFloatUnion.num << " BIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 3:
            if (idx > 31) {
                unsigned int mask = (1 << (idx - 32));
                modify_num = myDoubleUnion.tool[1] | mask;
                myDoubleUnion.tool[1] = modify_num;
            }
            else {
                unsigned int mask = (1 << (idx));
                modify_num = myDoubleUnion.tool[0] | mask;
                myDoubleUnion.tool[0] = modify_num;
            }
            cout << "Стало число " << myDoubleUnion.num << " BIN: ";
            Algorithm_print_double();
            break;
        }
    } else {
        unsigned int mask = (1 << BITS) - 1 - (1 << idx);
        modify_num = number & mask;

        switch (flag) {
        case 1:
            cout << "Стало число " << modify_num << " BIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 2:
            myFloatUnion.tool = modify_num;
            cout << "Стало число " << myFloatUnion.num << " BIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 3:
            if (idx > 31) {
                unsigned int mask = (1 << BITS) - 1 - (1 << idx - 32);
                modify_num = myDoubleUnion.tool[1] & mask;
                myDoubleUnion.tool[1] = modify_num;
            }
            else {
                unsigned int mask = (1 << BITS) - 1 - (1 << idx);
                modify_num = myDoubleUnion.tool[0] & mask;
                myDoubleUnion.tool[0] = modify_num;
            }
            cout << "Стало число " << myDoubleUnion.num << " BIN: ";
            Algorithm_print_double();
            break;
        }
    }
}

void Task_1() {
    cout << "TASK_1\n";
    cout
        << "int: " << sizeof(int) << " байта\n"
        << "short int: " << sizeof(short int) << " байта\n"
        << "long int: " << sizeof(long int) << " байта\n"
        << "long long int: " << sizeof(long long int) << " байт\n"
        << "float: " << sizeof(float) << " байта\n"
        << "double: " << sizeof(double) << " байт\n"
        << "long double: " << sizeof(long double) << " байт\n"
        << "char: " << sizeof(char) << " байт\n"
        << "bool: " << sizeof(bool) << " байт\n";
}

void Task_2(int num) {
    cout << "\nTASK_2\n";
    Algorithm_print_bits(num);
}

void Task_3(float n) {
    cout << "\nTASK_3\n";

    myFloatUnion.num = n;

    Algorithm_print_bits(myFloatUnion.tool);
    cout << '\n';
}

void Task_4(double n) {
    cout << "TASK_4\n";
    myDoubleUnion.num = n;

    Algorithm_print_double();
    cout << '\n';  
}

void Task_5() {
    short num_type;
    cout << "С каким числом работаем?\n1 - int\n2 - float\n3 - double\n";
    cin >> num_type;

    switch (num_type) {
    case 1:
        cout << "Было число " << TASK2 << " BIN: ";
        Algorithm_print_bits(TASK2);
        Algorithm_for_task_5(TASK2, 1);
        break;
    case 2:
        myFloatUnion.num = TASK3;
        cout << "Было число " << TASK3 << " BIN: ";
        Algorithm_print_bits(myFloatUnion.tool);
        Algorithm_for_task_5(myFloatUnion.tool, 2);
        break;
    case 3:
        myDoubleUnion.num = TASK4;
        cout << "Было число " << TASK4 << " BIN: ";
        Algorithm_print_double();
        Algorithm_for_task_5(myFloatUnion.tool, 3);
        break;
    }
}

int main() {
    setlocale(0, "");

    Task_1();
    Task_2(TASK2);
    Task_3(TASK3);
    Task_4(TASK4);

    while (1) {
        Task_5();
    }
    return 0;
}
