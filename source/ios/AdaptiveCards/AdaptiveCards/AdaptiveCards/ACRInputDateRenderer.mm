//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRInputDateRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRDateTextField.h"
#import "ACRInputLabelViewPrivate.h"
#import "UtiliOS.h"
#else
#import <AdaptiveCards/ACRInputDateRenderer.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRContentHoldingUIView.h>
#import <AdaptiveCards/ACRDateTextField.h>
#import <AdaptiveCards/ACRInputLabelViewPrivate.h>
#import <AdaptiveCards/UtiliOS.h>
#endif

@implementation ACRInputDateRenderer

+ (ACRInputDateRenderer *)getInstance
{
    static ACRInputDateRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRDateInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<BaseInputElement> dateInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *dateField = [[ACRDateTextField alloc] initWithTimeDateInput:dateInput dateStyle:NSDateFormatterShortStyle];

    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adaptiveInputElement:dateInput inputView:dateField accessibilityItem:dateField.inputView viewGroup:viewGroup dataSource:nil];
    dateField.accessibilityTraits = UIAccessibilityTraitButton | UIAccessibilityTraitStaticText;
    dateField.accessibilityHint = NSLocalizedString(@"opens the date picker", nil);

    [viewGroup addArrangedSubview:inputLabelView];

    [inputs addObject:inputLabelView];

    return inputLabelView;
}

@end
