// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

#include "ElementParserRegistration.h"
#include "ActionParserRegistration.h"
#include "AdaptiveCardParseWarning.h"

namespace AdaptiveSharedNamespace
{
    class BaseElement;
    class InternalId;
    class CollectionTypeElement;
    class ParseContext
    {
    public:
        ParseContext();
        ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration,
                     std::shared_ptr<ActionParserRegistration> actionRegistration);

        std::shared_ptr<ElementParserRegistration> elementParserRegistration;
        std::shared_ptr<ActionParserRegistration> actionParserRegistration;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
        // Push/PopElement are used during parsing to track the tree structure of a card.
        void PushElement(const std::string& idJsonProperty,
                         const AdaptiveSharedNamespace::InternalId& internalId,
                         const bool isFallback = false);
        void PopElement();

        // tells if it's possible to fallback to ancestor
        bool GetCanFallbackToAncestor() const { return m_canFallbackToAncestor; }
        void SetCanFallbackToAncestor(bool value) { m_canFallbackToAncestor = value; }

        void SetLanguage(const std::string& value);
        const std::string& GetLanguage() const;

        ContainerStyle GetParentalContainerStyle() const;
        void SetParentalContainerStyle(const ContainerStyle style);
        AdaptiveSharedNamespace::InternalId PaddingParentInternalId() const;
        void SaveContextForCollectionTypeElement(const CollectionTypeElement& current);
        void RestoreContextForCollectionTypeElement(const CollectionTypeElement& current);

        ContainerBleedDirection GetBleedDirection() const;
        void PushBleedDirection(const ContainerBleedDirection direction);
        void PopBleedDirection();

    private:
        const AdaptiveSharedNamespace::InternalId GetNearestFallbackId(const AdaptiveSharedNamespace::InternalId& skipId) const;
        // This enum is just a helper to keep track of the position of contents within the std::tuple used in
        // m_idStack below. We don't use enum class here because we don't want typed values for use in std::get
        enum TupleIndex : unsigned int
        {
            Id = 0U,
            InternalId,
            IsFallback
        };

        // m_elementIds keeps track of which elements we've seen during a parse. This is used to detect collisions on id
        // within an Adaptive Card json file. Specifically, we track which non-empty ids we've seen and correllate them
        // to the internal ID of the element for which it serves fallback (if any). We use unordered_multimap here as
        // duplicate entries are valid in some circumstances (i.e. where fallback content shares an ID with its parent)
        //
        //             map ID json property           ->             fallback ID
        std::unordered_multimap<std::string, AdaptiveSharedNamespace::InternalId> m_elementIds;

        // m_idStack is the stack we use during parse time to track the hierarchy of cards as they are encountered.
        // Any time we parse an element we push it on to the stack, parse its children (if any), then pop it off the
        // stack. When we pop off the stack, we perform id collision detection.
        //
        //                             (ID,  internal ID, isFallback)[]
        std::vector<std::tuple<std::string, AdaptiveSharedNamespace::InternalId, bool>> m_idStack;

        std::vector<ContainerStyle> m_parentalContainerStyles;
        std::vector<AdaptiveSharedNamespace::InternalId> m_parentalPadding;
        std::vector<ContainerBleedDirection> m_parentalBleedDirection;

        bool m_canFallbackToAncestor;
        std::string m_language;
    };
}
