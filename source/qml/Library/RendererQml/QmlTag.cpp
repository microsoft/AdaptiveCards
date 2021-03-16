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

    QmlTag& QmlTag::Property(const std::string& name, const std::string& value)
    {
        auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [name](const auto property) {
            return property.first == name;
        });

        if (iterator != m_properties.end())
        {
            iterator->second = value;
            return *this;
        }
        m_properties.emplace_back(name, value);
        return *this;
    }

	QmlTag& QmlTag::RemoveProperty(const std::string& name)
	{
		auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [name](const auto property) {
			return property.first == name;
		});

		if (iterator != m_properties.end())
		{
			m_properties.erase(iterator);
			return *this;
		}
		return *this;
	}

	QmlTag& QmlTag::AddFunctions(const std::string& function)
	{
		m_functions.emplace_back(function);
		return *this;
	}

    const std::string QmlTag::GetId() const
    {
        auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [](const auto property) {
            return property.first == "id";
        });

        if (iterator != m_properties.end())
        {
            return iterator->second;
        }

        return std::string();
    }

	const std::string QmlTag::GetElement()
	{
		return m_element;
	}

	const std::string QmlTag::GetProperty(const std::string& name)
	{
		auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [name](const auto property) {
			return property.first == name;
		});

		if (iterator != m_properties.end())
		{
			return iterator->second;
		}
		return std::string();
	}

	const std::vector<std::pair<std::string, std::string>>& QmlTag::GetProperties()
	{
		return m_properties;
	}

	void QmlTag::Transform(Customizer tagCustomization)
	{
		if (tagCustomization)
		{
			tagCustomization(*this);
		}
		for (const auto& child : m_children)
		{
			child->Transform(tagCustomization);
		}
	}

	const bool QmlTag::HasProperty(const std::string& name)
	{
		auto iterator = std::find_if(m_properties.begin(), m_properties.end(), [name](const auto property) {
			return property.first == name;
		});

		if (iterator != m_properties.end())
		{
			return true;
		}
		return false;
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
            qmlString << import << "\n";
        }

        if (!m_element.empty())
        {
            qmlString << m_element << "{\n";
        }

        if (!m_properties.empty())
        {
            qmlString << QmlUtils::Join(m_properties, ":", "\n");
        }

		for (const auto function : m_functions)
		{
			qmlString << function << "\n";
		}

        if (!m_children.empty())
        {
            for (const auto& child : m_children)
            {
                qmlString << child->ToString();
            }

            qmlString << "}\n";
        }
        else
        {
            // No children, so just self-close the element.
            qmlString << "}\n";
        }

        return qmlString.str();
    }

	const std::vector<std::shared_ptr<QmlTag>>& QmlTag::GetChildren()
	{
		return m_children;
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
