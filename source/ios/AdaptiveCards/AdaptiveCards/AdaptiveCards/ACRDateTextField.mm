//
//  ACRDateTextField
//  ACRDateTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRDateTextField.h"
#import "ACRInputLabelView.h"
#import "DateInput.h"
#import "DateTimePreparser.h"
#import "TimeInput.h"

using namespace AdaptiveCards;

@implementation ACRDateTextField {
    NSDateFormatter *_encodeFormatter;
    NSDateFormatter *_decodeFormatter;
    NSString *_dateFormatString;
}

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

        _decodeFormatter = [[NSDateFormatter alloc] init];
        [self configDateFormatter:_decodeFormatter formatterStyle:dateStyle];
        _encodeFormatter = [[NSDateFormatter alloc] init];
        [self configDateFormatter:_encodeFormatter formatterStyle:dateStyle];

        UIDatePicker *picker = nil;
        if (@available(iOS 14.0, *)) {
            picker = [[UIDatePicker alloc] init];
            picker.preferredDatePickerStyle = UIDatePickerStyleInline;
        } else {
            // Fallback on earlier versions
            picker = [bundle loadNibNamed:@"ACRDatePicker" owner:self options:nil][0];
        }

        picker.locale = [NSLocale currentLocale];

        self.id = [NSString stringWithCString:elem->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.isRequired = elem->GetIsRequired();

        DateTimePreparser preparser;

        NSDate *date = nil;

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

            _dateFormatString = @"yyyy-MM-dd";
            picker.datePickerMode = UIDatePickerModeDate;
            picker.calendar = [NSCalendar currentCalendar];

            [_encodeFormatter setDateFormat:_dateFormatString];
            date = [_encodeFormatter dateFromString:valueStr];
            self.min = [_encodeFormatter dateFromString:minDateStr];
            self.max = [_encodeFormatter dateFromString:maxDateStr];
            [picker setMinimumDate:self.min];
            [picker setMaximumDate:self.max];
        } else {
            std::shared_ptr<TimeInput> timeInput = std::dynamic_pointer_cast<TimeInput>(elem);
            NSCalendar *calendar = [NSCalendar currentCalendar];

            placeHolderStr = [NSString stringWithCString:timeInput->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];
            unsigned int hours = 0, minutes = 0;
            if (preparser.TryParseSimpleTime(timeInput->GetValue(), hours, minutes)) {
                valueStr = [NSString stringWithFormat:@"%02u:%02u", hours, minutes];
                date = [calendar dateBySettingHour:hours minute:minutes second:0 ofDate:[NSDate date] options:0];
            }

            hours = minutes = 0;

            if (preparser.TryParseSimpleTime(timeInput->GetMin(), hours, minutes)) {
                self.min = [calendar dateBySettingHour:hours minute:minutes second:0 ofDate:[NSDate date] options:0];
                [picker setMinimumDate:self.min];
            }

            hours = minutes = 0;
            if (preparser.TryParseSimpleTime(timeInput->GetMax(), hours, minutes)) {
                self.max = [calendar dateBySettingHour:hours minute:minutes second:0 ofDate:[NSDate date] options:0];
                [picker setMaximumDate:self.max];
            }
            picker.datePickerMode = UIDatePickerModeTime;
            _dateFormatString = @"HH:mm";
            [_encodeFormatter setDateFormat:_dateFormatString];
        }

        self.placeholder = placeHolderStr;
        self.allowsEditingTextAttributes = NO;
        self.borderStyle = UITextBorderStyleRoundedRect;
        self.backgroundColor = UIColor.groupTableViewBackgroundColor;
        self.delegate = self;

        if (date) {
            picker.date = date;
            self.text = [_decodeFormatter stringFromDate:date];
        }

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
        self.hasValidationProperties = self.isRequired || self.max || self.min;
    }

    return self;
}

- (IBAction)dismiss
{
    [self endEditing:YES];
    self.text = [_decodeFormatter stringFromDate:[self getCurrentDate]];
}

- (IBAction)update:(UIDatePicker *)picker
{
    self.text = [_decodeFormatter stringFromDate:[self getCurrentDate]];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    return NO;
}

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [ACRInputLabelView commonTextUIValidate:self.isRequired hasText:self.hasText predicate:nil text:nil error:error];
    NSDate *date = [self getCurrentDate];
    if (isValidated == YES) {
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
    dictionary[self.id] = (self.text.length == 0) ? self.text : [_encodeFormatter stringFromDate:[self getCurrentDate]];
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    self.accessibilityLabel = view.accessibilityLabel;
    if (shouldBecomeFirstResponder) {
        UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, self);
        [view becomeFirstResponder];
    } else {
        [view resignFirstResponder];
    }
}

- (NSDate *)getCurrentDate
{
    return ((UIDatePicker *)self.inputView).date;
}

- (void)configDateFormatter:(NSDateFormatter *)formatter formatterStyle:(NSDateFormatterStyle)style
{
    if (style == NSDateFormatterShortStyle) {
        formatter.dateStyle = NSDateFormatterMediumStyle;
    } else {
        formatter.timeStyle = NSDateFormatterShortStyle;
    }

    formatter.locale = [NSLocale currentLocale];
}

@synthesize hasValidationProperties;

@synthesize id;

@synthesize isRequired;

@synthesize hasVisibilityChanged;

@end
