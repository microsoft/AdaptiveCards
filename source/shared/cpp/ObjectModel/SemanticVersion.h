#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class SemanticVersion
    {
    public:
        SemanticVersion(const std::string& version);

        unsigned int GetMajor() const { return _major; }
        unsigned int GetMinor() const { return _minor; }
        unsigned int GetBuild() const { return _build; }
        unsigned int GetRevision() const { return _revision; }

        operator std::string() const
        {
            std::stringstream version{};
            version << _major << '.' << _minor << '.' << _build << '.'  << _revision;
            return version.str();
        }

    private:
        unsigned int _major;
        unsigned int _minor;
        unsigned int _build;
        unsigned int _revision;
    };

    inline bool operator==(const SemanticVersion& lhs, const SemanticVersion& rhs)
    {
        return lhs.GetMajor() == rhs.GetMajor() && lhs.GetMinor() == rhs.GetMinor() &&
            lhs.GetBuild() == rhs.GetBuild() && lhs.GetRevision() == rhs.GetRevision();
    }

    inline bool operator<(const SemanticVersion& lhs, const SemanticVersion& rhs)
    {
        if (lhs.GetMajor() != rhs.GetMajor())
        {
            return lhs.GetMajor() < rhs.GetMajor();
        }
        else if (lhs.GetMinor() != rhs.GetMinor())
        {
            return lhs.GetMinor() < rhs.GetMinor();
        }
        else if (lhs.GetBuild() != rhs.GetBuild())
        {
            return lhs.GetBuild() < rhs.GetBuild();
        }
        else if (lhs.GetRevision() != rhs.GetRevision())
        {
            return lhs.GetRevision() < rhs.GetRevision();
        }
        else
        {
            return false;
        }
    }

    inline bool operator!=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator==(lhs, rhs); }
    inline bool operator>(const SemanticVersion& lhs, const SemanticVersion& rhs) { return operator<(rhs, lhs); }
    inline bool operator<=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator>(lhs, rhs); }
    inline bool operator>=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator<(lhs, rhs); }
}
