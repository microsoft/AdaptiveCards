//
//  ACRDateTextField
//  ACRDateTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRDateTextField.h"
#import "DateInput.h"
#import "TimeInput.h"

using namespace AdaptiveCards;

@implementation ACRDateTextField

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    return self;
}
- (instancetype)initWithTimeDateInput:(std::shared_ptr<BaseInputElement> const &)elem
                            dateStyle:(NSDateFormatterStyle)dateStyle
{
    self = [self initWithFrame:CGRectMake(0,0,0,0)];

    if(self)
    {
        NSString *valueStr = nil;
        NSString *placeHolderStr = nil;
        NSString *minDateStr = nil;
        NSString *maxDateStr = nil;
        
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        formatter.dateStyle = dateStyle;
        formatter.locale = [NSLocale currentLocale];        
        
        UIDatePicker *picker = [[UIDatePicker alloc] init];
        
        self.id = [NSString stringWithCString:elem->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.isRequired = elem->GetIsRequired();
        
        if(dateStyle == NSDateFormatterShortStyle)
        {
            std::shared_ptr<DateInput> dateInput = std::dynamic_pointer_cast<DateInput>(elem);
            
            valueStr = [NSString stringWithCString:dateInput->GetValue().c_str()
                                                 encoding:NSUTF8StringEncoding];
            placeHolderStr = [NSString stringWithCString:dateInput->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];
            minDateStr = [NSString stringWithCString:dateInput->GetMin().c_str()
                                            encoding:NSUTF8StringEncoding];
            maxDateStr = [NSString stringWithCString:dateInput->GetMax().c_str()
                                            encoding:NSUTF8StringEncoding];
            formatter.timeStyle = NSDateFormatterNoStyle;
            
            [formatter setDateFormat:@"yyyy-MM-dd"];
            
            picker.datePickerMode = UIDatePickerModeDate;
        }
        else
        {
            std::shared_ptr<TimeInput> timeInput = std::dynamic_pointer_cast<TimeInput>(elem);
            
            valueStr = [NSString stringWithCString:timeInput->GetValue().c_str()
                                          encoding:NSUTF8StringEncoding];
            placeHolderStr = [NSString stringWithCString:timeInput->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];
            minDateStr = [NSString stringWithCString:timeInput->GetMin().c_str()
                                            encoding:NSUTF8StringEncoding];
            maxDateStr = [NSString stringWithCString:timeInput->GetMax().c_str()
                                            encoding:NSUTF8StringEncoding];
            formatter.timeStyle = NSDateFormatterShortStyle;
            
            [formatter setDateFormat:@"HH:mm"];

            picker.datePickerMode = UIDatePickerModeTime;
        }
       
        NSDate *date = [formatter dateFromString:valueStr];
        self.formatter = formatter;
        self.min = [formatter dateFromString:minDateStr];
        self.max = [formatter dateFromString:maxDateStr];
        self.placeholder = placeHolderStr;
        self.text = valueStr;
        self.allowsEditingTextAttributes = NO;
        self.borderStyle = UITextBorderStyleLine;

        if(date)
        {
            picker.date = date;
        }
        
        [picker setMinimumDate:self.min];
        [picker setMaximumDate:self.max];
        [picker addTarget:self action:@selector(update:) forControlEvents:UIControlEventValueChanged];
        
        UIBarButtonItem *button = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                                                target:self
                                                                                action:@selector(dismiss)];
        UIToolbar *bar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, 0, picker.frame.size.width, 44)];
        [bar setBarStyle:UIBarStyleBlackOpaque];
        
        bar.items = @[button];
        button.tintColor = [UIColor blackColor];
        
        self.inputAccessoryView = bar;
        self.inputView = picker;
    }

    return self;
}

- (IBAction)dismiss
{
    [self endEditing:YES];
}

- (IBAction)update:(UIDatePicker *)picker
{
    self.text = [self.formatter stringFromDate:picker.date];
}

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [super validate:error];
    if(isValidated == YES)
    {
        NSDate *date = [self.formatter dateFromString:self.text];
        if([date compare:self.min] == NSOrderedAscending)
        {
            if(error)
            {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorLessThanMinDate userInfo:nil];
            }
            return NO;
        }
        if([date compare:self.max] == NSOrderedDescending)
        {
            if(error)
            {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorGreaterThanMaxDate userInfo:nil];
            }
            return NO;
        }
        return YES;
    }
    return isValidated;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = self.text;
}
@end
