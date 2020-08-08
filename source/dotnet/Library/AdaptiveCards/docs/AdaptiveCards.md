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
  - [IsSupported()](#M-AdaptiveCards-Rendering-AdaptiveActionHandlers-IsSupported-System-Type- 'AdaptiveCards.Rendering.AdaptiveActionHandlers.IsSupported(System.Type)')
  - [RemoveSupportedAction\`\`1()](#M-AdaptiveCards-Rendering-AdaptiveActionHandlers-RemoveSupportedAction``1 'AdaptiveCards.Rendering.AdaptiveActionHandlers.RemoveSupportedAction``1')
- [AdaptiveActionSet](#T-AdaptiveCards-AdaptiveActionSet 'AdaptiveCards.AdaptiveActionSet')
  - [Actions](#P-AdaptiveCards-AdaptiveActionSet-Actions 'AdaptiveCards.AdaptiveActionSet.Actions')
- [AdaptiveBarChart](#T-AdaptiveCards-AdaptiveBarChart 'AdaptiveCards.AdaptiveBarChart')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveBarChart-#ctor 'AdaptiveCards.AdaptiveBarChart.#ctor')
- [AdaptiveCard](#T-AdaptiveCards-AdaptiveCard 'AdaptiveCards.AdaptiveCard')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveCard-#ctor-AdaptiveCards-AdaptiveSchemaVersion- 'AdaptiveCards.AdaptiveCard.#ctor(AdaptiveCards.AdaptiveSchemaVersion)')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveCard-#ctor-System-String- 'AdaptiveCards.AdaptiveCard.#ctor(System.String)')
  - [#ctor()](#M-AdaptiveCards-AdaptiveCard-#ctor 'AdaptiveCards.AdaptiveCard.#ctor')
  - [KnownSchemaVersion](#F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion 'AdaptiveCards.AdaptiveCard.KnownSchemaVersion')
  - [Actions](#P-AdaptiveCards-AdaptiveCard-Actions 'AdaptiveCards.AdaptiveCard.Actions')
  - [BackgroundImage](#P-AdaptiveCards-AdaptiveCard-BackgroundImage 'AdaptiveCards.AdaptiveCard.BackgroundImage')
  - [Body](#P-AdaptiveCards-AdaptiveCard-Body 'AdaptiveCards.AdaptiveCard.Body')
  - [FallbackText](#P-AdaptiveCards-AdaptiveCard-FallbackText 'AdaptiveCards.AdaptiveCard.FallbackText')
  - [Height](#P-AdaptiveCards-AdaptiveCard-Height 'AdaptiveCards.AdaptiveCard.Height')
  - [JsonSchema](#P-AdaptiveCards-AdaptiveCard-JsonSchema 'AdaptiveCards.AdaptiveCard.JsonSchema')
  - [Lang](#P-AdaptiveCards-AdaptiveCard-Lang 'AdaptiveCards.AdaptiveCard.Lang')
  - [OnDeserializingMissingVersion](#P-AdaptiveCards-AdaptiveCard-OnDeserializingMissingVersion 'AdaptiveCards.AdaptiveCard.OnDeserializingMissingVersion')
  - [PixelMinHeight](#P-AdaptiveCards-AdaptiveCard-PixelMinHeight 'AdaptiveCards.AdaptiveCard.PixelMinHeight')
  - [SelectAction](#P-AdaptiveCards-AdaptiveCard-SelectAction 'AdaptiveCards.AdaptiveCard.SelectAction')
  - [Speak](#P-AdaptiveCards-AdaptiveCard-Speak 'AdaptiveCards.AdaptiveCard.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveCard-Title 'AdaptiveCards.AdaptiveCard.Title')
  - [Version](#P-AdaptiveCards-AdaptiveCard-Version 'AdaptiveCards.AdaptiveCard.Version')
  - [VerticalContentAlignment](#P-AdaptiveCards-AdaptiveCard-VerticalContentAlignment 'AdaptiveCards.AdaptiveCard.VerticalContentAlignment')
  - [FromJson(json)](#M-AdaptiveCards-AdaptiveCard-FromJson-System-String- 'AdaptiveCards.AdaptiveCard.FromJson(System.String)')
  - [GetResourceInformation()](#M-AdaptiveCards-AdaptiveCard-GetResourceInformation 'AdaptiveCards.AdaptiveCard.GetResourceInformation')
  - [ToJson()](#M-AdaptiveCards-AdaptiveCard-ToJson 'AdaptiveCards.AdaptiveCard.ToJson')
- [AdaptiveCardParseResult](#T-AdaptiveCards-AdaptiveCardParseResult 'AdaptiveCards.AdaptiveCardParseResult')
  - [Card](#P-AdaptiveCards-AdaptiveCardParseResult-Card 'AdaptiveCards.AdaptiveCardParseResult.Card')
  - [Warnings](#P-AdaptiveCards-AdaptiveCardParseResult-Warnings 'AdaptiveCards.AdaptiveCardParseResult.Warnings')
- [AdaptiveCardRendererBase\`2](#T-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2')
  - [ElementRenderers](#P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-ElementRenderers 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.ElementRenderers')
  - [HostConfig](#P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-HostConfig 'AdaptiveCards.Rendering.AdaptiveCardRendererBase`2.HostConfig')
- [AdaptiveChart](#T-AdaptiveCards-AdaptiveChart 'AdaptiveCards.AdaptiveChart')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveChart-#ctor 'AdaptiveCards.AdaptiveChart.#ctor')
  - [Data](#P-AdaptiveCards-AdaptiveChart-Data 'AdaptiveCards.AdaptiveChart.Data')
- [AdaptiveChoice](#T-AdaptiveCards-AdaptiveChoice 'AdaptiveCards.AdaptiveChoice')
  - [IsSelected](#P-AdaptiveCards-AdaptiveChoice-IsSelected 'AdaptiveCards.AdaptiveChoice.IsSelected')
  - [Speak](#P-AdaptiveCards-AdaptiveChoice-Speak 'AdaptiveCards.AdaptiveChoice.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveChoice-Title 'AdaptiveCards.AdaptiveChoice.Title')
  - [Value](#P-AdaptiveCards-AdaptiveChoice-Value 'AdaptiveCards.AdaptiveChoice.Value')
- [AdaptiveChoiceInputStyle](#T-AdaptiveCards-AdaptiveChoiceInputStyle 'AdaptiveCards.AdaptiveChoiceInputStyle')
  - [Compact](#F-AdaptiveCards-AdaptiveChoiceInputStyle-Compact 'AdaptiveCards.AdaptiveChoiceInputStyle.Compact')
  - [Expanded](#F-AdaptiveCards-AdaptiveChoiceInputStyle-Expanded 'AdaptiveCards.AdaptiveChoiceInputStyle.Expanded')
- [AdaptiveChoiceSetInput](#T-AdaptiveCards-AdaptiveChoiceSetInput 'AdaptiveCards.AdaptiveChoiceSetInput')
  - [Choices](#P-AdaptiveCards-AdaptiveChoiceSetInput-Choices 'AdaptiveCards.AdaptiveChoiceSetInput.Choices')
  - [IsMultiSelect](#P-AdaptiveCards-AdaptiveChoiceSetInput-IsMultiSelect 'AdaptiveCards.AdaptiveChoiceSetInput.IsMultiSelect')
  - [Style](#P-AdaptiveCards-AdaptiveChoiceSetInput-Style 'AdaptiveCards.AdaptiveChoiceSetInput.Style')
  - [Value](#P-AdaptiveCards-AdaptiveChoiceSetInput-Value 'AdaptiveCards.AdaptiveChoiceSetInput.Value')
  - [Wrap](#P-AdaptiveCards-AdaptiveChoiceSetInput-Wrap 'AdaptiveCards.AdaptiveChoiceSetInput.Wrap')
- [AdaptiveCollectionElement](#T-AdaptiveCards-AdaptiveCollectionElement 'AdaptiveCards.AdaptiveCollectionElement')
  - [Bleed](#P-AdaptiveCards-AdaptiveCollectionElement-Bleed 'AdaptiveCards.AdaptiveCollectionElement.Bleed')
  - [PixelMinHeight](#P-AdaptiveCards-AdaptiveCollectionElement-PixelMinHeight 'AdaptiveCards.AdaptiveCollectionElement.PixelMinHeight')
  - [SelectAction](#P-AdaptiveCards-AdaptiveCollectionElement-SelectAction 'AdaptiveCards.AdaptiveCollectionElement.SelectAction')
  - [Style](#P-AdaptiveCards-AdaptiveCollectionElement-Style 'AdaptiveCards.AdaptiveCollectionElement.Style')
  - [VerticalContentAlignment](#P-AdaptiveCards-AdaptiveCollectionElement-VerticalContentAlignment 'AdaptiveCards.AdaptiveCollectionElement.VerticalContentAlignment')
- [AdaptiveColumn](#T-AdaptiveCards-AdaptiveColumn 'AdaptiveCards.AdaptiveColumn')
  - [Size](#P-AdaptiveCards-AdaptiveColumn-Size 'AdaptiveCards.AdaptiveColumn.Size')
  - [Width](#P-AdaptiveCards-AdaptiveColumn-Width 'AdaptiveCards.AdaptiveColumn.Width')
- [AdaptiveColumnSet](#T-AdaptiveCards-AdaptiveColumnSet 'AdaptiveCards.AdaptiveColumnSet')
  - [Columns](#P-AdaptiveCards-AdaptiveColumnSet-Columns 'AdaptiveCards.AdaptiveColumnSet.Columns')
- [AdaptiveColumnSize](#T-AdaptiveCards-AdaptiveColumnSize 'AdaptiveCards.AdaptiveColumnSize')
  - [Auto](#F-AdaptiveCards-AdaptiveColumnSize-Auto 'AdaptiveCards.AdaptiveColumnSize.Auto')
  - [Stretch](#F-AdaptiveCards-AdaptiveColumnSize-Stretch 'AdaptiveCards.AdaptiveColumnSize.Stretch')
- [AdaptiveColumnWidth](#T-AdaptiveCards-AdaptiveColumnWidth 'AdaptiveCards.AdaptiveColumnWidth')
  - [Auto](#F-AdaptiveCards-AdaptiveColumnWidth-Auto 'AdaptiveCards.AdaptiveColumnWidth.Auto')
  - [Stretch](#F-AdaptiveCards-AdaptiveColumnWidth-Stretch 'AdaptiveCards.AdaptiveColumnWidth.Stretch')
- [AdaptiveContainer](#T-AdaptiveCards-AdaptiveContainer 'AdaptiveCards.AdaptiveContainer')
  - [Items](#P-AdaptiveCards-AdaptiveContainer-Items 'AdaptiveCards.AdaptiveContainer.Items')
- [AdaptiveContainerStyle](#T-AdaptiveCards-AdaptiveContainerStyle 'AdaptiveCards.AdaptiveContainerStyle')
  - [Default](#F-AdaptiveCards-AdaptiveContainerStyle-Default 'AdaptiveCards.AdaptiveContainerStyle.Default')
  - [Emphasis](#F-AdaptiveCards-AdaptiveContainerStyle-Emphasis 'AdaptiveCards.AdaptiveContainerStyle.Emphasis')
  - [Normal](#F-AdaptiveCards-AdaptiveContainerStyle-Normal 'AdaptiveCards.AdaptiveContainerStyle.Normal')
- [AdaptiveDateInput](#T-AdaptiveCards-AdaptiveDateInput 'AdaptiveCards.AdaptiveDateInput')
  - [Max](#P-AdaptiveCards-AdaptiveDateInput-Max 'AdaptiveCards.AdaptiveDateInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveDateInput-Min 'AdaptiveCards.AdaptiveDateInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveDateInput-Placeholder 'AdaptiveCards.AdaptiveDateInput.Placeholder')
  - [Value](#P-AdaptiveCards-AdaptiveDateInput-Value 'AdaptiveCards.AdaptiveDateInput.Value')
- [AdaptiveElement](#T-AdaptiveCards-AdaptiveElement 'AdaptiveCards.AdaptiveElement')
  - [Height](#P-AdaptiveCards-AdaptiveElement-Height 'AdaptiveCards.AdaptiveElement.Height')
  - [IsVisible](#P-AdaptiveCards-AdaptiveElement-IsVisible 'AdaptiveCards.AdaptiveElement.IsVisible')
  - [Separator](#P-AdaptiveCards-AdaptiveElement-Separator 'AdaptiveCards.AdaptiveElement.Separator')
  - [Spacing](#P-AdaptiveCards-AdaptiveElement-Spacing 'AdaptiveCards.AdaptiveElement.Spacing')
  - [Speak](#P-AdaptiveCards-AdaptiveElement-Speak 'AdaptiveCards.AdaptiveElement.Speak')
- [AdaptiveFact](#T-AdaptiveCards-AdaptiveFact 'AdaptiveCards.AdaptiveFact')
  - [Speak](#P-AdaptiveCards-AdaptiveFact-Speak 'AdaptiveCards.AdaptiveFact.Speak')
  - [Title](#P-AdaptiveCards-AdaptiveFact-Title 'AdaptiveCards.AdaptiveFact.Title')
  - [Value](#P-AdaptiveCards-AdaptiveFact-Value 'AdaptiveCards.AdaptiveFact.Value')
- [AdaptiveFactSet](#T-AdaptiveCards-AdaptiveFactSet 'AdaptiveCards.AdaptiveFactSet')
  - [Facts](#P-AdaptiveCards-AdaptiveFactSet-Facts 'AdaptiveCards.AdaptiveFactSet.Facts')
- [AdaptiveFontType](#T-AdaptiveCards-AdaptiveFontType 'AdaptiveCards.AdaptiveFontType')
  - [Default](#F-AdaptiveCards-AdaptiveFontType-Default 'AdaptiveCards.AdaptiveFontType.Default')
  - [Monospace](#F-AdaptiveCards-AdaptiveFontType-Monospace 'AdaptiveCards.AdaptiveFontType.Monospace')
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
  - [ImageBaseUrl](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageBaseUrl 'AdaptiveCards.Rendering.AdaptiveHostConfig.ImageBaseUrl')
  - [SupportsInteractivity](#P-AdaptiveCards-Rendering-AdaptiveHostConfig-SupportsInteractivity 'AdaptiveCards.Rendering.AdaptiveHostConfig.SupportsInteractivity')
  - [ResolveFinalAbsoluteUri()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-Uri- 'AdaptiveCards.Rendering.AdaptiveHostConfig.ResolveFinalAbsoluteUri(System.Uri)')
  - [ToJson()](#M-AdaptiveCards-Rendering-AdaptiveHostConfig-ToJson 'AdaptiveCards.Rendering.AdaptiveHostConfig.ToJson')
- [AdaptiveImage](#T-AdaptiveCards-AdaptiveImage 'AdaptiveCards.AdaptiveImage')
  - [AltText](#P-AdaptiveCards-AdaptiveImage-AltText 'AdaptiveCards.AdaptiveImage.AltText')
  - [BackgroundColor](#P-AdaptiveCards-AdaptiveImage-BackgroundColor 'AdaptiveCards.AdaptiveImage.BackgroundColor')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveImage-HorizontalAlignment 'AdaptiveCards.AdaptiveImage.HorizontalAlignment')
  - [PixelHeight](#P-AdaptiveCards-AdaptiveImage-PixelHeight 'AdaptiveCards.AdaptiveImage.PixelHeight')
  - [PixelWidth](#P-AdaptiveCards-AdaptiveImage-PixelWidth 'AdaptiveCards.AdaptiveImage.PixelWidth')
  - [SelectAction](#P-AdaptiveCards-AdaptiveImage-SelectAction 'AdaptiveCards.AdaptiveImage.SelectAction')
  - [Size](#P-AdaptiveCards-AdaptiveImage-Size 'AdaptiveCards.AdaptiveImage.Size')
  - [Style](#P-AdaptiveCards-AdaptiveImage-Style 'AdaptiveCards.AdaptiveImage.Style')
  - [Url](#P-AdaptiveCards-AdaptiveImage-Url 'AdaptiveCards.AdaptiveImage.Url')
  - [UrlString](#P-AdaptiveCards-AdaptiveImage-UrlString 'AdaptiveCards.AdaptiveImage.UrlString')
- [AdaptiveImageSet](#T-AdaptiveCards-AdaptiveImageSet 'AdaptiveCards.AdaptiveImageSet')
  - [ImageSize](#P-AdaptiveCards-AdaptiveImageSet-ImageSize 'AdaptiveCards.AdaptiveImageSet.ImageSize')
  - [Images](#P-AdaptiveCards-AdaptiveImageSet-Images 'AdaptiveCards.AdaptiveImageSet.Images')
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
- [AdaptiveInput](#T-AdaptiveCards-AdaptiveInput 'AdaptiveCards.AdaptiveInput')
  - [IsRequired](#P-AdaptiveCards-AdaptiveInput-IsRequired 'AdaptiveCards.AdaptiveInput.IsRequired')
  - [GetNonInteractiveValue()](#M-AdaptiveCards-AdaptiveInput-GetNonInteractiveValue 'AdaptiveCards.AdaptiveInput.GetNonInteractiveValue')
- [AdaptiveLineChart](#T-AdaptiveCards-AdaptiveLineChart 'AdaptiveCards.AdaptiveLineChart')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveLineChart-#ctor 'AdaptiveCards.AdaptiveLineChart.#ctor')
- [AdaptiveMedia](#T-AdaptiveCards-AdaptiveMedia 'AdaptiveCards.AdaptiveMedia')
  - [AltText](#P-AdaptiveCards-AdaptiveMedia-AltText 'AdaptiveCards.AdaptiveMedia.AltText')
  - [Poster](#P-AdaptiveCards-AdaptiveMedia-Poster 'AdaptiveCards.AdaptiveMedia.Poster')
  - [Sources](#P-AdaptiveCards-AdaptiveMedia-Sources 'AdaptiveCards.AdaptiveMedia.Sources')
- [AdaptiveMediaSource](#T-AdaptiveCards-AdaptiveMediaSource 'AdaptiveCards.AdaptiveMediaSource')
- [AdaptiveNumberInput](#T-AdaptiveCards-AdaptiveNumberInput 'AdaptiveCards.AdaptiveNumberInput')
  - [Max](#P-AdaptiveCards-AdaptiveNumberInput-Max 'AdaptiveCards.AdaptiveNumberInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveNumberInput-Min 'AdaptiveCards.AdaptiveNumberInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveNumberInput-Placeholder 'AdaptiveCards.AdaptiveNumberInput.Placeholder')
  - [Value](#P-AdaptiveCards-AdaptiveNumberInput-Value 'AdaptiveCards.AdaptiveNumberInput.Value')
- [AdaptiveOpenUrlAction](#T-AdaptiveCards-AdaptiveOpenUrlAction 'AdaptiveCards.AdaptiveOpenUrlAction')
  - [Url](#P-AdaptiveCards-AdaptiveOpenUrlAction-Url 'AdaptiveCards.AdaptiveOpenUrlAction.Url')
  - [UrlString](#P-AdaptiveCards-AdaptiveOpenUrlAction-UrlString 'AdaptiveCards.AdaptiveOpenUrlAction.UrlString')
- [AdaptivePieChart](#T-AdaptiveCards-AdaptivePieChart 'AdaptiveCards.AdaptivePieChart')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptivePieChart-#ctor 'AdaptiveCards.AdaptivePieChart.#ctor')
- [AdaptiveRadarChart](#T-AdaptiveCards-AdaptiveRadarChart 'AdaptiveCards.AdaptiveRadarChart')
  - [#ctor(schemaVersion)](#M-AdaptiveCards-AdaptiveRadarChart-#ctor 'AdaptiveCards.AdaptiveRadarChart.#ctor')
- [AdaptiveRenderException](#T-AdaptiveCards-Rendering-AdaptiveRenderException 'AdaptiveCards.Rendering.AdaptiveRenderException')
  - [CardFallbackText](#P-AdaptiveCards-Rendering-AdaptiveRenderException-CardFallbackText 'AdaptiveCards.Rendering.AdaptiveRenderException.CardFallbackText')
- [AdaptiveRichTextBlock](#T-AdaptiveCards-AdaptiveRichTextBlock 'AdaptiveCards.AdaptiveRichTextBlock')
  - [HorizontalAlignment](#P-AdaptiveCards-AdaptiveRichTextBlock-HorizontalAlignment 'AdaptiveCards.AdaptiveRichTextBlock.HorizontalAlignment')
- [AdaptiveShowCardAction](#T-AdaptiveCards-AdaptiveShowCardAction 'AdaptiveCards.AdaptiveShowCardAction')
  - [Card](#P-AdaptiveCards-AdaptiveShowCardAction-Card 'AdaptiveCards.AdaptiveShowCardAction.Card')
- [AdaptiveSpacing](#T-AdaptiveCards-AdaptiveSpacing 'AdaptiveCards.AdaptiveSpacing')
  - [Padding](#F-AdaptiveCards-AdaptiveSpacing-Padding 'AdaptiveCards.AdaptiveSpacing.Padding')
- [AdaptiveSubmitAction](#T-AdaptiveCards-AdaptiveSubmitAction 'AdaptiveCards.AdaptiveSubmitAction')
  - [Data](#P-AdaptiveCards-AdaptiveSubmitAction-Data 'AdaptiveCards.AdaptiveSubmitAction.Data')
- [AdaptiveTargetElement](#T-AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement')
  - [ElementId](#P-AdaptiveCards-AdaptiveTargetElement-ElementId 'AdaptiveCards.AdaptiveTargetElement.ElementId')
  - [IsVisible](#P-AdaptiveCards-AdaptiveTargetElement-IsVisible 'AdaptiveCards.AdaptiveTargetElement.IsVisible')
  - [op_Implicit(elementId)](#M-AdaptiveCards-AdaptiveTargetElement-op_Implicit-System-String-~AdaptiveCards-AdaptiveTargetElement 'AdaptiveCards.AdaptiveTargetElement.op_Implicit(System.String)~AdaptiveCards.AdaptiveTargetElement')
- [AdaptiveTextBlock](#T-AdaptiveCards-AdaptiveTextBlock 'AdaptiveCards.AdaptiveTextBlock')
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
  - [InlineAction](#P-AdaptiveCards-AdaptiveTextInput-InlineAction 'AdaptiveCards.AdaptiveTextInput.InlineAction')
  - [IsMultiline](#P-AdaptiveCards-AdaptiveTextInput-IsMultiline 'AdaptiveCards.AdaptiveTextInput.IsMultiline')
  - [MaxLength](#P-AdaptiveCards-AdaptiveTextInput-MaxLength 'AdaptiveCards.AdaptiveTextInput.MaxLength')
  - [Placeholder](#P-AdaptiveCards-AdaptiveTextInput-Placeholder 'AdaptiveCards.AdaptiveTextInput.Placeholder')
  - [Style](#P-AdaptiveCards-AdaptiveTextInput-Style 'AdaptiveCards.AdaptiveTextInput.Style')
  - [Value](#P-AdaptiveCards-AdaptiveTextInput-Value 'AdaptiveCards.AdaptiveTextInput.Value')
- [AdaptiveTextInputStyle](#T-AdaptiveCards-AdaptiveTextInputStyle 'AdaptiveCards.AdaptiveTextInputStyle')
  - [Email](#F-AdaptiveCards-AdaptiveTextInputStyle-Email 'AdaptiveCards.AdaptiveTextInputStyle.Email')
  - [Tel](#F-AdaptiveCards-AdaptiveTextInputStyle-Tel 'AdaptiveCards.AdaptiveTextInputStyle.Tel')
  - [Text](#F-AdaptiveCards-AdaptiveTextInputStyle-Text 'AdaptiveCards.AdaptiveTextInputStyle.Text')
  - [Url](#F-AdaptiveCards-AdaptiveTextInputStyle-Url 'AdaptiveCards.AdaptiveTextInputStyle.Url')
- [AdaptiveTextRun](#T-AdaptiveCards-AdaptiveTextRun 'AdaptiveCards.AdaptiveTextRun')
  - [Color](#P-AdaptiveCards-AdaptiveTextRun-Color 'AdaptiveCards.AdaptiveTextRun.Color')
  - [FontType](#P-AdaptiveCards-AdaptiveTextRun-FontType 'AdaptiveCards.AdaptiveTextRun.FontType')
  - [Highlight](#P-AdaptiveCards-AdaptiveTextRun-Highlight 'AdaptiveCards.AdaptiveTextRun.Highlight')
  - [IsSubtle](#P-AdaptiveCards-AdaptiveTextRun-IsSubtle 'AdaptiveCards.AdaptiveTextRun.IsSubtle')
  - [Italic](#P-AdaptiveCards-AdaptiveTextRun-Italic 'AdaptiveCards.AdaptiveTextRun.Italic')
  - [SelectAction](#P-AdaptiveCards-AdaptiveTextRun-SelectAction 'AdaptiveCards.AdaptiveTextRun.SelectAction')
  - [Size](#P-AdaptiveCards-AdaptiveTextRun-Size 'AdaptiveCards.AdaptiveTextRun.Size')
  - [Strikethrough](#P-AdaptiveCards-AdaptiveTextRun-Strikethrough 'AdaptiveCards.AdaptiveTextRun.Strikethrough')
  - [Text](#P-AdaptiveCards-AdaptiveTextRun-Text 'AdaptiveCards.AdaptiveTextRun.Text')
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
  - [Max](#P-AdaptiveCards-AdaptiveTimeInput-Max 'AdaptiveCards.AdaptiveTimeInput.Max')
  - [Min](#P-AdaptiveCards-AdaptiveTimeInput-Min 'AdaptiveCards.AdaptiveTimeInput.Min')
  - [Placeholder](#P-AdaptiveCards-AdaptiveTimeInput-Placeholder 'AdaptiveCards.AdaptiveTimeInput.Placeholder')
  - [Value](#P-AdaptiveCards-AdaptiveTimeInput-Value 'AdaptiveCards.AdaptiveTimeInput.Value')
- [AdaptiveToggleInput](#T-AdaptiveCards-AdaptiveToggleInput 'AdaptiveCards.AdaptiveToggleInput')
  - [Title](#P-AdaptiveCards-AdaptiveToggleInput-Title 'AdaptiveCards.AdaptiveToggleInput.Title')
  - [Value](#P-AdaptiveCards-AdaptiveToggleInput-Value 'AdaptiveCards.AdaptiveToggleInput.Value')
  - [ValueOff](#P-AdaptiveCards-AdaptiveToggleInput-ValueOff 'AdaptiveCards.AdaptiveToggleInput.ValueOff')
  - [ValueOn](#P-AdaptiveCards-AdaptiveToggleInput-ValueOn 'AdaptiveCards.AdaptiveToggleInput.ValueOn')
  - [Wrap](#P-AdaptiveCards-AdaptiveToggleInput-Wrap 'AdaptiveCards.AdaptiveToggleInput.Wrap')
- [AdaptiveToggleVisibilityAction](#T-AdaptiveCards-AdaptiveToggleVisibilityAction 'AdaptiveCards.AdaptiveToggleVisibilityAction')
  - [TargetElements](#P-AdaptiveCards-AdaptiveToggleVisibilityAction-TargetElements 'AdaptiveCards.AdaptiveToggleVisibilityAction.TargetElements')
- [AdaptiveTypedBaseElementConverter](#T-AdaptiveCards-AdaptiveTypedBaseElementConverter 'AdaptiveCards.AdaptiveTypedBaseElementConverter')
- [AdaptiveTypedElement](#T-AdaptiveCards-AdaptiveTypedElement 'AdaptiveCards.AdaptiveTypedElement')
  - [Requires](#F-AdaptiveCards-AdaptiveTypedElement-Requires 'AdaptiveCards.AdaptiveTypedElement.Requires')
  - [AdditionalProperties](#P-AdaptiveCards-AdaptiveTypedElement-AdditionalProperties 'AdaptiveCards.AdaptiveTypedElement.AdditionalProperties')
  - [Id](#P-AdaptiveCards-AdaptiveTypedElement-Id 'AdaptiveCards.AdaptiveTypedElement.Id')
  - [Type](#P-AdaptiveCards-AdaptiveTypedElement-Type 'AdaptiveCards.AdaptiveTypedElement.Type')
- [AdaptiveTypedElementConverter](#T-AdaptiveCards-AdaptiveTypedElementConverter 'AdaptiveCards.AdaptiveTypedElementConverter')
  - [TypedElementTypes](#F-AdaptiveCards-AdaptiveTypedElementConverter-TypedElementTypes 'AdaptiveCards.AdaptiveTypedElementConverter.TypedElementTypes')
- [AdaptiveVisitor](#T-AdaptiveCards-Rendering-AdaptiveVisitor 'AdaptiveCards.Rendering.AdaptiveVisitor')
- [ChartData](#T-AdaptiveCards-ChartData 'AdaptiveCards.ChartData')
  - [BackgroundColor](#P-AdaptiveCards-ChartData-BackgroundColor 'AdaptiveCards.ChartData.BackgroundColor')
  - [BorderColor](#P-AdaptiveCards-ChartData-BorderColor 'AdaptiveCards.ChartData.BorderColor')
  - [DataSets](#P-AdaptiveCards-ChartData-DataSets 'AdaptiveCards.ChartData.DataSets')
  - [Labels](#P-AdaptiveCards-ChartData-Labels 'AdaptiveCards.ChartData.Labels')
  - [Options](#P-AdaptiveCards-ChartData-Options 'AdaptiveCards.ChartData.Options')
- [ChartDataSet](#T-AdaptiveCards-ChartDataSet 'AdaptiveCards.ChartDataSet')
  - [BackgroundColors](#P-AdaptiveCards-ChartDataSet-BackgroundColors 'AdaptiveCards.ChartDataSet.BackgroundColors')
  - [BorderColors](#P-AdaptiveCards-ChartDataSet-BorderColors 'AdaptiveCards.ChartDataSet.BorderColors')
  - [Data](#P-AdaptiveCards-ChartDataSet-Data 'AdaptiveCards.ChartDataSet.Data')
  - [Label](#P-AdaptiveCards-ChartDataSet-Label 'AdaptiveCards.ChartDataSet.Label')
- [ChartOptions](#T-AdaptiveCards-ChartOptions 'AdaptiveCards.ChartOptions')
  - [CutoutPercentage](#P-AdaptiveCards-ChartOptions-CutoutPercentage 'AdaptiveCards.ChartOptions.CutoutPercentage')
- [ContainerStyleConfig](#T-AdaptiveCards-Rendering-ContainerStyleConfig 'AdaptiveCards.Rendering.ContainerStyleConfig')
  - [BackgroundColor](#P-AdaptiveCards-Rendering-ContainerStyleConfig-BackgroundColor 'AdaptiveCards.Rendering.ContainerStyleConfig.BackgroundColor')
  - [ForegroundColors](#P-AdaptiveCards-Rendering-ContainerStyleConfig-ForegroundColors 'AdaptiveCards.Rendering.ContainerStyleConfig.ForegroundColors')
- [FactSetConfig](#T-AdaptiveCards-Rendering-FactSetConfig 'AdaptiveCards.Rendering.FactSetConfig')
  - [Spacing](#P-AdaptiveCards-Rendering-FactSetConfig-Spacing 'AdaptiveCards.Rendering.FactSetConfig.Spacing')
  - [Title](#P-AdaptiveCards-Rendering-FactSetConfig-Title 'AdaptiveCards.Rendering.FactSetConfig.Title')
  - [Value](#P-AdaptiveCards-Rendering-FactSetConfig-Value 'AdaptiveCards.Rendering.FactSetConfig.Value')
- [FontColorConfig](#T-AdaptiveCards-Rendering-FontColorConfig 'AdaptiveCards.Rendering.FontColorConfig')
  - [Default](#P-AdaptiveCards-Rendering-FontColorConfig-Default 'AdaptiveCards.Rendering.FontColorConfig.Default')
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
- [MediaConfig](#T-AdaptiveCards-Rendering-MediaConfig 'AdaptiveCards.Rendering.MediaConfig')
  - [AllowInlinePlayback](#P-AdaptiveCards-Rendering-MediaConfig-AllowInlinePlayback 'AdaptiveCards.Rendering.MediaConfig.AllowInlinePlayback')
  - [DefaultPoster](#P-AdaptiveCards-Rendering-MediaConfig-DefaultPoster 'AdaptiveCards.Rendering.MediaConfig.DefaultPoster')
  - [PlayButton](#P-AdaptiveCards-Rendering-MediaConfig-PlayButton 'AdaptiveCards.Rendering.MediaConfig.PlayButton')
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

<a name='T-AdaptiveCards-Rendering-ActionsConfig'></a>
## ActionsConfig `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Properties which control rendering of actions

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ActionAlignment'></a>
### ActionAlignment `property`

##### Summary

should they be aligned Left, Center or Right

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ActionsOrientation'></a>
### ActionsOrientation `property`

##### Summary

Arrange actions horizontal or vertical

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ButtonSpacing'></a>
### ButtonSpacing `property`

##### Summary

Space between actions

<a name='P-AdaptiveCards-Rendering-ActionsConfig-IconPlacement'></a>
### IconPlacement `property`

##### Summary

Position of Icon relative to Title

<a name='P-AdaptiveCards-Rendering-ActionsConfig-IconSize'></a>
### IconSize `property`

##### Summary

Size of Icon

<a name='P-AdaptiveCards-Rendering-ActionsConfig-MaxActions'></a>
### MaxActions `property`

##### Summary

Max number of actions to support on your Cards(e.g., 3)

<a name='P-AdaptiveCards-Rendering-ActionsConfig-ShowCard'></a>
### ShowCard `property`

##### Summary

ShowCard configuration

<a name='T-AdaptiveCards-Rendering-ActionsOrientation'></a>
## ActionsOrientation `type`

##### Namespace

AdaptiveCards.Rendering

<a name='F-AdaptiveCards-Rendering-ActionsOrientation-Horizontal'></a>
### Horizontal `constants`

##### Summary

actions should be laid out horizontally

<a name='F-AdaptiveCards-Rendering-ActionsOrientation-Vertical'></a>
### Vertical `constants`

##### Summary

Actions should be laid out vertically

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

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-AddSupportedAction``1'></a>
### AddSupportedAction\`\`1() `method`

##### Summary

Adds support for a given action type. Any action in a payload not specified here will be dropped from the rendered card

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-IsSupported-System-Type-'></a>
### IsSupported() `method`

##### Summary

Whether or not the action is supported by the renderer

##### Returns



##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveActionHandlers-RemoveSupportedAction``1'></a>
### RemoveSupportedAction\`\`1() `method`

##### Summary

Remove support for an action type. This will prevent these actions from appearing in the rendered card

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveActionSet'></a>
## AdaptiveActionSet `type`

##### Namespace

AdaptiveCards

##### Summary

ActionSet

<a name='P-AdaptiveCards-AdaptiveActionSet-Actions'></a>
### Actions `property`

##### Summary

Actions of the action set

<a name='T-AdaptiveCards-AdaptiveBarChart'></a>
## AdaptiveBarChart `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card rendering chartdata as a bar chart.

<a name='M-AdaptiveCards-AdaptiveBarChart-#ctor'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [M:AdaptiveCards.AdaptiveBarChart.#ctor](#T-M-AdaptiveCards-AdaptiveBarChart-#ctor 'M:AdaptiveCards.AdaptiveBarChart.#ctor') | The schema version to use |

<a name='T-AdaptiveCards-AdaptiveCard'></a>
## AdaptiveCard `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card which has flexible container

<a name='M-AdaptiveCards-AdaptiveCard-#ctor-AdaptiveCards-AdaptiveSchemaVersion-'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

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

Creates an AdaptiveCard using the [KnownSchemaVersion](#F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion 'AdaptiveCards.AdaptiveCard.KnownSchemaVersion') of this library

##### Parameters

This constructor has no parameters.

<a name='F-AdaptiveCards-AdaptiveCard-KnownSchemaVersion'></a>
### KnownSchemaVersion `constants`

##### Summary

The latest known schema version supported by this library

<a name='P-AdaptiveCards-AdaptiveCard-Actions'></a>
### Actions `property`

##### Summary

Actions for the card

<a name='P-AdaptiveCards-AdaptiveCard-BackgroundImage'></a>
### BackgroundImage `property`

##### Summary

Background image for card

<a name='P-AdaptiveCards-AdaptiveCard-Body'></a>
### Body `property`

##### Summary

The Body elements for this card

<a name='P-AdaptiveCards-AdaptiveCard-FallbackText'></a>
### FallbackText `property`

##### Summary

Text shown when the client doesn’t support the version specified. This can be in markdown format.

<a name='P-AdaptiveCards-AdaptiveCard-Height'></a>
### Height `property`

##### Summary

Value that denotes if the card must use all the vertical space that is set to it. Default value is [](#!-AdaptiveHeight-Default 'AdaptiveHeight.Default').

<a name='P-AdaptiveCards-AdaptiveCard-JsonSchema'></a>
### JsonSchema `property`

##### Summary

This makes sure the $schema property doesn't show up in AdditionalProperties

<a name='P-AdaptiveCards-AdaptiveCard-Lang'></a>
### Lang `property`

##### Summary

The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions

<a name='P-AdaptiveCards-AdaptiveCard-OnDeserializingMissingVersion'></a>
### OnDeserializingMissingVersion `property`

##### Summary

Callback that will be invoked should a null or empty version string is encountered. The callback may return an alternate version to use for parsing.

##### Example

AdaptiveCard.OnDeserializingMissingVersion = () => new AdaptiveSchemaVersion(0, 5);

<a name='P-AdaptiveCards-AdaptiveCard-PixelMinHeight'></a>
### PixelMinHeight `property`

##### Summary

Explicit card minimum height in pixels

<a name='P-AdaptiveCards-AdaptiveCard-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for the card (this allows a default action at the card level)

<a name='P-AdaptiveCards-AdaptiveCard-Speak'></a>
### Speak `property`

##### Summary

Speak annotation for the card

<a name='P-AdaptiveCards-AdaptiveCard-Title'></a>
### Title `property`

##### Summary

Title for the card (used when displayed in a dialog)

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

Parse an AdaptiveCard from a JSON string

##### Returns



##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| json | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | A JSON-serialized Adaptive Card |

<a name='M-AdaptiveCards-AdaptiveCard-GetResourceInformation'></a>
### GetResourceInformation() `method`

##### Summary

Get resource information for all Images/Media in the whole card
TODO: Add Media information to the list when Media type is added

##### Returns

An array of all card resource information

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-AdaptiveCard-ToJson'></a>
### ToJson() `method`

##### Summary

Serialize this Adaptive Card to JSON

##### Returns



##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveCardParseResult'></a>
## AdaptiveCardParseResult `type`

##### Namespace

AdaptiveCards

<a name='P-AdaptiveCards-AdaptiveCardParseResult-Card'></a>
### Card `property`

##### Summary

The parsed card object

<a name='P-AdaptiveCards-AdaptiveCardParseResult-Warnings'></a>
### Warnings `property`

##### Summary

If any modifications were done to the parsed card they will be reported here

<a name='T-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2'></a>
## AdaptiveCardRendererBase\`2 `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-ElementRenderers'></a>
### ElementRenderers `property`

##### Summary

The dictionary of supported element types and their associated rendering functions

<a name='P-AdaptiveCards-Rendering-AdaptiveCardRendererBase`2-HostConfig'></a>
### HostConfig `property`

##### Summary

A Host Configuration object to determine base styling and behavior of the rendered card

<a name='T-AdaptiveCards-AdaptiveChart'></a>
## AdaptiveChart `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card which has flexible container

<a name='M-AdaptiveCards-AdaptiveChart-#ctor'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [M:AdaptiveCards.AdaptiveChart.#ctor](#T-M-AdaptiveCards-AdaptiveChart-#ctor 'M:AdaptiveCards.AdaptiveChart.#ctor') | The schema version to use |

<a name='P-AdaptiveCards-AdaptiveChart-Data'></a>
### Data `property`

##### Summary

The facts to be displayed.

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

<a name='F-AdaptiveCards-AdaptiveChoiceInputStyle-Compact'></a>
### Compact `constants`

##### Summary

choices are prefered to be compactly displayed. Example: ComboBox

<a name='F-AdaptiveCards-AdaptiveChoiceInputStyle-Expanded'></a>
### Expanded `constants`

##### Summary

choices are prefered to be displayed for easy input. Example: Checkbox or Radio buttons

<a name='T-AdaptiveCards-AdaptiveChoiceSetInput'></a>
## AdaptiveChoiceSetInput `type`

##### Namespace

AdaptiveCards

##### Summary

Element which collects choice from the user

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Choices'></a>
### Choices `property`

##### Summary

the choice options

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-IsMultiSelect'></a>
### IsMultiSelect `property`

##### Summary

allow multiple choices to be selected (default false)

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Style'></a>
### Style `property`

##### Summary

Style for choice

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Value'></a>
### Value `property`

##### Summary

Comma separated string of selected Choice values

<a name='P-AdaptiveCards-AdaptiveChoiceSetInput-Wrap'></a>
### Wrap `property`

##### Summary

when set true, text will wrap

<a name='T-AdaptiveCards-AdaptiveCollectionElement'></a>
## AdaptiveCollectionElement `type`

##### Namespace

AdaptiveCards

##### Summary

Base class for all elements that contain elements

<a name='P-AdaptiveCards-AdaptiveCollectionElement-Bleed'></a>
### Bleed `property`

##### Summary

Defines if the element can bleed through its parent's padding

<a name='P-AdaptiveCards-AdaptiveCollectionElement-PixelMinHeight'></a>
### PixelMinHeight `property`

##### Summary

Explicit container element minimum height

<a name='P-AdaptiveCards-AdaptiveCollectionElement-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for this container (this allows a default action at the container level)

<a name='P-AdaptiveCards-AdaptiveCollectionElement-Style'></a>
### Style `property`

##### Summary

The style in which the image is displayed.

<a name='P-AdaptiveCards-AdaptiveCollectionElement-VerticalContentAlignment'></a>
### VerticalContentAlignment `property`

##### Summary

The content alignment for the element inside the container.

<a name='T-AdaptiveCards-AdaptiveColumn'></a>
## AdaptiveColumn `type`

##### Namespace

AdaptiveCards

##### Summary

Column

<a name='P-AdaptiveCards-AdaptiveColumn-Size'></a>
### Size `property`

##### Summary

Size for the column (either ColumnSize string or number which is relative size of the column)

<a name='P-AdaptiveCards-AdaptiveColumn-Width'></a>
### Width `property`

##### Summary

Width for the column (either ColumnWidth string or number which is relative size of the column)

<a name='T-AdaptiveCards-AdaptiveColumnSet'></a>
## AdaptiveColumnSet `type`

##### Namespace

AdaptiveCards

##### Summary

A set of columns

<a name='P-AdaptiveCards-AdaptiveColumnSet-Columns'></a>
### Columns `property`

##### Summary

Columns that are part of this group

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

<a name='T-AdaptiveCards-AdaptiveContainer'></a>
## AdaptiveContainer `type`

##### Namespace

AdaptiveCards

##### Summary

Container for a collection of elements

<a name='P-AdaptiveCards-AdaptiveContainer-Items'></a>
### Items `property`

##### Summary

Elements of the container

<a name='T-AdaptiveCards-AdaptiveContainerStyle'></a>
## AdaptiveContainerStyle `type`

##### Namespace

AdaptiveCards

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Default'></a>
### Default `constants`

##### Summary

The container is a default container

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Emphasis'></a>
### Emphasis `constants`

##### Summary

The container should be emphasized as a grouping of elements

<a name='F-AdaptiveCards-AdaptiveContainerStyle-Normal'></a>
### Normal `constants`

##### Summary

The container is a normal container

<a name='T-AdaptiveCards-AdaptiveDateInput'></a>
## AdaptiveDateInput `type`

##### Namespace

AdaptiveCards

##### Summary

Input which collects date from the user

<a name='P-AdaptiveCards-AdaptiveDateInput-Max'></a>
### Max `property`

##### Summary

hint of maximum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveDateInput-Min'></a>
### Min `property`

##### Summary

hint of minimum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveDateInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text for the input desired

<a name='P-AdaptiveCards-AdaptiveDateInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field

<a name='T-AdaptiveCards-AdaptiveElement'></a>
## AdaptiveElement `type`

##### Namespace

AdaptiveCards

<a name='P-AdaptiveCards-AdaptiveElement-Height'></a>
### Height `property`

##### Summary

The amount of space the element should be separated from the previous element. Default value is [](#!-AdaptiveHeight-Default 'AdaptiveHeight.Default').

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

SSML fragment for spoken interaction

<a name='T-AdaptiveCards-AdaptiveFact'></a>
## AdaptiveFact `type`

##### Namespace

AdaptiveCards

##### Summary

Represents one "fact" in a FactSet element.

<a name='P-AdaptiveCards-AdaptiveFact-Speak'></a>
### Speak `property`

##### Summary

(Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment

<a name='P-AdaptiveCards-AdaptiveFact-Title'></a>
### Title `property`

##### Summary

The facts label

<a name='P-AdaptiveCards-AdaptiveFact-Value'></a>
### Value `property`

##### Summary

The fact's value

<a name='T-AdaptiveCards-AdaptiveFactSet'></a>
## AdaptiveFactSet `type`

##### Namespace

AdaptiveCards

##### Summary

The FactSet element makes it simple to display a series of "facts" (e.g. name/value pairs) in a tabular form.

<a name='P-AdaptiveCards-AdaptiveFactSet-Facts'></a>
### Facts `property`

##### Summary

The facts to be displayed.

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

<a name='T-AdaptiveCards-AdaptiveHeightType'></a>
## AdaptiveHeightType `type`

##### Namespace

AdaptiveCards

##### Summary

Controls the vertical size (height) of element.

<a name='F-AdaptiveCards-AdaptiveHeightType-Auto'></a>
### Auto `constants`

##### Summary

The height of the element is wraps the element content

<a name='F-AdaptiveCards-AdaptiveHeightType-Pixel'></a>
### Pixel `constants`

##### Summary

The height of the element was explicitly specified (only for Image elements)

<a name='F-AdaptiveCards-AdaptiveHeightType-Stretch'></a>
### Stretch `constants`

##### Summary

The height of the element uses as much space as it is able to

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

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-ImageBaseUrl'></a>
### ImageBaseUrl `property`

##### Summary

Image Base URL for relative URLs

<a name='P-AdaptiveCards-Rendering-AdaptiveHostConfig-SupportsInteractivity'></a>
### SupportsInteractivity `property`

##### Summary

Toggles whether or not to render inputs and actions

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-ResolveFinalAbsoluteUri-System-Uri-'></a>
### ResolveFinalAbsoluteUri() `method`

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Rendering-AdaptiveHostConfig-ToJson'></a>
### ToJson() `method`

##### Summary

Serialize this Host Config to JSON

##### Returns



##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveImage'></a>
## AdaptiveImage `type`

##### Namespace

AdaptiveCards

##### Summary

The Image element allows for the inclusion of images in an Adaptive Card.

<a name='P-AdaptiveCards-AdaptiveImage-AltText'></a>
### AltText `property`

##### Summary

Alternate text to display for this image

<a name='P-AdaptiveCards-AdaptiveImage-BackgroundColor'></a>
### BackgroundColor `property`

##### Summary

A background color for the image specified as #AARRGGBB or #RRGGBB

<a name='P-AdaptiveCards-AdaptiveImage-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Horizontal alignment for element

<a name='P-AdaptiveCards-AdaptiveImage-PixelHeight'></a>
### PixelHeight `property`

##### Summary

Explicit Image Height

<a name='P-AdaptiveCards-AdaptiveImage-PixelWidth'></a>
### PixelWidth `property`

##### Summary

Explicit Image Width

<a name='P-AdaptiveCards-AdaptiveImage-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for this image (this allows a default action to happen when a click on an image happens)

<a name='P-AdaptiveCards-AdaptiveImage-Size'></a>
### Size `property`

##### Summary

Size for the Image

<a name='P-AdaptiveCards-AdaptiveImage-Style'></a>
### Style `property`

##### Summary

The style in which the image is displayed.

<a name='P-AdaptiveCards-AdaptiveImage-Url'></a>
### Url `property`

##### Summary

A url pointing to an image to display

<a name='P-AdaptiveCards-AdaptiveImage-UrlString'></a>
### UrlString `property`

##### Summary

This is necessary for XML serialization. You should use the [Url](#F-Url 'Url') property directly.

<a name='T-AdaptiveCards-AdaptiveImageSet'></a>
## AdaptiveImageSet `type`

##### Namespace

AdaptiveCards

##### Summary

The ImageSet allows for the inclusion of a collection images like a photogallery.

<a name='P-AdaptiveCards-AdaptiveImageSet-ImageSize'></a>
### ImageSize `property`

##### Summary

Specifies the horizontal size of each image in the set

<a name='P-AdaptiveCards-AdaptiveImageSet-Images'></a>
### Images `property`

##### Summary

Collection of images to display together

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

<a name='P-AdaptiveCards-AdaptiveInline-AdditionalProperties'></a>
### AdditionalProperties `property`

##### Summary

Additional properties not found on the default schema

<a name='P-AdaptiveCards-AdaptiveInline-Type'></a>
### Type `property`

##### Summary

The type name of the inline

<a name='T-AdaptiveCards-AdaptiveInput'></a>
## AdaptiveInput `type`

##### Namespace

AdaptiveCards

##### Summary

Input is used as part of a Form CardElement to collect information from a user

<a name='P-AdaptiveCards-AdaptiveInput-IsRequired'></a>
### IsRequired `property`

##### Summary

The input must have a value for it to be part of a Submit or Http action

<a name='M-AdaptiveCards-AdaptiveInput-GetNonInteractiveValue'></a>
### GetNonInteractiveValue() `method`

##### Summary

The string that will be rendered on a a host with "SupportsInteractivity" set to false.

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-AdaptiveLineChart'></a>
## AdaptiveLineChart `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card rendering chartdata as a bar chart.

<a name='M-AdaptiveCards-AdaptiveLineChart-#ctor'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [M:AdaptiveCards.AdaptiveLineChart.#ctor](#T-M-AdaptiveCards-AdaptiveLineChart-#ctor 'M:AdaptiveCards.AdaptiveLineChart.#ctor') | The schema version to use |

<a name='T-AdaptiveCards-AdaptiveMedia'></a>
## AdaptiveMedia `type`

##### Namespace

AdaptiveCards

##### Summary

The Media element allows for the inclusion of medias (videos and audios) in an Adaptive Card.

<a name='P-AdaptiveCards-AdaptiveMedia-AltText'></a>
### AltText `property`

##### Summary

Alternate text to display for this media

<a name='P-AdaptiveCards-AdaptiveMedia-Poster'></a>
### Poster `property`

##### Summary

Poster URL for this media

<a name='P-AdaptiveCards-AdaptiveMedia-Sources'></a>
### Sources `property`

##### Summary

The media sources to try

<a name='T-AdaptiveCards-AdaptiveMediaSource'></a>
## AdaptiveMediaSource `type`

##### Namespace

AdaptiveCards

##### Summary

Represents one "media source" in a Media element.

<a name='T-AdaptiveCards-AdaptiveNumberInput'></a>
## AdaptiveNumberInput `type`

##### Namespace

AdaptiveCards

##### Summary

Input which collects number from the user

<a name='P-AdaptiveCards-AdaptiveNumberInput-Max'></a>
### Max `property`

##### Summary

hint of maximum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveNumberInput-Min'></a>
### Min `property`

##### Summary

hint of minimum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveNumberInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text for the input desired

<a name='P-AdaptiveCards-AdaptiveNumberInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field

<a name='T-AdaptiveCards-AdaptiveOpenUrlAction'></a>
## AdaptiveOpenUrlAction `type`

##### Namespace

AdaptiveCards

##### Summary

When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or
    showing in-situ with embedded web browser.

<a name='P-AdaptiveCards-AdaptiveOpenUrlAction-Url'></a>
### Url `property`

##### Summary

Url to open using default operating system browser

<a name='P-AdaptiveCards-AdaptiveOpenUrlAction-UrlString'></a>
### UrlString `property`

##### Summary

This is necessary for XML serialization. You should use the [Url](#F-Url 'Url') property directly.

<a name='T-AdaptiveCards-AdaptivePieChart'></a>
## AdaptivePieChart `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card rendering chartdata as a bar chart.

<a name='M-AdaptiveCards-AdaptivePieChart-#ctor'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [M:AdaptiveCards.AdaptivePieChart.#ctor](#T-M-AdaptiveCards-AdaptivePieChart-#ctor 'M:AdaptiveCards.AdaptivePieChart.#ctor') | The schema version to use |

<a name='T-AdaptiveCards-AdaptiveRadarChart'></a>
## AdaptiveRadarChart `type`

##### Namespace

AdaptiveCards

##### Summary

Adaptive card rendering chartdata as a bar chart.

<a name='M-AdaptiveCards-AdaptiveRadarChart-#ctor'></a>
### #ctor(schemaVersion) `constructor`

##### Summary

Creates an AdaptiveCard using a specific schema version

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| schemaVersion | [M:AdaptiveCards.AdaptiveRadarChart.#ctor](#T-M-AdaptiveCards-AdaptiveRadarChart-#ctor 'M:AdaptiveCards.AdaptiveRadarChart.#ctor') | The schema version to use |

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

<a name='P-AdaptiveCards-AdaptiveRichTextBlock-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Horizontal alignment for element

<a name='T-AdaptiveCards-AdaptiveShowCardAction'></a>
## AdaptiveShowCardAction `type`

##### Namespace

AdaptiveCards

##### Summary

ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.

<a name='P-AdaptiveCards-AdaptiveShowCardAction-Card'></a>
### Card `property`

##### Summary

Container card to show when the action is invoked

<a name='T-AdaptiveCards-AdaptiveSpacing'></a>
## AdaptiveSpacing `type`

##### Namespace

AdaptiveCards

<a name='F-AdaptiveCards-AdaptiveSpacing-Padding'></a>
### Padding `constants`

##### Summary

This results in the same padding that's applied to the card itself.

<a name='T-AdaptiveCards-AdaptiveSubmitAction'></a>
## AdaptiveSubmitAction `type`

##### Namespace

AdaptiveCards

##### Summary

Submit action gathers up input fields, merges with optional data field and generates event to client asking for
    data to be submitted. It is up to the client to determine how that data is processed. For example: With
    BotFramework bots the client would send an activity through the messaging medium to the bot.

<a name='P-AdaptiveCards-AdaptiveSubmitAction-Data'></a>
### Data `property`

##### Summary

initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
    {"id":"123123123"}

<a name='T-AdaptiveCards-AdaptiveTargetElement'></a>
## AdaptiveTargetElement `type`

##### Namespace

AdaptiveCards

<a name='P-AdaptiveCards-AdaptiveTargetElement-ElementId'></a>
### ElementId `property`

##### Summary

Identifier of element to change visibility.

<a name='P-AdaptiveCards-AdaptiveTargetElement-IsVisible'></a>
### IsVisible `property`

##### Summary

Value to change visibility to.

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

The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive
    Cards.

<a name='P-AdaptiveCards-AdaptiveTextBlock-Color'></a>
### Color `property`

##### Summary

The color of the text

<a name='P-AdaptiveCards-AdaptiveTextBlock-FontType'></a>
### FontType `property`

##### Summary

The font types of the TextBlock

<a name='P-AdaptiveCards-AdaptiveTextBlock-HorizontalAlignment'></a>
### HorizontalAlignment `property`

##### Summary

Horizontal alignment for element

<a name='P-AdaptiveCards-AdaptiveTextBlock-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Make the text less prominent

<a name='P-AdaptiveCards-AdaptiveTextBlock-Italic'></a>
### Italic `property`

##### Summary

Make the text italic

<a name='P-AdaptiveCards-AdaptiveTextBlock-MaxLines'></a>
### MaxLines `property`

##### Summary

When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.

<a name='P-AdaptiveCards-AdaptiveTextBlock-MaxWidth'></a>
### MaxWidth `property`

##### Summary

The maximum width of the textblock

<a name='P-AdaptiveCards-AdaptiveTextBlock-Size'></a>
### Size `property`

##### Summary

The size of the text

<a name='P-AdaptiveCards-AdaptiveTextBlock-Strikethrough'></a>
### Strikethrough `property`

##### Summary

Make the struck through

<a name='P-AdaptiveCards-AdaptiveTextBlock-Text'></a>
### Text `property`

##### Summary

The text to display

<a name='P-AdaptiveCards-AdaptiveTextBlock-Weight'></a>
### Weight `property`

##### Summary

The weight of the text

<a name='P-AdaptiveCards-AdaptiveTextBlock-Wrap'></a>
### Wrap `property`

##### Summary

Is it allowed for the text to wrap

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

Input which collects text from the user

<a name='P-AdaptiveCards-AdaptiveTextInput-InlineAction'></a>
### InlineAction `property`

##### Summary

The Body elements for this card

<a name='P-AdaptiveCards-AdaptiveTextInput-IsMultiline'></a>
### IsMultiline `property`

##### Summary

true to collect multiple lines of text(default is false)

<a name='P-AdaptiveCards-AdaptiveTextInput-MaxLength'></a>
### MaxLength `property`

##### Summary

hint of maximum length characters to collect(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveTextInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text for the input desired

<a name='P-AdaptiveCards-AdaptiveTextInput-Style'></a>
### Style `property`

##### Summary

Hint of style of input, if client doesn't support the style it will become simple text input

<a name='P-AdaptiveCards-AdaptiveTextInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field

<a name='T-AdaptiveCards-AdaptiveTextInputStyle'></a>
## AdaptiveTextInputStyle `type`

##### Namespace

AdaptiveCards

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Email'></a>
### Email `constants`

##### Summary

Input is a email and the client may use this information to provide optimized keyboard input for the user.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Tel'></a>
### Tel `constants`

##### Summary

Input is a telephone number and the client may use this information to provide optimized keyboard input for the
    user.

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Text'></a>
### Text `constants`

##### Summary

plain text

<a name='F-AdaptiveCards-AdaptiveTextInputStyle-Url'></a>
### Url `constants`

##### Summary

Input is a url and the client may use this information to provide optimized keyboard input for the user.

<a name='T-AdaptiveCards-AdaptiveTextRun'></a>
## AdaptiveTextRun `type`

##### Namespace

AdaptiveCards

<a name='P-AdaptiveCards-AdaptiveTextRun-Color'></a>
### Color `property`

##### Summary

The color of the text

<a name='P-AdaptiveCards-AdaptiveTextRun-FontType'></a>
### FontType `property`

##### Summary

The font style of the text

<a name='P-AdaptiveCards-AdaptiveTextRun-Highlight'></a>
### Highlight `property`

##### Summary

Make the text highlighted

<a name='P-AdaptiveCards-AdaptiveTextRun-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Make the text less prominent

<a name='P-AdaptiveCards-AdaptiveTextRun-Italic'></a>
### Italic `property`

##### Summary

Make the text italic

<a name='P-AdaptiveCards-AdaptiveTextRun-SelectAction'></a>
### SelectAction `property`

##### Summary

Action for this text run

<a name='P-AdaptiveCards-AdaptiveTextRun-Size'></a>
### Size `property`

##### Summary

The size of the text

<a name='P-AdaptiveCards-AdaptiveTextRun-Strikethrough'></a>
### Strikethrough `property`

##### Summary

Make the struck through

<a name='P-AdaptiveCards-AdaptiveTextRun-Text'></a>
### Text `property`

##### Summary

The text to display

<a name='P-AdaptiveCards-AdaptiveTextRun-Underline'></a>
### Underline `property`

##### Summary

Make the text be underlined

<a name='P-AdaptiveCards-AdaptiveTextRun-Weight'></a>
### Weight `property`

##### Summary

The weight of the text

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

Input which collects Time from the user

<a name='P-AdaptiveCards-AdaptiveTimeInput-Max'></a>
### Max `property`

##### Summary

hint of maximum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveTimeInput-Min'></a>
### Min `property`

##### Summary

hint of minimum value(may be ignored by some clients)

<a name='P-AdaptiveCards-AdaptiveTimeInput-Placeholder'></a>
### Placeholder `property`

##### Summary

Placeholder text for the input desired

<a name='P-AdaptiveCards-AdaptiveTimeInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field

<a name='T-AdaptiveCards-AdaptiveToggleInput'></a>
## AdaptiveToggleInput `type`

##### Namespace

AdaptiveCards

##### Summary

Input which collects a choice between two options from the user

<a name='P-AdaptiveCards-AdaptiveToggleInput-Title'></a>
### Title `property`

##### Summary

Title text for toggle

<a name='P-AdaptiveCards-AdaptiveToggleInput-Value'></a>
### Value `property`

##### Summary

The initial value for the field

<a name='P-AdaptiveCards-AdaptiveToggleInput-ValueOff'></a>
### ValueOff `property`

##### Summary

Value to use for off (Default: false)

<a name='P-AdaptiveCards-AdaptiveToggleInput-ValueOn'></a>
### ValueOn `property`

##### Summary

Value to use for on (Default: true)

<a name='P-AdaptiveCards-AdaptiveToggleInput-Wrap'></a>
### Wrap `property`

##### Summary

when set true, text will wrap

<a name='T-AdaptiveCards-AdaptiveToggleVisibilityAction'></a>
## AdaptiveToggleVisibilityAction `type`

##### Namespace

AdaptiveCards

##### Summary

Toggle visibility action changes the visibility for the specified elements. You can also specify
    the visibility of a certain element to a set value instead of toggling it.

<a name='P-AdaptiveCards-AdaptiveToggleVisibilityAction-TargetElements'></a>
### TargetElements `property`

##### Summary

Identifiers of elements to change visibility. Example: "id1" or { "elementId": "id2", "isVisible": true }

<a name='T-AdaptiveCards-AdaptiveTypedBaseElementConverter'></a>
## AdaptiveTypedBaseElementConverter `type`

##### Namespace

AdaptiveCards

##### Summary

JsonConverters that deserialize to Adpative Elements and require
ParseContext must inherit this Class
ParseContext provides id generation, id collision detections, and other useful
services during deserialization

<a name='T-AdaptiveCards-AdaptiveTypedElement'></a>
## AdaptiveTypedElement `type`

##### Namespace

AdaptiveCards

<a name='F-AdaptiveCards-AdaptiveTypedElement-Requires'></a>
### Requires `constants`

##### Summary

A collection representing features and feature versions that this element is declared as requiring

<a name='P-AdaptiveCards-AdaptiveTypedElement-AdditionalProperties'></a>
### AdditionalProperties `property`

##### Summary

Additional properties not found on the default schema

<a name='P-AdaptiveCards-AdaptiveTypedElement-Id'></a>
### Id `property`

##### Summary

A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response

<a name='P-AdaptiveCards-AdaptiveTypedElement-Type'></a>
### Type `property`

##### Summary

The type name of the element

<a name='T-AdaptiveCards-AdaptiveTypedElementConverter'></a>
## AdaptiveTypedElementConverter `type`

##### Namespace

AdaptiveCards

##### Summary

This handles using type field to instantiate strongly typed object on deserialization

<a name='F-AdaptiveCards-AdaptiveTypedElementConverter-TypedElementTypes'></a>
### TypedElementTypes `constants`

##### Summary

Default types to support, register any new types to this list

<a name='T-AdaptiveCards-Rendering-AdaptiveVisitor'></a>
## AdaptiveVisitor `type`

##### Namespace

AdaptiveCards.Rendering

##### Summary

Utility class which allows you to visit every node

<a name='T-AdaptiveCards-ChartData'></a>
## ChartData `type`

##### Namespace

AdaptiveCards

##### Summary

ChartData

<a name='P-AdaptiveCards-ChartData-BackgroundColor'></a>
### BackgroundColor `property`

##### Summary

Background color for chart RGB or RGBA(#,#,#,#))

<a name='P-AdaptiveCards-ChartData-BorderColor'></a>
### BorderColor `property`

##### Summary

Border color to use for this data set. RGBA(#,#,#,#)

<a name='P-AdaptiveCards-ChartData-DataSets'></a>
### DataSets `property`

##### Summary

the data sets to render.

<a name='P-AdaptiveCards-ChartData-Labels'></a>
### Labels `property`

##### Summary

The labels for each element in the dataset

<a name='P-AdaptiveCards-ChartData-Options'></a>
### Options `property`

##### Summary

Options for the chart

<a name='T-AdaptiveCards-ChartDataSet'></a>
## ChartDataSet `type`

##### Namespace

AdaptiveCards

##### Summary

ChartDataSet

<a name='P-AdaptiveCards-ChartDataSet-BackgroundColors'></a>
### BackgroundColors `property`

##### Summary

Background colors to use for this data set. RGBA(#,#,#,#)

<a name='P-AdaptiveCards-ChartDataSet-BorderColors'></a>
### BorderColors `property`

##### Summary

Border colors to use for this data set. RGBA(#,#,#,#)

<a name='P-AdaptiveCards-ChartDataSet-Data'></a>
### Data `property`

##### Summary

Data

<a name='P-AdaptiveCards-ChartDataSet-Label'></a>
### Label `property`

##### Summary

Label for the data set

<a name='T-AdaptiveCards-ChartOptions'></a>
## ChartOptions `type`

##### Namespace

AdaptiveCards

<a name='P-AdaptiveCards-ChartOptions-CutoutPercentage'></a>
### CutoutPercentage `property`

##### Summary

Control pie chart cutut percentage.  > 0 gives you a donut chart. max value 50.

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

<a name='P-AdaptiveCards-IAdaptiveTextElement-Color'></a>
### Color `property`

##### Summary

The color of the text

<a name='P-AdaptiveCards-IAdaptiveTextElement-FontType'></a>
### FontType `property`

##### Summary

The font style of the TextBlock

<a name='P-AdaptiveCards-IAdaptiveTextElement-IsSubtle'></a>
### IsSubtle `property`

##### Summary

Make the text less prominent

<a name='P-AdaptiveCards-IAdaptiveTextElement-Italic'></a>
### Italic `property`

##### Summary

Make the text italic

<a name='P-AdaptiveCards-IAdaptiveTextElement-Size'></a>
### Size `property`

##### Summary

The size of the text

<a name='P-AdaptiveCards-IAdaptiveTextElement-Strikethrough'></a>
### Strikethrough `property`

##### Summary

Make the struck through

<a name='P-AdaptiveCards-IAdaptiveTextElement-Text'></a>
### Text `property`

##### Summary

The text to display

<a name='P-AdaptiveCards-IAdaptiveTextElement-Weight'></a>
### Weight `property`

##### Summary

The weight of the text

<a name='T-AdaptiveCards-Rendering-IconPlacement'></a>
## IconPlacement `type`

##### Namespace

AdaptiveCards.Rendering

<a name='F-AdaptiveCards-Rendering-IconPlacement-AboveTitle'></a>
### AboveTitle `constants`

##### Summary

Places the icons about the text in actions

<a name='F-AdaptiveCards-Rendering-IconPlacement-LeftOfTitle'></a>
### LeftOfTitle `constants`

##### Summary

Place the icon to the left of the text in actions

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

<a name='F-AdaptiveCards-Rendering-ShowCardActionMode-Inline'></a>
### Inline `constants`

##### Summary

Show the card inline

<a name='F-AdaptiveCards-Rendering-ShowCardActionMode-Popup'></a>
### Popup `constants`

##### Summary

Popup the card

<a name='T-AdaptiveCards-Rendering-ShowCardConfig'></a>
## ShowCardConfig `type`

##### Namespace

AdaptiveCards.Rendering

<a name='P-AdaptiveCards-Rendering-ShowCardConfig-InlineTopMargin'></a>
### InlineTopMargin `property`

##### Summary

If actionMode is inline this is the margin between the inline card and the actions

<a name='P-AdaptiveCards-Rendering-ShowCardConfig-Style'></a>
### Style `property`

##### Summary

Indicates the style of ShowCard

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
