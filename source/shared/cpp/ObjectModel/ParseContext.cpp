// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseContext.h"
#include "AdaptiveCardParseException.h"
#include "BaseElement.h"
#include "CollectionTypeElement.h"

namespace AdaptiveSharedNamespace
{
    ParseContext::ParseContext() :
        elementParserRegistration{std::make_shared<ElementParserRegistration>()},
        actionParserRegistration{std::make_shared<ActionParserRegistration>()}, warnings{}, m_elementIds{}, m_idStack{},
        m_parentalContainerStyles{}, m_parentalPadding{}, m_parentalBleedDirection{}, m_canFallbackToAncestor(false)
    {
    }

    ParseContext::ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration, std::shared_ptr<ActionParserRegistration> actionRegistration) :
        warnings{}, m_elementIds{}, m_idStack{}, m_parentalContainerStyles{}, m_parentalPadding{}, m_parentalBleedDirection{},
        m_canFallbackToAncestor(false)
    {
        elementParserRegistration = (elementRegistration) ? elementRegistration : std::make_shared<ElementParserRegistration>();
        actionParserRegistration = (actionRegistration) ? actionRegistration : std::make_shared<ActionParserRegistration>();
    }

    // Detecting ID collisions
    //
    // A word on nomenclature: There are two identifiers in discussion below. "ID" refers to the value of the "id"
    // property in our JSON schema (e.g. '{ "type": "TextBlock", "id": "SomeUniqueId" }').
    //                                                            ^^^^  ^^^^^^^^^^^^^^
    // "Internal ID" refers to an identifier we use internally to uniquely identify a card element while parsing. This
    // ID exists for all body and action elements regardless of whether an ID was specified in the provided JSON. This
    // internal ID is represented by the `InternalId` class (see BaseElement.h/cpp).
    //
    // In the past, ID collision detection was pretty simple. We'd simply keep track of what IDs had been seen and then
    // throw an exception if a duplicate was encountered. Unfortunately, with fallback content, the story is quite a bit
    // more complicated.
    //
    // Consider a card that utilizes a custom input element and a submit button for inputting telephone numbers. The
    // user is presented with the card, invokes the telephone input functionality providing a phone number, and then
    // clicks a submit button. The supplied number is in SubmitAction's data blob under the custom input element's ID.
    // On platforms that support this fancy input method, this story is enough.
    //
    // However, a card author may desire a reasonable experience on rendering platforms that *don't* support the custom
    // input element. So the author may supply fallback something like this:
    //     {
    //         "type": "FancyTelephoneInput",
    //         "id":   "telephoneNumber",
    //         "fallback": {
    //             "type": "Input.Text",
    //             "placeholder": "Enter telephone number",
    //             "id": "telephoneNumber"
    //         }
    //     }
    //
    // Note that the supplied ID is the same in fallback content. This solves a couple of problems for the author --
    // graceful fallback for input and, thanks to allowing a duplicate ID, easy backend parsing of the submit data. The
    // author doesn't have to care about which input method was used to collect the phone number (the author may, of
    // course, need to do some sanitization on the supplied number, but that's out of scope for this discussion).
    //
    // This does present a new problem for us, though. What if we see a card with elements in the body like this:
    //     {
    //         "type": "FancyInputElement",
    //         "id":   "ourFancyElement",
    //         "fallback": {
    //             "type": "Input.Text",
    //             "id":   "uhoh"             <--- totally fine
    //         }
    //     },
    //     {
    //         "type": "Input.Text",
    //         "id":   "uhoh"                 <--- not good
    //     }
    //
    // As noted above, we shouldn't allow IDs to collide in this manner. More generally, a duplicate ID should only be
    // allowed between fallback content and the element for which it is fallback (even in nested scenarios). In order to
    // validate this, we need to track parent/child relationships at parse time and we need to keep track of IDs we've
    // seen.
    //
    // In general, we visit elements in a card as a depth-first traversal of the tree. For each element in the "body"
    // and "actions" blocks we determine its type, retrieve the correct parser for it, and then call the parser's
    // Deserialize method with our ParseContext and the JSON of the object. Elements that have children (e.g. Container)
    // are responsible for populating their child elements through the same mechanism. To track our state, we push state
    // before we visit an element, and the pop the state as we're leaving it. We perform our validation as we pop an
    // element off the stack. To facilitate this, we wrap parsers such that we can push/pop around the deserialize
    // calls, obviating the need for parser implementors to remember to push/pop themselves (see
    // ActionParserRegistration::GetParser(), ElementParserRegistration::GetParser, and the wrapper classes they
    // consume). Note that we will also push/pop when parsing an element's fallback content.
    //
    // So how *do* we detect collisions? When we push an element we're visiting, we supply three pieces of information
    // for reference: the ID property, the element's internal ID, and whether we're parsing fallback content or not.
    // This information gets pushed on to our stack. The element is parsed, and then we pop. When popping (see
    // ParseContext::PopElement()), if the element we're currently looking at has an ID, we look to see if we're in
    // fallback content (anywhere on the stack). If we aren't, we check to see if we've seen this ID before. If we
    // haven't, we add it to the list with no fallback internal ID. If we have, we throw an exception because we've
    // encountered a duplicate. However, if we *are* parsing fallback content, we look through the list of times we've
    // seen this ID before. If never, we're cool -- add it to the list with the internal ID of the parent element. If
    // we've seen it before, we check the parent/child relationship. If this ID was previously seen on the fallback
    // parent (check the fallback internal ID), that's okay. Just add it to the list of times we've seen the ID. If the
    // ID was previously seen outside of the fallback parent, this is a collision -> throw an exception.
    //
    // ================================================================================
    // Putting it all together (assume that this content is in the body):
    //
    // {
    //     "type": "TextBlock",
    //     "id":   "standardTextBlock",
    //     "text": "This is some text."
    // {
    //     "type": "FancyInputElement",
    //     "id":   "duplicate",
    //     "fallback": {
    //         "type": "Input.Text",
    //         "id":   "duplicate"
    //     },
    //     "children": [ {
    //         "type": "TextBlock",
    //         "id":   "FancyInputElementTextBlock",
    //         "text": "FancyInputElement's TextBlock child"
    //     } ]
    // },
    // {
    //     "type": "Input.Text",
    //     "id":   "duplicate"
    // }
    //
    // stack: empty
    // ID list: empty
    //
    // Push on stack: [id: "standardTextBlock", internalId: 1, isFallback: false] <-- TextBlock
    // Pop stack: No collision detected in ID list. Add [id: "standardTextBlock", internalId: Invalid] to ID list
    // Push on stack: [id: "duplicate", internalId: 2, isFallback: false] <-- FancyInputElement
    // Push on stack: [id: "duplicate", internalId: 2, isFallback: true]  <-- FancyInputElement (about to parse fallback
    //     content)
    // Push on stack: [id: "duplicate", internalId: 3, isFallback: false] <-- FancyInputElement's fallback Input.Text
    // Pop stack: No collision detected in ID list. Add to ID list: [id: "duplicate", internalId: 2]
    // Pop stack: "duplicate" already exists in ID list. However, its internalId matches the current element, so this
    //     isn't a true collision. Add to ID list: [id: "duplicate", internalID: Invalid]
    // Push stack: [id: "TextBlock", internalId: 4, isFallback: false] <-- FancyInputElement's child TextBlock
    // Pop stack: No collision detected in ID list. Add to ID list: [id: "FancyInputElementTextBlock" internalId:
    //     Invalid]
    // Push stack: [id: "duplicate", internalId: 5, isFallback: false] <-- Input.Text
    // Pop stack: Collision detected in ID list. Current element isn't a fallback child, so throw an exception.
    // ================================================================================

    // Push the provided state on to our ID stack (see comment above)
    void ParseContext::PushElement(const std::string& idJsonProperty,
                                   const AdaptiveSharedNamespace::InternalId& internalId,
                                   const bool isFallback /*=false*/)
    {
        if (internalId == InternalId::Invalid)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Attemping to push an element on to the stack with an invalid ID");
        }

        m_idStack.push_back({idJsonProperty, internalId, isFallback});
    }

    // Pop the last id off our stack and perform validation (see comment above)
    void ParseContext::PopElement()
    {
        // about to pop an element off the stack. perform collision list maintenance and detection.
        const auto& idsToPop = m_idStack.back();
        const std::string& elementId{std::get<TupleIndex::Id>(idsToPop)};
        const auto& elementInternalId{std::get<TupleIndex::InternalId>(idsToPop)};
        const bool isFallback{std::get<TupleIndex::IsFallback>(idsToPop)};

        if (!elementId.empty())
        {
            bool haveCollision = false;
            const auto& nearestFallbackId = GetNearestFallbackId(elementInternalId);

            // Walk through the list of elements we've seen with this ID
            for (auto currentEntry = m_elementIds.find(elementId); currentEntry != m_elementIds.end(); ++currentEntry)
            {
                const AdaptiveSharedNamespace::InternalId& entryFallbackId = currentEntry->second;

                // If the element we're about to pop is the fallback parent for this entry, then there's no collision
                // (fallback content is allowed to have the same ID as its parent)
                if (entryFallbackId == elementInternalId)
                {
                    haveCollision = false;
                    break;
                }

                // The inverse of the above -- if this element's fallback parent is the entry we're looking at, there's
                // no collision.
                try
                {
                    // -1 is the last item on the stack (the one we're about to pop)
                    // -2 is the parent of the last item on the stack
                    const auto& previousInStack = m_idStack.at(m_idStack.size() - 2);
                    if (std::get<TupleIndex::InternalId>(previousInStack) == entryFallbackId)
                    {
                        // we're looking at a fallback entry for our parent
                        break;
                    }
                }
                catch (const std::out_of_range&)
                {
                    // we're looking at a toplevel element
                }

                // if the element we're inspecting is fallback content, continue on to the next entry
                if (isFallback)
                {
                    continue;
                }

                // at this point, we may or may not have a collision depending on additional entries.
                haveCollision = true;
            }

            if (haveCollision)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::IdCollision, "Collision detected for id '" + elementId + "'");
            }

            // no need to add an entry for this element if it's fallback (we'll add one when we parse it for non-fallback)
            if (!isFallback)
            {
                m_elementIds.emplace(std::make_pair(elementId, nearestFallbackId));
            }
        }

        m_idStack.pop_back();
    }

    // Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to skip), then
    // return its internal ID. If none, return an invalid ID. (see comment above)
    const AdaptiveSharedNamespace::InternalId ParseContext::GetNearestFallbackId(const AdaptiveSharedNamespace::InternalId& skipId) const
    {
        for (auto curElement = m_idStack.crbegin(); curElement != m_idStack.crend(); ++curElement)
        {
            if (std::get<TupleIndex::IsFallback>(*curElement)) // if element is fallback
            {
                // retrieve the internal ID
                const AdaptiveSharedNamespace::InternalId& internalId = std::get<TupleIndex::InternalId>(*curElement);
                if (internalId != skipId)
                {
                    return internalId;
                }
            }
        }
        AdaptiveSharedNamespace::InternalId invalidId;
        return invalidId;
    }

    ContainerStyle ParseContext::GetParentalContainerStyle() const
    {
        return m_parentalContainerStyles.size() ? m_parentalContainerStyles.back() : ContainerStyle::Default;
    }

    void ParseContext::SetParentalContainerStyle(const ContainerStyle style)
    {
        if (style != ContainerStyle::None)
        {
            m_parentalContainerStyles.push_back(style);
        }
    }

    AdaptiveSharedNamespace::InternalId ParseContext::PaddingParentInternalId(void) const
    {
        if (m_parentalPadding.size())
        {
            return m_parentalPadding.back();
        }
        AdaptiveSharedNamespace::InternalId invalidId;
        return invalidId;
    }

    void ParseContext::SaveContextForCollectionTypeElement(const CollectionTypeElement& current)
    {
        // save current style value
        if (current.GetStyle() != ContainerStyle::None)
        {
            m_parentalContainerStyles.push_back(current.GetStyle());
        }

        // save id of the current if the current has the padding
        // it will be the new parent id for children, when parsing is continued dfs
        // if current container gets padding, it resets container bleed state to not restricted
        if (current.GetPadding())
        {
            PushBleedDirection(ContainerBleedDirection::BleedAll);
            m_parentalPadding.push_back(current.GetInternalId());
        }
    }

    void ParseContext::RestoreContextForCollectionTypeElement(const CollectionTypeElement& current)
    {
        // pop container style
        if (m_parentalContainerStyles.size() && current.GetStyle() != ContainerStyle::None)
        {
            m_parentalContainerStyles.pop_back();
        }

        // restore to previous parental id for further parsing of remaining items
        if (current.GetPadding())
        {
            m_parentalPadding.pop_back();
            PopBleedDirection();
        }
    }

    ContainerBleedDirection ParseContext::GetBleedDirection() const
    {
        if (!m_parentalBleedDirection.empty())
        {
            return m_parentalBleedDirection.back();
        }
        else
        {
            return ContainerBleedDirection::BleedAll;
        }
    }

    void ParseContext::PushBleedDirection(const ContainerBleedDirection direction)
    {
        m_parentalBleedDirection.push_back(direction);
    }

    void ParseContext::PopBleedDirection() { m_parentalBleedDirection.pop_back(); }

    void ParseContext::SetLanguage(const std::string& value) { m_language = value; }

    const std::string& ParseContext::GetLanguage() const { return m_language; }
}
