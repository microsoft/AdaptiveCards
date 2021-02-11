#pragma once

#include "pch.h"

namespace RendererQml
{

    class AdaptiveFallbackException : public std::exception
    {
    public:
        AdaptiveFallbackException(const std::string& message);

        const char* what() const throw ();

    private:
        const std::string m_message;
    };

}
