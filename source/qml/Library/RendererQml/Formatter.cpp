#include "pch.h"

#include "Formatter.h"


namespace RendererQml
{

    Formatter::Formatter()
    {
    }

    std::string Formatter::Str() const
    {
        return m_stream.str();
    }

    Formatter::operator std::string() const
    {
        return m_stream.str();
    }

    std::string Formatter::operator>>(ConvertToString)
    {
        return m_stream.str();
    }

}
