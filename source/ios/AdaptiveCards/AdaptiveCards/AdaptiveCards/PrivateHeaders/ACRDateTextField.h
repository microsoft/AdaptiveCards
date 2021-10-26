//
//  ACRDateTextField
//  ACRDateTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACRTextField.h"
#import <Adaptivecards/BaseInputElement.h>
#import <Adaptivecards/SharedAdaptiveCard.h>
#import <UIKit/UIKit.h>

@interface ACRDateTextField : ACRTextField<ACRIBaseInputHandler>
@property NSDate *min;
@property NSDate *max;
@property NSRegularExpression *regularExpression;

- (instancetype)initWithTimeDateInput:(std::shared_ptr<AdaptiveCards::BaseInputElement> const &)elem
                            dateStyle:(NSDateFormatterStyle)dateStyle;
- (IBAction)update:(UIDatePicker *)picker;
- (IBAction)dismiss;
@end
