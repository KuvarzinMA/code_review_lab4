#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>


#include "name.h"
#include "time_wrapper.h"
#include "employee.h"
#include "department.h"

using company::Department;
using company::Employee;
using company::Name;
using company::Time;

int main() {
    std::setlocale(LC_ALL, "Russian");

    try {
        std::cout << "Введите 3 ФИО (Фамилия Имя Отчество):" << std::endl;
        Name names[3];

        for (int i = 0; i < 3; ++i) {
            std::string surname, first_name, patronymic;
            std::cout << "Имя " << i + 1 << ": ";
            std::cin >> surname >> first_name;
            std::cin.ignore();
            std::getline(std::cin, patronymic);
            names[i] = Name(surname, first_name, patronymic);
        }

        std::cout << "\nВведенные имена:" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "Имя " << i + 1 << ": ";
            names[i].Print();
        }

        std::cout << "\nВведите время в секундах: ";
        int seconds_input;
        while (!(std::cin >> seconds_input) || seconds_input < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите положительное число: ";
        }

        Time time_from_seconds(seconds_input);
        time_from_seconds.Print();

        std::cout << "\nВведите время (часы минуты секунды): ";
        int hours, minutes, seconds;
        while (!(std::cin >> hours >> minutes >> seconds) ||
            hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите корректное время: ";
        }

        Time time_from_components(hours, minutes, seconds);
        time_from_components.Print();

        std::vector<Employee> employees;
        std::vector<Department> departments;

        std::cout << "\nСколько сотрудников вы хотите создать? ";
        int employee_count;
        while (!(std::cin >> employee_count) || employee_count <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите положительное число: ";
        }

        std::cin.ignore();
        for (int i = 0; i < employee_count; ++i) {
            std::string name;
            std::cout << "Введите имя сотрудника " << i + 1 << ": ";
            std::getline(std::cin, name);
            employees.emplace_back(name);
        }

        std::cout << "\nСколько отделов вы хотите создать? ";
        int department_count;
        while (!(std::cin >> department_count) || department_count <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите положительное число: ";
        }

        std::cin.ignore();
        for (int i = 0; i < department_count; ++i) {
            std::string dept_name;
            std::cout << "\nНазвание отдела " << i + 1 << ": ";
            std::getline(std::cin, dept_name);
            departments.emplace_back(dept_name);

            std::cout << "Выберите начальника отдела (1-" << employees.size() << "): ";
            int head_index;
            while (!(std::cin >> head_index) || head_index < 1 || head_index > static_cast<int>(employees.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка! Введите корректный номер: ";
            }
            departments.back().SetHead(&employees[head_index - 1]);

            std::cout << "Введите номера сотрудников (через пробел, 0 — завершить): ";
            std::cin.ignore();
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            int employee_number;
            while (iss >> employee_number && employee_number != 0) {
                if (employee_number >= 1 && employee_number <= static_cast<int>(employees.size())) {
                    departments.back().AddEmployee(&employees[employee_number - 1]);
                }
            }
        }

        std::cout << "\nИнформация о сотрудниках:\n";
        for (const auto& employee : employees) {
            employee.Print();
        }

        std::cin.ignore();
        std::string search_name;
        std::cout << "\nВведите имя сотрудника для поиска: ";
        std::getline(std::cin, search_name);

        bool found = false;
        for (const auto& employee : employees) {
            if (employee.GetName() == search_name) {
                found = true;
                std::cout << "Сотрудник найден:\n";
                employee.Print();

                const Department* department = employee.GetDepartment();
                if (department) {
                    std::cout << "\nСписок сотрудников отдела " << department->GetName() << ":\n";
                    for (const auto& dept_emp : department->GetEmployees()) {
                        std::cout << "- " << dept_emp->GetName() << "\n";
                    }
                }
                else {
                    std::cout << "Сотрудник не принадлежит ни к одному отделу.\n";
                }
                break;
            }
        }

        if (!found) {
            std::cout << "Сотрудник с именем '" << search_name << "' не найден.\n";
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "Произошла ошибка: " << ex.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка" << std::endl;
        return 2;
    }

    return 0;
}
