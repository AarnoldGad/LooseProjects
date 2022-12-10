#include "scan/ProgramArguments/ArgumentDescriptor.hpp"

ArgumentDescriptor::ArgumentDescriptor(std::string const& name, char const shortName, std::string const& description)
    : m_name(name), m_shortName(shortName), m_description(description) {}