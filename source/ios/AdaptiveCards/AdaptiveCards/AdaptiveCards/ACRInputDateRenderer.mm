//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputDateRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRDateTextField.h"

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

- (UIView *)render:(UIView *) viewGroup
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &) elem
     andHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<BaseInputElement> dateInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *dateField = [[ACRDateTextField alloc] initWithTimeDateInput:dateInput dateStyle:NSDateFormatterShortStyle];

    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview: dateField];
    }
    
    [inputs addObject:dateField];
    
    return dateField;
}

@end
