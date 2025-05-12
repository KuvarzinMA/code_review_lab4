#include <string>
#include <vector>

namespace company {

	class Employee;

	class Department {
	public:
		explicit Department(const std::string& name, Employee* head = nullptr);

		void SetHead(Employee* employee);
		void AddEmployee(Employee* employee);
		std::string GetName() const;
		Employee* GetHead() const;
		const std::vector<Employee*>& GetEmployees() const;

	private:
		std::string name_;
		Employee* head_;
		std::vector<Employee*> employees_;
	};

}  // namespace company
