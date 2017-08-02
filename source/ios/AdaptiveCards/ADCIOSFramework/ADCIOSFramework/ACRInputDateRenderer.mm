//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputDateRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRDateTextField.h"
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
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &) elem
     andHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<DateInput> dateInput = std::dynamic_pointer_cast<DateInput>(elem);
    
    ACRDateTextField *dateField = [[ACRDateTextField alloc] init];
    NSString *placeHolderStr = [NSString stringWithCString:dateInput->GetValue().c_str()
                                                  encoding:NSUTF8StringEncoding];
    NSString *minDateStr = [NSString stringWithCString:dateInput->GetMin().c_str()
                                              encoding:NSUTF8StringEncoding];
    NSString *maxDateStr = [NSString stringWithCString:dateInput->GetMax().c_str()
                                              encoding:NSUTF8StringEncoding];
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.timeStyle = NSDateFormatterNoStyle;
    formatter.dateStyle = NSDateFormatterShortStyle;
    formatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];
    dateField.formatter = formatter;
    dateField.min = [formatter dateFromString:minDateStr];
    dateField.max = [formatter dateFromString:maxDateStr];
    
    NSDate *date = [formatter dateFromString:placeHolderStr];
    dateField.placeholder = [formatter stringFromDate:date];
    dateField.allowsEditingTextAttributes = NO;
    
    UIDatePicker *datePicker = [[UIDatePicker alloc] init];
    datePicker.datePickerMode = UIDatePickerModeDate;
    datePicker.date = date;
    [datePicker addTarget:dateField action:@selector(update:) forControlEvents:UIControlEventValueChanged];
    
    UIBarButtonItem *button = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                                            target:dateField
                                                                            action:@selector(dismiss)];
    UIToolbar *bar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, 0, datePicker.frame.size.width, 44)];
    [bar setBarStyle:UIBarStyleBlackOpaque];
   
    bar.items = @[button];
    button.tintColor = [UIColor blackColor];
    
    dateField.inputAccessoryView = bar;    
    dateField.inputView = datePicker;
    
    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview: dateField];
    }
    
    [inputs addObject:dateField];
    
    return dateField;
}

@end
