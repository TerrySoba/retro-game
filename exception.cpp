#include "exception.h"

Exception::Exception(const std::string& message) :
    std::runtime_error(message)
{
}
