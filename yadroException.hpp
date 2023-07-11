//
// Created by Kotozzavrik on 06.07.2023.
//

#ifndef YADRO2____YADROEXCEPTION_HPP
#define YADRO2____YADROEXCEPTION_HPP
#include <exception>

class yadroException : public std::exception {
public:
public:
    enum class ExceptionType {
        WrongValue,
        WrongPositioning,
        FileNotFound
    };

    yadroException(ExceptionType type)
            : m_type(type) {}

    const char* what() const noexcept override {
        switch (m_type) {
            case ExceptionType::WrongValue:
                return "Value should be >= 0 for delay and >0 for buffer size.";
            case ExceptionType::WrongPositioning:
                return "Position is out of tape.";
            case ExceptionType::FileNotFound:
                return "There is no such file";
            default:
                return "Unknown exception";
        }
    }

private:
    ExceptionType m_type;
};
#endif //YADRO2____YADROEXCEPTION_HPP
