#include <string>

namespace company {

	class Department;

	class Employee {
	public:
		explicit Employee(const std::string& name, Department* department = nullptr);

		void SetDepartment(Department* department);
		std::string GetName() const;
		void Print() const;
		Department* GetDepartment() const;
		bool IsDepartmentHead() const;

	private:
		std::string name_;
		Department* department_;
	};

}  // namespace company
