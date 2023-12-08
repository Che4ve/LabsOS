// Вариант 33:	6	9

#include <iostream>
#include "dlexp.h"
#include "dlsort.h"

int main() {
    char choice;
    std::cout << "Options:" << std::endl;
    std::cout << "'1' - 1st realization\n'2' - 2nd realization\n'q' - Quit" << std::endl;
    do {
        std::cout << "Enter your option: ";
        std::cin >> choice;
        int arg;
        switch (choice) {
            case '1':
                std::cout << "\tEnter argument: ";
                std::cin >> arg;
                std::cout << "\tAnswer: " << E1(arg) << std::endl;
                break;
            case '2':
                std::cout << "\tEnter argument: ";
                std::cin >> arg;
                std::cout << "\tAnswer: " << E2(arg) << std::endl;
                break;
            case 'q':
                std::cout << "Bye!" << std::endl;
                break;
            default: 
                std::cout << "No such option " << std::endl;
                break;
        }
    } while (choice != 'q');

    return 0;
}