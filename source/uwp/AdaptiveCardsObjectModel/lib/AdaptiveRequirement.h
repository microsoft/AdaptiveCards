#pragma once
#include "AdaptiveRequirement.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveRequirement : AdaptiveRequirementT<AdaptiveRequirement>
    {
        AdaptiveRequirement(hstring const& requirementName, hstring const& requirementversion);
        AdaptiveRequirement(std::pair<const std::string, ::AdaptiveCards::SemanticVersion> const& shared);

        property<hstring> Name;
        property<hstring> Version;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveRequirement : AdaptiveRequirementT<AdaptiveRequirement, implementation::AdaptiveRequirement>
    {
    };
}
