// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TableColumnDefinition.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("3ED8BE31-8D92-461B-8E8F-2C6C0F78E2ED") AdaptiveTableColumnDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableColumnDefinition,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveTableColumnDefinition);

    public:
        AdaptiveTableColumnDefinition();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableColumnDefinition>& sharedTableColumnDefinition);

        // IAdaptiveTableColumnDefinition
        IFACEMETHODIMP get_VerticalCellContentAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalCellContentAlignment) override;
        IFACEMETHODIMP put_VerticalCellContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalCellContentAlignment) override;

        IFACEMETHODIMP get_HorizontalCellContentAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalCellContentAlignment) override;
        IFACEMETHODIMP put_HorizontalCellContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalCellContentAlignment) override;

        IFACEMETHODIMP get_Width(_Outptr_ ABI::Windows::Foundation::IReference<UINT32>** width) override;
        IFACEMETHODIMP put_Width(_In_ ABI::Windows::Foundation::IReference<UINT32>* width) override;

        IFACEMETHODIMP get_PixelWidth(_Outptr_ ABI::Windows::Foundation::IReference<UINT32>** pixelWidth) override;
        IFACEMETHODIMP put_PixelWidth(_In_ ABI::Windows::Foundation::IReference<UINT32>* pixelWidth) override;

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::TableColumnDefinition>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>> m_verticalCellContentAlignment;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>> m_horizontalCellContentAlignment;

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<UINT32>> m_width;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<UINT32>> m_pixelWidth;
    };

    ActivatableClass(AdaptiveTableColumnDefinition);
}
