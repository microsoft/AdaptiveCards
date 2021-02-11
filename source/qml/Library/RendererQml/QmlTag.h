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
        QmlTag(const std::string& element, bool allowSelfClose = true);
        QmlTag& AddImports(const std::string& import);
        QmlTag& Property(const std::string& name, const std::string& value);
        void AddChild(const std::shared_ptr<QmlTag>& child);
        std::string ToString();

    private:
        bool m_allowSelfClose;
        std::string m_element;
        std::vector<std::string> m_imports;
        std::vector<std::pair<std::string, std::string>> m_properties;
        std::vector<std::shared_ptr<QmlTag>> m_children;
    };
}
