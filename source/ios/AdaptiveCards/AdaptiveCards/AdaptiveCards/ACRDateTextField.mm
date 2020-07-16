//
//  ACRDateTextField
//  ACRDateTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRDateTextField.h"
#import "DateInput.h"
#import "DateTimePreparser.h"
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
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    self = [super init];
    if (self) {
        NSString *valueStr = nil;
        NSString *placeHolderStr = nil;
        NSString *minDateStr = nil;
        NSString *maxDateStr = nil;

        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        formatter.dateStyle = dateStyle;
        formatter.locale = [NSLocale currentLocale];
        UIDatePicker *picker = [bundle loadNibNamed:@"ACRDatePicker" owner:self options:nil][0];

        self.id = [NSString stringWithCString:elem->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.isRequired = elem->GetIsRequired();

        DateTimePreparser preparser;

        if (dateStyle == NSDateFormatterShortStyle) {
            std::shared_ptr<DateInput> dateInput = std::dynamic_pointer_cast<DateInput>(elem);

            placeHolderStr = [NSString stringWithCString:dateInput->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];

            unsigned int year, month, day;
            if (preparser.TryParseSimpleDate(dateInput->GetValue(), year, month, day)) {
                valueStr = [NSString stringWithFormat:@"%u-%u-%u", year, month, day];
            }

            year = month = day = 0;
            if (preparser.TryParseSimpleDate(dateInput->GetMin(), year, month, day)) {
                minDateStr = [NSString stringWithFormat:@"%u-%u-%u", year, month, day];
            }

            year = month = day = 0;
            if (preparser.TryParseSimpleDate(dateInput->GetMax(), year, month, day)) {
                maxDateStr = [NSString stringWithFormat:@"%u-%u-%u", year, month, day];
            }

            formatter.timeStyle = NSDateFormatterNoStyle;

            [formatter setDateFormat:@"yyyy-dd-MM"];

            picker.calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
            picker.datePickerMode = UIDatePickerModeDate;
        } else {
            std::shared_ptr<TimeInput> timeInput = std::dynamic_pointer_cast<TimeInput>(elem);

            placeHolderStr = [NSString stringWithCString:timeInput->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];

            unsigned int hours = 0, minutes = 0;
            if (preparser.TryParseSimpleTime(timeInput->GetValue(), hours, minutes)) {
                valueStr = [NSString stringWithFormat:@"%u:%u", hours, minutes];
            }

            hours = minutes = 0;

            if (preparser.TryParseSimpleTime(timeInput->GetMin(), hours, minutes)) {
                minDateStr = [NSString stringWithFormat:@"%u:%u", hours, minutes];
            }

            hours = minutes = 0;
            if (preparser.TryParseSimpleTime(timeInput->GetMax(), hours, minutes)) {
                maxDateStr = [NSString stringWithFormat:@"%u:%u", hours, minutes];
            }

//            minDateStr = [NSString stringWithCString:timeInput->GetMin().c_str()
//                                            encoding:NSUTF8StringEncoding];
//            maxDateStr = [NSString stringWithCString:timeInput->GetMax().c_str()
//                                            encoding:NSUTF8StringEncoding];
            formatter.timeStyle = NSDateFormatterShortStyle;

            [formatter setDateFormat:@"HH:mm"];

            picker.datePickerMode = UIDatePickerModeTime;
        }

        NSDate *date = [formatter dateFromString:valueStr];
        self.min = [formatter dateFromString:minDateStr];
        self.max = [formatter dateFromString:maxDateStr];
        self.placeholder = placeHolderStr;
        self.text = valueStr;
        self.allowsEditingTextAttributes = NO;
        self.borderStyle = UITextBorderStyleRoundedRect;
        self.backgroundColor = UIColor.groupTableViewBackgroundColor;
        self.formatter = formatter;
  
        if (date) {
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

        bar.items = @[ button ];
        button.tintColor = [UIColor blackColor];

        self.inputAccessoryView = bar;
        self.inputView = picker;
    }

    return self;
}

- (IBAction)dismiss
{
    [self endEditing:YES];
    self.text = [self.formatter stringFromDate:((UIDatePicker *)self.inputView).date];
}

- (IBAction)update:(UIDatePicker *)picker
{
    self.text = [self.formatter stringFromDate:picker.date];
}

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [super validate:error];
    if (isValidated == YES) {
        NSDate *date = [self.formatter dateFromString:self.text];
        if ([date compare:self.min] == NSOrderedAscending) {
            if (error) {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorLessThanMinDate userInfo:nil];
            }
            return NO;
        }
        if ([date compare:self.max] == NSOrderedDescending) {
            if (error) {
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
