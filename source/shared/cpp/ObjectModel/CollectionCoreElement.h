// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class CollectionCoreElement : public BaseCardElement
{
public:
    CollectionCoreElement(const CollectionCoreElement&) = default;
    CollectionCoreElement(CollectionCoreElement&&) = default;
    CollectionCoreElement& operator=(const CollectionCoreElement&) = default;
    CollectionCoreElement& operator=(CollectionCoreElement&&) = default;
    virtual ~CollectionCoreElement() = default;
    CollectionCoreElement(CardElementType type);

    template <typename T>
    void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo, const std::vector<std::shared_ptr<T>>& elements);

    virtual void DeserializeChildren(AdaptiveCards::ParseContext& context, const Json::Value& value) = 0;

    template <typename T>
    static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& value);
};

template <typename T>
std::shared_ptr<T> CollectionCoreElement::Deserialize(ParseContext& context, const Json::Value& value)
{
    auto collection = BaseCardElement::Deserialize<T>(context, value);

    bool canFallbackToAncestor = context.GetCanFallbackToAncestor();
    context.SetCanFallbackToAncestor(canFallbackToAncestor || (collection->GetFallbackType() != FallbackType::None));
    collection->SetCanFallbackToAncestor(canFallbackToAncestor);

    // Parse Items
    collection->DeserializeChildren(context, value);

    context.SetCanFallbackToAncestor(canFallbackToAncestor);

    return collection;
}

template <typename T>
void CollectionCoreElement::GetResourceInformation(
    std::vector<RemoteResourceInformation>& resourceInfo, const std::vector<std::shared_ptr<T>>& elements)
{
    for (const auto& elem : elements)
    {
        elem->GetResourceInformation(resourceInfo);
    }
}
} // namespace AdaptiveCards
