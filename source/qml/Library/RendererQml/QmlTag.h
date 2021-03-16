#pragma once

#include <vector>
#include <string>
#include <functional>

namespace RendererQml
{
    class QmlTag;
    using Customizer = std::function<void(QmlTag&)>;

    class QmlUtils
    {
    public:
        static std::string Join(const std::vector<std::pair<std::string, std::string>>& vectorPairs, const std::string& kv_separator, const std::string& item_separator);
    };

    class QmlTag
    {
    public:
        QmlTag(const std::string& element);
        QmlTag& AddImports(const std::string& import);
        QmlTag& Property(const std::string& name, const std::string& value);
		QmlTag& RemoveProperty(const std::string& name);
		QmlTag& AddFunctions(const std::string& function);
        void AddChild(const std::shared_ptr<QmlTag>& child);
        std::string ToString();
		const std::vector<std::shared_ptr<QmlTag>>& GetChildren();


        const std::string GetId() const;
		const std::string GetElement();
		const std::string GetProperty(const std::string& name);
		const std::vector<std::pair<std::string, std::string>>& GetProperties();
		void Transform(Customizer tagCustomization);
		const bool HasProperty(const std::string& name);

    private:
        std::string m_element;
		std::vector<std::string> m_functions;
        std::vector<std::string> m_imports;
        std::vector<std::pair<std::string, std::string>> m_properties;
        std::vector<std::shared_ptr<QmlTag>> m_children;
    };
}
