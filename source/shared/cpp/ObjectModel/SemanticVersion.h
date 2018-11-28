#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    // In a semantic version, this enum tracks which segment we're referring to:
    // 1.2.3.4
    // ^ ^ ^ ^- Revision
    // | | - Build
    // | - Minor
    // - Major
    enum class SemanticVersionSegment : unsigned int
    {
        Major = 0,
        Minor,
        Build,
        Revision,
        Max // must always be last
    };

    // Indicates if a SemanticVersion instance supports wildcards. We could use a bool here, but it complicates the
    // SemanticVersion ctors.
    enum class WildcardSupport
    {
        Supported,
        NotSupported
    };

    class SemanticVersion final
    {
    public:
        SemanticVersion(WildcardSupport supportWildcards);
        SemanticVersion(const std::string& version, WildcardSupport supportWildcards);

        // Get the value of the requested version segment
        unsigned int get(const SemanticVersionSegment segment) const
        {
            return _version.at(static_cast<unsigned int>(segment));
        }
        bool supportsWildcards() const noexcept { return _supportWildcards == WildcardSupport::Supported; }
        bool hasWildcard(const SemanticVersionSegment segment) const
        {
            return supportsWildcards() && _wildcard.at(static_cast<unsigned int>(segment));
        }

    private:
        WildcardSupport _supportWildcards;
        std::vector<unsigned int> _version;
        std::vector<bool> _wildcard;
    };

    inline bool operator==(const SemanticVersion& lhs, const SemanticVersion& rhs)
    {
        for (unsigned int i = 0; i < static_cast<unsigned int>(SemanticVersionSegment::Max); i++)
        {
            const SemanticVersionSegment currSegment = static_cast<SemanticVersionSegment>(i);
            if (lhs.hasWildcard(currSegment) || rhs.hasWildcard(currSegment))
            {
                // wildcards always match.
                return true;
            }
            else if (lhs.get(currSegment) != rhs.get(currSegment))
            {
                // not equal, no need to examine further segments.
                return false;
            }
            else
            {
                // current segment matches. continue to next.
            }
        }
        return true;
    }

    inline bool operator<(const SemanticVersion& lhs, const SemanticVersion& rhs)
    {
        for (unsigned int i = 0; i < static_cast<unsigned int>(SemanticVersionSegment::Max); i++)
        {
            const SemanticVersionSegment currSegment = static_cast<SemanticVersionSegment>(i);
            const auto lhsVersion = lhs.get(currSegment);
            const auto rhsVersion = rhs.get(currSegment);
            if (lhs.hasWildcard(currSegment) || rhs.hasWildcard(currSegment))
            {
                return false;
            }
            else if (lhsVersion == rhsVersion)
            {
                // current segment matches. continue to next.
            }
            else
            {
                return lhsVersion < rhsVersion;
            }
        }
        return false;
    }

    inline bool operator!=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator==(lhs, rhs); }
    inline bool operator>(const SemanticVersion& lhs, const SemanticVersion& rhs) { return operator<(rhs, lhs); }
    inline bool operator<=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator>(lhs, rhs); }
    inline bool operator>=(const SemanticVersion& lhs, const SemanticVersion& rhs) { return !operator<(lhs, rhs); }

    namespace Version
    {
        bool IsInRange(const std::string& versionRange, const SemanticVersion& version);
    }
}
