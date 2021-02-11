#include "AdaptiveFallbackException.h"

namespace RendererQml
{

    AdaptiveFallbackException::AdaptiveFallbackException(const std::string& message) : m_message(message)
    {
    }

    const char* AdaptiveFallbackException::what() const throw()
    {
        return m_message.c_str();
    }

}
