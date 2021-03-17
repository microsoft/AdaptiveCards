// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRefresh.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRefresh::RuntimeClassInitialize() noexcept
    {
        std::shared_ptr<AdaptiveSharedNamespace::Refresh> refresh = std::make_shared<AdaptiveSharedNamespace::Refresh>();
        return RuntimeClassInitialize(refresh);
    }

    HRESULT AdaptiveRefresh::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Refresh>& sharedRefresh)
    {
        RETURN_IF_FAILED(GenerateActionProjection(sharedRefresh->GetAction(), &m_action));

        m_userIds = Microsoft::WRL::Make<Vector<HSTRING>>();
        for (auto& sharedUserId : sharedRefresh->GetUserIds())
        {
            HString userId;
            RETURN_IF_FAILED(UTF8ToHString(sharedUserId, userId.GetAddressOf()));
            RETURN_IF_FAILED(m_userIds->Append(userId.Get()));
        }

        return S_OK;
    }

    HRESULT AdaptiveRefresh::get_Action(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action)
    {
        return m_action.CopyTo(action);
    }

    HRESULT AdaptiveRefresh::put_Action(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action)
    {
        m_action = action;
        return S_OK;
    }

    HRESULT AdaptiveRefresh::get_UserIds(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING>** userIds)
    {
        return m_userIds.CopyTo(userIds);
    }

    HRESULT AdaptiveRefresh::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Refresh>& sharedModel)
    {
        std::shared_ptr<AdaptiveSharedNamespace::Refresh> refresh = std::make_shared<AdaptiveSharedNamespace::Refresh>();

        if (m_action != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_action.Get(), sharedAction));
            refresh->SetAction(std::move(sharedAction));
        }

        ComPtr<IIterable<HSTRING>> userIdIterable;
        RETURN_IF_FAILED(m_userIds.As(&userIdIterable));

        ComPtr<IIterator<HSTRING>> userIdIterator;
        if (SUCCEEDED(userIdIterable->First(&userIdIterator)))
        {
            boolean hasCurrent = false;
            HRESULT hr = userIdIterator->get_HasCurrent(&hasCurrent);
            while (SUCCEEDED(hr) && hasCurrent)
            {
                HString userId;
                RETURN_IF_FAILED(userIdIterator->get_Current(userId.GetAddressOf()));

                refresh->GetUserIds().push_back(HStringToUTF8(userId.Get()));
                hr = userIdIterator->MoveNext(&hasCurrent);
            }
        }

        sharedModel = std::move(refresh);
        return S_OK;
    }}
