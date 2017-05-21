#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

#define _MY_STR_HELPER(x) #x
#define _MY_STR_(x) _MY_STR_HELPER(x)
#define _LOG_PREFIX __FILE__ ":" _MY_STR_(__LINE__) "> "

#define THROW_EXCEPTION(message) throw Exception(std::string(_LOG_PREFIX) + message)


class Exception : public std::runtime_error
{
public:
    Exception(const std::string& message);
};

#endif // EXCEPTION_H
