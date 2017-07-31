//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputDateRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "DateInput.h"

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
      withCardElem:(std::shared_ptr<BaseCardElement> const &) elem
     andHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<DateInput> dateInput = std::dynamic_pointer_cast<DateInput>(elem);
    UIDatePicker *datePicker = [[UIDatePicker alloc] init];
    datePicker.datePickerMode = UIDatePickerModeDate;
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.timeStyle = NSDateFormatterNoStyle;
    formatter.dateStyle = NSDateFormatterShortStyle;
    formatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];

    NSString *placeHolderStr = [NSString stringWithCString:dateInput->GetValue().c_str()
                                                  encoding:NSUTF8StringEncoding];
    
    NSDate *date = [formatter dateFromString:placeHolderStr];
    datePicker.date = date;
    
    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview: datePicker];
    }
    
    return datePicker;
}

@end
