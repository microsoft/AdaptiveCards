// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFeatureRegistration.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    AdaptiveFeatureRegistration::AdaptiveFeatureRegistration() {}

    HRESULT AdaptiveFeatureRegistration::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<FeatureRegistration> sharedParserRegistration = std::make_shared<FeatureRegistration>();
        return RuntimeClassInitialize(sharedParserRegistration);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFeatureRegistration::RuntimeClassInitialize(std::shared_ptr<AdaptiveSharedNamespace::FeatureRegistration> sharedParserRegistration) noexcept
    try
    {
        m_sharedFeatureRegistration = sharedParserRegistration;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveFeatureRegistration::Set(_In_ HSTRING name, _In_ HSTRING version) noexcept
    try
    {
        m_sharedFeatureRegistration->AddFeature(HStringToUTF8(name), HStringToUTF8(version));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveFeatureRegistration::Get(_In_ HSTRING name, _Outptr_ HSTRING* version) noexcept
    try
    {
        *version = nullptr;
        const std::string featureVersion = m_sharedFeatureRegistration->GetFeatureVersion(HStringToUTF8(name));

        return UTF8ToHString(featureVersion, version);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFeatureRegistration::Remove(_In_ HSTRING name) noexcept
    try
    {
        m_sharedFeatureRegistration->RemoveFeature(HStringToUTF8(name));

        return S_OK;
    }
    CATCH_RETURN;

    std::shared_ptr<FeatureRegistration> AdaptiveFeatureRegistration::GetSharedFeatureRegistration()
    {
        return m_sharedFeatureRegistration;
    }
}
