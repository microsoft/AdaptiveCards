// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "SemanticVersion.h"
#include "AdaptiveCardParseException.h"

using namespace AdaptiveSharedNamespace;

SemanticVersion::SemanticVersion(const std::string& version) : _major(0), _minor(0), _build(0), _revision(0)
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

    bool versionValid = false;
#pragma warning(push)
#pragma warning(disable : 26426)
    // disable spurious warning (Global initializer calls a non-constexpr function.) -- this isn't global
    static const std::regex versionMatch(R"regex(^([\d]+)(?:\.([\d]+))?(?:\.([\d]+))?(?:\.([\d]+))?$)regex");
#pragma warning(pop)
    std::smatch subMatches;
    if (std::regex_match(version, subMatches, versionMatch))
    {
        versionValid = true;
        // subMatches[0] contains the entire string, so no need to refer to it here

        try
        {
            // subMatches[1] contains the major version
            if (subMatches[1].matched)
            {
                _major = std::stoi(subMatches[1]);
            }

            if (subMatches[2].matched)
            {
                // subMatches[2] contains the minor version
                _minor = std::stoi(subMatches[2]);
            }

            if (subMatches[3].matched)
            {
                // subMatches[3] contains the build version
                _build = std::stoi(subMatches[3]);
            }

            if (subMatches[4].matched)
            {
                // subMatches[4] contains the revision
                _revision = std::stoi(subMatches[4]);
            }
        }
        catch (const std::out_of_range&)
        {
            versionValid = false;
        }
    }

    if (!versionValid)
    {
        throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Semantic version invalid: " + version);
    }
}
