#include "pch.h"
#include "ParseContext.h"
#include "AdaptiveCardParseException.h"

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

    unsigned int ParseContext::GetNearestFallbackId(const unsigned int skipId) const
    {
        // Walk stack looking for first element to be marked fallback, then return its internal ID. If none, return
        for (auto curElement = m_idStack.crbegin(); curElement != m_idStack.crend(); ++curElement)
        {
            if (std::get<TupleIndex::IsFallback>(*curElement)) // if element is fallback
            {
                const auto internalId = std::get<TupleIndex::InternalId>(*curElement);
                if (internalId != skipId)
                {
                    return internalId;
                }
            }
        }
        return ParseContext::InvalidFallbackId;
    }

    void ParseContext::PushElement(const std::tuple<std::string, unsigned int, bool>& ids)
    {
        m_idStack.push_back(ids);
    }

    void ParseContext::PopElement()
    {
        // about to pop an element off the stack. perform collision list maintenance and detection.
        const auto& idsToPop = m_idStack.back();
        const std::string& elementId{std::get<TupleIndex::Id>(idsToPop)};
        const unsigned int elementInternalId{std::get<TupleIndex::InternalId>(idsToPop)};
        const bool isFallback{std::get<TupleIndex::IsFallback>(idsToPop)};

        if (!elementId.empty())
        {
            bool haveCollision = false;
            const unsigned int nearestFallbackId = GetNearestFallbackId(elementInternalId);

            // Walk through the list of elements we've seen with this ID
            for (auto currentEntry = m_elementIds.find(elementId); currentEntry != m_elementIds.end(); ++currentEntry)
            {
                const unsigned int entryInternalId = currentEntry->second.first;
                const unsigned int entryFallbackId = currentEntry->second.second;

                // If the element we're about to pop is the fallback parent for this entry, then there's no collision
                // (fallback content is allowed to collide with the fallback parent)
                if (entryFallbackId == elementInternalId)
                {
                    haveCollision = false;
                    break;
                }

                // The inverse of the above -- if this element's fallback parent (if available) is the entry we're
                // looking at, there's no collision.
                try
                {
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
                m_elementIds.emplace(std::make_pair(elementId, std::make_pair(elementInternalId, nearestFallbackId)));
            }
        }

        m_idStack.pop_back();
    }
}
