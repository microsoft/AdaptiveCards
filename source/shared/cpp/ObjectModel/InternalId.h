// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveCards
{
// Used to uniquely identify a single BaseElement-derived object through the course of deserializing. For more
// details, refer to the giant comment on ID collision detection in ParseContext.cpp.
class InternalId
{
public:
    InternalId();

    static InternalId Next();
    static InternalId Current();
    static constexpr unsigned int Invalid = 0;

    unsigned int Hash() const
    {
        return m_internalId;
    }

    bool operator==(const unsigned int other) const
    {
        return m_internalId == other;
    }
    bool operator!=(const unsigned int other) const
    {
        return m_internalId != other;
    }
    bool operator==(const InternalId& other) const
    {
        return m_internalId == other.m_internalId;
    }
    bool operator!=(const InternalId& other) const
    {
        return m_internalId != other.m_internalId;
    }

private:
    static unsigned int s_currentInternalId;
    InternalId(const unsigned int id);
    unsigned int m_internalId;
};

struct InternalIdKeyHash
{
    std::size_t operator()(const InternalId& internalId) const
    {
        return internalId.Hash();
    }
};
} // namespace AdaptiveCards
