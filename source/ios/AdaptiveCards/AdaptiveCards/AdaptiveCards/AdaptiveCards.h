//
//  ACFramework.h
//  ACFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for ACFramework.
FOUNDATION_EXPORT double AdaptiveCardsFrameworkVersionNumber;

//! Project version string for AFramework.
FOUNDATION_EXPORT const unsigned char AdaptiveCarsFrameworkVersionString[];
#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOActionOverflow.h"
#import "ACOAdaptiveCard.h"
#import "ACOAdaptiveCardParseResult.h"
#import "ACOBaseActionElement.h"
#import "ACOBaseCardElement.h"
#import "ACOEnums.h"
#import "ACOHostConfig.h"
#import "ACOHostConfigParseResult.h"
#import "ACOIResourceResolver.h"
#import "ACOInputResults.h"
#import "ACOMediaEvent.h"
#import "ACORemoteResourceInformation.h"
#import "ACORenderContext.h"
#import "ACOResourceResolvers.h"
#import "ACRActionDelegate.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRActionSetRenderer.h"
#import "ACRActionShowCardRenderer.h"
#import "ACRActionSubmitRenderer.h"
#import "ACRAggregateTarget.h"
#import "ACRBaseActionElementRenderer.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRBaseTarget.h"
#import "ACRButton.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRColumnRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRContainerRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRErrors.h"
#import "ACRFactSetRenderer.h"
#import "ACRIBaseActionElementRenderer.h"
#import "ACRIBaseCardElementRenderer.h"
#import "ACRIBaseInputHandler.h"
#import "ACRIMedia.h"
#import "ACRImageProperties.h"
#import "ACRImageRenderer.h"
#import "ACRImageSetRenderer.h"
#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputDateRenderer.h"
#import "ACRInputLabelView.h"
#import "ACRInputNumberRenderer.h"
#import "ACRInputRenderer.h"
#import "ACRInputTimeRenderer.h"
#import "ACRInputToggleRenderer.h"
#import "ACRMediaRenderer.h"
#import "ACRMediaTarget.h"
#import "ACROverflowTarget.h"
#import "ACRParseWarning.h"
#import "ACRRegistration.h"
#import "ACRRenderResult.h"
#import "ACRRenderer.h"
#import "ACRRichTextBlockRenderer.h"
#import "ACRTableCellRenderer.h"
#import "ACRTableRenderer.h"
#import "ACRTableRow.h"
#import "ACRTableView.h"
#import "ACRTapGestureRecognizerEventHandler.h"
#import "ACRTapGestureRecognizerFactory.h"
#import "ACRTextBlockRenderer.h"
#import "ACRTextInputHandler.h"
#import "ACRTextView.h"
#import "ACRToggleInputView.h"
#import "ACRView.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOActionOverflow.h>
#import <AdaptiveCards/ACOAdaptiveCard.h>
#import <AdaptiveCards/ACOAdaptiveCardParseResult.h>
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACOEnums.h>
#import <AdaptiveCards/ACOHostConfig.h>
#import <AdaptiveCards/ACOHostConfigParseResult.h>
#import <AdaptiveCards/ACOIResourceResolver.h>
#import <AdaptiveCards/ACOInputResults.h>
#import <AdaptiveCards/ACOMediaEvent.h>
#import <AdaptiveCards/ACORemoteResourceInformation.h>
#import <AdaptiveCards/ACORenderContext.h>
#import <AdaptiveCards/ACOResourceResolvers.h>
#import <AdaptiveCards/ACRActionDelegate.h>
#import <AdaptiveCards/ACRActionOpenURLRenderer.h>
#import <AdaptiveCards/ACRActionSetRenderer.h>
#import <AdaptiveCards/ACRActionShowCardRenderer.h>
#import <AdaptiveCards/ACRActionSubmitRenderer.h>
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRBaseTarget.h>
#import <AdaptiveCards/ACRButton.h>
#import <AdaptiveCards/ACRChoiceSetCompactStyleView.h>
#import <AdaptiveCards/ACRColumnRenderer.h>
#import <AdaptiveCards/ACRColumnSetRenderer.h>
#import <AdaptiveCards/ACRContainerRenderer.h>
#import <AdaptiveCards/ACRContentHoldingUIView.h>
#import <AdaptiveCards/ACRErrors.h>
#import <AdaptiveCards/ACRFactSetRenderer.h>
#import <AdaptiveCards/ACRIBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRIBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#import <AdaptiveCards/ACRIMedia.h>
#import <AdaptiveCards/ACRImageProperties.h>
#import <AdaptiveCards/ACRImageRenderer.h>
#import <AdaptiveCards/ACRImageSetRenderer.h>
#import <AdaptiveCards/ACRInputChoiceSetRenderer.h>
#import <AdaptiveCards/ACRInputDateRenderer.h>
#import <AdaptiveCards/ACRInputLabelView.h>
#import <AdaptiveCards/ACRInputNumberRenderer.h>
#import <AdaptiveCards/ACRInputRenderer.h>
#import <AdaptiveCards/ACRInputTimeRenderer.h>
#import <AdaptiveCards/ACRInputToggleRenderer.h>
#import <AdaptiveCards/ACRMediaRenderer.h>
#import <AdaptiveCards/ACRMediaTarget.h>
#import <AdaptiveCards/ACROverflowTarget.h>
#import <AdaptiveCards/ACRParseWarning.h>
#import <AdaptiveCards/ACRRegistration.h>
#import <AdaptiveCards/ACRRenderResult.h>
#import <AdaptiveCards/ACRRenderer.h>
#import <AdaptiveCards/ACRRichTextBlockRenderer.h>
#import <AdaptiveCards/ACRTableCellRenderer.h>
#import <AdaptiveCards/ACRTableRenderer.h>
#import <AdaptiveCards/ACRTableRow.h>
#import <AdaptiveCards/ACRTableView.h>
#import <AdaptiveCards/ACRTapGestureRecognizerEventHandler.h>
#import <AdaptiveCards/ACRTapGestureRecognizerFactory.h>
#import <AdaptiveCards/ACRTextBlockRenderer.h>
#import <AdaptiveCards/ACRTextInputHandler.h>
#import <AdaptiveCards/ACRTextView.h>
#import <AdaptiveCards/ACRToggleInputView.h>
#import <AdaptiveCards/ACRView.h>

#endif
