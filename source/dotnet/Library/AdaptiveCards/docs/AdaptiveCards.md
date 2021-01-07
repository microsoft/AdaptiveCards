<a name='assembly'></a>
# AdaptiveCards

## Contents

- [ActionsConfig](#T-AdaptiveCards-Rendering-ActionsConfig 'AdaptiveCards.Rendering.ActionsConfig')
  - [ActionAlignment](#P-AdaptiveCards-Rendering-ActionsConfig-ActionAlignment 'AdaptiveCards.Rendering.ActionsConfig.ActionAlignment')
  - [ActionsOrientation](#P-AdaptiveCards-Rendering-ActionsConfig-ActionsOrientation 'AdaptiveCards.Rendering.ActionsConfig.ActionsOrientation')
  - [ButtonSpacing](#P-AdaptiveCards-Rendering-ActionsConfig-ButtonSpacing 'AdaptiveCards.Rendering.ActionsConfig.ButtonSpacing')
  - [IconPlacement](#P-AdaptiveCards-Rendering-ActionsConfig-IconPlacement 'AdaptiveCards.Rendering.ActionsConfig.IconPlacement')
  - [IconSize](#P-AdaptiveCards-Rendering-ActionsConfig-IconSize 'AdaptiveCards.Rendering.ActionsConfig.IconSize')
  - [MaxActions](#P-AdaptiveCards-Rendering-ActionsConfig-MaxActions 'AdaptiveCards.Rendering.ActionsConfig.MaxActions')
  - [ShowCard](#P-AdaptiveCards-Rendering-ActionsConfig-ShowCard 'AdaptiveCards.Rendering.ActionsConfig.ShowCard')
  - [Spacing](#P-AdaptiveCards-Rendering-ActionsConfig-Spacing 'AdaptiveCards.Rendering.ActionsConfig.Spacing')
- [ActionsOrientation](#T-AdaptiveCards-Rendering-ActionsOrientation 'AdaptiveCards.Rendering.ActionsOrientation')
  - [Horizontal](#F-AdaptiveCards-Rendering-ActionsOrientation-Horizontal 'AdaptiveCards.Rendering.ActionsOrientation.Horizontal')
  - [Vertical](#F-AdaptiveCards-Rendering-ActionsOrientation-Vertical 'AdaptiveCards.Rendering.ActionsOrientation.Vertical')
- [AdaptiveAction](#T-AdaptiveCards-AdaptiveAction 'AdaptiveCards.AdaptiveAction')
  - [IconUrl](#P-AdaptiveCards-AdaptiveAction-IconUrl 'AdaptiveCards.AdaptiveAction.IconUrl')
  - [Speak](#P-AdaptiveCards-AdaptiveAction-Speak 'AdaptiveCards.AdaptiveAction.Speak')
  - [Style](#P-AdaptiveCards-AdaptiveAction-Style 'AdaptiveCards.AdaptiveAction.Style')
  - [Title](#P-AdaptiveCards-AdaptiveAction-Title 'AdaptiveCards.AdaptiveAction.Title')
- [AdaptiveActionHandlers](#T-AdaptiveCards-Rendering-AdaptiveActionHandlers 'AdaptiveCards.Rendering.AdaptiveActionHandlers')
  - [AddSupportedAction\`\`1()](#M-AdaptiveCards-Rendering-AdaptiveActionHandlers-AddSupportedAction``1 'AdaptiveCards.Rendering.AdaptiveActionHandlers.AddSupportedAction``1')
  - [IsSupported(type)](#M-AdaptiveCards-Rendering-AdaptiveActionHandlers-IsSupported-System-Type- 'AdaptiveCards.Rendering.AdaptiveActionHandlers.IsSupported(System.Type)')
  - [RemoveSupportedAction\`\`1()](#M-AdaptiveCards-Rendering-AdaptiveActionHandlers-RemoveSupportedAction``1 'AdaptiveCards.Rendering.AdaptiveActionHandlers.RemoveSupportedAction``1')
- [AdaptiveActionSet](#T-AdaptiveCards-AdaptiveActionSet 'AdaptiveCards.AdaptiveActionSet')
  - [TypeName](#F-AdaptiveCards-AdaptiveActionSet-TypeName 'AdaptiveCards.AdaptiveActionSet.TypeName')
  - [Actions](#P-AdaptiveCards-AdaptiveActionSet-Actions 'AdaptiveCards.AdaptiveActionSet.Actions')
  - [Type](#P-AdaptiveCards-AdaptiveActionSet-Type 'AdaptiveCards.AdaptiveActionSet.Type')
- [AdaptiveBackgroundImage](#T-AdaptiveCards-AdaptiveBackgroundImage 'AdaptiveCards.AdaptiveBackgroundImage')
  - [#ctor()](#M-AdaptiveCards-AdaptiveBackgroundImage-#ctor 'AdaptiveCards.AdaptiveBackgroundImage.#ctor')
  - [#ctor(url)](#M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-String- 'AdaptiveCards.AdaptiveBackgroundImage.#ctor(System.String)')
  - [#ctor(url)](#M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-Uri- 'AdaptiveCards.AdaptiveBackgroundImage.#ctor(System.Uri)')
  - [#ctor(url,fillMode,hAlignment,vAlignment)](#M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-String,AdaptiveCards-AdaptiveImageFillMode,AdaptiveCards-AdaptiveHorizontalAlignment,AdaptiveCards-AdaptiveVerticalAlignment- 'AdaptiveCards.AdaptiveBackgroundImage.#ctor(System.String,AdaptiveCards.AdaptiveImageFillMode,AdaptiveCards.AdaptiveHorizontalAlignment,AdaptiveCards.AdaptiveVerticalAlignment)')
  - [#ctor(url,fillMode,hAlignment,vAlignment)](#M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-Uri,AdaptiveCards-AdaptiveImageFillMode,AdaptiveCards-AdaptiveHorizontalAlignment,AdaptiveCards-AdaptiveVerticalAlignment- 'AdaptiveCards.AdaptiveBackgroundImage.#ctor(System.Uri,AdaptiveCards.AdaptiveImageFillMode,AdaptiveCards.AdaptiveHorizontalAlignment,AdaptiveCards.AdaptiveVerticalAlignment)')
  - [TypeName](#F-AdaptiveCards-AdaptiveBackgroundImage-TypeName 'AdaptiveCards.AdaptiveBackgroundImage.TypeName')
  - [FillMode](#P-AdaptiveCards-AdaptiveBackgroundImage-FillMode 'AdaptiveCards.AdaptiveBackgroundImage.FillMode')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveBackgroundImage-HorizontalAlignment 'AdaptiveCards.AdaptiveBackgroundImage.HorizontalAlignment')
  - [Url](#P-AdaptiveCards-AdaptiveBackgroundImage-Url 'AdaptiveCards.AdaptiveBackgroundImage.Url')
  - [UrlString](#P-AdaptiveCards-AdaptiveBackgroundImage-UrlString 'AdaptiveCards.AdaptiveBackgroundImage.UrlString')
  - [VerticalAlignment](#P-AdaptiveCards-AdaptiveBackgroundImage-VerticalAlignment 'AdaptiveCards.AdaptiveBackgroundImage.VerticalAlignment')
  - [HasDefaultValues()](#M-AdaptiveCards-AdaptiveBackgroundImage-HasDefaultValues 'AdaptiveCards.AdaptiveBackgroundImage.HasDefaultValues')
  - [op_Implicit(backgroundImageUrl)](#M-AdaptiveCards-AdaptiveBackgroundImage-op_Implicit-System-Uri-~AdaptiveCards-AdaptiveBackgroundImage 'AdaptiveCards.AdaptiveBackgroundImage.op_Implicit(System.Uri)~AdaptiveCards.AdaptiveBackgroundImage')
- [AdaptiveBackgroundImageConverter](#T-AdaptiveCards-AdaptiveBackgroundImageConverter 'AdaptiveCards.AdaptiveBackgroundImageConverter')
  - [CanWrite](#P-AdaptiveCards-AdaptiveBackgroundImageConverter-CanWrite 'AdaptiveCards.AdaptiveBackgroundImageConverter.CanWrite')
  - [Warnings](#P-AdaptiveCards-AdaptiveBackgroundImageConverter-Warnings 'AdaptiveCards.AdaptiveBackgroundImageConverter.Warnings')
  - [CanConvert(objectType)](#M-AdaptiveCards-AdaptiveBackgroundImageConverter-CanConvert-System-Type- 'AdaptiveCards.AdaptiveBackgroundImageConverter.CanConvert(System.Type)')
  - [ReadJson(reader,objectType,existingValue,serializer)](#M-AdaptiveCards-AdaptiveBackgroundImageConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveBackgroundImageConverter.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson(writer,backgroundImage,serializer)](#M-AdaptiveCards-AdaptiveBackgroundImageConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveBackgroundImageConverter.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [AdaptiveCard](#T-AdaptiveCards-AdaptiveCard 'AdaptiveCards.AdaptiveCard')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveCard-#ctor-AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveCard.#ctor(AdaptiveCards.AdaptiveSchemaVersion)')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveCard-#ctor-System-String- 'AdaptiveCards.AdaptiveCard.#ctor(System.String)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveCard-#ctor 'AdaptiveCards.AdaptiveCard.#ctor')
  - [ContentType](#F-AdaptiveCards-AdaptiveCard-ContentType 'AdaptiveCards.AdaptiveCard.ContentType')
  - [KnownSchemaVersion](#F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion 'AdaptiveCards.AdaptiveCard.KnownSchemaVersion')
  - [TypeName](#F-AdaptiveCards-AdaptiveCard-TypeName 'AdaptiveCards.AdaptiveCard.TypeName')
  - [Actions](#P-AdaptiveCards-AdaptiveCard-Actions 'AdaptiveCards.AdaptiveCard.Actions')
  - [BackgroundImage](#P-AdaptiveCards-AdaptiveCard-BackgroundImage 'AdaptiveCards.AdaptiveCard.BackgroundImage')
  - [Body](#P-AdaptiveCards-AdaptiveCard-Body 'AdaptiveCards.AdaptiveCard.Body')
  - [FallbackText](#P-AdaptiveCards-AdaptiveCard-FallbackText 'AdaptiveCards.AdaptiveCard.FallbackText')
  - [Height](#P-AdaptiveCards-AdaptiveCard-Height 'AdaptiveCards.AdaptiveCard.Height')
  - [JsonSchema](#P-AdaptiveCards-AdaptiveCard-JsonSchema 'AdaptiveCards.AdaptiveCard.JsonSchema')
  - [Lang](#P-AdaptiveCards-AdaptiveCard-Lang 'AdaptiveCards.AdaptiveCard.Lang')
  - [MinVersion](#P-AdaptiveCards-AdaptiveCard-MinVersion 'AdaptiveCards.AdaptiveCard.MinVersion')
  - [OnDeserializingMissingVersion](#P-AdaptiveCards-AdaptiveCard-OnDeserializingMissingVersion 'AdaptiveCards.AdaptiveCard.OnDeserializingMissingVersion')
  - [PixelMinHeight](#P-AdaptiveCards-AdaptiveCard-PixelMinHeight 'AdaptiveCards.AdaptiveCard.PixelMinHeight')
  - [SelectAction](#P-AdaptiveCards-AdaptiveCard-SelectAction 'AdaptiveCards.AdaptiveCard.SelectAction')
  - [Speak](#P-AdaptiveCards-AdaptiveCard-Speak 'AdaptiveCards.AdaptiveCard.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveCard-Title 'AdaptiveCards.AdaptiveCard.Title')
  - [Type](#P-AdaptiveCards-AdaptiveCard-Type 'AdaptiveCards.AdaptiveCard.Type')
  - [Version](#P-AdaptiveCards-AdaptiveCard-Version 'AdaptiveCards.AdaptiveCard.Version')
  - [VerticalContentAlignment](#P-AdaptiveCards-AdaptiveCard-VerticalContentAlignment 'AdaptiveCards.AdaptiveCard.VerticalContentAlignment')
  - [FromJson(json)](#M-AdaptiveCards-AdaptiveCard-FromJson-System-String- 'AdaptiveCards.AdaptiveCard.FromJson(System.String)')
  - [GetResourceInformation()](#M-AdaptiveCards-AdaptiveCard-GetResourceInformation 'AdaptiveCards.AdaptiveCard.GetResourceInformation')
  - [ShouldSerializeActions()](#M-AdaptiveCards-AdaptiveCard-ShouldSerializeActions 'AdaptiveCards.AdaptiveCard.ShouldSerializeActions')
  - [ShouldSerializeBody()](#M-AdaptiveCards-AdaptiveCard-ShouldSerializeBody 'AdaptiveCards.AdaptiveCard.ShouldSerializeBody')
  - [ShouldSerializeHeight()](#M-AdaptiveCards-AdaptiveCard-ShouldSerializeHeight 'AdaptiveCards.AdaptiveCard.ShouldSerializeHeight')
  - [ShouldSerializeJsonSchema()](#M-AdaptiveCards-AdaptiveCard-ShouldSerializeJsonSchema 'AdaptiveCards.AdaptiveCard.ShouldSerializeJsonSchema')
  - [ToJson()](#M-AdaptiveCards-AdaptiveCard-ToJson 'AdaptiveCards.AdaptiveCard.ToJson')
- [AdaptiveCardConfig](#T-AdaptiveCards-Rendering-AdaptiveCardConfig 'AdaptiveCards.Rendering.AdaptiveCardConfig')
  - [AllowCustomStyle](#P-AdaptiveCards-Rendering-AdaptiveCardConfig-AllowCustomStyle 'AdaptiveCards.Rendering.AdaptiveCardConfig.AllowCustomStyle')
- [AdaptiveCardConverter](#T-AdaptiveCards-AdaptiveCardConverter 'AdaptiveCards.AdaptiveCardConverter')
  - [CanWrite](#P-AdaptiveCards-AdaptiveCardConverter-CanWrite 'AdaptiveCards.AdaptiveCardConverter.CanWrite')
  - [Warnings](#P-AdaptiveCards-AdaptiveCardConverter-Warnings 'AdaptiveCards.AdaptiveCardConverter.Warnings')
  - [CanConvert()](#M-AdaptiveCards-AdaptiveCardConverter-CanConvert-System-Type- 'AdaptiveCards.AdaptiveCardConverter.CanConvert(System.Type)')
  - [ReadJson(reader,objectType,existingValue,serializer)](#M-AdaptiveCards-AdaptiveCardConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveCardConverter.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson()](#M-AdaptiveCards-AdaptiveCardConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveCardConverter.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [AdaptiveCardParseResult](#T-AdaptiveCards-AdaptiveCardParseResult 'AdaptiveCards.AdaptiveCardParseResult')
  - [Card](#P-AdaptiveCards-AdaptiveCardParseResult-Card 'AdaptiveCards.AdaptiveCardParseResult.Card')
  - [Warnings](#P-AdaptiveCards-AdaptiveCardParseResult-Warnings 'AdaptiveCards.AdaptiveCardParseResult.Warnings')
- [AdaptiveCardRendererBase\`2](#T-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2')
  - [ElementRenderers](#P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-ElementRenderers 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.ElementRenderers')
  - [HostConfig](#P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-HostConfig 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.HostConfig')
  - [SupportedSchemaVersion](#P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-SupportedSchemaVersion 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.SupportedSchemaVersion')
  - [GetSupportedSchemaVersion()](#M-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-GetSupportedSchemaVersion 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.GetSupportedSchemaVersion')
- [AdaptiveChoice](#T-AdaptiveCards-AdaptiveChoice 'AdaptiveCards.AdaptiveChoice')
  - [IsSelected](#P-AdaptiveCards-AdaptiveChoice-IsSelected 'AdaptiveCards.AdaptiveChoice.IsSelected')
  - [Speak](#P-AdaptiveCards-AdaptiveChoice-Speak 'AdaptiveCards.AdaptiveChoice.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveChoice-Title 'AdaptiveCards.AdaptiveChoice.Title')
  - [Value](#P-AdaptiveCards-AdaptiveChoice-Value 'AdaptiveCards.AdaptiveChoice.Value')
- [AdaptiveChoiceInputStyle](#T-AdaptiveCards-AdaptiveChoiceInputStyle 'AdaptiveCards.AdaptiveChoiceInputStyle')
  - [Compact](#F-AdaptiveCards-AdaptiveChoiceInputStyle-Compact 'AdaptiveCards.AdaptiveChoiceInputStyle.Compact')
  - [Expanded](#F-AdaptiveCards-AdaptiveChoiceInputStyle-Expanded 'AdaptiveCards.AdaptiveChoiceInputStyle.Expanded')
- [AdaptiveChoiceSetInput](#T-AdaptiveCards-AdaptiveChoiceSetInput 'AdaptiveCards.AdaptiveChoiceSetInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveChoiceSetInput-TypeName 'AdaptiveCards.AdaptiveChoiceSetInput.TypeName')
  - [Choices](#P-AdaptiveCards-AdaptiveChoiceSetInput-Choices 'AdaptiveCards.AdaptiveChoiceSetInput.Choices')
  - [IsMultiSelect](#P-AdaptiveCards-AdaptiveChoiceSetInput-IsMultiSelect 'AdaptiveCards.AdaptiveChoiceSetInput.IsMultiSelect')
  - [Style](#P-AdaptiveCards-AdaptiveChoiceSetInput-Style 'AdaptiveCards.AdaptiveChoiceSetInput.Style')
  - [Type](#P-AdaptiveCards-AdaptiveChoiceSetInput-Type 'AdaptiveCards.AdaptiveChoiceSetInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveChoiceSetInput-Value 'AdaptiveCards.AdaptiveChoiceSetInput.Value')
  - [Wrap](#P-AdaptiveCards-AdaptiveChoiceSetInput-Wrap 'AdaptiveCards.AdaptiveChoiceSetInput.Wrap')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveChoiceSetInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveChoiceSetInput.GetNonInteractiveValue')
- [AdaptiveCollectionElement](#T-AdaptiveCards-AdaptiveCollectionElement 'AdaptiveCards.AdaptiveCollectionElement')
  - [Bleed](#P-AdaptiveCards-AdaptiveCollectionElement-Bleed 'AdaptiveCards.AdaptiveCollectionElement.Bleed')
  - [PixelMinHeight](#P-AdaptiveCards-AdaptiveCollectionElement-PixelMinHeight 'AdaptiveCards.AdaptiveCollectionElement.PixelMinHeight')
  - [SelectAction](#P-AdaptiveCards-AdaptiveCollectionElement-SelectAction 'AdaptiveCards.AdaptiveCollectionElement.SelectAction')
  - [Style](#P-AdaptiveCards-AdaptiveCollectionElement-Style 'AdaptiveCards.AdaptiveCollectionElement.Style')
  - [StyleXml](#P-AdaptiveCards-AdaptiveCollectionElement-StyleXml 'AdaptiveCards.AdaptiveCollectionElement.StyleXml')
  - [VerticalContentAlignment](#P-AdaptiveCards-AdaptiveCollectionElement-VerticalContentAlignment 'AdaptiveCards.AdaptiveCollectionElement.VerticalContentAlignment')
  - [ShouldSerializeStyleXml()](#M-AdaptiveCards-AdaptiveCollectionElement-ShouldSerializeStyleXml 'AdaptiveCards.AdaptiveCollectionElement.ShouldSerializeStyleXml')
- [AdaptiveColumn](#T-AdaptiveCards-AdaptiveColumn 'AdaptiveCards.AdaptiveColumn')
  - [TypeName](#F-AdaptiveCards-AdaptiveColumn-TypeName 'AdaptiveCards.AdaptiveColumn.TypeName')
  - [Size](#P-AdaptiveCards-AdaptiveColumn-Size 'AdaptiveCards.AdaptiveColumn.Size')
  - [Type](#P-AdaptiveCards-AdaptiveColumn-Type 'AdaptiveCards.AdaptiveColumn.Type')
  - [Width](#P-AdaptiveCards-AdaptiveColumn-Width 'AdaptiveCards.AdaptiveColumn.Width')
- [AdaptiveColumnSet](#T-AdaptiveCards-AdaptiveColumnSet 'AdaptiveCards.AdaptiveColumnSet')
  - [TypeName](#F-AdaptiveCards-AdaptiveColumnSet-TypeName 'AdaptiveCards.AdaptiveColumnSet.TypeName')
  - [Columns](#P-AdaptiveCards-AdaptiveColumnSet-Columns 'AdaptiveCards.AdaptiveColumnSet.Columns')
  - [Type](#P-AdaptiveCards-AdaptiveColumnSet-Type 'AdaptiveCards.AdaptiveColumnSet.Type')
- [AdaptiveColumnSize](#T-AdaptiveCards-AdaptiveColumnSize 'AdaptiveCards.AdaptiveColumnSize')
  - [Auto](#F-AdaptiveCards-AdaptiveColumnSize-Auto 'AdaptiveCards.AdaptiveColumnSize.Auto')
  - [Stretch](#F-AdaptiveCards-AdaptiveColumnSize-Stretch 'AdaptiveCards.AdaptiveColumnSize.Stretch')
- [AdaptiveColumnWidth](#T-AdaptiveCards-AdaptiveColumnWidth 'AdaptiveCards.AdaptiveColumnWidth')
  - [Auto](#F-AdaptiveCards-AdaptiveColumnWidth-Auto 'AdaptiveCards.AdaptiveColumnWidth.Auto')
  - [Stretch](#F-AdaptiveCards-AdaptiveColumnWidth-Stretch 'AdaptiveCards.AdaptiveColumnWidth.Stretch')
- [AdaptiveConfigBase](#T-AdaptiveCards-Rendering-AdaptiveConfigBase 'AdaptiveCards.Rendering.AdaptiveConfigBase')
  - [AdditionalData](#P-AdaptiveCards-Rendering-AdaptiveConfigBase-AdditionalData 'AdaptiveCards.Rendering.AdaptiveConfigBase.AdditionalData')
- [AdaptiveContainer](#T-AdaptiveCards-AdaptiveContainer 'AdaptiveCards.AdaptiveContainer')
  - [TypeName](#F-AdaptiveCards-AdaptiveContainer-TypeName 'AdaptiveCards.AdaptiveContainer.TypeName')
  - [BackgroundImage](#P-AdaptiveCards-AdaptiveContainer-BackgroundImage 'AdaptiveCards.AdaptiveContainer.BackgroundImage')
  - [Items](#P-AdaptiveCards-AdaptiveContainer-Items 'AdaptiveCards.AdaptiveContainer.Items')
  - [Type](#P-AdaptiveCards-AdaptiveContainer-Type 'AdaptiveCards.AdaptiveContainer.Type')
- [AdaptiveContainerStyle](#T-AdaptiveCards-AdaptiveContainerStyle 'AdaptiveCards.AdaptiveContainerStyle')
  - [Accent](#F-AdaptiveCards-AdaptiveContainerStyle-Accent 'AdaptiveCards.AdaptiveContainerStyle.Accent')
  - [Attention](#F-AdaptiveCards-AdaptiveContainerStyle-Attention 'AdaptiveCards.AdaptiveContainerStyle.Attention')
  - [Default](#F-AdaptiveCards-AdaptiveContainerStyle-Default 'AdaptiveCards.AdaptiveContainerStyle.Default')
  - [Emphasis](#F-AdaptiveCards-AdaptiveContainerStyle-Emphasis 'AdaptiveCards.AdaptiveContainerStyle.Emphasis')
  - [Good](#F-AdaptiveCards-AdaptiveContainerStyle-Good 'AdaptiveCards.AdaptiveContainerStyle.Good')
  - [Normal](#F-AdaptiveCards-AdaptiveContainerStyle-Normal 'AdaptiveCards.AdaptiveContainerStyle.Normal')
  - [Warning](#F-AdaptiveCards-AdaptiveContainerStyle-Warning 'AdaptiveCards.AdaptiveContainerStyle.Warning')
- [AdaptiveDateInput](#T-AdaptiveCards-AdaptiveDateInput 'AdaptiveCards.AdaptiveDateInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveDateInput-TypeName 'AdaptiveCards.AdaptiveDateInput.TypeName')
  - [Max](#P-AdaptiveCards-AdaptiveDateInput-Max 'AdaptiveCards.AdaptiveDateInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveDateInput-Min 'AdaptiveCards.AdaptiveDateInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveDateInput-Placeholder 'AdaptiveCards.AdaptiveDateInput.Placeholder')
  - [Type](#P-AdaptiveCards-AdaptiveDateInput-Type 'AdaptiveCards.AdaptiveDateInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveDateInput-Value 'AdaptiveCards.AdaptiveDateInput.Value')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveDateInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveDateInput.GetNonInteractiveValue')
- [AdaptiveElement](#T-AdaptiveCards-AdaptiveElement 'AdaptiveCards.AdaptiveElement')
  - [Height](#P-AdaptiveCards-AdaptiveElement-Height 'AdaptiveCards.AdaptiveElement.Height')
  - [IsVisible](#P-AdaptiveCards-AdaptiveElement-IsVisible 'AdaptiveCards.AdaptiveElement.IsVisible')
  - [Separator](#P-AdaptiveCards-AdaptiveElement-Separator 'AdaptiveCards.AdaptiveElement.Separator')
  - [Spacing](#P-AdaptiveCards-AdaptiveElement-Spacing 'AdaptiveCards.AdaptiveElement.Spacing')
  - [Speak](#P-AdaptiveCards-AdaptiveElement-Speak 'AdaptiveCards.AdaptiveElement.Speak')
  - [ShouldSerializeHeight()](#M-AdaptiveCards-AdaptiveElement-ShouldSerializeHeight 'AdaptiveCards.AdaptiveElement.ShouldSerializeHeight')
- [AdaptiveElementRenderers\`2](#T-AdaptiveCards-Rendering-AdaptiveElementRenderers`2 'AdaptiveCards.Rendering.AdaptiveElementRenderers`2')
  - [Get(type)](#M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Get-System-Type- 'AdaptiveCards.Rendering.AdaptiveElementRenderers`2.Get(System.Type)')
  - [Get\`\`1()](#M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Get``1 'AdaptiveCards.Rendering.AdaptiveElementRenderers`2.Get``1')
  - [Remove\`\`1()](#M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Remove``1 'AdaptiveCards.Rendering.AdaptiveElementRenderers`2.Remove``1')
  - [Set\`\`1(renderer)](#M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Set``1-System-Func{``0,`1,`0}- 'AdaptiveCards.Rendering.AdaptiveElementRenderers`2.Set``1(System.Func{``0,`1,`0})')
- [AdaptiveException](#T-AdaptiveCards-AdaptiveException 'AdaptiveCards.AdaptiveException')
  - [#ctor()](#M-AdaptiveCards-AdaptiveException-#ctor 'AdaptiveCards.AdaptiveException.#ctor')
  - [#ctor()](#M-AdaptiveCards-AdaptiveException-#ctor-System-String- 'AdaptiveCards.AdaptiveException.#ctor(System.String)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveException-#ctor-System-String,System-Exception- 'AdaptiveCards.AdaptiveException.#ctor(System.String,System.Exception)')
- [AdaptiveFact](#T-AdaptiveCards-AdaptiveFact 'AdaptiveCards.AdaptiveFact')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFact-#ctor 'AdaptiveCards.AdaptiveFact.#ctor')
  - [#ctor(title,value)](#M-AdaptiveCards-AdaptiveFact-#ctor-System-String,System-String- 'AdaptiveCards.AdaptiveFact.#ctor(System.String,System.String)')
  - [Speak](#P-AdaptiveCards-AdaptiveFact-Speak 'AdaptiveCards.AdaptiveFact.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveFact-Title 'AdaptiveCards.AdaptiveFact.Title')
  - [Value](#P-AdaptiveCards-AdaptiveFact-Value 'AdaptiveCards.AdaptiveFact.Value')
- [AdaptiveFactSet](#T-AdaptiveCards-AdaptiveFactSet 'AdaptiveCards.AdaptiveFactSet')
  - [TypeName](#F-AdaptiveCards-AdaptiveFactSet-TypeName 'AdaptiveCards.AdaptiveFactSet.TypeName')
  - [Facts](#P-AdaptiveCards-AdaptiveFactSet-Facts 'AdaptiveCards.AdaptiveFactSet.Facts')
  - [Type](#P-AdaptiveCards-AdaptiveFactSet-Type 'AdaptiveCards.AdaptiveFactSet.Type')
- [AdaptiveFallbackConverter](#T-AdaptiveCards-AdaptiveFallbackConverter 'AdaptiveCards.AdaptiveFallbackConverter')
  - [IsInFallback](#F-AdaptiveCards-AdaptiveFallbackConverter-IsInFallback 'AdaptiveCards.AdaptiveFallbackConverter.IsInFallback')
  - [CanRead](#P-AdaptiveCards-AdaptiveFallbackConverter-CanRead 'AdaptiveCards.AdaptiveFallbackConverter.CanRead')
  - [CanWrite](#P-AdaptiveCards-AdaptiveFallbackConverter-CanWrite 'AdaptiveCards.AdaptiveFallbackConverter.CanWrite')
  - [Warnings](#P-AdaptiveCards-AdaptiveFallbackConverter-Warnings 'AdaptiveCards.AdaptiveFallbackConverter.Warnings')
  - [CanConvert(objectType)](#M-AdaptiveCards-AdaptiveFallbackConverter-CanConvert-System-Type- 'AdaptiveCards.AdaptiveFallbackConverter.CanConvert(System.Type)')
  - [ParseFallback()](#M-AdaptiveCards-AdaptiveFallbackConverter-ParseFallback-Newtonsoft-Json-Linq-JToken,Newtonsoft-Json-JsonSerializer,System-String,AdaptiveCards-AdaptiveInternalID- 'AdaptiveCards.AdaptiveFallbackConverter.ParseFallback(Newtonsoft.Json.Linq.JToken,Newtonsoft.Json.JsonSerializer,System.String,AdaptiveCards.AdaptiveInternalID)')
  - [ReadJson()](#M-AdaptiveCards-AdaptiveFallbackConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveFallbackConverter.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson(writer,cardElement,serializer)](#M-AdaptiveCards-AdaptiveFallbackConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveFallbackConverter.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [AdaptiveFallbackElement](#T-AdaptiveCards-AdaptiveFallbackElement 'AdaptiveCards.AdaptiveFallbackElement')
  - [#ctor(fallbackType)](#M-AdaptiveCards-AdaptiveFallbackElement-#ctor-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType- 'AdaptiveCards.AdaptiveFallbackElement.#ctor(AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType)')
  - [#ctor(fallbackContent)](#M-AdaptiveCards-AdaptiveFallbackElement-#ctor-AdaptiveCards-AdaptiveTypedElement- 'AdaptiveCards.AdaptiveFallbackElement.#ctor(AdaptiveCards.AdaptiveTypedElement)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFallbackElement-#ctor 'AdaptiveCards.AdaptiveFallbackElement.#ctor')
  - [drop](#F-AdaptiveCards-AdaptiveFallbackElement-drop 'AdaptiveCards.AdaptiveFallbackElement.drop')
  - [Content](#P-AdaptiveCards-AdaptiveFallbackElement-Content 'AdaptiveCards.AdaptiveFallbackElement.Content')
  - [Type](#P-AdaptiveCards-AdaptiveFallbackElement-Type 'AdaptiveCards.AdaptiveFallbackElement.Type')
- [AdaptiveFallbackException](#T-AdaptiveCards-AdaptiveFallbackException 'AdaptiveCards.AdaptiveFallbackException')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFallbackException-#ctor 'AdaptiveCards.AdaptiveFallbackException.#ctor')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFallbackException-#ctor-System-String- 'AdaptiveCards.AdaptiveFallbackException.#ctor(System.String)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFallbackException-#ctor-System-String,System-Exception- 'AdaptiveCards.AdaptiveFallbackException.#ctor(System.String,System.Exception)')
- [AdaptiveFallbackType](#T-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType 'AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType')
  - [Content](#F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-Content 'AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType.Content')
  - [Drop](#F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-Drop 'AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType.Drop')
  - [None](#F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-None 'AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType.None')
- [AdaptiveFeatureRegistration](#T-AdaptiveCards-AdaptiveFeatureRegistration 'AdaptiveCards.AdaptiveFeatureRegistration')
  - [#ctor()](#M-AdaptiveCards-AdaptiveFeatureRegistration-#ctor 'AdaptiveCards.AdaptiveFeatureRegistration.#ctor')
  - [Get(feature)](#M-AdaptiveCards-AdaptiveFeatureRegistration-Get-System-String- 'AdaptiveCards.AdaptiveFeatureRegistration.Get(System.String)')
  - [Remove(feature)](#M-AdaptiveCards-AdaptiveFeatureRegistration-Remove-System-String- 'AdaptiveCards.AdaptiveFeatureRegistration.Remove(System.String)')
  - [Set(feature,version)](#M-AdaptiveCards-AdaptiveFeatureRegistration-Set-System-String,System-String- 'AdaptiveCards.AdaptiveFeatureRegistration.Set(System.String,System.String)')
- [AdaptiveFontType](#T-AdaptiveCards-AdaptiveFontType 'AdaptiveCards.AdaptiveFontType')
  - [Default](#F-AdaptiveCards-AdaptiveFontType-Default 'AdaptiveCards.AdaptiveFontType.Default')
  - [Monospace](#F-AdaptiveCards-AdaptiveFontType-Monospace 'AdaptiveCards.AdaptiveFontType.Monospace')
- [AdaptiveHeight](#T-AdaptiveCards-AdaptiveHeight 'AdaptiveCards.AdaptiveHeight')
  - [#ctor()](#M-AdaptiveCards-AdaptiveHeight-#ctor 'AdaptiveCards.AdaptiveHeight.#ctor')
  - [#ctor(px)](#M-AdaptiveCards-AdaptiveHeight-#ctor-System-UInt32- 'AdaptiveCards.AdaptiveHeight.#ctor(System.UInt32)')
  - [#ctor(heightType)](#M-AdaptiveCards-AdaptiveHeight-#ctor-AdaptiveCards-AdaptiveHeightType- 'AdaptiveCards.AdaptiveHeight.#ctor(AdaptiveCards.AdaptiveHeightType)')
  - [Auto](#P-AdaptiveCards-AdaptiveHeight-Auto 'AdaptiveCards.AdaptiveHeight.Auto')
  - [HeightType](#P-AdaptiveCards-AdaptiveHeight-HeightType 'AdaptiveCards.AdaptiveHeight.HeightType')
  - [Stretch](#P-AdaptiveCards-AdaptiveHeight-Stretch 'AdaptiveCards.AdaptiveHeight.Stretch')
  - [Unit](#P-AdaptiveCards-AdaptiveHeight-Unit 'AdaptiveCards.AdaptiveHeight.Unit')
  - [UnitXml](#P-AdaptiveCards-AdaptiveHeight-UnitXml 'AdaptiveCards.AdaptiveHeight.UnitXml')
  - [Equals()](#M-AdaptiveCards-AdaptiveHeight-Equals-System-Object- 'AdaptiveCards.AdaptiveHeight.Equals(System.Object)')
  - [Equals()](#M-AdaptiveCards-AdaptiveHeight-Equals-AdaptiveCards-AdaptiveHeight- 'AdaptiveCards.AdaptiveHeight.Equals(AdaptiveCards.AdaptiveHeight)')
  - [GetHashCode()](#M-AdaptiveCards-AdaptiveHeight-GetHashCode 'AdaptiveCards.AdaptiveHeight.GetHashCode')
  - [IsPixel()](#M-AdaptiveCards-AdaptiveHeight-IsPixel 'AdaptiveCards.AdaptiveHeight.IsPixel')
  - [ShouldSerializeAdaptiveHeight()](#M-AdaptiveCards-AdaptiveHeight-ShouldSerializeAdaptiveHeight 'AdaptiveCards.AdaptiveHeight.ShouldSerializeAdaptiveHeight')
  - [ShouldSerializeUnitXml()](#M-AdaptiveCards-AdaptiveHeight-ShouldSerializeUnitXml 'AdaptiveCards.AdaptiveHeight.ShouldSerializeUnitXml')
  - [op_Equality()](#M-AdaptiveCards-AdaptiveHeight-op_Equality-AdaptiveCards-AdaptiveHeight,AdaptiveCards-AdaptiveHeight- 'AdaptiveCards.AdaptiveHeight.op_Equality(AdaptiveCards.AdaptiveHeight,AdaptiveCards.AdaptiveHeight)')
  - [op_Inequality()](#M-AdaptiveCards-AdaptiveHeight-op_Inequality-AdaptiveCards-AdaptiveHeight,AdaptiveCards-AdaptiveHeight- 'AdaptiveCards.AdaptiveHeight.op_Inequality(AdaptiveCards.AdaptiveHeight,AdaptiveCards.AdaptiveHeight)')
- [AdaptiveHeightType](#T-AdaptiveCards-AdaptiveHeightType 'AdaptiveCards.AdaptiveHeightType')
  - [Auto](#F-AdaptiveCards-AdaptiveHeightType-Auto 'AdaptiveCards.AdaptiveHeightType.Auto')
  - [Pixel](#F-AdaptiveCards-AdaptiveHeightType-Pixel 'AdaptiveCards.AdaptiveHeightType.Pixel')
  - [Stretch](#F-AdaptiveCards-AdaptiveHeightType-Stretch 'AdaptiveCards.AdaptiveHeightType.Stretch')
- [AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment')
  - [Center](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Center 'AdaptiveCards.AdaptiveHorizontalAlignment.Center')
  - [Left](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Left 'AdaptiveCards.AdaptiveHorizontalAlignment.Left')
  - [Right](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Right 'AdaptiveCards.AdaptiveHorizontalAlignment.Right')
  - [Stretch](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Stretch 'AdaptiveCards.AdaptiveHorizontalAlignment.Stretch')
- [AdaptiveHostConfig](#T-AdaptiveCards-Rendering-AdaptiveHostConfig 'AdaptiveCards.Rendering.AdaptiveHostConfig')
  - [Actions](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-Actions 'AdaptiveCards.Rendering.AdaptiveHostConfig.Actions')
  - [AdaptiveCard](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-AdaptiveCard 'AdaptiveCards.Rendering.AdaptiveHostConfig.AdaptiveCard')
  - [ContainerStyles](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ContainerStyles 'AdaptiveCards.Rendering.AdaptiveHostConfig.ContainerStyles')
  - [FactSet](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-FactSet 'AdaptiveCards.Rendering.AdaptiveHostConfig.FactSet')
  - [FontFamily](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontFamily 'AdaptiveCards.Rendering.AdaptiveHostConfig.FontFamily')
  - [FontSizes](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontSizes 'AdaptiveCards.Rendering.AdaptiveHostConfig.FontSizes')
  - [FontTypes](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontTypes 'AdaptiveCards.Rendering.AdaptiveHostConfig.FontTypes')
  - [FontWeights](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontWeights 'AdaptiveCards.Rendering.AdaptiveHostConfig.FontWeights')
  - [ImageBaseUrl](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageBaseUrl 'AdaptiveCards.Rendering.AdaptiveHostConfig.ImageBaseUrl')
  - [ImageSet](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageSet 'AdaptiveCards.Rendering.AdaptiveHostConfig.ImageSet')
  - [ImageSizes](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageSizes 'AdaptiveCards.Rendering.AdaptiveHostConfig.ImageSizes')
  - [Inputs](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-Inputs 'AdaptiveCards.Rendering.AdaptiveHostConfig.Inputs')
  - [Media](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-Media 'AdaptiveCards.Rendering.AdaptiveHostConfig.Media')
  - [Separator](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-Separator 'AdaptiveCards.Rendering.AdaptiveHostConfig.Separator')
  - [Spacing](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-Spacing 'AdaptiveCards.Rendering.AdaptiveHostConfig.Spacing')
  - [SupportsInteractivity](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-SupportsInteractivity 'AdaptiveCards.Rendering.AdaptiveHostConfig.SupportsInteractivity')
  - [FromJson()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-FromJson-System-String- 'AdaptiveCards.Rendering.AdaptiveHostConfig.FromJson(System.String)')
  - [GetFontFamily()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontFamily-AdaptiveCards-AdaptiveFontType- 'AdaptiveCards.Rendering.AdaptiveHostConfig.GetFontFamily(AdaptiveCards.AdaptiveFontType)')
  - [GetFontSize()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontSize-AdaptiveCards-AdaptiveFontType,AdaptiveCards-AdaptiveTextSize- 'AdaptiveCards.Rendering.AdaptiveHostConfig.GetFontSize(AdaptiveCards.AdaptiveFontType,AdaptiveCards.AdaptiveTextSize)')
  - [GetFontWeight()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontWeight-AdaptiveCards-AdaptiveFontType,AdaptiveCards-AdaptiveTextWeight- 'AdaptiveCards.Rendering.AdaptiveHostConfig.GetFontWeight(AdaptiveCards.AdaptiveFontType,AdaptiveCards.AdaptiveTextWeight)')
  - [GetSpacing(spacing)](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetSpacing-AdaptiveCards-AdaptiveSpacing- 'AdaptiveCards.Rendering.AdaptiveHostConfig.GetSpacing(AdaptiveCards.AdaptiveSpacing)')
  - [ResolveFinalAbsoluteUri(uriString)](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-String- 'AdaptiveCards.Rendering.AdaptiveHostConfig.ResolveFinalAbsoluteUri(System.String)')
  - [ResolveFinalAbsoluteUri(uri)](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-Uri- 'AdaptiveCards.Rendering.AdaptiveHostConfig.ResolveFinalAbsoluteUri(System.Uri)')
  - [ToJson()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-ToJson 'AdaptiveCards.Rendering.AdaptiveHostConfig.ToJson')
- [AdaptiveImage](#T-AdaptiveCards-AdaptiveImage 'AdaptiveCards.AdaptiveImage')
  - [#ctor()](#M-AdaptiveCards-AdaptiveImage-#ctor 'AdaptiveCards.AdaptiveImage.#ctor')
  - [#ctor(url)](#M-AdaptiveCards-AdaptiveImage-#ctor-System-String- 'AdaptiveCards.AdaptiveImage.#ctor(System.String)')
  - [#ctor(url)](#M-AdaptiveCards-AdaptiveImage-#ctor-System-Uri- 'AdaptiveCards.AdaptiveImage.#ctor(System.Uri)')
  - [TypeName](#F-AdaptiveCards-AdaptiveImage-TypeName 'AdaptiveCards.AdaptiveImage.TypeName')
  - [AltText](#P-AdaptiveCards-AdaptiveImage-AltText 'AdaptiveCards.AdaptiveImage.AltText')
  - [BackgroundColor](#P-AdaptiveCards-AdaptiveImage-BackgroundColor 'AdaptiveCards.AdaptiveImage.BackgroundColor')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveImage-HorizontalAlignment 'AdaptiveCards.AdaptiveImage.HorizontalAlignment')
  - [PixelHeight](#P-AdaptiveCards-AdaptiveImage-PixelHeight 'AdaptiveCards.AdaptiveImage.PixelHeight')
  - [PixelWidth](#P-AdaptiveCards-AdaptiveImage-PixelWidth 'AdaptiveCards.AdaptiveImage.PixelWidth')
  - [SelectAction](#P-AdaptiveCards-AdaptiveImage-SelectAction 'AdaptiveCards.AdaptiveImage.SelectAction')
  - [Size](#P-AdaptiveCards-AdaptiveImage-Size 'AdaptiveCards.AdaptiveImage.Size')
  - [Style](#P-AdaptiveCards-AdaptiveImage-Style 'AdaptiveCards.AdaptiveImage.Style')
  - [Type](#P-AdaptiveCards-AdaptiveImage-Type 'AdaptiveCards.AdaptiveImage.Type')
  - [Url](#P-AdaptiveCards-AdaptiveImage-Url 'AdaptiveCards.AdaptiveImage.Url')
  - [UrlString](#P-AdaptiveCards-AdaptiveImage-UrlString 'AdaptiveCards.AdaptiveImage.UrlString')
- [AdaptiveImageFillMode](#T-AdaptiveCards-AdaptiveImageFillMode 'AdaptiveCards.AdaptiveImageFillMode')
  - [Cover](#F-AdaptiveCards-AdaptiveImageFillMode-Cover 'AdaptiveCards.AdaptiveImageFillMode.Cover')
  - [Repeat](#F-AdaptiveCards-AdaptiveImageFillMode-Repeat 'AdaptiveCards.AdaptiveImageFillMode.Repeat')
  - [RepeatHorizontally](#F-AdaptiveCards-AdaptiveImageFillMode-RepeatHorizontally 'AdaptiveCards.AdaptiveImageFillMode.RepeatHorizontally')
  - [RepeatVertically](#F-AdaptiveCards-AdaptiveImageFillMode-RepeatVertically 'AdaptiveCards.AdaptiveImageFillMode.RepeatVertically')
- [AdaptiveImageSet](#T-AdaptiveCards-AdaptiveImageSet 'AdaptiveCards.AdaptiveImageSet')
  - [TypeName](#F-AdaptiveCards-AdaptiveImageSet-TypeName 'AdaptiveCards.AdaptiveImageSet.TypeName')
  - [ImageSize](#P-AdaptiveCards-AdaptiveImageSet-ImageSize 'AdaptiveCards.AdaptiveImageSet.ImageSize')
  - [Images](#P-AdaptiveCards-AdaptiveImageSet-Images 'AdaptiveCards.AdaptiveImageSet.Images')
  - [Type](#P-AdaptiveCards-AdaptiveImageSet-Type 'AdaptiveCards.AdaptiveImageSet.Type')
- [AdaptiveImageSize](#T-AdaptiveCards-AdaptiveImageSize 'AdaptiveCards.AdaptiveImageSize')
  - [Auto](#F-AdaptiveCards-AdaptiveImageSize-Auto 'AdaptiveCards.AdaptiveImageSize.Auto')
  - [Large](#F-AdaptiveCards-AdaptiveImageSize-Large 'AdaptiveCards.AdaptiveImageSize.Large')
  - [Medium](#F-AdaptiveCards-AdaptiveImageSize-Medium 'AdaptiveCards.AdaptiveImageSize.Medium')
  - [Small](#F-AdaptiveCards-AdaptiveImageSize-Small 'AdaptiveCards.AdaptiveImageSize.Small')
  - [Stretch](#F-AdaptiveCards-AdaptiveImageSize-Stretch 'AdaptiveCards.AdaptiveImageSize.Stretch')
- [AdaptiveImageStyle](#T-AdaptiveCards-AdaptiveImageStyle 'AdaptiveCards.AdaptiveImageStyle')
  - [Default](#F-AdaptiveCards-AdaptiveImageStyle-Default 'AdaptiveCards.AdaptiveImageStyle.Default')
  - [Normal](#F-AdaptiveCards-AdaptiveImageStyle-Normal 'AdaptiveCards.AdaptiveImageStyle.Normal')
  - [Person](#F-AdaptiveCards-AdaptiveImageStyle-Person 'AdaptiveCards.AdaptiveImageStyle.Person')
- [AdaptiveInline](#T-AdaptiveCards-AdaptiveInline 'AdaptiveCards.AdaptiveInline')
  - [AdditionalProperties](#P-AdaptiveCards-AdaptiveInline-AdditionalProperties 'AdaptiveCards.AdaptiveInline.AdditionalProperties')
  - [Type](#P-AdaptiveCards-AdaptiveInline-Type 'AdaptiveCards.AdaptiveInline.Type')
  - [ShouldSerializeAdditionalProperties()](#M-AdaptiveCards-AdaptiveInline-ShouldSerializeAdditionalProperties 'AdaptiveCards.AdaptiveInline.ShouldSerializeAdditionalProperties')
- [AdaptiveInput](#T-AdaptiveCards-AdaptiveInput 'AdaptiveCards.AdaptiveInput')
  - [ErrorMessage](#P-AdaptiveCards-AdaptiveInput-ErrorMessage 'AdaptiveCards.AdaptiveInput.ErrorMessage')
  - [IsRequired](#P-AdaptiveCards-AdaptiveInput-IsRequired 'AdaptiveCards.AdaptiveInput.IsRequired')
  - [Label](#P-AdaptiveCards-AdaptiveInput-Label 'AdaptiveCards.AdaptiveInput.Label')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveInput.GetNonInteractiveValue')
- [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID')
  - [#ctor()](#M-AdaptiveCards-AdaptiveInternalID-#ctor 'AdaptiveCards.AdaptiveInternalID.#ctor')
  - [#ctor(id)](#M-AdaptiveCards-AdaptiveInternalID-#ctor-System-UInt32- 'AdaptiveCards.AdaptiveInternalID.#ctor(System.UInt32)')
  - [Invalid](#F-AdaptiveCards-AdaptiveInternalID-Invalid 'AdaptiveCards.AdaptiveInternalID.Invalid')
  - [Current()](#M-AdaptiveCards-AdaptiveInternalID-Current 'AdaptiveCards.AdaptiveInternalID.Current')
  - [Equals()](#M-AdaptiveCards-AdaptiveInternalID-Equals-System-Object- 'AdaptiveCards.AdaptiveInternalID.Equals(System.Object)')
  - [GetHashCode()](#M-AdaptiveCards-AdaptiveInternalID-GetHashCode 'AdaptiveCards.AdaptiveInternalID.GetHashCode')
  - [Next()](#M-AdaptiveCards-AdaptiveInternalID-Next 'AdaptiveCards.AdaptiveInternalID.Next')
  - [ToString()](#M-AdaptiveCards-AdaptiveInternalID-ToString 'AdaptiveCards.AdaptiveInternalID.ToString')
- [AdaptiveMedia](#T-AdaptiveCards-AdaptiveMedia 'AdaptiveCards.AdaptiveMedia')
  - [TypeName](#F-AdaptiveCards-AdaptiveMedia-TypeName 'AdaptiveCards.AdaptiveMedia.TypeName')
  - [AltText](#P-AdaptiveCards-AdaptiveMedia-AltText 'AdaptiveCards.AdaptiveMedia.AltText')
  - [Poster](#P-AdaptiveCards-AdaptiveMedia-Poster 'AdaptiveCards.AdaptiveMedia.Poster')
  - [Sources](#P-AdaptiveCards-AdaptiveMedia-Sources 'AdaptiveCards.AdaptiveMedia.Sources')
  - [Type](#P-AdaptiveCards-AdaptiveMedia-Type 'AdaptiveCards.AdaptiveMedia.Type')
- [AdaptiveMediaSource](#T-AdaptiveCards-AdaptiveMediaSource 'AdaptiveCards.AdaptiveMediaSource')
  - [#ctor()](#M-AdaptiveCards-AdaptiveMediaSource-#ctor 'AdaptiveCards.AdaptiveMediaSource.#ctor')
  - [#ctor(mimeType,url)](#M-AdaptiveCards-AdaptiveMediaSource-#ctor-System-String,System-String- 'AdaptiveCards.AdaptiveMediaSource.#ctor(System.String,System.String)')
  - [MimeType](#P-AdaptiveCards-AdaptiveMediaSource-MimeType 'AdaptiveCards.AdaptiveMediaSource.MimeType')
  - [Url](#P-AdaptiveCards-AdaptiveMediaSource-Url 'AdaptiveCards.AdaptiveMediaSource.Url')
- [AdaptiveNumberInput](#T-AdaptiveCards-AdaptiveNumberInput 'AdaptiveCards.AdaptiveNumberInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveNumberInput-TypeName 'AdaptiveCards.AdaptiveNumberInput.TypeName')
  - [Max](#P-AdaptiveCards-AdaptiveNumberInput-Max 'AdaptiveCards.AdaptiveNumberInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveNumberInput-Min 'AdaptiveCards.AdaptiveNumberInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveNumberInput-Placeholder 'AdaptiveCards.AdaptiveNumberInput.Placeholder')
  - [Type](#P-AdaptiveCards-AdaptiveNumberInput-Type 'AdaptiveCards.AdaptiveNumberInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveNumberInput-Value 'AdaptiveCards.AdaptiveNumberInput.Value')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveNumberInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveNumberInput.GetNonInteractiveValue')
- [AdaptiveOpenUrlAction](#T-AdaptiveCards-AdaptiveOpenUrlAction 'AdaptiveCards.AdaptiveOpenUrlAction')
  - [TypeName](#F-AdaptiveCards-AdaptiveOpenUrlAction-TypeName 'AdaptiveCards.AdaptiveOpenUrlAction.TypeName')
  - [Type](#P-AdaptiveCards-AdaptiveOpenUrlAction-Type 'AdaptiveCards.AdaptiveOpenUrlAction.Type')
  - [Url](#P-AdaptiveCards-AdaptiveOpenUrlAction-Url 'AdaptiveCards.AdaptiveOpenUrlAction.Url')
  - [UrlString](#P-AdaptiveCards-AdaptiveOpenUrlAction-UrlString 'AdaptiveCards.AdaptiveOpenUrlAction.UrlString')
- [AdaptiveRenderException](#T-AdaptiveCards-Rendering-AdaptiveRenderException 'AdaptiveCards.Rendering.AdaptiveRenderException')
  - [CardFallbackText](#P-AdaptiveCards-Rendering-AdaptiveRenderException-CardFallbackText 'AdaptiveCards.Rendering.AdaptiveRenderException.CardFallbackText')
- [AdaptiveRichTextBlock](#T-AdaptiveCards-AdaptiveRichTextBlock 'AdaptiveCards.AdaptiveRichTextBlock')
  - [#ctor()](#M-AdaptiveCards-AdaptiveRichTextBlock-#ctor 'AdaptiveCards.AdaptiveRichTextBlock.#ctor')
  - [TypeName](#F-AdaptiveCards-AdaptiveRichTextBlock-TypeName 'AdaptiveCards.AdaptiveRichTextBlock.TypeName')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveRichTextBlock-HorizontalAlignment 'AdaptiveCards.AdaptiveRichTextBlock.HorizontalAlignment')
  - [Inlines](#P-AdaptiveCards-AdaptiveRichTextBlock-Inlines 'AdaptiveCards.AdaptiveRichTextBlock.Inlines')
  - [Type](#P-AdaptiveCards-AdaptiveRichTextBlock-Type 'AdaptiveCards.AdaptiveRichTextBlock.Type')
- [AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion')
  - [#ctor()](#M-AdaptiveCards-AdaptiveSchemaVersion-#ctor 'AdaptiveCards.AdaptiveSchemaVersion.#ctor')
  - [#ctor(versionString)](#M-AdaptiveCards-AdaptiveSchemaVersion-#ctor-System-String- 'AdaptiveCards.AdaptiveSchemaVersion.#ctor(System.String)')
  - [#ctor(major,minor)](#M-AdaptiveCards-AdaptiveSchemaVersion-#ctor-System-Int32,System-Int32- 'AdaptiveCards.AdaptiveSchemaVersion.#ctor(System.Int32,System.Int32)')
  - [Major](#P-AdaptiveCards-AdaptiveSchemaVersion-Major 'AdaptiveCards.AdaptiveSchemaVersion.Major')
  - [Minor](#P-AdaptiveCards-AdaptiveSchemaVersion-Minor 'AdaptiveCards.AdaptiveSchemaVersion.Minor')
  - [CompareTo(other)](#M-AdaptiveCards-AdaptiveSchemaVersion-CompareTo-AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.CompareTo(AdaptiveCards.AdaptiveSchemaVersion)')
  - [Equals()](#M-AdaptiveCards-AdaptiveSchemaVersion-Equals-System-Object- 'AdaptiveCards.AdaptiveSchemaVersion.Equals(System.Object)')
  - [GetHashCode()](#M-AdaptiveCards-AdaptiveSchemaVersion-GetHashCode 'AdaptiveCards.AdaptiveSchemaVersion.GetHashCode')
  - [ToString()](#M-AdaptiveCards-AdaptiveSchemaVersion-ToString 'AdaptiveCards.AdaptiveSchemaVersion.ToString')
  - [op_Equality()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_Equality-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_Equality(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
  - [op_GreaterThan()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_GreaterThan-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_GreaterThan(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
  - [op_GreaterThanOrEqual()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_GreaterThanOrEqual-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_GreaterThanOrEqual(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
  - [op_Implicit(versionString)](#M-AdaptiveCards-AdaptiveSchemaVersion-op_Implicit-System-String-~AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion.op_Implicit(System.String)~AdaptiveCards.AdaptiveSchemaVersion')
  - [op_Inequality()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_Inequality-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_Inequality(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
  - [op_LessThan()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_LessThan-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_LessThan(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
  - [op_LessThanOrEqual()](#M-AdaptiveCards-AdaptiveSchemaVersion-op_LessThanOrEqual-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveSchemaVersion.op_LessThanOrEqual(AdaptiveCards.AdaptiveSchemaVersion,AdaptiveCards.AdaptiveSchemaVersion)')
- [AdaptiveSerializationException](#T-AdaptiveCards-AdaptiveSerializationException 'AdaptiveCards.AdaptiveSerializationException')
  - [#ctor()](#M-AdaptiveCards-AdaptiveSerializationException-#ctor 'AdaptiveCards.AdaptiveSerializationException.#ctor')
  - [#ctor()](#M-AdaptiveCards-AdaptiveSerializationException-#ctor-System-String- 'AdaptiveCards.AdaptiveSerializationException.#ctor(System.String)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveSerializationException-#ctor-System-String,System-Exception- 'AdaptiveCards.AdaptiveSerializationException.#ctor(System.String,System.Exception)')
- [AdaptiveShowCardAction](#T-AdaptiveCards-AdaptiveShowCardAction 'AdaptiveCards.AdaptiveShowCardAction')
  - [TypeName](#F-AdaptiveCards-AdaptiveShowCardAction-TypeName 'AdaptiveCards.AdaptiveShowCardAction.TypeName')
  - [Card](#P-AdaptiveCards-AdaptiveShowCardAction-Card 'AdaptiveCards.AdaptiveShowCardAction.Card')
  - [Type](#P-AdaptiveCards-AdaptiveShowCardAction-Type 'AdaptiveCards.AdaptiveShowCardAction.Type')
- [AdaptiveSpacing](#T-AdaptiveCards-AdaptiveSpacing 'AdaptiveCards.AdaptiveSpacing')
  - [Default](#F-AdaptiveCards-AdaptiveSpacing-Default 'AdaptiveCards.AdaptiveSpacing.Default')
  - [ExtraLarge](#F-AdaptiveCards-AdaptiveSpacing-ExtraLarge 'AdaptiveCards.AdaptiveSpacing.ExtraLarge')
  - [Large](#F-AdaptiveCards-AdaptiveSpacing-Large 'AdaptiveCards.AdaptiveSpacing.Large')
  - [Medium](#F-AdaptiveCards-AdaptiveSpacing-Medium 'AdaptiveCards.AdaptiveSpacing.Medium')
  - [None](#F-AdaptiveCards-AdaptiveSpacing-None 'AdaptiveCards.AdaptiveSpacing.None')
  - [Padding](#F-AdaptiveCards-AdaptiveSpacing-Padding 'AdaptiveCards.AdaptiveSpacing.Padding')
  - [Small](#F-AdaptiveCards-AdaptiveSpacing-Small 'AdaptiveCards.AdaptiveSpacing.Small')
- [AdaptiveSubmitAction](#T-AdaptiveCards-AdaptiveSubmitAction 'AdaptiveCards.AdaptiveSubmitAction')
  - [TypeName](#F-AdaptiveCards-AdaptiveSubmitAction-TypeName 'AdaptiveCards.AdaptiveSubmitAction.TypeName')
  - [Data](#P-AdaptiveCards-AdaptiveSubmitAction-Data 'AdaptiveCards.AdaptiveSubmitAction.Data')
  - [DataJson](#P-AdaptiveCards-AdaptiveSubmitAction-DataJson 'AdaptiveCards.AdaptiveSubmitAction.DataJson')
  - [Type](#P-AdaptiveCards-AdaptiveSubmitAction-Type 'AdaptiveCards.AdaptiveSubmitAction.Type')
- [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement')
  - [#ctor()](#M-AdaptiveCards-AdaptiveTargetElement-#ctor 'AdaptiveCards.AdaptiveTargetElement.#ctor')
  - [#ctor(elementId)](#M-AdaptiveCards-AdaptiveTargetElement-#ctor-System-String- 'AdaptiveCards.AdaptiveTargetElement.#ctor(System.String)')
  - [#ctor(elementId,isVisible)](#M-AdaptiveCards-AdaptiveTargetElement-#ctor-System-String,System-Boolean- 'AdaptiveCards.AdaptiveTargetElement.#ctor(System.String,System.Boolean)')
  - [ElementId](#P-AdaptiveCards-AdaptiveTargetElement-ElementId 'AdaptiveCards.AdaptiveTargetElement.ElementId')
  - [IsVisible](#P-AdaptiveCards-AdaptiveTargetElement-IsVisible 'AdaptiveCards.AdaptiveTargetElement.IsVisible')
  - [IsVisibleXml](#P-AdaptiveCards-AdaptiveTargetElement-IsVisibleXml 'AdaptiveCards.AdaptiveTargetElement.IsVisibleXml')
  - [ShouldSerializeIsVisibleXml()](#M-AdaptiveCards-AdaptiveTargetElement-ShouldSerializeIsVisibleXml 'AdaptiveCards.AdaptiveTargetElement.ShouldSerializeIsVisibleXml')
  - [op_Implicit(elementId)](#M-AdaptiveCards-AdaptiveTargetElement-op_Implicit-System-String-~AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement.op_Implicit(System.String)~AdaptiveCards.AdaptiveTargetElement')
- [AdaptiveTextBlock](#T-AdaptiveCards-AdaptiveTextBlock 'AdaptiveCards.AdaptiveTextBlock')
  - [#ctor()](#M-AdaptiveCards-AdaptiveTextBlock-#ctor 'AdaptiveCards.AdaptiveTextBlock.#ctor')
  - [#ctor(text)](#M-AdaptiveCards-AdaptiveTextBlock-#ctor-System-String- 'AdaptiveCards.AdaptiveTextBlock.#ctor(System.String)')
  - [TypeName](#F-AdaptiveCards-AdaptiveTextBlock-TypeName 'AdaptiveCards.AdaptiveTextBlock.TypeName')
  - [Color](#P-AdaptiveCards-AdaptiveTextBlock-Color 'AdaptiveCards.AdaptiveTextBlock.Color')
  - [FontType](#P-AdaptiveCards-AdaptiveTextBlock-FontType 'AdaptiveCards.AdaptiveTextBlock.FontType')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveTextBlock-HorizontalAlignment 'AdaptiveCards.AdaptiveTextBlock.HorizontalAlignment')
  - [IsSubtle](#P-AdaptiveCards-AdaptiveTextBlock-IsSubtle 'AdaptiveCards.AdaptiveTextBlock.IsSubtle')
  - [Italic](#P-AdaptiveCards-AdaptiveTextBlock-Italic 'AdaptiveCards.AdaptiveTextBlock.Italic')
  - [MaxLines](#P-AdaptiveCards-AdaptiveTextBlock-MaxLines 'AdaptiveCards.AdaptiveTextBlock.MaxLines')
  - [MaxWidth](#P-AdaptiveCards-AdaptiveTextBlock-MaxWidth 'AdaptiveCards.AdaptiveTextBlock.MaxWidth')
  - [Size](#P-AdaptiveCards-AdaptiveTextBlock-Size 'AdaptiveCards.AdaptiveTextBlock.Size')
  - [Strikethrough](#P-AdaptiveCards-AdaptiveTextBlock-Strikethrough 'AdaptiveCards.AdaptiveTextBlock.Strikethrough')
  - [Text](#P-AdaptiveCards-AdaptiveTextBlock-Text 'AdaptiveCards.AdaptiveTextBlock.Text')
  - [Type](#P-AdaptiveCards-AdaptiveTextBlock-Type 'AdaptiveCards.AdaptiveTextBlock.Type')
  - [Weight](#P-AdaptiveCards-AdaptiveTextBlock-Weight 'AdaptiveCards.AdaptiveTextBlock.Weight')
  - [Wrap](#P-AdaptiveCards-AdaptiveTextBlock-Wrap 'AdaptiveCards.AdaptiveTextBlock.Wrap')
- [AdaptiveTextColor](#T-AdaptiveCards-AdaptiveTextColor 'AdaptiveCards.AdaptiveTextColor')
  - [Accent](#F-AdaptiveCards-AdaptiveTextColor-Accent 'AdaptiveCards.AdaptiveTextColor.Accent')
  - [Attention](#F-AdaptiveCards-AdaptiveTextColor-Attention 'AdaptiveCards.AdaptiveTextColor.Attention')
  - [Dark](#F-AdaptiveCards-AdaptiveTextColor-Dark 'AdaptiveCards.AdaptiveTextColor.Dark')
  - [Default](#F-AdaptiveCards-AdaptiveTextColor-Default 'AdaptiveCards.AdaptiveTextColor.Default')
  - [Good](#F-AdaptiveCards-AdaptiveTextColor-Good 'AdaptiveCards.AdaptiveTextColor.Good')
  - [Light](#F-AdaptiveCards-AdaptiveTextColor-Light 'AdaptiveCards.AdaptiveTextColor.Light')
  - [Warning](#F-AdaptiveCards-AdaptiveTextColor-Warning 'AdaptiveCards.AdaptiveTextColor.Warning')
- [AdaptiveTextInput](#T-AdaptiveCards-AdaptiveTextInput 'AdaptiveCards.AdaptiveTextInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveTextInput-TypeName 'AdaptiveCards.AdaptiveTextInput.TypeName')
  - [InlineAction](#P-AdaptiveCards-AdaptiveTextInput-InlineAction 'AdaptiveCards.AdaptiveTextInput.InlineAction')
  - [IsMultiline](#P-AdaptiveCards-AdaptiveTextInput-IsMultiline 'AdaptiveCards.AdaptiveTextInput.IsMultiline')
  - [MaxLength](#P-AdaptiveCards-AdaptiveTextInput-MaxLength 'AdaptiveCards.AdaptiveTextInput.MaxLength')
  - [Placeholder](#P-AdaptiveCards-AdaptiveTextInput-Placeholder 'AdaptiveCards.AdaptiveTextInput.Placeholder')
  - [Regex](#P-AdaptiveCards-AdaptiveTextInput-Regex 'AdaptiveCards.AdaptiveTextInput.Regex')
  - [Style](#P-AdaptiveCards-AdaptiveTextInput-Style 'AdaptiveCards.AdaptiveTextInput.Style')
  - [Type](#P-AdaptiveCards-AdaptiveTextInput-Type 'AdaptiveCards.AdaptiveTextInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveTextInput-Value 'AdaptiveCards.AdaptiveTextInput.Value')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveTextInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveTextInput.GetNonInteractiveValue')
- [AdaptiveTextInputStyle](#T-AdaptiveCards-AdaptiveTextInputStyle 'AdaptiveCards.AdaptiveTextInputStyle')
  - [Email](#F-AdaptiveCards-AdaptiveTextInputStyle-Email 'AdaptiveCards.AdaptiveTextInputStyle.Email')
  - [Tel](#F-AdaptiveCards-AdaptiveTextInputStyle-Tel 'AdaptiveCards.AdaptiveTextInputStyle.Tel')
  - [Text](#F-AdaptiveCards-AdaptiveTextInputStyle-Text 'AdaptiveCards.AdaptiveTextInputStyle.Text')
  - [Url](#F-AdaptiveCards-AdaptiveTextInputStyle-Url 'AdaptiveCards.AdaptiveTextInputStyle.Url')
- [AdaptiveTextRun](#T-AdaptiveCards-AdaptiveTextRun 'AdaptiveCards.AdaptiveTextRun')
  - [#ctor()](#M-AdaptiveCards-AdaptiveTextRun-#ctor 'AdaptiveCards.AdaptiveTextRun.#ctor')
  - [#ctor(text)](#M-AdaptiveCards-AdaptiveTextRun-#ctor-System-String- 'AdaptiveCards.AdaptiveTextRun.#ctor(System.String)')
  - [TypeName](#F-AdaptiveCards-AdaptiveTextRun-TypeName 'AdaptiveCards.AdaptiveTextRun.TypeName')
  - [Color](#P-AdaptiveCards-AdaptiveTextRun-Color 'AdaptiveCards.AdaptiveTextRun.Color')
  - [FontType](#P-AdaptiveCards-AdaptiveTextRun-FontType 'AdaptiveCards.AdaptiveTextRun.FontType')
  - [Highlight](#P-AdaptiveCards-AdaptiveTextRun-Highlight 'AdaptiveCards.AdaptiveTextRun.Highlight')
  - [IsSubtle](#P-AdaptiveCards-AdaptiveTextRun-IsSubtle 'AdaptiveCards.AdaptiveTextRun.IsSubtle')
  - [Italic](#P-AdaptiveCards-AdaptiveTextRun-Italic 'AdaptiveCards.AdaptiveTextRun.Italic')
  - [SelectAction](#P-AdaptiveCards-AdaptiveTextRun-SelectAction 'AdaptiveCards.AdaptiveTextRun.SelectAction')
  - [Size](#P-AdaptiveCards-AdaptiveTextRun-Size 'AdaptiveCards.AdaptiveTextRun.Size')
  - [Strikethrough](#P-AdaptiveCards-AdaptiveTextRun-Strikethrough 'AdaptiveCards.AdaptiveTextRun.Strikethrough')
  - [Text](#P-AdaptiveCards-AdaptiveTextRun-Text 'AdaptiveCards.AdaptiveTextRun.Text')
  - [Type](#P-AdaptiveCards-AdaptiveTextRun-Type 'AdaptiveCards.AdaptiveTextRun.Type')
  - [Underline](#P-AdaptiveCards-AdaptiveTextRun-Underline 'AdaptiveCards.AdaptiveTextRun.Underline')
  - [Weight](#P-AdaptiveCards-AdaptiveTextRun-Weight 'AdaptiveCards.AdaptiveTextRun.Weight')
- [AdaptiveTextSize](#T-AdaptiveCards-AdaptiveTextSize 'AdaptiveCards.AdaptiveTextSize')
  - [Default](#F-AdaptiveCards-AdaptiveTextSize-Default 'AdaptiveCards.AdaptiveTextSize.Default')
  - [ExtraLarge](#F-AdaptiveCards-AdaptiveTextSize-ExtraLarge 'AdaptiveCards.AdaptiveTextSize.ExtraLarge')
  - [Large](#F-AdaptiveCards-AdaptiveTextSize-Large 'AdaptiveCards.AdaptiveTextSize.Large')
  - [Medium](#F-AdaptiveCards-AdaptiveTextSize-Medium 'AdaptiveCards.AdaptiveTextSize.Medium')
  - [Normal](#F-AdaptiveCards-AdaptiveTextSize-Normal 'AdaptiveCards.AdaptiveTextSize.Normal')
  - [Small](#F-AdaptiveCards-AdaptiveTextSize-Small 'AdaptiveCards.AdaptiveTextSize.Small')
- [AdaptiveTextWeight](#T-AdaptiveCards-AdaptiveTextWeight 'AdaptiveCards.AdaptiveTextWeight')
  - [Bolder](#F-AdaptiveCards-AdaptiveTextWeight-Bolder 'AdaptiveCards.AdaptiveTextWeight.Bolder')
  - [Default](#F-AdaptiveCards-AdaptiveTextWeight-Default 'AdaptiveCards.AdaptiveTextWeight.Default')
  - [Lighter](#F-AdaptiveCards-AdaptiveTextWeight-Lighter 'AdaptiveCards.AdaptiveTextWeight.Lighter')
  - [Normal](#F-AdaptiveCards-AdaptiveTextWeight-Normal 'AdaptiveCards.AdaptiveTextWeight.Normal')
- [AdaptiveTimeInput](#T-AdaptiveCards-AdaptiveTimeInput 'AdaptiveCards.AdaptiveTimeInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveTimeInput-TypeName 'AdaptiveCards.AdaptiveTimeInput.TypeName')
  - [Max](#P-AdaptiveCards-AdaptiveTimeInput-Max 'AdaptiveCards.AdaptiveTimeInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveTimeInput-Min 'AdaptiveCards.AdaptiveTimeInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveTimeInput-Placeholder 'AdaptiveCards.AdaptiveTimeInput.Placeholder')
  - [Type](#P-AdaptiveCards-AdaptiveTimeInput-Type 'AdaptiveCards.AdaptiveTimeInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveTimeInput-Value 'AdaptiveCards.AdaptiveTimeInput.Value')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveTimeInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveTimeInput.GetNonInteractiveValue')
- [AdaptiveToggleInput](#T-AdaptiveCards-AdaptiveToggleInput 'AdaptiveCards.AdaptiveToggleInput')
  - [TypeName](#F-AdaptiveCards-AdaptiveToggleInput-TypeName 'AdaptiveCards.AdaptiveToggleInput.TypeName')
  - [Title](#P-AdaptiveCards-AdaptiveToggleInput-Title 'AdaptiveCards.AdaptiveToggleInput.Title')
  - [Type](#P-AdaptiveCards-AdaptiveToggleInput-Type 'AdaptiveCards.AdaptiveToggleInput.Type')
  - [Value](#P-AdaptiveCards-AdaptiveToggleInput-Value 'AdaptiveCards.AdaptiveToggleInput.Value')
  - [ValueOff](#P-AdaptiveCards-AdaptiveToggleInput-ValueOff 'AdaptiveCards.AdaptiveToggleInput.ValueOff')
  - [ValueOn](#P-AdaptiveCards-AdaptiveToggleInput-ValueOn 'AdaptiveCards.AdaptiveToggleInput.ValueOn')
  - [Wrap](#P-AdaptiveCards-AdaptiveToggleInput-Wrap 'AdaptiveCards.AdaptiveToggleInput.Wrap')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveToggleInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveToggleInput.GetNonInteractiveValue')
- [AdaptiveToggleVisibilityAction](#T-AdaptiveCards-AdaptiveToggleVisibilityAction 'AdaptiveCards.AdaptiveToggleVisibilityAction')
  - [TypeName](#F-AdaptiveCards-AdaptiveToggleVisibilityAction-TypeName 'AdaptiveCards.AdaptiveToggleVisibilityAction.TypeName')
  - [TargetElements](#P-AdaptiveCards-AdaptiveToggleVisibilityAction-TargetElements 'AdaptiveCards.AdaptiveToggleVisibilityAction.TargetElements')
  - [Type](#P-AdaptiveCards-AdaptiveToggleVisibilityAction-Type 'AdaptiveCards.AdaptiveToggleVisibilityAction.Type')
- [AdaptiveTypedBaseElementConverter](#T-AdaptiveCards-AdaptiveTypedBaseElementConverter 'AdaptiveCards.AdaptiveTypedBaseElementConverter')
  - [ParseContext](#P-AdaptiveCards-AdaptiveTypedBaseElementConverter-ParseContext 'AdaptiveCards.AdaptiveTypedBaseElementConverter.ParseContext')
- [AdaptiveTypedElement](#T-AdaptiveCards-AdaptiveTypedElement 'AdaptiveCards.AdaptiveTypedElement')
  - [Requires](#F-AdaptiveCards-AdaptiveTypedElement-Requires 'AdaptiveCards.AdaptiveTypedElement.Requires')
  - [AdditionalProperties](#P-AdaptiveCards-AdaptiveTypedElement-AdditionalProperties 'AdaptiveCards.AdaptiveTypedElement.AdditionalProperties')
  - [Fallback](#P-AdaptiveCards-AdaptiveTypedElement-Fallback 'AdaptiveCards.AdaptiveTypedElement.Fallback')
  - [Id](#P-AdaptiveCards-AdaptiveTypedElement-Id 'AdaptiveCards.AdaptiveTypedElement.Id')
  - [InternalID](#P-AdaptiveCards-AdaptiveTypedElement-InternalID 'AdaptiveCards.AdaptiveTypedElement.InternalID')
  - [Type](#P-AdaptiveCards-AdaptiveTypedElement-Type 'AdaptiveCards.AdaptiveTypedElement.Type')
  - [MeetsRequirements(featureRegistration)](#M-AdaptiveCards-AdaptiveTypedElement-MeetsRequirements-AdaptiveCards-AdaptiveFeatureRegistration- 'AdaptiveCards.AdaptiveTypedElement.MeetsRequirements(AdaptiveCards.AdaptiveFeatureRegistration)')
  - [ShouldSerializeAdditionalProperties()](#M-AdaptiveCards-AdaptiveTypedElement-ShouldSerializeAdditionalProperties 'AdaptiveCards.AdaptiveTypedElement.ShouldSerializeAdditionalProperties')
- [AdaptiveTypedElementConverter](#T-AdaptiveCards-AdaptiveTypedElementConverter 'AdaptiveCards.AdaptiveTypedElementConverter')
  - [TypedElementTypes](#F-AdaptiveCards-AdaptiveTypedElementConverter-TypedElementTypes 'AdaptiveCards.AdaptiveTypedElementConverter.TypedElementTypes')
  - [CanRead](#P-AdaptiveCards-AdaptiveTypedElementConverter-CanRead 'AdaptiveCards.AdaptiveTypedElementConverter.CanRead')
  - [CanWrite](#P-AdaptiveCards-AdaptiveTypedElementConverter-CanWrite 'AdaptiveCards.AdaptiveTypedElementConverter.CanWrite')
  - [Warnings](#P-AdaptiveCards-AdaptiveTypedElementConverter-Warnings 'AdaptiveCards.AdaptiveTypedElementConverter.Warnings')
  - [CanConvert()](#M-AdaptiveCards-AdaptiveTypedElementConverter-CanConvert-System-Type- 'AdaptiveCards.AdaptiveTypedElementConverter.CanConvert(System.Type)')
  - [CreateElement\`\`1()](#M-AdaptiveCards-AdaptiveTypedElementConverter-CreateElement``1-System-String- 'AdaptiveCards.AdaptiveTypedElementConverter.CreateElement``1(System.String)')
  - [GetElementTypeName()](#M-AdaptiveCards-AdaptiveTypedElementConverter-GetElementTypeName-System-Type,Newtonsoft-Json-Linq-JObject- 'AdaptiveCards.AdaptiveTypedElementConverter.GetElementTypeName(System.Type,Newtonsoft.Json.Linq.JObject)')
  - [ReadJson()](#M-AdaptiveCards-AdaptiveTypedElementConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveTypedElementConverter.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [RegisterTypedElement\`\`1(typeName)](#M-AdaptiveCards-AdaptiveTypedElementConverter-RegisterTypedElement``1-System-String- 'AdaptiveCards.AdaptiveTypedElementConverter.RegisterTypedElement``1(System.String)')
  - [WriteJson()](#M-AdaptiveCards-AdaptiveTypedElementConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.AdaptiveTypedElementConverter.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [AdaptiveUnknownAction](#T-AdaptiveCards-AdaptiveUnknownAction 'AdaptiveCards.AdaptiveUnknownAction')
  - [Type](#P-AdaptiveCards-AdaptiveUnknownAction-Type 'AdaptiveCards.AdaptiveUnknownAction.Type')
- [AdaptiveUnknownElement](#T-AdaptiveCards-AdaptiveUnknownElement 'AdaptiveCards.AdaptiveUnknownElement')
  - [Type](#P-AdaptiveCards-AdaptiveUnknownElement-Type 'AdaptiveCards.AdaptiveUnknownElement.Type')
- [AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment')
  - [Bottom](#F-AdaptiveCards-AdaptiveVerticalAlignment-Bottom 'AdaptiveCards.AdaptiveVerticalAlignment.Bottom')
  - [Center](#F-AdaptiveCards-AdaptiveVerticalAlignment-Center 'AdaptiveCards.AdaptiveVerticalAlignment.Center')
  - [Top](#F-AdaptiveCards-AdaptiveVerticalAlignment-Top 'AdaptiveCards.AdaptiveVerticalAlignment.Top')
- [AdaptiveVerticalContentAlignment](#T-AdaptiveCards-AdaptiveVerticalContentAlignment 'AdaptiveCards.AdaptiveVerticalContentAlignment')
  - [Bottom](#F-AdaptiveCards-AdaptiveVerticalContentAlignment-Bottom 'AdaptiveCards.AdaptiveVerticalContentAlignment.Bottom')
  - [Center](#F-AdaptiveCards-AdaptiveVerticalContentAlignment-Center 'AdaptiveCards.AdaptiveVerticalContentAlignment.Center')
  - [Top](#F-AdaptiveCards-AdaptiveVerticalContentAlignment-Top 'AdaptiveCards.AdaptiveVerticalContentAlignment.Top')
- [AdaptiveVisitor](#T-AdaptiveCards-Rendering-AdaptiveVisitor 'AdaptiveCards.Rendering.AdaptiveVisitor')
- [AdaptiveWarning](#T-AdaptiveCards-AdaptiveWarning 'AdaptiveCards.AdaptiveWarning')
  - [#ctor(code,message)](#M-AdaptiveCards-AdaptiveWarning-#ctor-System-Int32,System-String- 'AdaptiveCards.AdaptiveWarning.#ctor(System.Int32,System.String)')
  - [Code](#P-AdaptiveCards-AdaptiveWarning-Code 'AdaptiveCards.AdaptiveWarning.Code')
  - [Message](#P-AdaptiveCards-AdaptiveWarning-Message 'AdaptiveCards.AdaptiveWarning.Message')
- [ColorUtil](#T-AdaptiveCards-ColorUtil 'AdaptiveCards.ColorUtil')
  - [alphaColorLength](#F-AdaptiveCards-ColorUtil-alphaColorLength 'AdaptiveCards.ColorUtil.alphaColorLength')
  - [colorStringLength](#F-AdaptiveCards-ColorUtil-colorStringLength 'AdaptiveCards.ColorUtil.colorStringLength')
  - [GenerateLighterColor(hexColor)](#M-AdaptiveCards-ColorUtil-GenerateLighterColor-System-String- 'AdaptiveCards.ColorUtil.GenerateLighterColor(System.String)')
  - [IsValidColor(color)](#M-AdaptiveCards-ColorUtil-IsValidColor-System-String- 'AdaptiveCards.ColorUtil.IsValidColor(System.String)')
  - [TryParseColor(color,result)](#M-AdaptiveCards-ColorUtil-TryParseColor-System-String,System-Int32@- 'AdaptiveCards.ColorUtil.TryParseColor(System.String,System.Int32@)')
- [ContainerStyleConfig](#T-AdaptiveCards-Rendering-ContainerStyleConfig 'AdaptiveCards.Rendering.ContainerStyleConfig')
  - [BackgroundColor](#P-AdaptiveCards-Rendering-ContainerStyleConfig-BackgroundColor 'AdaptiveCards.Rendering.ContainerStyleConfig.BackgroundColor')
  - [ForegroundColors](#P-AdaptiveCards-Rendering-ContainerStyleConfig-ForegroundColors 'AdaptiveCards.Rendering.ContainerStyleConfig.ForegroundColors')
- [ContextType](#T-AdaptiveCards-ParseContext-ContextType 'AdaptiveCards.ParseContext.ContextType')
  - [Action](#F-AdaptiveCards-ParseContext-ContextType-Action 'AdaptiveCards.ParseContext.ContextType.Action')
  - [Element](#F-AdaptiveCards-ParseContext-ContextType-Element 'AdaptiveCards.ParseContext.ContextType.Element')
- [ErrorMessageConfig](#T-AdaptiveCards-Rendering-ErrorMessageConfig 'AdaptiveCards.Rendering.ErrorMessageConfig')
  - [Size](#P-AdaptiveCards-Rendering-ErrorMessageConfig-Size 'AdaptiveCards.Rendering.ErrorMessageConfig.Size')
  - [Spacing](#P-AdaptiveCards-Rendering-ErrorMessageConfig-Spacing 'AdaptiveCards.Rendering.ErrorMessageConfig.Spacing')
  - [Weight](#P-AdaptiveCards-Rendering-ErrorMessageConfig-Weight 'AdaptiveCards.Rendering.ErrorMessageConfig.Weight')
- [FactSetConfig](#T-AdaptiveCards-Rendering-FactSetConfig 'AdaptiveCards.Rendering.FactSetConfig')
  - [Spacing](#P-AdaptiveCards-Rendering-FactSetConfig-Spacing 'AdaptiveCards.Rendering.FactSetConfig.Spacing')
  - [Title](#P-AdaptiveCards-Rendering-FactSetConfig-Title 'AdaptiveCards.Rendering.FactSetConfig.Title')
  - [Value](#P-AdaptiveCards-Rendering-FactSetConfig-Value 'AdaptiveCards.Rendering.FactSetConfig.Value')
- [FontColorConfig](#T-AdaptiveCards-Rendering-FontColorConfig 'AdaptiveCards.Rendering.FontColorConfig')
  - [Default](#P-AdaptiveCards-Rendering-FontColorConfig-Default 'AdaptiveCards.Rendering.FontColorConfig.Default')
- [HashColorConverter](#T-AdaptiveCards-HashColorConverter 'AdaptiveCards.HashColorConverter')
  - [CanWrite](#P-AdaptiveCards-HashColorConverter-CanWrite 'AdaptiveCards.HashColorConverter.CanWrite')
  - [Warnings](#P-AdaptiveCards-HashColorConverter-Warnings 'AdaptiveCards.HashColorConverter.Warnings')
  - [CanConvert()](#M-AdaptiveCards-HashColorConverter-CanConvert-System-Type- 'AdaptiveCards.HashColorConverter.CanConvert(System.Type)')
  - [ReadJson()](#M-AdaptiveCards-HashColorConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.HashColorConverter.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson()](#M-AdaptiveCards-HashColorConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.HashColorConverter.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [HighlightColorConfig](#T-AdaptiveCards-Rendering-HighlightColorConfig 'AdaptiveCards.Rendering.HighlightColorConfig')
  - [Default](#P-AdaptiveCards-Rendering-HighlightColorConfig-Default 'AdaptiveCards.Rendering.HighlightColorConfig.Default')
- [IAdaptiveTextElement](#T-AdaptiveCards-IAdaptiveTextElement 'AdaptiveCards.IAdaptiveTextElement')
  - [Color](#P-AdaptiveCards-IAdaptiveTextElement-Color 'AdaptiveCards.IAdaptiveTextElement.Color')
  - [FontType](#P-AdaptiveCards-IAdaptiveTextElement-FontType 'AdaptiveCards.IAdaptiveTextElement.FontType')
  - [IsSubtle](#P-AdaptiveCards-IAdaptiveTextElement-IsSubtle 'AdaptiveCards.IAdaptiveTextElement.IsSubtle')
  - [Italic](#P-AdaptiveCards-IAdaptiveTextElement-Italic 'AdaptiveCards.IAdaptiveTextElement.Italic')
  - [Size](#P-AdaptiveCards-IAdaptiveTextElement-Size 'AdaptiveCards.IAdaptiveTextElement.Size')
  - [Strikethrough](#P-AdaptiveCards-IAdaptiveTextElement-Strikethrough 'AdaptiveCards.IAdaptiveTextElement.Strikethrough')
  - [Text](#P-AdaptiveCards-IAdaptiveTextElement-Text 'AdaptiveCards.IAdaptiveTextElement.Text')
  - [Weight](#P-AdaptiveCards-IAdaptiveTextElement-Weight 'AdaptiveCards.IAdaptiveTextElement.Weight')
- [IconPlacement](#T-AdaptiveCards-Rendering-IconPlacement 'AdaptiveCards.Rendering.IconPlacement')
  - [AboveTitle](#F-AdaptiveCards-Rendering-IconPlacement-AboveTitle 'AdaptiveCards.Rendering.IconPlacement.AboveTitle')
  - [LeftOfTitle](#F-AdaptiveCards-Rendering-IconPlacement-LeftOfTitle 'AdaptiveCards.Rendering.IconPlacement.LeftOfTitle')
- [IgnoreEmptyItemsConverter\`1](#T-AdaptiveCards-IgnoreEmptyItemsConverter`1 'AdaptiveCards.IgnoreEmptyItemsConverter`1')
  - [CanWrite](#P-AdaptiveCards-IgnoreEmptyItemsConverter`1-CanWrite 'AdaptiveCards.IgnoreEmptyItemsConverter`1.CanWrite')
  - [CanConvert()](#M-AdaptiveCards-IgnoreEmptyItemsConverter`1-CanConvert-System-Type- 'AdaptiveCards.IgnoreEmptyItemsConverter`1.CanConvert(System.Type)')
  - [ReadJson()](#M-AdaptiveCards-IgnoreEmptyItemsConverter`1-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.IgnoreEmptyItemsConverter`1.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson()](#M-AdaptiveCards-IgnoreEmptyItemsConverter`1-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.IgnoreEmptyItemsConverter`1.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [IgnoreNullEnumConverter\`1](#T-AdaptiveCards-IgnoreNullEnumConverter`1 'AdaptiveCards.IgnoreNullEnumConverter`1')
  - [#ctor()](#M-AdaptiveCards-IgnoreNullEnumConverter`1-#ctor 'AdaptiveCards.IgnoreNullEnumConverter`1.#ctor')
  - [#ctor()](#M-AdaptiveCards-IgnoreNullEnumConverter`1-#ctor-System-Boolean- 'AdaptiveCards.IgnoreNullEnumConverter`1.#ctor(System.Boolean)')
  - [Warnings](#P-AdaptiveCards-IgnoreNullEnumConverter`1-Warnings 'AdaptiveCards.IgnoreNullEnumConverter`1.Warnings')
  - [ReadJson()](#M-AdaptiveCards-IgnoreNullEnumConverter`1-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.IgnoreNullEnumConverter`1.ReadJson(Newtonsoft.Json.JsonReader,System.Type,System.Object,Newtonsoft.Json.JsonSerializer)')
  - [WriteJson()](#M-AdaptiveCards-IgnoreNullEnumConverter`1-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer- 'AdaptiveCards.IgnoreNullEnumConverter`1.WriteJson(Newtonsoft.Json.JsonWriter,System.Object,Newtonsoft.Json.JsonSerializer)')
- [InputLabelConfig](#T-AdaptiveCards-Rendering-InputLabelConfig 'AdaptiveCards.Rendering.InputLabelConfig')
  - [Color](#P-AdaptiveCards-Rendering-InputLabelConfig-Color 'AdaptiveCards.Rendering.InputLabelConfig.Color')
  - [IsSubtle](#P-AdaptiveCards-Rendering-InputLabelConfig-IsSubtle 'AdaptiveCards.Rendering.InputLabelConfig.IsSubtle')
  - [Size](#P-AdaptiveCards-Rendering-InputLabelConfig-Size 'AdaptiveCards.Rendering.InputLabelConfig.Size')
  - [Suffix](#P-AdaptiveCards-Rendering-InputLabelConfig-Suffix 'AdaptiveCards.Rendering.InputLabelConfig.Suffix')
  - [Weight](#P-AdaptiveCards-Rendering-InputLabelConfig-Weight 'AdaptiveCards.Rendering.InputLabelConfig.Weight')
- [InputsConfig](#T-AdaptiveCards-Rendering-InputsConfig 'AdaptiveCards.Rendering.InputsConfig')
- [JsonExtensions](#T-AdaptiveCards-JsonExtensions 'AdaptiveCards.JsonExtensions')
  - [IsHexDigit(c)](#M-AdaptiveCards-JsonExtensions-IsHexDigit-System-Char- 'AdaptiveCards.JsonExtensions.IsHexDigit(System.Char)')
- [LabelConfig](#T-AdaptiveCards-Rendering-LabelConfig 'AdaptiveCards.Rendering.LabelConfig')
  - [InputSpacing](#P-AdaptiveCards-Rendering-LabelConfig-InputSpacing 'AdaptiveCards.Rendering.LabelConfig.InputSpacing')
- [MediaConfig](#T-AdaptiveCards-Rendering-MediaConfig 'AdaptiveCards.Rendering.MediaConfig')
  - [AllowInlinePlayback](#P-AdaptiveCards-Rendering-MediaConfig-AllowInlinePlayback 'AdaptiveCards.Rendering.MediaConfig.AllowInlinePlayback')
  - [DefaultPoster](#P-AdaptiveCards-Rendering-MediaConfig-DefaultPoster 'AdaptiveCards.Rendering.MediaConfig.DefaultPoster')
  - [PlayButton](#P-AdaptiveCards-Rendering-MediaConfig-PlayButton 'AdaptiveCards.Rendering.MediaConfig.PlayButton')
- [ParseContext](#T-AdaptiveCards-ParseContext 'AdaptiveCards.ParseContext')
  - [Type](#P-AdaptiveCards-ParseContext-Type 'AdaptiveCards.ParseContext.Type')
  - [GetNearestFallbackID(skipID)](#M-AdaptiveCards-ParseContext-GetNearestFallbackID-AdaptiveCards-AdaptiveInternalID- 'AdaptiveCards.ParseContext.GetNearestFallbackID(AdaptiveCards.AdaptiveInternalID)')
  - [PopElement()](#M-AdaptiveCards-ParseContext-PopElement 'AdaptiveCards.ParseContext.PopElement')
  - [PushElement(idJsonProperty,internalId)](#M-AdaptiveCards-ParseContext-PushElement-System-String,AdaptiveCards-AdaptiveInternalID- 'AdaptiveCards.ParseContext.PushElement(System.String,AdaptiveCards.AdaptiveInternalID)')
- [RemoteResourceInformation](#T-AdaptiveCards-RemoteResourceInformation 'AdaptiveCards.RemoteResourceInformation')
  - [#ctor(url,mimeType)](#M-AdaptiveCards-RemoteResourceInformation-#ctor-System-String,System-String- 'AdaptiveCards.RemoteResourceInformation.#ctor(System.String,System.String)')
- [RenderedAdaptiveCardBase](#T-AdaptiveCards-Rendering-RenderedAdaptiveCardBase 'AdaptiveCards.Rendering.RenderedAdaptiveCardBase')
  - [OriginatingCard](#P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-OriginatingCard 'AdaptiveCards.Rendering.RenderedAdaptiveCardBase.OriginatingCard')
  - [UserInputs](#P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-UserInputs 'AdaptiveCards.Rendering.RenderedAdaptiveCardBase.UserInputs')
  - [Warnings](#P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-Warnings 'AdaptiveCards.Rendering.RenderedAdaptiveCardBase.Warnings')
- [RenderedAdaptiveCardInputs](#T-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs 'AdaptiveCards.Rendering.RenderedAdaptiveCardInputs')
  - [AsDictionary()](#M-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs-AsDictionary 'AdaptiveCards.Rendering.RenderedAdaptiveCardInputs.AsDictionary')
  - [AsJson()](#M-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs-AsJson 'AdaptiveCards.Rendering.RenderedAdaptiveCardInputs.AsJson')
- [RendererUtilities](#T-AdaptiveCards-Rendering-RendererUtilities 'AdaptiveCards.Rendering.RendererUtilities')
  - [ApplyTextFunctions(text)](#M-AdaptiveCards-Rendering-RendererUtilities-ApplyTextFunctions-System-String,System-String- 'AdaptiveCards.Rendering.RendererUtilities.ApplyTextFunctions(System.String,System.String)')
- [SeparatorConfig](#T-AdaptiveCards-Rendering-SeparatorConfig 'AdaptiveCards.Rendering.SeparatorConfig')
  - [LineColor](#P-AdaptiveCards-Rendering-SeparatorConfig-LineColor 'AdaptiveCards.Rendering.SeparatorConfig.LineColor')
  - [LineThickness](#P-AdaptiveCards-Rendering-SeparatorConfig-LineThickness 'AdaptiveCards.Rendering.SeparatorConfig.LineThickness')
- [ShowCardActionMode](#T-AdaptiveCards-Rendering-ShowCardActionMode 'AdaptiveCards.Rendering.ShowCardActionMode')
  - [Inline](#F-AdaptiveCards-Rendering-ShowCardActionMode-Inline 'AdaptiveCards.Rendering.ShowCardActionMode.Inline')
  - [Popup](#F-AdaptiveCards-Rendering-ShowCardActionMode-Popup 'AdaptiveCards.Rendering.ShowCardActionMode.Popup')
- [ShowCardConfig](#T-AdaptiveCards-Rendering-ShowCardConfig 'AdaptiveCards.Rendering.ShowCardConfig')
  - [#ctor()](#M-AdaptiveCards-Rendering-ShowCardConfig-#ctor 'AdaptiveCards.Rendering.ShowCardConfig.#ctor')
  - [ActionMode](#P-AdaptiveCards-Rendering-ShowCardConfig-ActionMode 'AdaptiveCards.Rendering.ShowCardConfig.ActionMode')
  - [InlineTopMargin](#P-AdaptiveCards-Rendering-ShowCardConfig-InlineTopMargin 'AdaptiveCards.Rendering.ShowCardConfig.InlineTopMargin')
  - [Style](#P-AdaptiveCards-Rendering-ShowCardConfig-Style 'AdaptiveCards.Rendering.ShowCardConfig.Style')
- [SpacingsConfig](#T-AdaptiveCards-Rendering-SpacingsConfig 'AdaptiveCards.Rendering.SpacingsConfig')
- [TextBlockConfig](#T-AdaptiveCards-Rendering-TextBlockConfig 'AdaptiveCards.Rendering.TextBlockConfig')
  - [Color](#P-AdaptiveCards-Rendering-TextBlockConfig-Color 'AdaptiveCards.Rendering.TextBlockConfig.Color')
  - [IsSubtle](#P-AdaptiveCards-Rendering-TextBlockConfig-IsSubtle 'AdaptiveCards.Rendering.TextBlockConfig.IsSubtle')
  - [MaxWidth](#P-AdaptiveCards-Rendering-TextBlockConfig-MaxWidth 'AdaptiveCards.Rendering.TextBlockConfig.MaxWidth')
  - [Size](#P-AdaptiveCards-Rendering-TextBlockConfig-Size 'AdaptiveCards.Rendering.TextBlockConfig.Size')
  - [Weight](#P-AdaptiveCards-Rendering-TextBlockConfig-Weight 'AdaptiveCards.Rendering.TextBlockConfig.Weight')
  - [Wrap](#P-AdaptiveCards-Rendering-TextBlockConfig-Wrap 'AdaptiveCards.Rendering.TextBlockConfig.Wrap')
- [WarningLoggingContractResolver](#T-AdaptiveCards-WarningLoggingContractResolver 'AdaptiveCards.WarningLoggingContractResolver')
  - [CreateProperty(member,memberSerialization)](#M-AdaptiveCards-WarningLoggingContractResolver-CreateProperty-System-Reflection-MemberInfo,Newtonsoft-Json-MemberSerialization- 'AdaptiveCards.WarningLoggingContractResolver.CreateProperty(System.Reflection.MemberInfo,Newtonsoft.Json.MemberSerialization)')
- [WarningStatusCode](#T-AdaptiveCards-AdaptiveWarning-WarningStatusCode 'AdaptiveCards.AdaptiveWarning.WarningStatusCode')
  - [EmptyLabelInRequiredInput](#F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-EmptyLabelInRequiredInput 'AdaptiveCards.AdaptiveWarning.WarningStatusCode.EmptyLabelInRequiredInput')
  - [InvalidLanguage](#F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-InvalidLanguage 'AdaptiveCards.AdaptiveWarning.WarningStatusCode.InvalidLanguage')
  - [MaxActionsExceeded](#F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-MaxActionsExceeded 'AdaptiveCards.AdaptiveWarning.WarningStatusCode.MaxActionsExceeded')
  - [UnsupportedSchemaVersion](#F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-UnsupportedSchemaVersion 'AdaptiveCards.AdaptiveWarning.WarningStatusCode.UnsupportedSchemaVersion')

<a name='T-AdaptiveCards-Rendering-ActionsConfig'></a>
## ActionsConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering and behavior of actions.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ActionAlignment'></a>
### ActionAlignment `property`

##### Summary

Control horizontal alignment behavior.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ActionsOrientation'></a>
### ActionsOrientation `property`

##### Summary

Arrange actions horizontally or vertically.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ButtonSpacing'></a>
### ButtonSpacing `property`

##### Summary

Controls the amount of space between actions.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-IconPlacement'></a>
### IconPlacement `property`

##### Summary

Controls where action icons are placed relative to titles.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-IconSize'></a>
### IconSize `property`

##### Summary

Defines the size at which to render icons.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-MaxActions'></a>
### MaxActions `property`

##### Summary

Max number of actions to allow in parsed cards.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ShowCard'></a>
### ShowCard `property`

##### Summary

Controls the behavior of Action.ShowCard.

<a name='P-AdaptiveCards-Rendering-ActionsConfig-Spacing'></a>
### Spacing `property`

##### Summary

Controls spacing between card elements.

<a name='T-AdaptiveCards-Rendering-ActionsOrientation'></a>
## ActionsOrientation `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Controls the layout of actions.

<a name='F-AdaptiveCards-Rendering-ActionsOrientation-Horizontal'></a>
### Horizontal `constants`

##### Summary

Actions should be laid out horizontally.

<a name='F-AdaptiveCards-Rendering-ActionsOrientation-Vertical'></a>
### Vertical `constants`

##### Summary

Actions should be laid out vertically.

<a name='T-AdaptiveCards-AdaptiveAction'></a>
## AdaptiveAction `type`

##### Namespace

AdaptiveCards

##### Summary

Base of Action types

<a name='P-AdaptiveCards-AdaptiveAction-IconUrl'></a>
### IconUrl `property`

##### Summary

IconUrl that can be specified for actions

<a name='P-AdaptiveCards-AdaptiveAction-Speak'></a>
### Speak `property`

##### Summary

Speak phrase for this action

<a name='P-AdaptiveCards-AdaptiveAction-Style'></a>
### Style `property`

##### Summary

Style that can be specified for actions

<a name='P-AdaptiveCards-AdaptiveAction-Title'></a>
### Title `property`

##### Summary

Title of the action

<a name='T-AdaptiveCards-Rendering-AdaptiveActionHandlers'></a>
## AdaptiveActionHandlers `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

A collection of actions known by the host.

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-AddSupportedAction``1'></a>
### AddSupportedAction\`\`1() `method`

##### Summary

Adds a given action type. Any action in a payload not specified here will be dropped from the rendered card.

##### Parameters

This method has no parameters.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TAction | The type of the action to add. |

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-IsSupported-System-Type-'></a>
### IsSupported(type) `method`

##### Summary

Determines whether or not the action is supported by the renderer.

##### Returns

true iff the Type is supported.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| type | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | The Type for which to determine support. |

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-RemoveSupportedAction``1'></a>
### RemoveSupportedAction\`\`1() `method`

##### Summary

Remove support for an action type. This will prevent these actions from appearing in the rendered card.

##### Parameters

This method has no parameters.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TAction | The type of the action to remove. |

<a name='T-AdaptiveCards-AdaptiveActionSet'></a>
## AdaptiveActionSet `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the ActionSet element.

<a name='F-AdaptiveCards-AdaptiveActionSet-TypeName'></a>
### TypeName `constants`

##### Summary

The AdaptiveCard element that this class implements.

<a name='P-AdaptiveCards-AdaptiveActionSet-Actions'></a>
### Actions `property`

##### Summary

The actions contained within this ActionSet.

<a name='P-AdaptiveCards-AdaptiveActionSet-Type'></a>
### Type `property`

##### Summary

The JSON property name that this class implements.

<a name='T-AdaptiveCards-AdaptiveBackgroundImage'></a>
## AdaptiveBackgroundImage `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the backgroundImage property

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes a new AdaptiveBackgroundImage instance.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-String-'></a>
### #ctor(url) `constructor`

##### Summary

Initializes a new AdaptiveBackgroundImage instance using the specified URL.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The background image URL expressed as a string. |

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-Uri-'></a>
### #ctor(url) `constructor`

##### Summary

Initializes a new AdaptiveBackgroundImage instance using the specified URL.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.Uri](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri 'System.Uri') | The background image URL represented as a Uri object. |

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-String,AdaptiveCards-AdaptiveImageFillMode,AdaptiveCards-AdaptiveHorizontalAlignment,AdaptiveCards-AdaptiveVerticalAlignment-'></a>
### #ctor(url,fillMode,hAlignment,vAlignment) `constructor`

##### Summary

Initializes a new AdaptiveBackgroundImage instance using the specified parameters.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The background image URL expressed as a string. |
| fillMode | [AdaptiveCards.AdaptiveImageFillMode](#T-AdaptiveCards-AdaptiveImageFillMode 'AdaptiveCards.AdaptiveImageFillMode') | Controls how the background image should be displayed. |
| hAlignment | [AdaptiveCards.AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') | Controls horizontal alignment. |
| vAlignment | [AdaptiveCards.AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment') | Controls vertical alignment. |

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-#ctor-System-Uri,AdaptiveCards-AdaptiveImageFillMode,AdaptiveCards-AdaptiveHorizontalAlignment,AdaptiveCards-AdaptiveVerticalAlignment-'></a>
### #ctor(url,fillMode,hAlignment,vAlignment) `constructor`

##### Summary

Initializes a new AdaptiveBackgroundImage instance using the specified parameters.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.Uri](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri 'System.Uri') | The background image URL represented as a Uri object. |
| fillMode | [AdaptiveCards.AdaptiveImageFillMode](#T-AdaptiveCards-AdaptiveImageFillMode 'AdaptiveCards.AdaptiveImageFillMode') | Controls how the background image should be displayed. |
| hAlignment | [AdaptiveCards.AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') | Controls horizontal alignment. |
| vAlignment | [AdaptiveCards.AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment') | Controls vertical alignment. |

<a name='F-AdaptiveCards-AdaptiveBackgroundImage-TypeName'></a>
### TypeName `constants`

##### Summary

The JSON property name that this class implements.

<a name='P-AdaptiveCards-AdaptiveBackgroundImage-FillMode'></a>
### FillMode `property`

##### Summary

Controls how the image is tiled or stretched.

<a name='P-AdaptiveCards-AdaptiveBackgroundImage-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Determines how to align the background image horizontally.

<a name='P-AdaptiveCards-AdaptiveBackgroundImage-Url'></a>
### Url `property`

##### Summary

The Url of the background image.

<a name='P-AdaptiveCards-AdaptiveBackgroundImage-UrlString'></a>
### UrlString `property`

##### Summary

The Url of the background image as a string.

<a name='P-AdaptiveCards-AdaptiveBackgroundImage-VerticalAlignment'></a>
### VerticalAlignment `property`

##### Summary

Determines how to align the background image vertically.

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-HasDefaultValues'></a>
### HasDefaultValues() `method`

##### Summary

Determines if this instance only has default property values set (aside from [Url](#P-AdaptiveCards-AdaptiveBackgroundImage-Url 'AdaptiveCards.AdaptiveBackgroundImage.Url')).

##### Returns

true iff this instance has only default property values.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveBackgroundImage-op_Implicit-System-Uri-~AdaptiveCards-AdaptiveBackgroundImage'></a>
### op_Implicit(backgroundImageUrl) `method`

##### Summary

Implicitly create an AdaptiveBackgroundImage from a Uri

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| backgroundImageUrl | [System.Uri)~AdaptiveCards.AdaptiveBackgroundImage](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri)~AdaptiveCards.AdaptiveBackgroundImage 'System.Uri)~AdaptiveCards.AdaptiveBackgroundImage') |  |

<a name='T-AdaptiveCards-AdaptiveBackgroundImageConverter'></a>
## AdaptiveBackgroundImageConverter `type`

##### Namespace

AdaptiveCards

##### Summary

Helper class used by Newtonsoft.Json to convert the backgroundImage property to/from JSON.

<a name='P-AdaptiveCards-AdaptiveBackgroundImageConverter-CanWrite'></a>
### CanWrite `property`

##### Summary

Lets Newtonsoft.Json know that this class supports writing.

<a name='P-AdaptiveCards-AdaptiveBackgroundImageConverter-Warnings'></a>
### Warnings `property`

##### Summary

A list of warnings generated by the converter.

<a name='M-AdaptiveCards-AdaptiveBackgroundImageConverter-CanConvert-System-Type-'></a>
### CanConvert(objectType) `method`

##### Summary

Called by Newtonsoft.Json to determine if this converter knows how to convert an object of type `objectType`.

##### Returns



##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| objectType | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | The type of object to convert. |

<a name='M-AdaptiveCards-AdaptiveBackgroundImageConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson(reader,objectType,existingValue,serializer) `method`

##### Summary

Generates a new [AdaptiveBackgroundImage](#T-AdaptiveCards-AdaptiveBackgroundImage 'AdaptiveCards.AdaptiveBackgroundImage') instance from JSON.

##### Returns

A new [AdaptiveBackgroundImage](#T-AdaptiveCards-AdaptiveBackgroundImage 'AdaptiveCards.AdaptiveBackgroundImage') instance.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| reader | [Newtonsoft.Json.JsonReader](#T-Newtonsoft-Json-JsonReader 'Newtonsoft.Json.JsonReader') | JsonReader from which to read. |
| objectType | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | Not used. |
| existingValue | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Not used. |
| serializer | [Newtonsoft.Json.JsonSerializer](#T-Newtonsoft-Json-JsonSerializer 'Newtonsoft.Json.JsonSerializer') | Not used. |

<a name='M-AdaptiveCards-AdaptiveBackgroundImageConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson(writer,backgroundImage,serializer) `method`

##### Summary

Writes the object to JSON. If the supplied `backgroundImage` is all default values and a URL, will write as a simple string. Otherwise, serialize the supplied `backgroundImage` as a JSON object via the `serializer`.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| writer | [Newtonsoft.Json.JsonWriter](#T-Newtonsoft-Json-JsonWriter 'Newtonsoft.Json.JsonWriter') | JsonWriter to write to. |
| backgroundImage | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | The AdaptiveBackgroundImage object to write. |
| serializer | [Newtonsoft.Json.JsonSerializer](#T-Newtonsoft-Json-JsonSerializer 'Newtonsoft.Json.JsonSerializer') | JsonSerializer to use for serialization. |

<a name='T-AdaptiveCards-AdaptiveCard'></a>
## AdaptiveCard `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card which has flexible container

<a name='M-AdaptiveCards-AdaptiveCard-#ctor-AdaptiveCards-AdaptiveSchemaVersion-'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [AdaptiveCards.AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion') | The schema version to use |

<a name='M-AdaptiveCards-AdaptiveCard-#ctor-System-String-'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The schema version to use |

<a name='M-AdaptiveCards-AdaptiveCard-#ctor'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Summary

Creates an AdaptiveCard using the [KnownSchemaVersion](#F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion 'AdaptiveCards.AdaptiveCard.KnownSchemaVersion') of this library.

##### Parameters

This constructor has no parameters.

<a name='F-AdaptiveCards-AdaptiveCard-ContentType'></a>
### ContentType `constants`

##### Summary

AdaptiveCard mimetype.

<a name='F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion'></a>
### KnownSchemaVersion `constants`

##### Summary

The latest known schema version supported by this library.

<a name='F-AdaptiveCards-AdaptiveCard-TypeName'></a>
### TypeName `constants`

##### Summary

The AdaptiveCard element that this class implements.

<a name='P-AdaptiveCards-AdaptiveCard-Actions'></a>
### Actions `property`

##### Summary

The Actions for this card.

<a name='P-AdaptiveCards-AdaptiveCard-BackgroundImage'></a>
### BackgroundImage `property`

##### Summary

Background image for card.

<a name='P-AdaptiveCards-AdaptiveCard-Body'></a>
### Body `property`

##### Summary

The Body elements for this card.

<a name='P-AdaptiveCards-AdaptiveCard-FallbackText'></a>
### FallbackText `property`

##### Summary

Text shown when the client doesn’t support the version specified. This can be in markdown format.

<a name='P-AdaptiveCards-AdaptiveCard-Height'></a>
### Height `property`

##### Summary

Value that denotes if the card must use all the vertical space that is set to it. Default value is [Auto](#F-AdaptiveCards-AdaptiveHeightType-Auto 'AdaptiveCards.AdaptiveHeightType.Auto').

<a name='P-AdaptiveCards-AdaptiveCard-JsonSchema'></a>
### JsonSchema `property`

##### Summary

This makes sure the $schema property doesn't show up in AdditionalProperties

<a name='P-AdaptiveCards-AdaptiveCard-Lang'></a>
### Lang `property`

##### Summary

The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions.

<a name='P-AdaptiveCards-AdaptiveCard-MinVersion'></a>
### MinVersion `property`

##### Summary

This is obsolete. Use the [Version](#P-AdaptiveCards-AdaptiveCard-Version 'AdaptiveCards.AdaptiveCard.Version') property instead.

<a name='P-AdaptiveCards-AdaptiveCard-OnDeserializingMissingVersion'></a>
### OnDeserializingMissingVersion `property`

##### Summary

Callback that will be invoked should a null or empty version string is encountered. The callback may return an alternate version to use for parsing.

##### Example

AdaptiveCard.OnDeserializingMissingVersion = () => new AdaptiveSchemaVersion(0, 5);

<a name='P-AdaptiveCards-AdaptiveCard-PixelMinHeight'></a>
### PixelMinHeight `property`

##### Summary

Explicit card minimum height in pixels.

<a name='P-AdaptiveCards-AdaptiveCard-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for the card (this allows a default action at the card level)

<a name='P-AdaptiveCards-AdaptiveCard-Speak'></a>
### Speak `property`

##### Summary

Speak annotation for the card.

<a name='P-AdaptiveCards-AdaptiveCard-Title'></a>
### Title `property`

##### Summary

Title for the card (used when displayed in a dialog).

<a name='P-AdaptiveCards-AdaptiveCard-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveCard-Version'></a>
### Version `property`

##### Summary

Schema version that this card requires. If a client is lower than this version the fallbackText will be rendered.

<a name='P-AdaptiveCards-AdaptiveCard-VerticalContentAlignment'></a>
### VerticalContentAlignment `property`

##### Summary

The content alignment for the element inside the container.

<a name='M-AdaptiveCards-AdaptiveCard-FromJson-System-String-'></a>
### FromJson(json) `method`

##### Summary

Parse an AdaptiveCard from a JSON string.

##### Returns

The result of parsing `json`.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| json | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | A JSON-serialized Adaptive Card. |

<a name='M-AdaptiveCards-AdaptiveCard-GetResourceInformation'></a>
### GetResourceInformation() `method`

##### Summary

Get resource information for all images and media present in this card.

##### Returns

Resource information for the entire card.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ShouldSerializeActions'></a>
### ShouldSerializeActions() `method`

##### Summary

Determines whether the actions portion of an AdaptiveCard should be serialized.

##### Returns

true iff actions should be serialized.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ShouldSerializeBody'></a>
### ShouldSerializeBody() `method`

##### Summary

Determines whether the body portion of an AdaptiveCard should be serialized.

##### Returns

true iff the body should be serialized.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ShouldSerializeHeight'></a>
### ShouldSerializeHeight() `method`

##### Summary

Determines whether the height property of an AdaptiveCard should be serialized.

##### Returns

true iff the height property should be serialized.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ShouldSerializeJsonSchema'></a>
### ShouldSerializeJsonSchema() `method`

##### Summary

Determines whether the schema entry in an AdaptiveCard should be serialized.

##### Returns

false

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ToJson'></a>
### ToJson() `method`

##### Summary

Serialize this AdaptiveCard to JSON.

##### Returns

The JSON representation of this AdaptiveCard.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Rendering-AdaptiveCardConfig'></a>
## AdaptiveCardConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Contains options for the AdaptiveCard element.

<a name='P-AdaptiveCards-Rendering-AdaptiveCardConfig-AllowCustomStyle'></a>
### AllowCustomStyle `property`

##### Summary

Determines whether custom styles should be honored.

<a name='T-AdaptiveCards-AdaptiveCardConverter'></a>
## AdaptiveCardConverter `type`

##### Namespace

AdaptiveCards

##### Summary

Helper class used by Newtonsoft.Json to convert an AdaptiveCard to/from JSON.

<a name='P-AdaptiveCards-AdaptiveCardConverter-CanWrite'></a>
### CanWrite `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveCardConverter-Warnings'></a>
### Warnings `property`

##### Summary

A list of warnings generated by the converter.

<a name='M-AdaptiveCards-AdaptiveCardConverter-CanConvert-System-Type-'></a>
### CanConvert() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCardConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson(reader,objectType,existingValue,serializer) `method`

##### Summary

Generates a new [AdaptiveCard](#T-AdaptiveCards-AdaptiveCard 'AdaptiveCards.AdaptiveCard') instance from JSON.

##### Returns

A new AdaptiveCard instance on success.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| reader | [Newtonsoft.Json.JsonReader](#T-Newtonsoft-Json-JsonReader 'Newtonsoft.Json.JsonReader') | JsonReader from which to read. |
| objectType | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') |  |
| existingValue | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') |  |
| serializer | [Newtonsoft.Json.JsonSerializer](#T-Newtonsoft-Json-JsonSerializer 'Newtonsoft.Json.JsonSerializer') |  |

<a name='M-AdaptiveCards-AdaptiveCardConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveCardParseResult'></a>
## AdaptiveCardParseResult `type`

##### Namespace

AdaptiveCards

##### Summary

The result of parsing an AdaptiveCard from JSON.

<a name='P-AdaptiveCards-AdaptiveCardParseResult-Card'></a>
### Card `property`

##### Summary

The parsed card object.

<a name='P-AdaptiveCards-AdaptiveCardParseResult-Warnings'></a>
### Warnings `property`

##### Summary

A collection of any warnings that might have been encountered when parsing the card.

<a name='T-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2'></a>
## AdaptiveCardRendererBase\`2 `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Abstract base class that every AdaptiveCards renderer must implement.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TUIElement | The base UI element type the renderer implements (e.g. "HTMLElement" or
"FrameworkElement"). |
| TContext | The type of the renderer context to use (e.g. "AdaptiveRenderContext"). |

<a name='P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-ElementRenderers'></a>
### ElementRenderers `property`

##### Summary

The dictionary of supported element types and their associated rendering functions

<a name='P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-HostConfig'></a>
### HostConfig `property`

##### Summary

A Host Configuration object to determine base styling and behavior of the rendered card

<a name='P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-SupportedSchemaVersion'></a>
### SupportedSchemaVersion `property`

##### Summary

Provides the highest schema version that this renderer supports.

<a name='M-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-GetSupportedSchemaVersion'></a>
### GetSupportedSchemaVersion() `method`

##### Summary

Provides the highest schema version that this renderer supports.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveChoice'></a>
## AdaptiveChoice `type`

##### Namespace

AdaptiveCards

##### Summary

Choice as part of a Input.AdaptiveChoiceSetInput element

<a name='P-AdaptiveCards-AdaptiveChoice-IsSelected'></a>
### IsSelected `property`

##### Summary

Is this choice selected?

<a name='P-AdaptiveCards-AdaptiveChoice-Speak'></a>
### Speak `property`

##### Summary

(OPTIONAL) Speech description of the choice

<a name='P-AdaptiveCards-AdaptiveChoice-Title'></a>
### Title `property`

##### Summary

Display text for the choice

<a name='P-AdaptiveCards-AdaptiveChoice-Value'></a>
### Value `property`

##### Summary

Internal value which will be collected as input if the choice is selected

<a name='T-AdaptiveCards-AdaptiveChoiceInputStyle'></a>
## AdaptiveChoiceInputStyle `type`

##### Namespace

AdaptiveCards

##### Summary

The style of ChoiceInput to display.

<a name='F-AdaptiveCards-AdaptiveChoiceInputStyle-Compact'></a>
### Compact `constants`

##### Summary

Compact display similar to a ComboBox.

<a name='F-AdaptiveCards-AdaptiveChoiceInputStyle-Expanded'></a>
### Expanded `constants`

##### Summary

Expanded display i.e. Checkbox or Radio buttons.

<a name='T-AdaptiveCards-AdaptiveChoiceSetInput'></a>
## AdaptiveChoiceSetInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Input.ChoiceSet element.

<a name='F-AdaptiveCards-AdaptiveChoiceSetInput-TypeName'></a>
### TypeName `constants`

##### Summary

The AdaptiveCard element that this class implements.

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Choices'></a>
### Choices `property`

##### Summary

A collection of available choices.

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-IsMultiSelect'></a>
### IsMultiSelect `property`

##### Summary

Determines whether multiple selections are allowed.

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Style'></a>
### Style `property`

##### Summary

The style to use when displaying this Input.ChoiceSet.

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Value'></a>
### Value `property`

##### Summary

Comma separated string of selected Choice values.

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Wrap'></a>
### Wrap `property`

##### Summary

Controls text wrapping behavior.

<a name='M-AdaptiveCards-AdaptiveChoiceSetInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveCollectionElement'></a>
## AdaptiveCollectionElement `type`

##### Namespace

AdaptiveCards

##### Summary

Base class for all elements that contain other elements.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-Bleed'></a>
### Bleed `property`

##### Summary

Defines if the element can bleed through its parent's padding.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-PixelMinHeight'></a>
### PixelMinHeight `property`

##### Summary

Explicit container element minimum height.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for this container. This allows for setting a default action at the container level.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-Style'></a>
### Style `property`

##### Summary

The style used to display this element. See [AdaptiveContainerStyle](#T-AdaptiveCards-AdaptiveContainerStyle 'AdaptiveCards.AdaptiveContainerStyle').

<a name='P-AdaptiveCards-AdaptiveCollectionElement-StyleXml'></a>
### StyleXml `property`

##### Summary

Controls XML serialization of style.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-VerticalContentAlignment'></a>
### VerticalContentAlignment `property`

##### Summary

The content alignment for the element inside the container.

<a name='M-AdaptiveCards-AdaptiveCollectionElement-ShouldSerializeStyleXml'></a>
### ShouldSerializeStyleXml() `method`

##### Summary

Determines whether to serialize the style for XML.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveColumn'></a>
## AdaptiveColumn `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Column element.

<a name='F-AdaptiveCards-AdaptiveColumn-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveColumn-Size'></a>
### Size `property`

##### Summary

Size for the column (either ColumnSize string or number which is relative size of the column).

<a name='P-AdaptiveCards-AdaptiveColumn-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveColumn-Width'></a>
### Width `property`

##### Summary

Width for the column (either ColumnWidth string or number which is relative size of the column).

<a name='T-AdaptiveCards-AdaptiveColumnSet'></a>
## AdaptiveColumnSet `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the ColumnSet element.

<a name='F-AdaptiveCards-AdaptiveColumnSet-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveColumnSet-Columns'></a>
### Columns `property`

##### Summary

Collection of Columns that this ColumnSet contains.

<a name='P-AdaptiveCards-AdaptiveColumnSet-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveColumnSize'></a>
## AdaptiveColumnSize `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the horizontal size (width) of Column.

<a name='F-AdaptiveCards-AdaptiveColumnSize-Auto'></a>
### Auto `constants`

##### Summary

The width of the Column is optimally chosen depending on the space available in the element's container

<a name='F-AdaptiveCards-AdaptiveColumnSize-Stretch'></a>
### Stretch `constants`

##### Summary

The width of the Column adjusts to match that of its container

<a name='T-AdaptiveCards-AdaptiveColumnWidth'></a>
## AdaptiveColumnWidth `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the horizontal size (width) of Column.

<a name='F-AdaptiveCards-AdaptiveColumnWidth-Auto'></a>
### Auto `constants`

##### Summary

The width of the Column is optimally chosen depending on the space available in the element's container

<a name='F-AdaptiveCards-AdaptiveColumnWidth-Stretch'></a>
### Stretch `constants`

##### Summary

The width of the Column adjusts to match that of its container

<a name='T-AdaptiveCards-Rendering-AdaptiveConfigBase'></a>
## AdaptiveConfigBase `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Base class for configuration-holding renderer classes.

<a name='P-AdaptiveCards-Rendering-AdaptiveConfigBase-AdditionalData'></a>
### AdditionalData `property`

##### Summary

Holds additional data in a configuration that doesn't map to known properties.

<a name='T-AdaptiveCards-AdaptiveContainer'></a>
## AdaptiveContainer `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Container element.

<a name='F-AdaptiveCards-AdaptiveContainer-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveContainer-BackgroundImage'></a>
### BackgroundImage `property`

##### Summary

Background image to use when displaying this container.

<a name='P-AdaptiveCards-AdaptiveContainer-Items'></a>
### Items `property`

##### Summary

Elements within this container.

<a name='P-AdaptiveCards-AdaptiveContainer-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveContainerStyle'></a>
## AdaptiveContainerStyle `type`

##### Namespace

AdaptiveCards

##### Summary

Controls which style to apply to a container.

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Accent'></a>
### Accent `constants`

##### Summary

The container should be displayed using the accent style

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Attention'></a>
### Attention `constants`

##### Summary

The container should be displayed using the attention style

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Default'></a>
### Default `constants`

##### Summary

The container should be displayed using the default style

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Emphasis'></a>
### Emphasis `constants`

##### Summary

The container should be displayed using the emphasis style

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Good'></a>
### Good `constants`

##### Summary

The container should be displayed using the good style

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Normal'></a>
### Normal `constants`

##### Summary

The container is a normal container

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Warning'></a>
### Warning `constants`

##### Summary

The container should be displayed using the warning style

<a name='T-AdaptiveCards-AdaptiveDateInput'></a>
## AdaptiveDateInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Input.Date element.

<a name='F-AdaptiveCards-AdaptiveDateInput-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveDateInput-Max'></a>
### Max `property`

##### Summary

Hint of maximum value (note: may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveDateInput-Min'></a>
### Min `property`

##### Summary

Hint of minimum value (note: may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveDateInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text to display.

<a name='P-AdaptiveCards-AdaptiveDateInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveDateInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field.

<a name='M-AdaptiveCards-AdaptiveDateInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveElement'></a>
## AdaptiveElement `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an element in Adaptive Cards.

<a name='P-AdaptiveCards-AdaptiveElement-Height'></a>
### Height `property`

##### Summary

The amount of space the element should be separated from the previous element. Default value is [Auto](#P-AdaptiveCards-AdaptiveHeight-Auto 'AdaptiveCards.AdaptiveHeight.Auto').

<a name='P-AdaptiveCards-AdaptiveElement-IsVisible'></a>
### IsVisible `property`

##### Summary

Indicates whether the element should be visible when the card has been rendered.

<a name='P-AdaptiveCards-AdaptiveElement-Separator'></a>
### Separator `property`

##### Summary

Indicates whether there should be a visible separator (e.g. a line) between this element and the one before it.

<a name='P-AdaptiveCards-AdaptiveElement-Spacing'></a>
### Spacing `property`

##### Summary

The amount of space the element should be separated from the previous element. Default value is [Default](#F-AdaptiveCards-AdaptiveSpacing-Default 'AdaptiveCards.AdaptiveSpacing.Default').

<a name='P-AdaptiveCards-AdaptiveElement-Speak'></a>
### Speak `property`

##### Summary

SSML fragment for spoken interaction.

<a name='M-AdaptiveCards-AdaptiveElement-ShouldSerializeHeight'></a>
### ShouldSerializeHeight() `method`

##### Summary

Determines whether the height property should be serialized or not.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Rendering-AdaptiveElementRenderers`2'></a>
## AdaptiveElementRenderers\`2 `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Encapsulates information needed to map from element types to factory methods for instantiating them.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TUIElement | The base UI element type the renderer implements (e.g. "HTMLElement" or
"FrameworkElement"). |
| TContext | The type of the renderer context to use (e.g. "AdaptiveRenderContext"). |

<a name='M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Get-System-Type-'></a>
### Get(type) `method`

##### Summary

Gets the factory method for an element type.

##### Returns

The factory method for the element object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| type | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | The type of object for which to retrieve the factory method. |

<a name='M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Get``1'></a>
### Get\`\`1() `method`

##### Summary

Gets the factory method for an element type.

##### Returns

The factory method for the element object of type TElement.

##### Parameters

This method has no parameters.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TElement | The type of element object to get. |

<a name='M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Remove``1'></a>
### Remove\`\`1() `method`

##### Summary

Removes the registration for the element type.

##### Parameters

This method has no parameters.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TElement | The type of element object to remove. |

<a name='M-AdaptiveCards-Rendering-AdaptiveElementRenderers`2-Set``1-System-Func{``0,`1,`0}-'></a>
### Set\`\`1(renderer) `method`

##### Summary

Registers or replaces a factory method for the given element type.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| renderer | [System.Func{\`\`0,\`1,\`0}](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Func 'System.Func{``0,`1,`0}') | Factory method for instantiating an element object of type TElement. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| TElement | The type of the element object. |

<a name='T-AdaptiveCards-AdaptiveException'></a>
## AdaptiveException `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an exception thrown by Adaptive Cards itself.

<a name='M-AdaptiveCards-AdaptiveException-#ctor'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveException-#ctor-System-String-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveException-#ctor-System-String,System-Exception-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='T-AdaptiveCards-AdaptiveFact'></a>
## AdaptiveFact `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a "fact" in a FactSet element.

<a name='M-AdaptiveCards-AdaptiveFact-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty Fact.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveFact-#ctor-System-String,System-String-'></a>
### #ctor(title,value) `constructor`

##### Summary

Initializes a Fact with the given properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| title | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The title of the Fact. |
| value | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The value of the Fact. |

<a name='P-AdaptiveCards-AdaptiveFact-Speak'></a>
### Speak `property`

##### Summary

(Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment.

<a name='P-AdaptiveCards-AdaptiveFact-Title'></a>
### Title `property`

##### Summary

The Fact's title.

<a name='P-AdaptiveCards-AdaptiveFact-Value'></a>
### Value `property`

##### Summary

The Fact's value.

<a name='T-AdaptiveCards-AdaptiveFactSet'></a>
## AdaptiveFactSet `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the FactSet element.

<a name='F-AdaptiveCards-AdaptiveFactSet-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveFactSet-Facts'></a>
### Facts `property`

##### Summary

A collection of Facts to this FactSet contains.

<a name='P-AdaptiveCards-AdaptiveFactSet-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveFallbackConverter'></a>
## AdaptiveFallbackConverter `type`

##### Namespace

AdaptiveCards

##### Summary

A converter to use with Newtonsoft.Json that handles fallback scenarios.

<a name='F-AdaptiveCards-AdaptiveFallbackConverter-IsInFallback'></a>
### IsInFallback `constants`

##### Summary

State tracking to determine whether we're currently processing a fallback request.

<a name='P-AdaptiveCards-AdaptiveFallbackConverter-CanRead'></a>
### CanRead `property`

##### Summary

Lets Newtonsoft.Json know that this converter knows how to read JSON.

<a name='P-AdaptiveCards-AdaptiveFallbackConverter-CanWrite'></a>
### CanWrite `property`

##### Summary

Lets Newtonsoft.Json know that this converter knows how to write JSON.

<a name='P-AdaptiveCards-AdaptiveFallbackConverter-Warnings'></a>
### Warnings `property`

##### Summary

A list of warnings generated by this converter.

<a name='M-AdaptiveCards-AdaptiveFallbackConverter-CanConvert-System-Type-'></a>
### CanConvert(objectType) `method`

##### Summary

Called by Newtonsoft.Json to determine if an object is recognized by this converter.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| objectType | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | Type of object. |

<a name='M-AdaptiveCards-AdaptiveFallbackConverter-ParseFallback-Newtonsoft-Json-Linq-JToken,Newtonsoft-Json-JsonSerializer,System-String,AdaptiveCards-AdaptiveInternalID-'></a>
### ParseFallback() `method`

##### Summary

Helper to handle instantiating an [AdaptiveFallbackElement](#T-AdaptiveCards-AdaptiveFallbackElement 'AdaptiveCards.AdaptiveFallbackElement') during JSON parsing.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveFallbackConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson() `method`

##### Summary

Called by Newtonsoft.Json to convert the given JSON to an object instance.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveFallbackConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson(writer,cardElement,serializer) `method`

##### Summary

Called by Newtonsoft.Json to write the given element as JSON.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| writer | [Newtonsoft.Json.JsonWriter](#T-Newtonsoft-Json-JsonWriter 'Newtonsoft.Json.JsonWriter') | Destination for serialized content. |
| cardElement | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Element to serialize. |
| serializer | [Newtonsoft.Json.JsonSerializer](#T-Newtonsoft-Json-JsonSerializer 'Newtonsoft.Json.JsonSerializer') | Serializer to use. |

<a name='T-AdaptiveCards-AdaptiveFallbackElement'></a>
## AdaptiveFallbackElement `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the fallback property.

<a name='M-AdaptiveCards-AdaptiveFallbackElement-#ctor-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-'></a>
### #ctor(fallbackType) `constructor`

##### Summary

Initializes an AdaptiveFallbackElement with the given `fallbackType`.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| fallbackType | [AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType](#T-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType 'AdaptiveCards.AdaptiveFallbackElement.AdaptiveFallbackType') | The type of fallback this instance represents. |

<a name='M-AdaptiveCards-AdaptiveFallbackElement-#ctor-AdaptiveCards-AdaptiveTypedElement-'></a>
### #ctor(fallbackContent) `constructor`

##### Summary

Initializes an AdaptiveFallbackElement with the given `fallbackContent`.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| fallbackContent | [AdaptiveCards.AdaptiveTypedElement](#T-AdaptiveCards-AdaptiveTypedElement 'AdaptiveCards.AdaptiveTypedElement') | The content to show in the event of fallback. |

<a name='M-AdaptiveCards-AdaptiveFallbackElement-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an AdaptiveFallbackElement with no fallback type.

##### Parameters

This constructor has no parameters.

<a name='F-AdaptiveCards-AdaptiveFallbackElement-drop'></a>
### drop `constants`

##### Summary

String that represents "drop" fallback type

<a name='P-AdaptiveCards-AdaptiveFallbackElement-Content'></a>
### Content `property`

##### Summary

The content to show in the event of fallback.

<a name='P-AdaptiveCards-AdaptiveFallbackElement-Type'></a>
### Type `property`

##### Summary

Represents the type of fallback to perform.

<a name='T-AdaptiveCards-AdaptiveFallbackException'></a>
## AdaptiveFallbackException `type`

##### Namespace

AdaptiveCards

##### Summary

An exception thrown while processing fallback.

##### Remarks

This exception is intended to be caught and handled by an element that has a fallback action.

<a name='M-AdaptiveCards-AdaptiveFallbackException-#ctor'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveFallbackException-#ctor-System-String-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveFallbackException-#ctor-System-String,System-Exception-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='T-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType'></a>
## AdaptiveFallbackType `type`

##### Namespace

AdaptiveCards.AdaptiveFallbackElement

##### Summary

Enumeration describing an object's fallback type.

<a name='F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-Content'></a>
### Content `constants`

##### Summary

This element has content to show in the event of fallback being triggered.

<a name='F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-Drop'></a>
### Drop `constants`

##### Summary

Drop this element during fallback.

<a name='F-AdaptiveCards-AdaptiveFallbackElement-AdaptiveFallbackType-None'></a>
### None `constants`

##### Summary

This object does not have fallback specified.

<a name='T-AdaptiveCards-AdaptiveFeatureRegistration'></a>
## AdaptiveFeatureRegistration `type`

##### Namespace

AdaptiveCards

##### Summary

Tracks features supported by a host. When an Adaptive Cards element declares "requires", this is the collection
that gets used.

<a name='M-AdaptiveCards-AdaptiveFeatureRegistration-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes a new AdaptiveFeatureRegistration instance.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveFeatureRegistration-Get-System-String-'></a>
### Get(feature) `method`

##### Summary

Retrieves the version of a registered feature.

##### Returns

The version of the feature if it is registered. Otherwise, the empty string.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| feature | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The feature whose version is being requested. |

<a name='M-AdaptiveCards-AdaptiveFeatureRegistration-Remove-System-String-'></a>
### Remove(feature) `method`

##### Summary

Removes (or unregisters) a feature.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| feature | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The feature to remove. |

<a name='M-AdaptiveCards-AdaptiveFeatureRegistration-Set-System-String,System-String-'></a>
### Set(feature,version) `method`

##### Summary

Sets (or registers) a feature to a particular version.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| feature | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The feature upon which to set a version. |
| version | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The version to set. |

<a name='T-AdaptiveCards-AdaptiveFontType'></a>
## AdaptiveFontType `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the font type of the TextBlock Elements

<a name='F-AdaptiveCards-AdaptiveFontType-Default'></a>
### Default `constants`

##### Summary

The default font type for general use

<a name='F-AdaptiveCards-AdaptiveFontType-Monospace'></a>
### Monospace `constants`

##### Summary

The monospace font type

<a name='T-AdaptiveCards-AdaptiveHeight'></a>
## AdaptiveHeight `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the height property in Adaptive Cards.

<a name='M-AdaptiveCards-AdaptiveHeight-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty AdaptiveHeight instance.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-#ctor-System-UInt32-'></a>
### #ctor(px) `constructor`

##### Summary

Initializes an AdaptiveHeight instance with the given pixel size.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| px | [System.UInt32](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.UInt32 'System.UInt32') | The device-independent pixel size to use. |

<a name='M-AdaptiveCards-AdaptiveHeight-#ctor-AdaptiveCards-AdaptiveHeightType-'></a>
### #ctor(heightType) `constructor`

##### Summary

Initializes an AdaptiveHeight instance with the given [AdaptiveHeightType](#T-AdaptiveCards-AdaptiveHeightType 'AdaptiveCards.AdaptiveHeightType').

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| heightType | [AdaptiveCards.AdaptiveHeightType](#T-AdaptiveCards-AdaptiveHeightType 'AdaptiveCards.AdaptiveHeightType') | The AdaptiveHeightType to use. |

<a name='P-AdaptiveCards-AdaptiveHeight-Auto'></a>
### Auto `property`

##### Summary

Returns a new AdaptiveHeight instance initialized for the [Auto](#F-AdaptiveCards-AdaptiveHeightType-Auto 'AdaptiveCards.AdaptiveHeightType.Auto') height type.

<a name='P-AdaptiveCards-AdaptiveHeight-HeightType'></a>
### HeightType `property`

##### Summary

The [AdaptiveHeightType](#T-AdaptiveCards-AdaptiveHeightType 'AdaptiveCards.AdaptiveHeightType') this instance represents.

<a name='P-AdaptiveCards-AdaptiveHeight-Stretch'></a>
### Stretch `property`

##### Summary

Returns a new AdaptiveHeight instance initialized for the [Stretch](#F-AdaptiveCards-AdaptiveHeightType-Stretch 'AdaptiveCards.AdaptiveHeightType.Stretch') height type.

<a name='P-AdaptiveCards-AdaptiveHeight-Unit'></a>
### Unit `property`

##### Summary

The specific height to use (only valid for the [Pixel](#F-AdaptiveCards-AdaptiveHeightType-Pixel 'AdaptiveCards.AdaptiveHeightType.Pixel') type).

<a name='P-AdaptiveCards-AdaptiveHeight-UnitXml'></a>
### UnitXml `property`

##### Summary

Helper to aid in XML serialization of the [Unit](#P-AdaptiveCards-AdaptiveHeight-Unit 'AdaptiveCards.AdaptiveHeight.Unit') property.

<a name='M-AdaptiveCards-AdaptiveHeight-Equals-System-Object-'></a>
### Equals() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-Equals-AdaptiveCards-AdaptiveHeight-'></a>
### Equals() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-GetHashCode'></a>
### GetHashCode() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-IsPixel'></a>
### IsPixel() `method`

##### Summary

Returns true if this [AdaptiveHeight](#T-AdaptiveCards-AdaptiveHeight 'AdaptiveCards.AdaptiveHeight') instance represents the [Pixel](#F-AdaptiveCards-AdaptiveHeightType-Pixel 'AdaptiveCards.AdaptiveHeightType.Pixel')[AdaptiveHeightType](#T-AdaptiveCards-AdaptiveHeightType 'AdaptiveCards.AdaptiveHeightType').

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-ShouldSerializeAdaptiveHeight'></a>
### ShouldSerializeAdaptiveHeight() `method`

##### Summary

Determines whether this [AdaptiveHeight](#T-AdaptiveCards-AdaptiveHeight 'AdaptiveCards.AdaptiveHeight') instance should be serialized.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-ShouldSerializeUnitXml'></a>
### ShouldSerializeUnitXml() `method`

##### Summary

Determines whether to serialize the [UnitXml](#P-AdaptiveCards-AdaptiveHeight-UnitXml 'AdaptiveCards.AdaptiveHeight.UnitXml') property.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-op_Equality-AdaptiveCards-AdaptiveHeight,AdaptiveCards-AdaptiveHeight-'></a>
### op_Equality() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveHeight-op_Inequality-AdaptiveCards-AdaptiveHeight,AdaptiveCards-AdaptiveHeight-'></a>
### op_Inequality() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveHeightType'></a>
## AdaptiveHeightType `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the vertical size (height) of element.

<a name='F-AdaptiveCards-AdaptiveHeightType-Auto'></a>
### Auto `constants`

##### Summary

The height of the element matches element content.

<a name='F-AdaptiveCards-AdaptiveHeightType-Pixel'></a>
### Pixel `constants`

##### Summary

The height of the element was explicitly specified (only for Image elements).

<a name='F-AdaptiveCards-AdaptiveHeightType-Stretch'></a>
### Stretch `constants`

##### Summary

The height of the element uses as much space as it is able to.

<a name='T-AdaptiveCards-AdaptiveHorizontalAlignment'></a>
## AdaptiveHorizontalAlignment `type`

##### Namespace

AdaptiveCards

##### Summary

Controls how elements are horizontally positioned within their container.

<a name='F-AdaptiveCards-AdaptiveHorizontalAlignment-Center'></a>
### Center `constants`

##### Summary

The element is centered inside its container

<a name='F-AdaptiveCards-AdaptiveHorizontalAlignment-Left'></a>
### Left `constants`

##### Summary

The element is left aligned

<a name='F-AdaptiveCards-AdaptiveHorizontalAlignment-Right'></a>
### Right `constants`

##### Summary

The element is right aligned

<a name='F-AdaptiveCards-AdaptiveHorizontalAlignment-Stretch'></a>
### Stretch `constants`

##### Summary

Stretch the actions to fit the containerhrit

<a name='T-AdaptiveCards-Rendering-AdaptiveHostConfig'></a>
## AdaptiveHostConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Contains host-configurable options for controlling rendering behavior.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-Actions'></a>
### Actions `property`

##### Summary

Properties which control rendering and behavior of actions.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-AdaptiveCard'></a>
### AdaptiveCard `property`

##### Summary

Properties that control the rendering and behavior of the toplevel Adaptive Card.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-ContainerStyles'></a>
### ContainerStyles `property`

##### Summary

Definitions of the various styles that can be applied to containers and container-like elements.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-FactSet'></a>
### FactSet `property`

##### Summary

Controls the rendering of the FactSet element.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontFamily'></a>
### FontFamily `property`

##### Summary

Defines which font families to use during rendering. (Obsolete)

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontSizes'></a>
### FontSizes `property`

##### Summary

Defines which font sizes to use during rendering. (Obsolete)

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontTypes'></a>
### FontTypes `property`

##### Summary

Defines font families, sizes, and weights to use during rendering.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-FontWeights'></a>
### FontWeights `property`

##### Summary

Defines which font weights to use during rendering. (Obsolete)

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageBaseUrl'></a>
### ImageBaseUrl `property`

##### Summary

Image Base URL for relative URLs.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageSet'></a>
### ImageSet `property`

##### Summary

Controls the default size at which images in an ImageSet are rendered.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageSizes'></a>
### ImageSizes `property`

##### Summary

Controls the sizes at which images render.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-Inputs'></a>
### Inputs `property`

##### Summary

Controls the rendering and behavior of input elements.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-Media'></a>
### Media `property`

##### Summary

Controls the rendering and behavior of media elements.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-Separator'></a>
### Separator `property`

##### Summary

Controls the appearance of the separator.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-Spacing'></a>
### Spacing `property`

##### Summary

Defines the various values to use for spacing.

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-SupportsInteractivity'></a>
### SupportsInteractivity `property`

##### Summary

Toggles whether or not to render inputs and actions.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-FromJson-System-String-'></a>
### FromJson() `method`

##### Summary

Constructs an [AdaptiveHostConfig](#T-AdaptiveCards-Rendering-AdaptiveHostConfig 'AdaptiveCards.Rendering.AdaptiveHostConfig') instance from the given JSON.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontFamily-AdaptiveCards-AdaptiveFontType-'></a>
### GetFontFamily() `method`

##### Summary

Retrieves the name of the font family given the desired AdaptiveFontType.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontSize-AdaptiveCards-AdaptiveFontType,AdaptiveCards-AdaptiveTextSize-'></a>
### GetFontSize() `method`

##### Summary

Retrieves a font size for an AdaptiveFontType.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetFontWeight-AdaptiveCards-AdaptiveFontType,AdaptiveCards-AdaptiveTextWeight-'></a>
### GetFontWeight() `method`

##### Summary

Retrieves a font weight for an AdaptiveFontType.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-GetSpacing-AdaptiveCards-AdaptiveSpacing-'></a>
### GetSpacing(spacing) `method`

##### Summary

Get the numeric value of spacing to use for a given spacing type.

##### Returns

The numeric value for the type of spacing.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| spacing | [AdaptiveCards.AdaptiveSpacing](#T-AdaptiveCards-AdaptiveSpacing 'AdaptiveCards.AdaptiveSpacing') | The spacing to look up. |

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-String-'></a>
### ResolveFinalAbsoluteUri(uriString) `method`

##### Summary

Resolves a URI string in an absolute [Uri](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri 'System.Uri').

##### Returns

The absolute Uri that uriString represents.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| uriString | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The URI to resolve. |

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-Uri-'></a>
### ResolveFinalAbsoluteUri(uri) `method`

##### Summary

Converts a Uri into absolute form using [ImageBaseUrl](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageBaseUrl 'AdaptiveCards.Rendering.AdaptiveHostConfig.ImageBaseUrl') as needed.

##### Returns

An absolute URI for uri.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| uri | [System.Uri](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri 'System.Uri') | URI to resolve. |

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-ToJson'></a>
### ToJson() `method`

##### Summary

Serialize this Host Config to JSON.

##### Returns

A JSON string representation of this Host Config.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveImage'></a>
## AdaptiveImage `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Adaptive Cards Image element type.

<a name='M-AdaptiveCards-AdaptiveImage-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveImage](#T-AdaptiveCards-AdaptiveImage 'AdaptiveCards.AdaptiveImage') instance.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveImage-#ctor-System-String-'></a>
### #ctor(url) `constructor`

##### Summary

Initializes an [AdaptiveImage](#T-AdaptiveCards-AdaptiveImage 'AdaptiveCards.AdaptiveImage') instance with the given URL.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The URL of the image as a string. |

<a name='M-AdaptiveCards-AdaptiveImage-#ctor-System-Uri-'></a>
### #ctor(url) `constructor`

##### Summary

Initializes an [AdaptiveImage](#T-AdaptiveCards-AdaptiveImage 'AdaptiveCards.AdaptiveImage') instance with the given URL.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.Uri](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Uri 'System.Uri') | The URL of the image. |

<a name='F-AdaptiveCards-AdaptiveImage-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveImage-AltText'></a>
### AltText `property`

##### Summary

Alternate text (alttext) to display for this image.

<a name='P-AdaptiveCards-AdaptiveImage-BackgroundColor'></a>
### BackgroundColor `property`

##### Summary

A background color for the image specified as #AARRGGBB or #RRGGBB.

<a name='P-AdaptiveCards-AdaptiveImage-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Horizontal alignment ([AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment')) to use.

<a name='P-AdaptiveCards-AdaptiveImage-PixelHeight'></a>
### PixelHeight `property`

##### Summary

Explicit image height.

<a name='P-AdaptiveCards-AdaptiveImage-PixelWidth'></a>
### PixelWidth `property`

##### Summary

Explicit image width.

<a name='P-AdaptiveCards-AdaptiveImage-SelectAction'></a>
### SelectAction `property`

##### Summary

Action to execute when image is invoked.

<a name='P-AdaptiveCards-AdaptiveImage-Size'></a>
### Size `property`

##### Summary

Controls the sizing ([AdaptiveImageSize](#T-AdaptiveCards-AdaptiveImageSize 'AdaptiveCards.AdaptiveImageSize')) of the displayed image.

<a name='P-AdaptiveCards-AdaptiveImage-Style'></a>
### Style `property`

##### Summary

The style ([AdaptiveImageStyle](#T-AdaptiveCards-AdaptiveImageStyle 'AdaptiveCards.AdaptiveImageStyle')) in which the image is displayed.

<a name='P-AdaptiveCards-AdaptiveImage-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveImage-Url'></a>
### Url `property`

##### Summary

The URL of the image.

<a name='P-AdaptiveCards-AdaptiveImage-UrlString'></a>
### UrlString `property`

##### Summary

This is necessary for XML serialization. You should use the [Url](#F-Url 'Url') property directly.

<a name='T-AdaptiveCards-AdaptiveImageFillMode'></a>
## AdaptiveImageFillMode `type`

##### Namespace

AdaptiveCards

##### Summary

Controls how an image fills a space.

<a name='F-AdaptiveCards-AdaptiveImageFillMode-Cover'></a>
### Cover `constants`

##### Summary

Image covers the entire width of its container (preserving aspect ratio). The image may be clipped if the
aspect ratio of the image doesn't match the aspect ratio of its container. [AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment') is respected, but [AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') is ignored
(as it's irrelevant).

<a name='F-AdaptiveCards-AdaptiveImageFillMode-Repeat'></a>
### Repeat `constants`

##### Summary

The image isn't stretched. Rather, it's repeated on the x-axis and then on the y-axis as many
times as needed to cover the container's width. Both [AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') and [Left](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Left 'AdaptiveCards.AdaptiveHorizontalAlignment.Left')) are respected. (defaults to [Top](#F-AdaptiveCards-AdaptiveVerticalAlignment-Top 'AdaptiveCards.AdaptiveVerticalAlignment.Top') and [Left](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Left 'AdaptiveCards.AdaptiveHorizontalAlignment.Left')

<a name='F-AdaptiveCards-AdaptiveImageFillMode-RepeatHorizontally'></a>
### RepeatHorizontally `constants`

##### Summary

The image isn't stretched. Rather, it's repeated on the x-axis as many times as needed to cover the
container's width. [AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment') is respected (defaults to [Top](#F-AdaptiveCards-AdaptiveVerticalAlignment-Top 'AdaptiveCards.AdaptiveVerticalAlignment.Top')). [AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') is ignored.

<a name='F-AdaptiveCards-AdaptiveImageFillMode-RepeatVertically'></a>
### RepeatVertically `constants`

##### Summary

The image isn't stretched. Rather, it's repeated on the y-axis as many times as needed to cover the
container's width. [AdaptiveHorizontalAlignment](#T-AdaptiveCards-AdaptiveHorizontalAlignment 'AdaptiveCards.AdaptiveHorizontalAlignment') is respected (defaults to [Left](#F-AdaptiveCards-AdaptiveHorizontalAlignment-Left 'AdaptiveCards.AdaptiveHorizontalAlignment.Left')). [AdaptiveVerticalAlignment](#T-AdaptiveCards-AdaptiveVerticalAlignment 'AdaptiveCards.AdaptiveVerticalAlignment') is ignored.

<a name='T-AdaptiveCards-AdaptiveImageSet'></a>
## AdaptiveImageSet `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an ImageSet element.

<a name='F-AdaptiveCards-AdaptiveImageSet-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveImageSet-ImageSize'></a>
### ImageSize `property`

##### Summary

Specifies the [AdaptiveImageSize](#T-AdaptiveCards-AdaptiveImageSize 'AdaptiveCards.AdaptiveImageSize') of each image in the set.

<a name='P-AdaptiveCards-AdaptiveImageSet-Images'></a>
### Images `property`

##### Summary

Collection of images to display.

<a name='P-AdaptiveCards-AdaptiveImageSet-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveImageSize'></a>
## AdaptiveImageSize `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the horizontal size (width) of element.

<a name='F-AdaptiveCards-AdaptiveImageSize-Auto'></a>
### Auto `constants`

##### Summary

The width of the element is optimally chosen depending on the space available in the element's container

<a name='F-AdaptiveCards-AdaptiveImageSize-Large'></a>
### Large `constants`

##### Summary

Large width

<a name='F-AdaptiveCards-AdaptiveImageSize-Medium'></a>
### Medium `constants`

##### Summary

Medium width

<a name='F-AdaptiveCards-AdaptiveImageSize-Small'></a>
### Small `constants`

##### Summary

Small width

<a name='F-AdaptiveCards-AdaptiveImageSize-Stretch'></a>
### Stretch `constants`

##### Summary

The width of the element adjusts to match that of its container

<a name='T-AdaptiveCards-AdaptiveImageStyle'></a>
## AdaptiveImageStyle `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the way Image elements are displayed.

<a name='F-AdaptiveCards-AdaptiveImageStyle-Default'></a>
### Default `constants`

##### Summary

The image is displayed within a rectangle.

<a name='F-AdaptiveCards-AdaptiveImageStyle-Normal'></a>
### Normal `constants`

##### Summary

The image is displayed within a rectangle.

<a name='F-AdaptiveCards-AdaptiveImageStyle-Person'></a>
### Person `constants`

##### Summary

The image is cropped to a circle, a common way to represent people photos.

<a name='T-AdaptiveCards-AdaptiveInline'></a>
## AdaptiveInline `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a single inline text entry.

<a name='P-AdaptiveCards-AdaptiveInline-AdditionalProperties'></a>
### AdditionalProperties `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveInline-Type'></a>
### Type `property`

##### Summary

The type name of the inline.

<a name='M-AdaptiveCards-AdaptiveInline-ShouldSerializeAdditionalProperties'></a>
### ShouldSerializeAdditionalProperties() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveInput'></a>
## AdaptiveInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents any input element.

<a name='P-AdaptiveCards-AdaptiveInput-ErrorMessage'></a>
### ErrorMessage `property`

##### Summary

Error message to be shown when validation fails.

<a name='P-AdaptiveCards-AdaptiveInput-IsRequired'></a>
### IsRequired `property`

##### Summary

Sets the input as required for triggering Submit actions.

<a name='P-AdaptiveCards-AdaptiveInput-Label'></a>
### Label `property`

##### Summary

Label to be shown next to input.

<a name='M-AdaptiveCards-AdaptiveInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

The string that will be rendered on a a host with "SupportsInteractivity" set to false.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveInternalID'></a>
## AdaptiveInternalID `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a unique identifier.

<a name='M-AdaptiveCards-AdaptiveInternalID-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an invalid AdaptiveInternalID

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveInternalID-#ctor-System-UInt32-'></a>
### #ctor(id) `constructor`

##### Summary

Initializes an AdaptiveInternalID with the supplied `id`.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| id | [System.UInt32](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.UInt32 'System.UInt32') | The id with which to initialize. |

<a name='F-AdaptiveCards-AdaptiveInternalID-Invalid'></a>
### Invalid `constants`

##### Summary

Value representing an invalid (or unset) AdaptiveInternalID

<a name='M-AdaptiveCards-AdaptiveInternalID-Current'></a>
### Current() `method`

##### Summary

Retrieves the current AdaptiveInternalID

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveInternalID-Equals-System-Object-'></a>
### Equals() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveInternalID-GetHashCode'></a>
### GetHashCode() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveInternalID-Next'></a>
### Next() `method`

##### Summary

Advances to the next AdaptiveInternalID.

##### Returns

The next AdaptiveInternalID.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveInternalID-ToString'></a>
### ToString() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveMedia'></a>
## AdaptiveMedia `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Media element.

<a name='F-AdaptiveCards-AdaptiveMedia-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveMedia-AltText'></a>
### AltText `property`

##### Summary

Alternate text to display for this media element.

<a name='P-AdaptiveCards-AdaptiveMedia-Poster'></a>
### Poster `property`

##### Summary

URL for the poster image to show for this media element.

<a name='P-AdaptiveCards-AdaptiveMedia-Sources'></a>
### Sources `property`

##### Summary

A collection of source from which to retrieve the media.

<a name='P-AdaptiveCards-AdaptiveMedia-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveMediaSource'></a>
## AdaptiveMediaSource `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a "media source" for a Media element.

<a name='M-AdaptiveCards-AdaptiveMediaSource-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveMediaSource](#T-AdaptiveCards-AdaptiveMediaSource 'AdaptiveCards.AdaptiveMediaSource').

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveMediaSource-#ctor-System-String,System-String-'></a>
### #ctor(mimeType,url) `constructor`

##### Summary

Initializes an [AdaptiveMediaSource](#T-AdaptiveCards-AdaptiveMediaSource 'AdaptiveCards.AdaptiveMediaSource') instance with the given properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| mimeType | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The mime type of the media. |
| url | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The url from which to load the media. |

<a name='P-AdaptiveCards-AdaptiveMediaSource-MimeType'></a>
### MimeType `property`

##### Summary

The mime type of this media source.

<a name='P-AdaptiveCards-AdaptiveMediaSource-Url'></a>
### Url `property`

##### Summary

The URL of this media source.

<a name='T-AdaptiveCards-AdaptiveNumberInput'></a>
## AdaptiveNumberInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Input.Number element.

<a name='F-AdaptiveCards-AdaptiveNumberInput-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveNumberInput-Max'></a>
### Max `property`

##### Summary

Hint of maximum value (may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveNumberInput-Min'></a>
### Min `property`

##### Summary

Hint of minimum value (may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveNumberInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Text to display as a placeholder.

<a name='P-AdaptiveCards-AdaptiveNumberInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveNumberInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field.

<a name='M-AdaptiveCards-AdaptiveNumberInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveOpenUrlAction'></a>
## AdaptiveOpenUrlAction `type`

##### Namespace

AdaptiveCards

##### Summary

When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web
browser or showing in-situ with embedded web browser.

<a name='F-AdaptiveCards-AdaptiveOpenUrlAction-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveOpenUrlAction-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveOpenUrlAction-Url'></a>
### Url `property`

##### Summary

Url to open using default operating system browser.

<a name='P-AdaptiveCards-AdaptiveOpenUrlAction-UrlString'></a>
### UrlString `property`

##### Summary

This is necessary for XML serialization. You should use the [Url](#F-Url 'Url') property directly.

<a name='T-AdaptiveCards-Rendering-AdaptiveRenderException'></a>
## AdaptiveRenderException `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-AdaptiveRenderException-CardFallbackText'></a>
### CardFallbackText `property`

##### Summary

The fallback text associated with this card, if provided by the card author

<a name='T-AdaptiveCards-AdaptiveRichTextBlock'></a>
## AdaptiveRichTextBlock `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the RichTextBlock element.

<a name='M-AdaptiveCards-AdaptiveRichTextBlock-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveRichTextBlock](#T-AdaptiveCards-AdaptiveRichTextBlock 'AdaptiveCards.AdaptiveRichTextBlock').

##### Parameters

This constructor has no parameters.

<a name='F-AdaptiveCards-AdaptiveRichTextBlock-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveRichTextBlock-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Horizontal alignment for element.

<a name='P-AdaptiveCards-AdaptiveRichTextBlock-Inlines'></a>
### Inlines `property`

##### Summary

A list of text inlines in this RichTextBlock.

<a name='P-AdaptiveCards-AdaptiveRichTextBlock-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveSchemaVersion'></a>
## AdaptiveSchemaVersion `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the AdaptiveCards schema version.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion').

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-#ctor-System-String-'></a>
### #ctor(versionString) `constructor`

##### Summary

Initializes an [AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion') instance.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| versionString | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | A string representing the schema version. |

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-#ctor-System-Int32,System-Int32-'></a>
### #ctor(major,minor) `constructor`

##### Summary

Iniializes an [AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion') instance.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| major | [System.Int32](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Int32 'System.Int32') | The schema major version. |
| minor | [System.Int32](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Int32 'System.Int32') | The schema minor version. |

<a name='P-AdaptiveCards-AdaptiveSchemaVersion-Major'></a>
### Major `property`

##### Summary

Major version number.

<a name='P-AdaptiveCards-AdaptiveSchemaVersion-Minor'></a>
### Minor `property`

##### Summary

Minor version number.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-CompareTo-AdaptiveCards-AdaptiveSchemaVersion-'></a>
### CompareTo(other) `method`

##### Summary

Compares this instance to another instance.

##### Returns

0 iff the other AdaptiveSchemaVersion is equal to this one.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| other | [AdaptiveCards.AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion') | AdaptiveSchemaVersion instance to compare to. |

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-Equals-System-Object-'></a>
### Equals() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-GetHashCode'></a>
### GetHashCode() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-ToString'></a>
### ToString() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_Equality-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_Equality() `method`

##### Summary

Equality comparison operator.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_GreaterThan-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_GreaterThan() `method`

##### Summary

Greater-than operator.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_GreaterThanOrEqual-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_GreaterThanOrEqual() `method`

##### Summary

Greater-than-or-equal operator.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_Implicit-System-String-~AdaptiveCards-AdaptiveSchemaVersion'></a>
### op_Implicit(versionString) `method`

##### Summary

Implicit conversion operator from [String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') to [AdaptiveSchemaVersion](#T-AdaptiveCards-AdaptiveSchemaVersion 'AdaptiveCards.AdaptiveSchemaVersion').

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| versionString | [System.String)~AdaptiveCards.AdaptiveSchemaVersion](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String)~AdaptiveCards.AdaptiveSchemaVersion 'System.String)~AdaptiveCards.AdaptiveSchemaVersion') | A string representing the schema version. |

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_Inequality-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_Inequality() `method`

##### Summary

Inequality comparison operator.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_LessThan-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_LessThan() `method`

##### Summary

Less-than operator.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveSchemaVersion-op_LessThanOrEqual-AdaptiveCards-AdaptiveSchemaVersion,AdaptiveCards-AdaptiveSchemaVersion-'></a>
### op_LessThanOrEqual() `method`

##### Summary

Less-than-or-equal operator.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveSerializationException'></a>
## AdaptiveSerializationException `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an exception that occurs during serialization.

<a name='M-AdaptiveCards-AdaptiveSerializationException-#ctor'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveSerializationException-#ctor-System-String-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveSerializationException-#ctor-System-String,System-Exception-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='T-AdaptiveCards-AdaptiveShowCardAction'></a>
## AdaptiveShowCardAction `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Action.ShowCard element.

<a name='F-AdaptiveCards-AdaptiveShowCardAction-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveShowCardAction-Card'></a>
### Card `property`

##### Summary

[AdaptiveCard](#T-AdaptiveCards-AdaptiveCard 'AdaptiveCards.AdaptiveCard') to show when the action is invoked.

<a name='P-AdaptiveCards-AdaptiveShowCardAction-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveSpacing'></a>
## AdaptiveSpacing `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the spacing of an element.

<a name='F-AdaptiveCards-AdaptiveSpacing-Default'></a>
### Default `constants`

##### Summary

Use the default spacing.

<a name='F-AdaptiveCards-AdaptiveSpacing-ExtraLarge'></a>
### ExtraLarge `constants`

##### Summary

Use extra large spacing.

<a name='F-AdaptiveCards-AdaptiveSpacing-Large'></a>
### Large `constants`

##### Summary

Use large spacing.

<a name='F-AdaptiveCards-AdaptiveSpacing-Medium'></a>
### Medium `constants`

##### Summary

Use medium spacing.

<a name='F-AdaptiveCards-AdaptiveSpacing-None'></a>
### None `constants`

##### Summary

Use no spacing.

<a name='F-AdaptiveCards-AdaptiveSpacing-Padding'></a>
### Padding `constants`

##### Summary

This results in the same padding that's applied to the card itself.

<a name='F-AdaptiveCards-AdaptiveSpacing-Small'></a>
### Small `constants`

##### Summary

Use small spacing.

<a name='T-AdaptiveCards-AdaptiveSubmitAction'></a>
## AdaptiveSubmitAction `type`

##### Namespace

AdaptiveCards

##### Summary

Submit action gathers up input fields, merges with optional data field and generates event to client
    asking for data to be submitted. It is up to the client to determine how that data is processed. For
    example: With BotFramework bots the client would send an activity through the messaging medium to the bot.

<a name='F-AdaptiveCards-AdaptiveSubmitAction-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveSubmitAction-Data'></a>
### Data `property`

##### Summary

initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
    {"id":"123123123"}

<a name='P-AdaptiveCards-AdaptiveSubmitAction-DataJson'></a>
### DataJson `property`

##### Summary

Get or set the data as a JSON string.

<a name='P-AdaptiveCards-AdaptiveSubmitAction-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveTargetElement'></a>
## AdaptiveTargetElement `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the target of an Action.ToggleVisibility element.

<a name='M-AdaptiveCards-AdaptiveTargetElement-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement').

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveTargetElement-#ctor-System-String-'></a>
### #ctor(elementId) `constructor`

##### Summary

Initializes an [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement') instance with the supplied properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| elementId | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The id of the target element. |

<a name='M-AdaptiveCards-AdaptiveTargetElement-#ctor-System-String,System-Boolean-'></a>
### #ctor(elementId,isVisible) `constructor`

##### Summary

Initializes an [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement') instance with the supplied properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| elementId | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The Id of the target element. |
| isVisible | [System.Boolean](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Boolean 'System.Boolean') | Initial visible state. |

<a name='P-AdaptiveCards-AdaptiveTargetElement-ElementId'></a>
### ElementId `property`

##### Summary

Target element Id.

<a name='P-AdaptiveCards-AdaptiveTargetElement-IsVisible'></a>
### IsVisible `property`

##### Summary

Target element visibility.

<a name='P-AdaptiveCards-AdaptiveTargetElement-IsVisibleXml'></a>
### IsVisibleXml `property`

##### Summary

Helper to do custom serialization of [IsVisible](#P-AdaptiveCards-AdaptiveTargetElement-IsVisible 'AdaptiveCards.AdaptiveTargetElement.IsVisible') property for XML.

<a name='M-AdaptiveCards-AdaptiveTargetElement-ShouldSerializeIsVisibleXml'></a>
### ShouldSerializeIsVisibleXml() `method`

##### Summary

Determines whether the [IsVisibleXml](#P-AdaptiveCards-AdaptiveTargetElement-IsVisibleXml 'AdaptiveCards.AdaptiveTargetElement.IsVisibleXml') property should be serialized.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveTargetElement-op_Implicit-System-String-~AdaptiveCards-AdaptiveTargetElement'></a>
### op_Implicit(elementId) `method`

##### Summary

Implicit conversion from [String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') to [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement').

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| elementId | [System.String)~AdaptiveCards.AdaptiveTargetElement](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String)~AdaptiveCards.AdaptiveTargetElement 'System.String)~AdaptiveCards.AdaptiveTargetElement') |  |

<a name='T-AdaptiveCards-AdaptiveTextBlock'></a>
## AdaptiveTextBlock `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the TextBlock element.

<a name='M-AdaptiveCards-AdaptiveTextBlock-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveTextBlock](#T-AdaptiveCards-AdaptiveTextBlock 'AdaptiveCards.AdaptiveTextBlock') instance.

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveTextBlock-#ctor-System-String-'></a>
### #ctor(text) `constructor`

##### Summary

Initializes an [AdaptiveTextBlock](#T-AdaptiveCards-AdaptiveTextBlock 'AdaptiveCards.AdaptiveTextBlock') instance with the supplied text.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| text | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The text of this TextBlock. |

<a name='F-AdaptiveCards-AdaptiveTextBlock-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Color'></a>
### Color `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-FontType'></a>
### FontType `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-IsSubtle'></a>
### IsSubtle `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Italic'></a>
### Italic `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-MaxLines'></a>
### MaxLines `property`

##### Summary

When [Wrap](#P-AdaptiveCards-AdaptiveTextBlock-Wrap 'AdaptiveCards.AdaptiveTextBlock.Wrap') is true, this controls the maximum number of lines of text to display.

<a name='P-AdaptiveCards-AdaptiveTextBlock-MaxWidth'></a>
### MaxWidth `property`

##### Summary

The maximum width of the TextBlock.

<a name='P-AdaptiveCards-AdaptiveTextBlock-Size'></a>
### Size `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Strikethrough'></a>
### Strikethrough `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Text'></a>
### Text `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Weight'></a>
### Weight `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextBlock-Wrap'></a>
### Wrap `property`

##### Summary

Controls text wrapping behavior.

<a name='T-AdaptiveCards-AdaptiveTextColor'></a>
## AdaptiveTextColor `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the color style of TextBlock Elements

<a name='F-AdaptiveCards-AdaptiveTextColor-Accent'></a>
### Accent `constants`

##### Summary

Accent the text

<a name='F-AdaptiveCards-AdaptiveTextColor-Attention'></a>
### Attention `constants`

##### Summary

Highlight as needing attention (such as red)

<a name='F-AdaptiveCards-AdaptiveTextColor-Dark'></a>
### Dark `constants`

##### Summary

Forces the text to be rendered in a dark color which is suitable when displayed over a light background

<a name='F-AdaptiveCards-AdaptiveTextColor-Default'></a>
### Default `constants`

##### Summary

The default color which guarentees appropriate contrast

<a name='F-AdaptiveCards-AdaptiveTextColor-Good'></a>
### Good `constants`

##### Summary

Good (such as green)

<a name='F-AdaptiveCards-AdaptiveTextColor-Light'></a>
### Light `constants`

##### Summary

Forces the text to be rendered in a light color which is suitable when displayed over a dark background

<a name='F-AdaptiveCards-AdaptiveTextColor-Warning'></a>
### Warning `constants`

##### Summary

Warning (such as yellow)

<a name='T-AdaptiveCards-AdaptiveTextInput'></a>
## AdaptiveTextInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an Input.Text element.

<a name='F-AdaptiveCards-AdaptiveTextInput-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextInput-InlineAction'></a>
### InlineAction `property`

##### Summary

[AdaptiveAction](#T-AdaptiveCards-AdaptiveAction 'AdaptiveCards.AdaptiveAction') to invoke inline.

<a name='P-AdaptiveCards-AdaptiveTextInput-IsMultiline'></a>
### IsMultiline `property`

##### Summary

Controls whether multiple lines of text are allowed.

<a name='P-AdaptiveCards-AdaptiveTextInput-MaxLength'></a>
### MaxLength `property`

##### Summary

Hint of maximum number of characters to collect (may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveTextInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text to display when the input is empty.

<a name='P-AdaptiveCards-AdaptiveTextInput-Regex'></a>
### Regex `property`

##### Summary

Regular expression used for validating the input.

<a name='P-AdaptiveCards-AdaptiveTextInput-Style'></a>
### Style `property`

##### Summary

Hint of style of input, if client doesn't support the style it will become simple text input.

<a name='P-AdaptiveCards-AdaptiveTextInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field.

<a name='M-AdaptiveCards-AdaptiveTextInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveTextInputStyle'></a>
## AdaptiveTextInputStyle `type`

##### Namespace

AdaptiveCards

##### Summary

Style of text input.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Email'></a>
### Email `constants`

##### Summary

Input is an email address. The client may use this information to provide optimized keyboard input for the user.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Tel'></a>
### Tel `constants`

##### Summary

Input is a telephone number. The client may use this information to provide optimized keyboard input for the
user.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Text'></a>
### Text `constants`

##### Summary

Unstructured plain text.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Url'></a>
### Url `constants`

##### Summary

Input is a url. The client may use this information to provide optimized keyboard input for the user.

<a name='T-AdaptiveCards-AdaptiveTextRun'></a>
## AdaptiveTextRun `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a TextRun.

<a name='M-AdaptiveCards-AdaptiveTextRun-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes an empty [AdaptiveTextRun](#T-AdaptiveCards-AdaptiveTextRun 'AdaptiveCards.AdaptiveTextRun').

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-AdaptiveTextRun-#ctor-System-String-'></a>
### #ctor(text) `constructor`

##### Summary

Initializes an [AdaptiveTextRun](#T-AdaptiveCards-AdaptiveTextRun 'AdaptiveCards.AdaptiveTextRun') with the given text.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| text | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The initial text for this TextRun. |

<a name='F-AdaptiveCards-AdaptiveTextRun-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Color'></a>
### Color `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-FontType'></a>
### FontType `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Highlight'></a>
### Highlight `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-IsSubtle'></a>
### IsSubtle `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Italic'></a>
### Italic `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for this text run

<a name='P-AdaptiveCards-AdaptiveTextRun-Size'></a>
### Size `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Strikethrough'></a>
### Strikethrough `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Text'></a>
### Text `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTextRun-Underline'></a>
### Underline `property`

##### Summary

Display this text underlined.

<a name='P-AdaptiveCards-AdaptiveTextRun-Weight'></a>
### Weight `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveTextSize'></a>
## AdaptiveTextSize `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the relative size of TextBlock elements

<a name='F-AdaptiveCards-AdaptiveTextSize-Default'></a>
### Default `constants`

##### Summary

Default text size

<a name='F-AdaptiveCards-AdaptiveTextSize-ExtraLarge'></a>
### ExtraLarge `constants`

##### Summary

The largest text size

<a name='F-AdaptiveCards-AdaptiveTextSize-Large'></a>
### Large `constants`

##### Summary

Slightly larger then medium

<a name='F-AdaptiveCards-AdaptiveTextSize-Medium'></a>
### Medium `constants`

##### Summary

Slightly larger than default

<a name='F-AdaptiveCards-AdaptiveTextSize-Normal'></a>
### Normal `constants`

##### Summary

Default text size

<a name='F-AdaptiveCards-AdaptiveTextSize-Small'></a>
### Small `constants`

##### Summary

Smallest text size

<a name='T-AdaptiveCards-AdaptiveTextWeight'></a>
## AdaptiveTextWeight `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the weight of TextBock Elements

<a name='F-AdaptiveCards-AdaptiveTextWeight-Bolder'></a>
### Bolder `constants`

##### Summary

Bolder text (wider stroke)

<a name='F-AdaptiveCards-AdaptiveTextWeight-Default'></a>
### Default `constants`

##### Summary

The default text weight

<a name='F-AdaptiveCards-AdaptiveTextWeight-Lighter'></a>
### Lighter `constants`

##### Summary

Lighter text (thinner stroke)

<a name='F-AdaptiveCards-AdaptiveTextWeight-Normal'></a>
### Normal `constants`

##### Summary

The default text weight

<a name='T-AdaptiveCards-AdaptiveTimeInput'></a>
## AdaptiveTimeInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Input.Time element.

<a name='F-AdaptiveCards-AdaptiveTimeInput-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTimeInput-Max'></a>
### Max `property`

##### Summary

Hint of maximum value (may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveTimeInput-Min'></a>
### Min `property`

##### Summary

Hint of minimum value (may be ignored by some clients).

<a name='P-AdaptiveCards-AdaptiveTimeInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text to display when the input is empty.

<a name='P-AdaptiveCards-AdaptiveTimeInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTimeInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field.

<a name='M-AdaptiveCards-AdaptiveTimeInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveToggleInput'></a>
## AdaptiveToggleInput `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Input.Toggle element.

<a name='F-AdaptiveCards-AdaptiveToggleInput-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveToggleInput-Title'></a>
### Title `property`

##### Summary

Title text for this element.

<a name='P-AdaptiveCards-AdaptiveToggleInput-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveToggleInput-Value'></a>
### Value `property`

##### Summary

The value for the field.

<a name='P-AdaptiveCards-AdaptiveToggleInput-ValueOff'></a>
### ValueOff `property`

##### Summary

Value to use when toggle is off.

<a name='P-AdaptiveCards-AdaptiveToggleInput-ValueOn'></a>
### ValueOn `property`

##### Summary

Value to use when toggle is on.

<a name='P-AdaptiveCards-AdaptiveToggleInput-Wrap'></a>
### Wrap `property`

##### Summary

Controls text wrapping behavior.

<a name='M-AdaptiveCards-AdaptiveToggleInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveToggleVisibilityAction'></a>
## AdaptiveToggleVisibilityAction `type`

##### Namespace

AdaptiveCards

##### Summary

Represents the Action.ToggleVisibility element.

<a name='F-AdaptiveCards-AdaptiveToggleVisibilityAction-TypeName'></a>
### TypeName `constants`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveToggleVisibilityAction-TargetElements'></a>
### TargetElements `property`

##### Summary

Ids of elements whose visibility this element should change.

<a name='P-AdaptiveCards-AdaptiveToggleVisibilityAction-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveTypedBaseElementConverter'></a>
## AdaptiveTypedBaseElementConverter `type`

##### Namespace

AdaptiveCards

##### Summary

JsonConverters that deserialize to AdaptiveCards elements and use ParseContext must inherit this class.
ParseContext provides id generation, id collision detections, and other useful services during deserialization.

<a name='P-AdaptiveCards-AdaptiveTypedBaseElementConverter-ParseContext'></a>
### ParseContext `property`

##### Summary

The [ParseContext](#P-AdaptiveCards-AdaptiveTypedBaseElementConverter-ParseContext 'AdaptiveCards.AdaptiveTypedBaseElementConverter.ParseContext') to use while parsing in AdaptiveCards.

<a name='T-AdaptiveCards-AdaptiveTypedElement'></a>
## AdaptiveTypedElement `type`

##### Namespace

AdaptiveCards

##### Summary

Base for almost all representable elements in AdaptiveCards.

<a name='F-AdaptiveCards-AdaptiveTypedElement-Requires'></a>
### Requires `constants`

##### Summary

A collection representing features and feature versions that this element requires.

<a name='P-AdaptiveCards-AdaptiveTypedElement-AdditionalProperties'></a>
### AdditionalProperties `property`

##### Summary

Additional properties not found on the default schema.

<a name='P-AdaptiveCards-AdaptiveTypedElement-Fallback'></a>
### Fallback `property`

##### Summary

The fallback property controls behavior when an unexpected element or error is encountered.

<a name='P-AdaptiveCards-AdaptiveTypedElement-Id'></a>
### Id `property`

##### Summary

A unique ID associated with the element. For Inputs, the ID will be used as the key for Action.Submit response.

<a name='P-AdaptiveCards-AdaptiveTypedElement-InternalID'></a>
### InternalID `property`

##### Summary

The [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') for this element.

<a name='P-AdaptiveCards-AdaptiveTypedElement-Type'></a>
### Type `property`

##### Summary

The AdaptiveCard element that this class implements.

<a name='M-AdaptiveCards-AdaptiveTypedElement-MeetsRequirements-AdaptiveCards-AdaptiveFeatureRegistration-'></a>
### MeetsRequirements(featureRegistration) `method`

##### Summary

Determines if this element's requirements are satisfied.

##### Returns

true iff this element's requirements are met.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| featureRegistration | [AdaptiveCards.AdaptiveFeatureRegistration](#T-AdaptiveCards-AdaptiveFeatureRegistration 'AdaptiveCards.AdaptiveFeatureRegistration') | The host's [AdaptiveFeatureRegistration](#T-AdaptiveCards-AdaptiveFeatureRegistration 'AdaptiveCards.AdaptiveFeatureRegistration'). |

<a name='M-AdaptiveCards-AdaptiveTypedElement-ShouldSerializeAdditionalProperties'></a>
### ShouldSerializeAdditionalProperties() `method`

##### Summary

Determines whether the [AdditionalProperties](#P-AdaptiveCards-AdaptiveTypedElement-AdditionalProperties 'AdaptiveCards.AdaptiveTypedElement.AdditionalProperties') property should be serialized.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveTypedElementConverter'></a>
## AdaptiveTypedElementConverter `type`

##### Namespace

AdaptiveCards

##### Summary

This handles using the type field to instantiate strongly typed objects on deserialization.

<a name='F-AdaptiveCards-AdaptiveTypedElementConverter-TypedElementTypes'></a>
### TypedElementTypes `constants`

##### Summary

Default types to support, register any new types to this list

<a name='P-AdaptiveCards-AdaptiveTypedElementConverter-CanRead'></a>
### CanRead `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTypedElementConverter-CanWrite'></a>
### CanWrite `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-AdaptiveTypedElementConverter-Warnings'></a>
### Warnings `property`

##### Summary

The list of warnings generated while converting.

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-CanConvert-System-Type-'></a>
### CanConvert() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-CreateElement``1-System-String-'></a>
### CreateElement\`\`1() `method`

##### Summary

Instantiates a new strongly-typed element of the given type.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-GetElementTypeName-System-Type,Newtonsoft-Json-Linq-JObject-'></a>
### GetElementTypeName() `method`

##### Summary

Retrieves the type name of an AdaptiveCards object.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-RegisterTypedElement``1-System-String-'></a>
### RegisterTypedElement\`\`1(typeName) `method`

##### Summary

Registers a new element with the element converter.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| typeName | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The [Type](#P-AdaptiveCards-AdaptiveTypedElement-Type 'AdaptiveCards.AdaptiveTypedElement.Type') of the element to register. |

<a name='M-AdaptiveCards-AdaptiveTypedElementConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveUnknownAction'></a>
## AdaptiveUnknownAction `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an unknown action encountered while parsing.

<a name='P-AdaptiveCards-AdaptiveUnknownAction-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveUnknownElement'></a>
## AdaptiveUnknownElement `type`

##### Namespace

AdaptiveCards

##### Summary

Represents an unknown element encountered while parsing.

<a name='P-AdaptiveCards-AdaptiveUnknownElement-Type'></a>
### Type `property`

##### Summary

*Inherit from parent.*

<a name='T-AdaptiveCards-AdaptiveVerticalAlignment'></a>
## AdaptiveVerticalAlignment `type`

##### Namespace

AdaptiveCards

##### Summary

Defines the vertical alignment behavior of an element.

<a name='F-AdaptiveCards-AdaptiveVerticalAlignment-Bottom'></a>
### Bottom `constants`

##### Summary

Align to the bottom.

<a name='F-AdaptiveCards-AdaptiveVerticalAlignment-Center'></a>
### Center `constants`

##### Summary

Centered.

<a name='F-AdaptiveCards-AdaptiveVerticalAlignment-Top'></a>
### Top `constants`

##### Summary

Align to the top.

<a name='T-AdaptiveCards-AdaptiveVerticalContentAlignment'></a>
## AdaptiveVerticalContentAlignment `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the vertical alignment of child elements within a container.

<a name='F-AdaptiveCards-AdaptiveVerticalContentAlignment-Bottom'></a>
### Bottom `constants`

##### Summary

Align to the bottom of the container.

<a name='F-AdaptiveCards-AdaptiveVerticalContentAlignment-Center'></a>
### Center `constants`

##### Summary

Center within the container.

<a name='F-AdaptiveCards-AdaptiveVerticalContentAlignment-Top'></a>
### Top `constants`

##### Summary

Align to the top.

<a name='T-AdaptiveCards-Rendering-AdaptiveVisitor'></a>
## AdaptiveVisitor `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Utility class which allows you to visit every node

<a name='T-AdaptiveCards-AdaptiveWarning'></a>
## AdaptiveWarning `type`

##### Namespace

AdaptiveCards

##### Summary

Represents a warning generated while parsing.

<a name='M-AdaptiveCards-AdaptiveWarning-#ctor-System-Int32,System-String-'></a>
### #ctor(code,message) `constructor`

##### Summary

Initializes an [AdaptiveWarning](#T-AdaptiveCards-AdaptiveWarning 'AdaptiveCards.AdaptiveWarning') instance with the given properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| code | [System.Int32](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Int32 'System.Int32') | The [WarningStatusCode](#T-AdaptiveCards-AdaptiveWarning-WarningStatusCode 'AdaptiveCards.AdaptiveWarning.WarningStatusCode') encountered. |
| message | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The warning message. |

<a name='P-AdaptiveCards-AdaptiveWarning-Code'></a>
### Code `property`

##### Summary

The [WarningStatusCode](#T-AdaptiveCards-AdaptiveWarning-WarningStatusCode 'AdaptiveCards.AdaptiveWarning.WarningStatusCode').

<a name='P-AdaptiveCards-AdaptiveWarning-Message'></a>
### Message `property`

##### Summary

The warning message.

<a name='T-AdaptiveCards-ColorUtil'></a>
## ColorUtil `type`

##### Namespace

AdaptiveCards

##### Summary

A collection of utilities for processing colors.

<a name='F-AdaptiveCards-ColorUtil-alphaColorLength'></a>
### alphaColorLength `constants`

##### Summary

The length of a string in the "#AARRGGBB" format.

<a name='F-AdaptiveCards-ColorUtil-colorStringLength'></a>
### colorStringLength `constants`

##### Summary

The length of a string in the "#RRGGBB" format.

<a name='M-AdaptiveCards-ColorUtil-GenerateLighterColor-System-String-'></a>
### GenerateLighterColor(hexColor) `method`

##### Summary

Create a color that's 25% lighter than the given color.

##### Returns

A 25% brighter version of the supplied color, or "#FF000000" if hexColor is an invalid format.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| hexColor | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | A string in the format of #AARRGGBB or #RRGGBB to lighten. |

<a name='M-AdaptiveCards-ColorUtil-IsValidColor-System-String-'></a>
### IsValidColor(color) `method`

##### Summary

Determines if a string is a valid string of the format #AARRGGBB or #RRGGBB.

##### Returns

true iff the string is of the format #AARRGGBB or #RRGGBB.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| color | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The string to test for color format. |

<a name='M-AdaptiveCards-ColorUtil-TryParseColor-System-String,System-Int32@-'></a>
### TryParseColor(color,result) `method`

##### Summary

Attempts to parse the supplied string as an integer if it is a valid color format.

##### Returns

true iff the string was successfully converted.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| color | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The string to convert to an int. |
| result | [System.Int32@](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Int32@ 'System.Int32@') | The result of converting the string. |

<a name='T-AdaptiveCards-Rendering-ContainerStyleConfig'></a>
## ContainerStyleConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-ContainerStyleConfig-BackgroundColor'></a>
### BackgroundColor `property`

##### Summary

The background color to use for this container

<a name='P-AdaptiveCards-Rendering-ContainerStyleConfig-ForegroundColors'></a>
### ForegroundColors `property`

##### Summary

The font colors to use for this container

<a name='T-AdaptiveCards-ParseContext-ContextType'></a>
## ContextType `type`

##### Namespace

AdaptiveCards.ParseContext

##### Summary

Denotes what type of AdaptiveCard element this ParseContext represents.

<a name='F-AdaptiveCards-ParseContext-ContextType-Action'></a>
### Action `constants`

##### Summary

Represents an Action (i.e. something that belongs in an ActionSet or in the actions of a card).

<a name='F-AdaptiveCards-ParseContext-ContextType-Element'></a>
### Element `constants`

##### Summary

Represents an Element (i.e. something that belongs in the body of a card).

<a name='T-AdaptiveCards-Rendering-ErrorMessageConfig'></a>
## ErrorMessageConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of media

<a name='P-AdaptiveCards-Rendering-ErrorMessageConfig-Size'></a>
### Size `property`

##### Summary

The text size of the label

<a name='P-AdaptiveCards-Rendering-ErrorMessageConfig-Spacing'></a>
### Spacing `property`

##### Summary

The text color of the label

<a name='P-AdaptiveCards-Rendering-ErrorMessageConfig-Weight'></a>
### Weight `property`

##### Summary

The text weight of the label

<a name='T-AdaptiveCards-Rendering-FactSetConfig'></a>
## FactSetConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-FactSetConfig-Spacing'></a>
### Spacing `property`

##### Summary

Spacing between facts and values

<a name='P-AdaptiveCards-Rendering-FactSetConfig-Title'></a>
### Title `property`

##### Summary

TextBlock to use for Titles in factsets

<a name='P-AdaptiveCards-Rendering-FactSetConfig-Value'></a>
### Value `property`

##### Summary

TextBlock to use for Values in fact sets

<a name='T-AdaptiveCards-Rendering-FontColorConfig'></a>
## FontColorConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-FontColorConfig-Default'></a>
### Default `property`

##### Summary

Color in #RRGGBB format

<a name='T-AdaptiveCards-HashColorConverter'></a>
## HashColorConverter `type`

##### Namespace

AdaptiveCards

##### Summary

Helper class to validate and convert color strings.

<a name='P-AdaptiveCards-HashColorConverter-CanWrite'></a>
### CanWrite `property`

##### Summary

*Inherit from parent.*

<a name='P-AdaptiveCards-HashColorConverter-Warnings'></a>
### Warnings `property`

##### Summary

A list of warnings encountered during processing.

<a name='M-AdaptiveCards-HashColorConverter-CanConvert-System-Type-'></a>
### CanConvert() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-HashColorConverter-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-HashColorConverter-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Rendering-HighlightColorConfig'></a>
## HighlightColorConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-HighlightColorConfig-Default'></a>
### Default `property`

##### Summary

Color in #RRGGBB format

<a name='T-AdaptiveCards-IAdaptiveTextElement'></a>
## IAdaptiveTextElement `type`

##### Namespace

AdaptiveCards

##### Summary

Interface encapsulating the properties of an AdaptiveCards element that displays text.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Color'></a>
### Color `property`

##### Summary

The color to use while displaying the text.

<a name='P-AdaptiveCards-IAdaptiveTextElement-FontType'></a>
### FontType `property`

##### Summary

Controls which [AdaptiveFontType](#T-AdaptiveCards-AdaptiveFontType 'AdaptiveCards.AdaptiveFontType') is used to display the text.

<a name='P-AdaptiveCards-IAdaptiveTextElement-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Make the text less prominent when displayed.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Italic'></a>
### Italic `property`

##### Summary

Display the text using italics.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Size'></a>
### Size `property`

##### Summary

The size to use while displaying the text.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Strikethrough'></a>
### Strikethrough `property`

##### Summary

Display this text with strikethrough.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Text'></a>
### Text `property`

##### Summary

The text to display.

<a name='P-AdaptiveCards-IAdaptiveTextElement-Weight'></a>
### Weight `property`

##### Summary

The weight to use while displaying the text.

<a name='T-AdaptiveCards-Rendering-IconPlacement'></a>
## IconPlacement `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Controls where to place icons in actions.

<a name='F-AdaptiveCards-Rendering-IconPlacement-AboveTitle'></a>
### AboveTitle `constants`

##### Summary

Display icons above text.

<a name='F-AdaptiveCards-Rendering-IconPlacement-LeftOfTitle'></a>
### LeftOfTitle `constants`

##### Summary

Display icons to the left of the text.

<a name='T-AdaptiveCards-IgnoreEmptyItemsConverter`1'></a>
## IgnoreEmptyItemsConverter\`1 `type`

##### Namespace

AdaptiveCards

##### Summary

JSON converter that will drop empty element items.

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | Type of the objects to be converted. |

<a name='P-AdaptiveCards-IgnoreEmptyItemsConverter`1-CanWrite'></a>
### CanWrite `property`

##### Summary

*Inherit from parent.*

<a name='M-AdaptiveCards-IgnoreEmptyItemsConverter`1-CanConvert-System-Type-'></a>
### CanConvert() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-IgnoreEmptyItemsConverter`1-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-IgnoreEmptyItemsConverter`1-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-IgnoreNullEnumConverter`1'></a>
## IgnoreNullEnumConverter\`1 `type`

##### Namespace

AdaptiveCards

##### Summary

JSON converter that will ignore enum values that can't be parsed correctly.

<a name='M-AdaptiveCards-IgnoreNullEnumConverter`1-#ctor'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-IgnoreNullEnumConverter`1-#ctor-System-Boolean-'></a>
### #ctor() `constructor`

##### Summary

*Inherit from parent.*

##### Parameters

This constructor has no parameters.

<a name='P-AdaptiveCards-IgnoreNullEnumConverter`1-Warnings'></a>
### Warnings `property`

##### Summary

*Inherit from parent.*

<a name='M-AdaptiveCards-IgnoreNullEnumConverter`1-ReadJson-Newtonsoft-Json-JsonReader,System-Type,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### ReadJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-IgnoreNullEnumConverter`1-WriteJson-Newtonsoft-Json-JsonWriter,System-Object,Newtonsoft-Json-JsonSerializer-'></a>
### WriteJson() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Rendering-InputLabelConfig'></a>
## InputLabelConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of media

<a name='P-AdaptiveCards-Rendering-InputLabelConfig-Color'></a>
### Color `property`

##### Summary

The text color of the label

<a name='P-AdaptiveCards-Rendering-InputLabelConfig-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Make the label less prominent

<a name='P-AdaptiveCards-Rendering-InputLabelConfig-Size'></a>
### Size `property`

##### Summary

The text size of the label

<a name='P-AdaptiveCards-Rendering-InputLabelConfig-Suffix'></a>
### Suffix `property`

##### Summary

Suffix to be displayed next to the label. Only respected for required inputs

<a name='P-AdaptiveCards-Rendering-InputLabelConfig-Weight'></a>
### Weight `property`

##### Summary

The text weight of the label

<a name='T-AdaptiveCards-Rendering-InputsConfig'></a>
## InputsConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of media

<a name='T-AdaptiveCards-JsonExtensions'></a>
## JsonExtensions `type`

##### Namespace

AdaptiveCards

##### Summary

Helper class for color validation.

<a name='M-AdaptiveCards-JsonExtensions-IsHexDigit-System-Char-'></a>
### IsHexDigit(c) `method`

##### Summary

Determines if a character is a valid hex digit.

##### Returns

true iff c is a valid hex digit.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| c | [System.Char](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Char 'System.Char') | Character to check. |

<a name='T-AdaptiveCards-Rendering-LabelConfig'></a>
## LabelConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of input labels

<a name='P-AdaptiveCards-Rendering-LabelConfig-InputSpacing'></a>
### InputSpacing `property`

##### Summary

Specifies the spacing between the label and the input

<a name='T-AdaptiveCards-Rendering-MediaConfig'></a>
## MediaConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of media

<a name='P-AdaptiveCards-Rendering-MediaConfig-AllowInlinePlayback'></a>
### AllowInlinePlayback `property`

##### Summary

Controls whether the media is played in the card or sent to host

<a name='P-AdaptiveCards-Rendering-MediaConfig-DefaultPoster'></a>
### DefaultPoster `property`

##### Summary

Default poster URL to use for media thumbnail

<a name='P-AdaptiveCards-Rendering-MediaConfig-PlayButton'></a>
### PlayButton `property`

##### Summary

Play button URL to use for media thumbnail

<a name='T-AdaptiveCards-ParseContext'></a>
## ParseContext `type`

##### Namespace

AdaptiveCards

##### Summary

Encapsulates state necessary to correctly parse an AdaptiveCard.

<a name='P-AdaptiveCards-ParseContext-Type'></a>
### Type `property`

##### Summary

Tracks the most recently encountered element type.

<a name='M-AdaptiveCards-ParseContext-GetNearestFallbackID-AdaptiveCards-AdaptiveInternalID-'></a>
### GetNearestFallbackID(skipID) `method`

##### Summary

Walk stack looking for first element to be marked fallback (which isn't the ID we're supposed to
skip), then return its internal ID. If none, return an invalid ID.

##### Returns

The [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') of the nearest element with fallback, or an invalid [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') if there is no element with fallback.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| skipID | [AdaptiveCards.AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') | [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') of the element to ignore. |

<a name='M-AdaptiveCards-ParseContext-PopElement'></a>
### PopElement() `method`

##### Summary

Pops an element off of the context stack.

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-ParseContext-PushElement-System-String,AdaptiveCards-AdaptiveInternalID-'></a>
### PushElement(idJsonProperty,internalId) `method`

##### Summary

Pushes the supplied element state on to the context stack.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| idJsonProperty | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The value of the current element's "id" property. |
| internalId | [AdaptiveCards.AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID') | The current element's [AdaptiveInternalID](#T-AdaptiveCards-AdaptiveInternalID 'AdaptiveCards.AdaptiveInternalID'). |

##### Remarks

Used by element converters to determine how to perform element fallback.

<a name='T-AdaptiveCards-RemoteResourceInformation'></a>
## RemoteResourceInformation `type`

##### Namespace

AdaptiveCards

##### Summary

Contains information about a remote source.

<a name='M-AdaptiveCards-RemoteResourceInformation-#ctor-System-String,System-String-'></a>
### #ctor(url,mimeType) `constructor`

##### Summary

Initializes a [RemoteResourceInformation](#T-AdaptiveCards-RemoteResourceInformation 'AdaptiveCards.RemoteResourceInformation') with the given properties.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| url | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The URL of the remote resource. |
| mimeType | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The mimetype of the remote resource. |

<a name='T-AdaptiveCards-Rendering-RenderedAdaptiveCardBase'></a>
## RenderedAdaptiveCardBase `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

The base class for RenderedAdaptiveCard. Renderers extend this class to provide their native UI element property.

<a name='P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-OriginatingCard'></a>
### OriginatingCard `property`

##### Summary

The card that the visual was rendered from.

<a name='P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-UserInputs'></a>
### UserInputs `property`

##### Summary

Provides access to the input fields on a card

<a name='P-AdaptiveCards-Rendering-RenderedAdaptiveCardBase-Warnings'></a>
### Warnings `property`

##### Summary

If any modifications were done to the rendered card they will be reported here

<a name='T-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs'></a>
## RenderedAdaptiveCardInputs `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Provides access to the input fields on a card

<a name='M-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs-AsDictionary'></a>
### AsDictionary() `method`

##### Summary

Read the input fields as a Dictionary. All input values will serialize the strings

##### Returns



##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-RenderedAdaptiveCardInputs-AsJson'></a>
### AsJson() `method`

##### Summary

Read the input fields as a JSON object. All input values will serialize to strings

##### Returns



##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Rendering-RendererUtilities'></a>
## RendererUtilities `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Utility methods for dealing with body and binding

<a name='M-AdaptiveCards-Rendering-RendererUtilities-ApplyTextFunctions-System-String,System-String-'></a>
### ApplyTextFunctions(text) `method`

##### Summary

This funct will return modified text replacing {{DATE|TIME()}} style functions as the formatted text

##### Returns



##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| text | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') |  |

<a name='T-AdaptiveCards-Rendering-SeparatorConfig'></a>
## SeparatorConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-SeparatorConfig-LineColor'></a>
### LineColor `property`

##### Summary

If there is a visible color, what color to use

<a name='P-AdaptiveCards-Rendering-SeparatorConfig-LineThickness'></a>
### LineThickness `property`

##### Summary

If there is a visible line, how thick should the line be

<a name='T-AdaptiveCards-Rendering-ShowCardActionMode'></a>
## ShowCardActionMode `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Controls the behavior of an invoked Action.ShowCard.

<a name='F-AdaptiveCards-Rendering-ShowCardActionMode-Inline'></a>
### Inline `constants`

##### Summary

Expand the Action.ShowCard in-place.

<a name='F-AdaptiveCards-Rendering-ShowCardActionMode-Popup'></a>
### Popup `constants`

##### Summary

Display the Action.ShowCard in a popup window.

<a name='T-AdaptiveCards-Rendering-ShowCardConfig'></a>
## ShowCardConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Configuration for Action.ShowCard elements.

<a name='M-AdaptiveCards-Rendering-ShowCardConfig-#ctor'></a>
### #ctor() `constructor`

##### Summary

Initializes a default [ShowCardConfig](#T-AdaptiveCards-Rendering-ShowCardConfig 'AdaptiveCards.Rendering.ShowCardConfig').

##### Parameters

This constructor has no parameters.

<a name='P-AdaptiveCards-Rendering-ShowCardConfig-ActionMode'></a>
### ActionMode `property`

##### Summary

Controls how Action.ShowCard elements behave when invoked.

<a name='P-AdaptiveCards-Rendering-ShowCardConfig-InlineTopMargin'></a>
### InlineTopMargin `property`

##### Summary

Controls the margin to use when showing an inline Action.ShowCard.

<a name='P-AdaptiveCards-Rendering-ShowCardConfig-Style'></a>
### Style `property`

##### Summary

Determines what style to use when displaying an inline Action.ShowCard.

<a name='T-AdaptiveCards-Rendering-SpacingsConfig'></a>
## SpacingsConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Specifies how much spacing should be used for the various spacing options

<a name='T-AdaptiveCards-Rendering-TextBlockConfig'></a>
## TextBlockConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-Color'></a>
### Color `property`

##### Summary

The color of the text

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Should it be subtle?

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-MaxWidth'></a>
### MaxWidth `property`

##### Summary

The maximum width for text

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-Size'></a>
### Size `property`

##### Summary

The size of the text

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-Weight'></a>
### Weight `property`

##### Summary

The weight of the text

<a name='P-AdaptiveCards-Rendering-TextBlockConfig-Wrap'></a>
### Wrap `property`

##### Summary

Is it allowed for the text to wrap

<a name='T-AdaptiveCards-WarningLoggingContractResolver'></a>
## WarningLoggingContractResolver `type`

##### Namespace

AdaptiveCards

##### Summary

This JSON contract resolver checks if the JsonConverter can log warnings, and if so sets the Warnings property

<a name='M-AdaptiveCards-WarningLoggingContractResolver-CreateProperty-System-Reflection-MemberInfo,Newtonsoft-Json-MemberSerialization-'></a>
### CreateProperty(member,memberSerialization) `method`

##### Summary

Override when a member property is being instantiated. At this point we know what converter
    is being used for the property. If the converter can log warnings, then give it our collection

##### Returns



##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| member | [System.Reflection.MemberInfo](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Reflection.MemberInfo 'System.Reflection.MemberInfo') |  |
| memberSerialization | [Newtonsoft.Json.MemberSerialization](#T-Newtonsoft-Json-MemberSerialization 'Newtonsoft.Json.MemberSerialization') |  |

<a name='T-AdaptiveCards-AdaptiveWarning-WarningStatusCode'></a>
## WarningStatusCode `type`

##### Namespace

AdaptiveCards.AdaptiveWarning

##### Summary

Status code representing the type of warning encountered.

<a name='F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-EmptyLabelInRequiredInput'></a>
### EmptyLabelInRequiredInput `constants`

##### Summary

An input was marked as requiring input, but didn't have a label.

<a name='F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-InvalidLanguage'></a>
### InvalidLanguage `constants`

##### Summary

The supplied language was not valid.

<a name='F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-MaxActionsExceeded'></a>
### MaxActionsExceeded `constants`

##### Summary

The maximum number of [AdaptiveAction](#T-AdaptiveCards-AdaptiveAction 'AdaptiveCards.AdaptiveAction')s was exceeded.

<a name='F-AdaptiveCards-AdaptiveWarning-WarningStatusCode-UnsupportedSchemaVersion'></a>
### UnsupportedSchemaVersion `constants`

##### Summary

The supplied schema version wasn't recognized.
