//
//  ACRDateTextField
//  ACRDateTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIBaseInputHandler.h"
#import "SharedAdaptiveCard.h"
#import "BaseInputElement.h"
#import "ACRTextField.h"

@interface ACRDateTextField:ACRTextField
@property NSDate *min;
@property NSDate *max;
@property NSDateFormatter *formatter;

- (instancetype)initWithTimeDateInput:(std::shared_ptr<AdaptiveCards::BaseInputElement> const &)elem
                            dateStyle:(NSDateFormatterStyle)dateStyle;
- (IBAction)update:(UIDatePicker *)picker;
- (IBAction)dismiss;
@end
