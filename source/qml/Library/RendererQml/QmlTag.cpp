#include "pch.h"

#include "QmlTag.h"

namespace RendererQml
{
    QmlTag::QmlTag(const std::string& element) :
        m_element(element)
    {
    }

    QmlTag& QmlTag::AddImports(const std::string& import)
    {
        m_imports.emplace_back(import);
        return *this;
    }

    QmlTag& QmlTag::Property(const std::string& name, const std::string& value, const bool stringValue)
    {
        auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [name](const auto property) {
            return property.first == name;
        });

        if (iterator != m_properties.end())
        {
            iterator->second = stringValue ? Formatter() << "'" << value << "'" : value;
            return *this;
        }
        m_properties.emplace_back(name, stringValue ? Formatter() << "'" << value << "'" : value);
        return *this;
    }

    void QmlTag::AddChild(const std::shared_ptr<QmlTag>& child)
    {
        m_children.emplace_back(child);
    }

    std::string QmlTag::ToString()
    {
        std::ostringstream qmlString;

        for (const auto import : m_imports)
        {
            qmlString << import << ";";
        }

        if (!m_element.empty())
        {
            qmlString << m_element << "{";
        }

        if (!m_properties.empty())
        {
            qmlString << QmlUtils::Join(m_properties, ":", ";");
        }

        if (!m_children.empty())
        {
            for (const auto& child : m_children)
            {
                qmlString << child->ToString();
            }

            qmlString << "}";
        }
        else
        {
            // No children, so just self-close the element.
            qmlString << "}";
        }

        return qmlString.str();
    }

    std::string QmlUtils::Join(const std::vector<std::pair<std::string, std::string>>& vectorPairs, const std::string& kvSeparator, const std::string& itemSeparator)
    {
        std::ostringstream os;

        for (const auto pair : vectorPairs)
        {
            os << pair.first << kvSeparator << pair.second << itemSeparator;
        }
        
        return os.str();
    }
}
