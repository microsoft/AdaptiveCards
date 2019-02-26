#pragma once

#include "Enums.h"
#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveSharedNamespace
{
    class BackgroundImage
    {
    public:
        BackgroundImage() :
            m_mode(BackgroundImageMode::Stretch), m_hAlignment(HorizontalAlignment::Left), m_vAlignment(VerticalAlignment::Top)
        {
        }
        BackgroundImage(std::string const& url) : m_url(url) {}
        BackgroundImage(std::string const& url, BackgroundImageMode mode, HorizontalAlignment hAlignment, VerticalAlignment vAlignment) :
            m_url(url), m_mode(mode), m_hAlignment(hAlignment), m_vAlignment(vAlignment)
        {
        }

        std::string GetUrl() const;
        void SetUrl(const std::string& value);
        BackgroundImageMode GetMode() const;
        void SetMode(const BackgroundImageMode& value);
        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment& value);
        VerticalAlignment GetVerticalAlignment() const;
        void SetVerticalAlignment(const VerticalAlignment& value);

        Json::Value SerializeToJsonValue() const;

        static std::shared_ptr<BackgroundImage> Deserialize(const Json::Value& json);

    private:
        std::string m_url;
        BackgroundImageMode m_mode = BackgroundImageMode::Stretch;
        HorizontalAlignment m_hAlignment = HorizontalAlignment::Left;
        VerticalAlignment m_vAlignment = VerticalAlignment::Top;
    };
}
