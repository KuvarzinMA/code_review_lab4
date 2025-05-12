#include "name.h"
#include <iostream>

namespace company {

    Name::Name(const std::string& surname, const std::string& first_name, const std::string& patronymic)
        : surname_(surname), first_name_(first_name), patronymic_(patronymic) {
    }

    void Name::Print() const {
        if (!surname_.empty()) std::cout << surname_;
        if (!first_name_.empty()) std::cout << (surname_.empty() ? "" : " ") << first_name_;
        if (!patronymic_.empty()) std::cout << ((surname_.empty() && first_name_.empty()) ? "" : " ") << patronymic_;
        std::cout << std::endl;
    }

    std::string Name::ToString() const {
        std::string result;
        if (!surname_.empty()) result += surname_;
        if (!first_name_.empty()) result += (result.empty() ? "" : " ") + first_name_;
        if (!patronymic_.empty()) result += (result.empty() ? "" : " ") + patronymic_;
        return result;
    }

}  // namespace company
