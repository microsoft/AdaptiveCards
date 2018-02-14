//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputDateRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRDateTextField.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRInputDateRenderer

+ (ACRInputDateRenderer *)getInstance
{
    static ACRInputDateRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::DateInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *) viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<BaseInputElement> dateInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *dateField = [[ACRDateTextField alloc] initWithTimeDateInput:dateInput dateStyle:NSDateFormatterShortStyle];

    [viewGroup addArrangedSubview: dateField];

    [inputs addObject:dateField];

    return dateField;
}

@end
