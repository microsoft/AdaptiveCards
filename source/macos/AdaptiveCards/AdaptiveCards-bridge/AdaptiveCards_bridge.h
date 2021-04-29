//
//  AdaptiveCards_bridge.h
//  AdaptiveCards-bridge
//
//  Created by aksc on 17/01/21.
//

#import <Foundation/Foundation.h>
#import <AdaptiveCards_bridge/AdaptiveCards_bridge-BridgingHeader.h>

//! Project version number for AdaptiveCards_bridge.
FOUNDATION_EXPORT double AdaptiveCards_bridgeVersionNumber;

//! Project version string for AdaptiveCards_bridge.
FOUNDATION_EXPORT const unsigned char AdaptiveCards_bridgeVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AdaptiveCards_bridge/PublicHeader.h>

#import <AdaptiveCards_bridge/ACSActionAlignment.h>
#import <AdaptiveCards_bridge/ACSActionMode.h>
#import <AdaptiveCards_bridge/ACSActionSet.h>
#import <AdaptiveCards_bridge/ACSActionType.h>
#import <AdaptiveCards_bridge/ACSActionsOrientation.h>
#import <AdaptiveCards_bridge/ACSAdaptiveBase64Util.h>
#import <AdaptiveCards_bridge/ACSAdaptiveCard.h>
#import <AdaptiveCards_bridge/ACSAdaptiveCardParseException.h>
#import <AdaptiveCards_bridge/ACSAdaptiveCardParseWarning.h>
#import <AdaptiveCards_bridge/ACSAdaptiveCardSchemaKey.h>
#import <AdaptiveCards_bridge/ACSAssociatedInputs.h>
#import <AdaptiveCards_bridge/ACSBackgroundImage.h>
#import <AdaptiveCards_bridge/ACSBaseActionElement.h>
#import <AdaptiveCards_bridge/ACSBaseCardElement.h>
#import <AdaptiveCards_bridge/ACSBaseElement.h>
#import <AdaptiveCards_bridge/ACSBaseInputElement.h>
#import <AdaptiveCards_bridge/ACSCardElementType.h>
#import <AdaptiveCards_bridge/ACSChoiceInput.h>
#import <AdaptiveCards_bridge/ACSChoiceSetInput.h>
#import <AdaptiveCards_bridge/ACSChoiceSetStyle.h>
#import <AdaptiveCards_bridge/ACSCollectionTypeElement.h>
#import <AdaptiveCards_bridge/ACSColumn.h>
#import <AdaptiveCards_bridge/ACSColumnSet.h>
#import <AdaptiveCards_bridge/ACSContainer.h>
#import <AdaptiveCards_bridge/ACSContainerBleedDirection.h>
#import <AdaptiveCards_bridge/ACSContainerStyle.h>
#import <AdaptiveCards_bridge/ACSDateInput.h>
#import <AdaptiveCards_bridge/ACSDateTimePreparsedToken.h>
#import <AdaptiveCards_bridge/ACSDateTimePreparsedTokenFormat.h>
#import <AdaptiveCards_bridge/ACSDateTimePreparser.h>
#import <AdaptiveCards_bridge/ACSDelimiterType.h>
#import <AdaptiveCards_bridge/ACSEmphasisState.h>
#import <AdaptiveCards_bridge/ACSErrorStatusCode.h>
#import <AdaptiveCards_bridge/ACSFact.h>
#import <AdaptiveCards_bridge/ACSFactSet.h>
#import <AdaptiveCards_bridge/ACSFallbackType.h>
#import <AdaptiveCards_bridge/ACSFeatureRegistration.h>
#import <AdaptiveCards_bridge/ACSFontSizesConfig.h>
#import <AdaptiveCards_bridge/ACSFontType.h>
#import <AdaptiveCards_bridge/ACSFontWeightsConfig.h>
#import <AdaptiveCards_bridge/ACSForegroundColor.h>
#import <AdaptiveCards_bridge/ACSHeightType.h>
#import <AdaptiveCards_bridge/ACSHorizontalAlignment.h>
#import <AdaptiveCards_bridge/ACSHostConfig.h>
#import <AdaptiveCards_bridge/ACSIconPlacement.h>
#import <AdaptiveCards_bridge/ACSImage.h>
#import <AdaptiveCards_bridge/ACSImageFillMode.h>
#import <AdaptiveCards_bridge/ACSImageSet.h>
#import <AdaptiveCards_bridge/ACSImageSize.h>
#import <AdaptiveCards_bridge/ACSImageStyle.h>
#import <AdaptiveCards_bridge/ACSInline.h>
#import <AdaptiveCards_bridge/ACSInlineElementType.h>
#import <AdaptiveCards_bridge/ACSInternalId.h>
#import <AdaptiveCards_bridge/ACSIsVisible.h>
#import <AdaptiveCards_bridge/ACSMedia.h>
#import <AdaptiveCards_bridge/ACSMediaSource.h>
#import <AdaptiveCards_bridge/ACSNumberInput.h>
#import <AdaptiveCards_bridge/ACSOpenUrlAction.h>
#import <AdaptiveCards_bridge/ACSParseContext.h>
#import <AdaptiveCards_bridge/ACSParseResult.h>
#import <AdaptiveCards_bridge/ACSRichTextBlock.h>
#import <AdaptiveCards_bridge/ACSRichTextElementProperties.h>
#import <AdaptiveCards_bridge/ACSSemanticVersion.h>
#import <AdaptiveCards_bridge/ACSSeparator.h>
#import <AdaptiveCards_bridge/ACSSeparatorThickness.h>
#import <AdaptiveCards_bridge/ACSShowCardAction.h>
#import <AdaptiveCards_bridge/ACSSpacing.h>
#import <AdaptiveCards_bridge/ACSSubmitAction.h>
#import <AdaptiveCards_bridge/ACSTextBlock.h>
#import <AdaptiveCards_bridge/ACSTextElementProperties.h>
#import <AdaptiveCards_bridge/ACSTextInput.h>
#import <AdaptiveCards_bridge/ACSTextInputStyle.h>
#import <AdaptiveCards_bridge/ACSTextRun.h>
#import <AdaptiveCards_bridge/ACSTextSize.h>
#import <AdaptiveCards_bridge/ACSTextWeight.h>
#import <AdaptiveCards_bridge/ACSTimeInput.h>
#import <AdaptiveCards_bridge/ACSToggleInput.h>
#import <AdaptiveCards_bridge/ACSToggleVisibilityAction.h>
#import <AdaptiveCards_bridge/ACSToggleVisibilityTarget.h>
#import <AdaptiveCards_bridge/ACSUnknownAction.h>
#import <AdaptiveCards_bridge/ACSUnknownElement.h>
#import <AdaptiveCards_bridge/ACSVerticalAlignment.h>
#import <AdaptiveCards_bridge/ACSVerticalContentAlignment.h>
#import <AdaptiveCards_bridge/ACSWarningStatusCode.h>
#import <AdaptiveCards_bridge/ACSHostConfigParseResult.h>
#import <AdaptiveCards_bridge/BridgeConverter.h>
#import <AdaptiveCards_bridge/BridgeTextUtils.h>
