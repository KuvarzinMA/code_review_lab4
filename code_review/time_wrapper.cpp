#include "time_wrapper.h"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace company {

    Time::Time() : total_seconds_(0) {}

    Time::Time(int total_seconds) : total_seconds_(total_seconds) {
        Normalize();
    }

    Time::Time(int hours, int minutes, int seconds) {
        total_seconds_ = hours * 3600 + minutes * 60 + seconds;
        Normalize();
    }

    void Time::Normalize() {
        total_seconds_ %= 86400;
        if (total_seconds_ < 0) {
            total_seconds_ += 86400;
        }
    }

    std::string Time::GetTextFormat() const {
        int hours = (total_seconds_ / 3600) % 24;
        int minutes = (total_seconds_ % 3600) / 60;
        int seconds = total_seconds_ % 60;

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
        return oss.str();
    }

    void Time::Print() const {
        std::cout << "Текущее время: " << GetTextFormat() << std::endl;
    }

    int Time::GetCurrentHour() const {
        return (total_seconds_ / 3600) % 24;
    }

    int Time::GetMinutesFromCurrentHour() const {
        return (total_seconds_ % 3600) / 60;
    }

    int Time::GetSecondsFromCurrentMinute() const {
        return total_seconds_ % 60;
    }

    int Time::GetTotalHours() const {
        return total_seconds_ / 3600;
    }

    int Time::GetTotalMinutes() const {
        return total_seconds_ / 60;
    }

    int Time::GetTotalSeconds() const {
        return total_seconds_;
    }

}  // namespace company
