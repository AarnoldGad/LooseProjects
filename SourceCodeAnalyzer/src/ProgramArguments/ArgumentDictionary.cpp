#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>

#include "scan/ProgramArguments/ArgumentDictionary.hpp"
#include "scan/ProgramArguments/ArgumentDescriptor.hpp"

ArgumentDictionary::ArgumentDictionary() {}

ArgumentDictionary::ArgumentDictionary(std::initializer_list<ArgumentDescriptor> descriptors)
{
   addEntries(descriptors);
}

void ArgumentDictionary::addEntry(ArgumentDescriptor const& descriptor)
{
   add(descriptor);
}

void ArgumentDictionary::addEntry(std::string const& name, char shortName, std::string const& description)
{
   add({name, shortName, description});
}

void ArgumentDictionary::addEntries(std::initializer_list<ArgumentDescriptor> descriptors)
{
   for (auto const& descriptor : descriptors)
      add(descriptor);
}

ArgumentDescriptor const* ArgumentDictionary::find(std::string const& name) const
{
   auto desc = m_nameIndex.find(name);
   if (desc != m_nameIndex.end())
      return desc->second;
   else
      return nullptr;
}

ArgumentDescriptor const* ArgumentDictionary::find(char const shortName) const
{
   auto desc = m_shortNameIndex.find(shortName);
   if (desc != m_shortNameIndex.end())
      return desc->second;
   else
      return nullptr;
}

void ArgumentDictionary::add(ArgumentDescriptor const& descriptor)
{
   if (!find(descriptor.getName()) && !find(descriptor.getShortName())) {
      ArgumentDescriptor const* descPtr = &*m_descriptors.insert(m_descriptors.end(), descriptor);
      m_nameIndex.emplace(descPtr->getName(), descPtr);
      m_shortNameIndex.emplace(descPtr->getShortName(), descPtr);
   } else {
      std::cout << "ERROR: An argument with this name already exist" << std::endl;
   }
}