#include "pch.h"
#include "ParseContext.h"
#include "AdaptiveCardParseException.h"
#include "BaseElement.h"

namespace AdaptiveSharedNamespace
{
    ParseContext::ParseContext() :
        elementParserRegistration{std::make_shared<ElementParserRegistration>()},
        actionParserRegistration{std::make_shared<ActionParserRegistration>()}, warnings{}, m_idStack{}, m_elementIds{}
    {
    }

    ParseContext::ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration, std::shared_ptr<ActionParserRegistration> actionRegistration) :
        warnings{}, m_idStack{}, m_elementIds{}
    {
        elementParserRegistration = (elementRegistration) ? elementRegistration : std::make_shared<ElementParserRegistration>();
        actionParserRegistration = (actionRegistration) ? actionRegistration : std::make_shared<ActionParserRegistration>();
    }

    const AdaptiveSharedNamespace::InternalId ParseContext::GetNearestFallbackId(const AdaptiveSharedNamespace::InternalId& skipId) const
    {
        // Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to skip), then
        // return its internal ID. If none, return an invalid ID.
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
        return std::move(invalidId);
    }

    // Push the provided state on to our ID stack
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

    // Pop the last id off our stack and perform validation
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
}
