#include "pch.h"
#include "AdaptiveHostConfig.h"
#include "Util.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveCardConfig.h"
#include "AdaptiveChoiceSetInputConfig.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColumnConfig.h"
#include "AdaptiveColumnSetConfig.h"
#include "AdaptiveContainerConfig.h"
#include "AdaptiveDateInputConfig.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFontSizesConfig.h"
#include "AdaptiveImageConfig.h"
#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveNumberInputConfig.h"
#include "AdaptiveSeparationConfig.h"
#include "AdaptiveTextBlockConfig.h"
#include "AdaptiveTextInputConfig.h"
#include "AdaptiveTimeInputConfig.h"
#include "AdaptiveToggleInputConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveHostConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontFamily(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHostConfig.fontFamily, text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontFamily(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHostConfig.fontFamily = out;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontSizes(IAdaptiveFontSizesConfig** fontSizesConfig)
    {
        return MakeAndInitialize<AdaptiveFontSizesConfig>(fontSizesConfig, m_sharedHostConfig.fontSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontSizes(IAdaptiveFontSizesConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_SupportsInteractivity(boolean* supporsInteractivity)
    {
        *supporsInteractivity = m_sharedHostConfig.supportsInteractivity;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_SupportsInteractivity(boolean supportsInteractivity)
    {
        m_sharedHostConfig.supportsInteractivity = Boolify(supportsInteractivity);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveHostConfig::get_Colors(IAdaptiveColorsConfig** colorsConfig)
    {
        return MakeAndInitialize<AdaptiveColorsConfig>(colorsConfig, m_sharedHostConfig.colors);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveHostConfig::put_Colors(IAdaptiveColorsConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSizes(IAdaptiveImageSizesConfig** imageSizes)
    {
        return MakeAndInitialize<AdaptiveImageSizesConfig>(imageSizes, m_sharedHostConfig.imageSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSizes(IAdaptiveImageSizesConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_MaxActions(UINT32* maxActions)
    {
        *maxActions = m_sharedHostConfig.maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_MaxActions(UINT32 maxActions)
    {
        m_sharedHostConfig.maxActions = maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_StrongSeparation(IAdaptiveSeparationConfig** strongSeparationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(strongSeparationConfig, m_sharedHostConfig.strongSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_StrongSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_AdaptiveCard(IAdaptiveCardConfig** adaptiveCardConfig)
    {
        return MakeAndInitialize<AdaptiveCardConfig>(adaptiveCardConfig, m_sharedHostConfig.adaptiveCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_AdaptiveCard(IAdaptiveCardConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSet(IAdaptiveImageSetConfig** imageSetConfig)
    {
        return MakeAndInitialize<AdaptiveImageSetConfig>(imageSetConfig, m_sharedHostConfig.imageSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSet(IAdaptiveImageSetConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Image(IAdaptiveImageConfig** imageConfig)
    {
        return MakeAndInitialize<AdaptiveImageConfig>(imageConfig, m_sharedHostConfig.image);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Image(IAdaptiveImageConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FactSet(IAdaptiveFactSetConfig** factSetConfig)
    {
        return MakeAndInitialize<AdaptiveFactSetConfig>(factSetConfig, m_sharedHostConfig.factSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FactSet(IAdaptiveFactSetConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Column(IAdaptiveColumnConfig** columnConfig)
    {
        return MakeAndInitialize<AdaptiveColumnConfig>(columnConfig, m_sharedHostConfig.column);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Column(IAdaptiveColumnConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Container(IAdaptiveContainerConfig** containerConfig)
    {
        return MakeAndInitialize<AdaptiveContainerConfig>(containerConfig, m_sharedHostConfig.container);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Container(IAdaptiveContainerConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ColumnSet(IAdaptiveColumnSetConfig** columnSetConfig)
    {
        return MakeAndInitialize<AdaptiveColumnSetConfig>(columnSetConfig, m_sharedHostConfig.columnSet);

    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ColumnSet(IAdaptiveColumnSetConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_TextBlock(IAdaptiveTextBlockConfig** textBlockConfig)
    {
        return MakeAndInitialize<AdaptiveTextBlockConfig>(textBlockConfig, m_sharedHostConfig.textBlock);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_TextBlock(IAdaptiveTextBlockConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_DateInput(IAdaptiveDateInputConfig** dateInputConfig)
    {
        return MakeAndInitialize<AdaptiveDateInputConfig>(dateInputConfig, m_sharedHostConfig.dateInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_DateInput(IAdaptiveDateInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_TimeInput(IAdaptiveTimeInputConfig** timeInputConfig)
    {
        return MakeAndInitialize<AdaptiveTimeInputConfig>(timeInputConfig, m_sharedHostConfig.timeInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_TimeInput(IAdaptiveTimeInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_NumberInput(IAdaptiveNumberInputConfig** numberInputConfig)
    {
        return MakeAndInitialize<AdaptiveNumberInputConfig>(numberInputConfig, m_sharedHostConfig.numberInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_NumberInput(IAdaptiveNumberInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ToggleInput(IAdaptiveToggleInputConfig** toggleInputConfig)
    {
        return MakeAndInitialize<AdaptiveToggleInputConfig>(toggleInputConfig, m_sharedHostConfig.toggleInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ToggleInput(IAdaptiveToggleInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_TextInput(IAdaptiveTextInputConfig** textInputConfig)
    {
        return MakeAndInitialize<AdaptiveTextInputConfig>(textInputConfig, m_sharedHostConfig.textInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_TextInput(IAdaptiveTextInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ChoiceSetInput(IAdaptiveChoiceSetInputConfig** choiceSetConfig)
    {
        return MakeAndInitialize<AdaptiveChoiceSetInputConfig>(choiceSetConfig, m_sharedHostConfig.choiceSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ChoiceSetInput(IAdaptiveChoiceSetInputConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Actions(IAdaptiveActionsConfig** actionsConfig)
    {
        return MakeAndInitialize<AdaptiveActionsConfig>(actionsConfig, m_sharedHostConfig.actions);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Actions(IAdaptiveActionsConfig* )
    {
        return E_NOTIMPL;
    }
}}
