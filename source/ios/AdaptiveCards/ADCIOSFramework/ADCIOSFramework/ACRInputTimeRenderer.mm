//
//  ACRInputTimeRenderer
//  ACRInputTimeRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputTimeRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "TimeInput.h"

@implementation ACRInputTimeRenderer

+ (ACRInputTimeRenderer *)getInstance
{
    static ACRInputTimeRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::TimeInput;
}

- (UIView *)render:(UIView *)viewGroup
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<TimeInput> timeInput = std::dynamic_pointer_cast<TimeInput>(elem);
    UIDatePicker *timePicker = [[UIDatePicker alloc] init];
    timePicker.datePickerMode = UIDatePickerModeTime;
    
    NSString *placeHolderStr = [NSString stringWithCString:timeInput->GetValue().c_str()
                                                  encoding:NSUTF8StringEncoding];
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.timeStyle = NSDateFormatterShortStyle;
    formatter.dateStyle = NSDateFormatterNoStyle;
    formatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];
    NSDate *date = [formatter dateFromString:placeHolderStr];
    timePicker.date = date;
    
    if(viewGroup)[(UIStackView *)viewGroup addArrangedSubview: timePicker];
    
    return timePicker;
}

@end
