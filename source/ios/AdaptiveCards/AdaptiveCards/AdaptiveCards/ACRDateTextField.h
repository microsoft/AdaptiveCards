//
//  ACRDateTextField
//  ACRDateTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACRTextField.h"
#import "BaseInputElement.h"
#import "SharedAdaptiveCard.h"
#import <UIKit/UIKit.h>

@interface ACRDateTextField : ACRTextField
@property NSDate *min;
@property NSDate *max;
@property NSRegularExpression *regularExpression;
@property NSDateFormatter *formatter;

- (instancetype)initWithTimeDateInput:(std::shared_ptr<AdaptiveCards::BaseInputElement> const &)elem
                            dateStyle:(NSDateFormatterStyle)dateStyle;
- (IBAction)update:(UIDatePicker *)picker;
- (IBAction)dismiss;
@end
