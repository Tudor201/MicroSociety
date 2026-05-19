#ifndef MICROSOCIETY_EXCEPTIONS_H
#define MICROSOCIETY_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class MicroSocietyException : public std::runtime_error {
public:
    explicit MicroSocietyException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidAgentException : public MicroSocietyException {
public:
    explicit InvalidAgentException(const std::string& message)
        : MicroSocietyException(message) {}
};

class WorldException : public MicroSocietyException {
public:
    explicit WorldException(const std::string& message)
        : MicroSocietyException(message) {}
};

class ConfigException : public MicroSocietyException {
public:
    explicit ConfigException(const std::string& message)
        : MicroSocietyException(message) {}
};

#endif //MICROSOCIETY_EXCEPTIONS_H