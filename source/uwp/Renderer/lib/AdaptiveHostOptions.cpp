#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include "AdaptiveActionOptions.h"
#include "AdaptiveCardOptions.h"
#include "AdaptiveChoiceSetInputOptions.h"
#include "AdaptiveColorOptions.h"
#include "AdaptiveColumnOptions.h"
#include "AdaptiveColumnSetOptions.h"
#include "AdaptiveContainerOptions.h"
#include "AdaptiveDateInputOptions.h"
#include "AdaptiveFactSetOptions.h"
#include "AdaptiveFontSizeOptions.h"
#include "AdaptiveImageOptions.h"
#include "AdaptiveImageSetOptions.h"
#include "AdaptiveImageSizeOptions.h"
#include "AdaptiveNumberInputOptions.h"
#include "AdaptiveSeparationOptions.h"
#include "AdaptiveTextBlockOptions.h"
#include "AdaptiveTextInputOptions.h"
#include "AdaptiveTimeInputOptions.h"
#include "AdaptiveToggleInputOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveHostOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_FontFamily(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHostOptions.fontFamily, text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_FontFamily(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHostOptions.fontFamily = out;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_FontSizes(IAdaptiveFontSizeOptions** fontSizeOptions)
    {
        return MakeAndInitialize<AdaptiveFontSizeOptions>(fontSizeOptions, m_sharedHostOptions.fontSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_FontSizes(IAdaptiveFontSizeOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_SupportsInteractivity(boolean* supporsInteractivity)
    {
        *supporsInteractivity = m_sharedHostOptions.supportsInteractivity;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_SupportsInteractivity(boolean supportsInteractivity)
    {
        m_sharedHostOptions.supportsInteractivity = Boolify(supportsInteractivity);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveHostOptions::get_Colors(IAdaptiveColorOptions** colorOptions)
    {
        return MakeAndInitialize<AdaptiveColorOptions>(colorOptions, m_sharedHostOptions.colors);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveHostOptions::put_Colors(IAdaptiveColorOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_ImageSizes(IAdaptiveImageSizeOptions** imageSizes)
    {
        return MakeAndInitialize<AdaptiveImageSizeOptions>(imageSizes, m_sharedHostOptions.imageSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_ImageSizes(IAdaptiveImageSizeOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_MaxActions(UINT32* maxActions)
    {
        *maxActions = m_sharedHostOptions.maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_MaxActions(UINT32 maxActions)
    {
        m_sharedHostOptions.maxActions = maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_StrongSeparation(IAdaptiveSeparationOptions** strongSeparationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(strongSeparationOptions, m_sharedHostOptions.strongSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_StrongSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_AdaptiveCard(IAdaptiveCardOptions** adaptiveCardOptions)
    {
        return MakeAndInitialize<AdaptiveCardOptions>(adaptiveCardOptions, m_sharedHostOptions.adaptiveCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_AdaptiveCard(IAdaptiveCardOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_ImageSet(IAdaptiveImageSetOptions** imageSetOptions)
    {
        return MakeAndInitialize<AdaptiveImageSetOptions>(imageSetOptions, m_sharedHostOptions.imageSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_ImageSet(IAdaptiveImageSetOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_Image(IAdaptiveImageOptions** imageOptions)
    {
        return MakeAndInitialize<AdaptiveImageOptions>(imageOptions, m_sharedHostOptions.image);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_Image(IAdaptiveImageOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_FactSet(IAdaptiveFactSetOptions** factSetOptions)
    {
        return MakeAndInitialize<AdaptiveFactSetOptions>(factSetOptions, m_sharedHostOptions.factSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_FactSet(IAdaptiveFactSetOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_Column(IAdaptiveColumnOptions** columnOptions)
    {
        return MakeAndInitialize<AdaptiveColumnOptions>(columnOptions, m_sharedHostOptions.column);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_Column(IAdaptiveColumnOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_Container(IAdaptiveContainerOptions** containerOptions)
    {
        return MakeAndInitialize<AdaptiveContainerOptions>(containerOptions, m_sharedHostOptions.container);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_Container(IAdaptiveContainerOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_ColumnSet(IAdaptiveColumnSetOptions** columnSetOptions)
    {
        return MakeAndInitialize<AdaptiveColumnSetOptions>(columnSetOptions, m_sharedHostOptions.columnSet);

    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_ColumnSet(IAdaptiveColumnSetOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_TextBlock(IAdaptiveTextBlockOptions** textBlockOptions)
    {
        return MakeAndInitialize<AdaptiveTextBlockOptions>(textBlockOptions, m_sharedHostOptions.textBlock);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_TextBlock(IAdaptiveTextBlockOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_DateInput(IAdaptiveDateInputOptions** dateInputOptions)
    {
        return MakeAndInitialize<AdaptiveDateInputOptions>(dateInputOptions, m_sharedHostOptions.dateInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_DateInput(IAdaptiveDateInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_TimeInput(IAdaptiveTimeInputOptions** timeInputOptions)
    {
        return MakeAndInitialize<AdaptiveTimeInputOptions>(timeInputOptions, m_sharedHostOptions.timeInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_TimeInput(IAdaptiveTimeInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_NumberInput(IAdaptiveNumberInputOptions** numberInputOptions)
    {
        return MakeAndInitialize<AdaptiveNumberInputOptions>(numberInputOptions, m_sharedHostOptions.numberInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_NumberInput(IAdaptiveNumberInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_ToggleInput(IAdaptiveToggleInputOptions** toggleInputOptions)
    {
        return MakeAndInitialize<AdaptiveToggleInputOptions>(toggleInputOptions, m_sharedHostOptions.toggleInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_ToggleInput(IAdaptiveToggleInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_TextInput(IAdaptiveTextInputOptions** textInputOptions)
    {
        return MakeAndInitialize<AdaptiveTextInputOptions>(textInputOptions, m_sharedHostOptions.textInput);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_TextInput(IAdaptiveTextInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_ChoiceSetInput(IAdaptiveChoiceSetInputOptions** choiceSetOptions)
    {
        return MakeAndInitialize<AdaptiveChoiceSetInputOptions>(choiceSetOptions, m_sharedHostOptions.choiceSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_ChoiceSetInput(IAdaptiveChoiceSetInputOptions* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::get_Actions(IAdaptiveActionOptions** actionOptions)
    {
        return MakeAndInitialize<AdaptiveActionOptions>(actionOptions, m_sharedHostOptions.actions);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostOptions::put_Actions(IAdaptiveActionOptions* )
    {
        return E_NOTIMPL;
    }
}}
