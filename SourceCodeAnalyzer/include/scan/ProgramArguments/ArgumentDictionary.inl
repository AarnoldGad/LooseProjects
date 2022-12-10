inline std::vector<ArgumentDescriptor>::iterator ArgumentDictionary::begin() noexcept
{
    return m_descriptors.begin();
}

inline std::vector<ArgumentDescriptor>::const_iterator ArgumentDictionary::begin() const noexcept
{
    return m_descriptors.begin();
}

inline std::vector<ArgumentDescriptor>::reverse_iterator ArgumentDictionary::rbegin() noexcept
{
    return m_descriptors.rbegin();
}

inline std::vector<ArgumentDescriptor>::const_reverse_iterator ArgumentDictionary::rbegin() const noexcept
{
    return m_descriptors.rbegin();
}

inline std::vector<ArgumentDescriptor>::iterator ArgumentDictionary::end() noexcept
{
    return m_descriptors.end();
}

inline std::vector<ArgumentDescriptor>::const_iterator ArgumentDictionary::end() const noexcept
{
    return m_descriptors.cend();
}

inline std::vector<ArgumentDescriptor>::reverse_iterator ArgumentDictionary::rend() noexcept
{
    return m_descriptors.rend();
}

inline std::vector<ArgumentDescriptor>::const_reverse_iterator ArgumentDictionary::rend() const noexcept
{
    return m_descriptors.crend();
}