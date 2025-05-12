#include <string>

namespace company {

	class Name {
	public:
		Name(const std::string& surname = "", const std::string& first_name = "", const std::string& patronymic = "");

		void Print() const;
		std::string ToString() const;

	private:
		std::string surname_;
		std::string first_name_;
		std::string patronymic_;
	};

}  // namespace company
