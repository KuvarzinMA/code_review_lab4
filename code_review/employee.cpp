#include "employee.h"
#include "department.h"
#include <iostream>

namespace company {

    Employee::Employee(const std::string& name, Department* department)
        : name_(name), department_(department) {
    }

    void Employee::SetDepartment(Department* department) {
        department_ = department;
    }

    std::string Employee::GetName() const {
        return name_;
    }

    void Employee::Print() const {
        if (department_) {
            if (IsDepartmentHead()) {
                std::cout << name_ << " начальник отдела " << department_->GetName() << std::endl;
            }
            else {
                std::cout << name_ << " работает в отделе " << department_->GetName()
                    << ", начальник которого " << department_->GetHead()->GetName() << std::endl;
            }
        }
        else {
            std::cout << name_ << " не прикреплен к отделу" << std::endl;
        }
    }

    Department* Employee::GetDepartment() const {
        return department_;
    }

    bool Employee::IsDepartmentHead() const {
        return department_ && department_->GetHead() == this;
    }

}  // namespace company
