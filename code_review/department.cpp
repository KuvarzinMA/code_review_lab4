#include "department.h"
#include "employee.h"

namespace company {

    Department::Department(const std::string& name, Employee* head)
        : name_(name), head_(head) {
    }

    void Department::SetHead(Employee* employee) {
        head_ = employee;
        AddEmployee(employee);
    }

    void Department::AddEmployee(Employee* employee) {
        employees_.push_back(employee);
        employee->SetDepartment(this);
    }

    std::string Department::GetName() const {
        return name_;
    }

    Employee* Department::GetHead() const {
        return head_;
    }

    const std::vector<Employee*>& Department::GetEmployees() const {
        return employees_;
    }

}  // namespace company
