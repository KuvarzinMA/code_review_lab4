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
        std::cout << "������� 3 ��� (������� ��� ��������):" << std::endl;
        Name names[3];

        for (int i = 0; i < 3; ++i) {
            std::string surname, first_name, patronymic;
            std::cout << "��� " << i + 1 << ": ";
            std::cin >> surname >> first_name;
            std::cin.ignore();
            std::getline(std::cin, patronymic);
            names[i] = Name(surname, first_name, patronymic);
        }

        std::cout << "\n��������� �����:" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "��� " << i + 1 << ": ";
            names[i].Print();
        }

        std::cout << "\n������� ����� � ��������: ";
        int seconds_input;
        while (!(std::cin >> seconds_input) || seconds_input < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ������������� �����: ";
        }

        Time time_from_seconds(seconds_input);
        time_from_seconds.Print();

        std::cout << "\n������� ����� (���� ������ �������): ";
        int hours, minutes, seconds;
        while (!(std::cin >> hours >> minutes >> seconds) ||
            hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ���������� �����: ";
        }

        Time time_from_components(hours, minutes, seconds);
        time_from_components.Print();

        std::vector<Employee> employees;
        std::vector<Department> departments;

        std::cout << "\n������� ����������� �� ������ �������? ";
        int employee_count;
        while (!(std::cin >> employee_count) || employee_count <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ������������� �����: ";
        }

        std::cin.ignore();
        for (int i = 0; i < employee_count; ++i) {
            std::string name;
            std::cout << "������� ��� ���������� " << i + 1 << ": ";
            std::getline(std::cin, name);
            employees.emplace_back(name);
        }

        std::cout << "\n������� ������� �� ������ �������? ";
        int department_count;
        while (!(std::cin >> department_count) || department_count <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ������������� �����: ";
        }

        std::cin.ignore();
        for (int i = 0; i < department_count; ++i) {
            std::string dept_name;
            std::cout << "\n�������� ������ " << i + 1 << ": ";
            std::getline(std::cin, dept_name);
            departments.emplace_back(dept_name);

            std::cout << "�������� ���������� ������ (1-" << employees.size() << "): ";
            int head_index;
            while (!(std::cin >> head_index) || head_index < 1 || head_index > static_cast<int>(employees.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������! ������� ���������� �����: ";
            }
            departments.back().SetHead(&employees[head_index - 1]);

            std::cout << "������� ������ ����������� (����� ������, 0 � ���������): ";
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

        std::cout << "\n���������� � �����������:\n";
        for (const auto& employee : employees) {
            employee.Print();
        }

        std::cin.ignore();
        std::string search_name;
        std::cout << "\n������� ��� ���������� ��� ������: ";
        std::getline(std::cin, search_name);

        bool found = false;
        for (const auto& employee : employees) {
            if (employee.GetName() == search_name) {
                found = true;
                std::cout << "��������� ������:\n";
                employee.Print();

                const Department* department = employee.GetDepartment();
                if (department) {
                    std::cout << "\n������ ����������� ������ " << department->GetName() << ":\n";
                    for (const auto& dept_emp : department->GetEmployees()) {
                        std::cout << "- " << dept_emp->GetName() << "\n";
                    }
                }
                else {
                    std::cout << "��������� �� ����������� �� � ������ ������.\n";
                }
                break;
            }
        }

        if (!found) {
            std::cout << "��������� � ������ '" << search_name << "' �� ������.\n";
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "��������� ������: " << ex.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "����������� ������" << std::endl;
        return 2;
    }

    return 0;
}
