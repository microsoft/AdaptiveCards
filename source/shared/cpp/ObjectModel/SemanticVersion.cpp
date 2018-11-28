#include "pch.h"
#include "SemanticVersion.h"
#include "AdaptiveCardParseException.h"

namespace AdaptiveSharedNamespace
{
    static inline bool _IsWildcard(const std::string& subVersion)
    {
        return (subVersion.length() == 1 && subVersion.at(0) == '*');
    }

    static inline void _ValidateNoFurtherMatches(const unsigned int index, const std::smatch& matches)
    {
        for (unsigned int i = index; i < matches.size(); i++)
        {
            if (matches[i].matched)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Semantic version wildcard invalid");
            }
        }
    }

    SemanticVersion::SemanticVersion(WildcardSupport supportWildcards) :
        _supportWildcards(supportWildcards), _version(static_cast<unsigned int>(SemanticVersionSegment::Max)),
        _wildcard(static_cast<unsigned int>(SemanticVersionSegment::Max))
    {
    }

    SemanticVersion::SemanticVersion(const std::string& version, WildcardSupport supportWildcards) :
        _supportWildcards(supportWildcards), _version(static_cast<unsigned int>(SemanticVersionSegment::Max)),
        _wildcard(static_cast<unsigned int>(SemanticVersionSegment::Max))
    {
        bool versionValid = false;
        if (supportsWildcards())
        {
#pragma warning(push)
#pragma warning(disable : 26426)
            // disable spurious warning (Global initializer calls a non-constexpr function.) -- this isn't global
            static const std::regex versionMatch(R"regex(^([\d]+|\*)(?:\.((?:[\d]+|\*)))?(?:\.((?:[\d]+|\*)))?(?:\.((?:[\d]+|\*)))?$)regex");
#pragma warning(pop)
            std::smatch subMatches;
            if (std::regex_match(version, subMatches, versionMatch))
            {
                versionValid = true;
                try
                {
                    // subMatches[0] contains the entire string, so no need to refer to it here
                    // subMatches[i+1] contains the version segments
                    for (unsigned int i = 0; i < static_cast<unsigned int>(SemanticVersionSegment::Max); i++)
                    {
                        const SemanticVersionSegment currSegment = static_cast<SemanticVersionSegment>(i);
                        if (subMatches[i + 1].matched)
                        {
                            auto match = subMatches[i + 1].str();
                            if (_IsWildcard(match))
                            {
                                // found wildcard -- set this and all further segments as wildcard. make sure we don't
                                // have any further matches.
                                for (unsigned int j = i; j < static_cast<unsigned int>(SemanticVersionSegment::Max); j++)
                                {
                                    _wildcard[j] = true;
                                    if (j > i && subMatches[j + 1].matched)
                                    {
                                        throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                                         "Semantic version wildcard invalid");
                                    }
                                }
                                break;
                            }
                            else
                            {
                                // not a wildcard. convert to int and continue.
                                _version[i] = std::stoi(match);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                catch (const std::out_of_range&)
                {
                    versionValid = false;
                }
            }
        }
        else
        {
            // valid:
            // "1"
            // "1.2"
            // "1.2.3"
            // "1.2.3.4"
            //
            // invalid:
            // ""
            // "1."
            // "F"

#pragma warning(push)
#pragma warning(disable : 26426)
            // disable spurious warning (Global initializer calls a non-constexpr function.) -- this isn't global
            static const std::regex versionMatch(R"regex(^([\d]+)(?:\.([\d]+))?(?:\.([\d]+))?(?:\.([\d]+))?$)regex");
#pragma warning(pop)
            std::smatch subMatches;
            if (std::regex_match(version, subMatches, versionMatch))
            {
                versionValid = true;

                try
                {
                    // subMatches[i+1] contains version segment (subMatches[0] contains entire string)
                    for (unsigned int i = 0; i < static_cast<unsigned int>(SemanticVersionSegment::Max); i++)
                    {
                        const SemanticVersionSegment currSegment = static_cast<SemanticVersionSegment>(i);
                        if (subMatches[i + 1].matched)
                        {
                            _version[i] = std::stoi(subMatches[i + 1]);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                catch (const std::out_of_range&)
                {
                    versionValid = false;
                }
            }
        }

        if (!versionValid)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Semantic version invalid: " + version);
        }
    }

    namespace Version
    {
        bool IsInRange(const std::string& versionRange, const SemanticVersion& version)
        {
            static const std::regex versionRangeMatch(R"regex(^([\(\[]?)?([\d\.\*]+)?(,)?([\d\.\*]+)?([\)\]]?)?$)regex");
            std::smatch submatches;
            if (std::regex_match(versionRange, submatches, versionRangeMatch))
            {
                SemanticVersion lhs(WildcardSupport::Supported);
                bool lhsInclusive = false;
                SemanticVersion rhs(WildcardSupport::Supported);
                bool rhsInclusive = false;

                // submatches[0] contains the entire string, so no need to refer to it here
                const bool hasOpeningBracket = submatches[1].matched &&
                    !submatches[1].str().empty(); // submatches[1] -> opening bracket (paren or square brace) or nothing
                const bool hasLhs = submatches[2].matched;   // submatches[2] -> lhs version or nothing
                const bool hasComma = submatches[3].matched; // submatches[3] -> ',' or nothing
                const bool hasRhs = submatches[4].matched;   // submatches[4] -> rhs version or nothing
                const bool hasClosingBracket = submatches[5].matched &&
                    !submatches[5].str().empty(); // submatches[5] -> closing bracket (paren or square brace) or nothing

                if (hasOpeningBracket)
                {
                    switch (submatches[1].str().at(0))
                    {
                    case L'(':
                    {
                        lhsInclusive = false;
                        break;
                    }
                    case L'[':
                    {
                        lhsInclusive = true;
                        break;
                    }
                    }
                }

                if (hasLhs)
                {
                    SemanticVersion lhsRange(submatches[2].str(), WildcardSupport::Supported);
                    lhs = lhsRange;
                }

                if (hasComma && !(hasLhs || hasRhs))
                {
                    // oops -- comma with no version on either side!
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                     "Version range invalid (comma with no supplied version): " + versionRange);
                }

                if (hasRhs)
                {
                    SemanticVersion rhsRange(submatches[4].str(), WildcardSupport::Supported);
                    rhs = rhsRange;
                }

                if (hasLhs && hasRhs && lhs > rhs)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                     "Version range invalid (minimum version larger than maximum): " + versionRange);
                }

                if (hasClosingBracket)
                {
                    switch (submatches[5].str().at(0))
                    {
                    case L')':
                    {
                        rhsInclusive = false;
                        break;
                    }
                    case L']':
                    {
                        rhsInclusive = true;
                        break;
                    }
                    }
                }

                if (hasOpeningBracket && !hasClosingBracket)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                     "Version range invalid (has opening bracket, but no closing bracket)");
                }
                else if (!hasOpeningBracket && hasClosingBracket)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                     "Version range invalid (has closing bracket, but no opening bracket)");
                }
                else
                {
                    // don't allow `(1)` -- it's invalid
                    if (hasOpeningBracket && hasLhs && !hasComma && !hasRhs && hasClosingBracket && !lhsInclusive && !rhsInclusive)
                    {
                        throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                         "Version range invalid (exclusive of a single version)");
                    }

                    if (hasOpeningBracket && hasClosingBracket)
                    {
                        bool inRangeLhs = !hasLhs;
                        if (hasLhs)
                        {
                            if (lhsInclusive)
                            {
                                inRangeLhs = (lhs <= version);
                            }
                            else
                            {
                                inRangeLhs = (lhs < version);
                            }
                        }

                        bool inRangeRhs = !hasRhs;
                        if (hasRhs)
                        {
                            if (rhsInclusive)
                            {
                                inRangeRhs = (version <= rhs);
                            }
                            else
                            {
                                inRangeRhs = (version < rhs);
                            }
                        }
                        return inRangeLhs && inRangeRhs;
                    }
                    else
                    {
                        // the only valid scenario that has no brackets here would be if lhs is the only item set (wildcards allowed)
                        if (hasRhs || hasComma)
                        {
                            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                             "Version range invalid (no brackets, but have a comma or right-hand-side of range)");
                        }
                        else
                        {
                            return version == lhs;
                        }
                    }
                }
            }

            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Version range invalid");
        }
    }
}
