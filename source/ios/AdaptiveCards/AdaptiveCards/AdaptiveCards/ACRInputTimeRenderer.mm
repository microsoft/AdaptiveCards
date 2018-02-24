//
//  ACRInputTimeRenderer
//  ACRInputTimeRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputTimeRenderer.h"
#import "ACRDateTextField.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRInputTimeRenderer

+ (ACRInputTimeRenderer *)getInstance
{
    static ACRInputTimeRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTimeInput;
}

- (UIView *)render:(UIView *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<BaseInputElement> timeInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *field = [[ACRDateTextField alloc] initWithTimeDateInput:timeInput dateStyle:NSDateFormatterNoStyle];

    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview:field];
    }

    [inputs addObject:field];

    return field;
}

@end
