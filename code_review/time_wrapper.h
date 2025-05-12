#include <string>

namespace company {

	class Time {
	public:
		Time();
		explicit Time(int total_seconds);
		Time(int hours, int minutes, int seconds);

		std::string GetTextFormat() const;
		void Print() const;

		int GetCurrentHour() const;
		int GetMinutesFromCurrentHour() const;
		int GetSecondsFromCurrentMinute() const;

		int GetTotalHours() const;
		int GetTotalMinutes() const;
		int GetTotalSeconds() const;

	private:
		void Normalize();

		int total_seconds_;
	};

}  // namespace company
