#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>


/**
 * DS exceptions - adjustment to StatusType return values
 * 
 */
class ExceptionsDS : public std::exception {
public:
    ExceptionsDS() = default;
    ~ExceptionsDS() override = default;
};

class KeyNotFound : public ExceptionsDS {
public:
    KeyNotFound() = default; 
    ~KeyNotFound() = default;
};

class KeyExists : public ExceptionsDS {
public:
    KeyExists() = default; 
    ~KeyExists() = default;
};


#endif 