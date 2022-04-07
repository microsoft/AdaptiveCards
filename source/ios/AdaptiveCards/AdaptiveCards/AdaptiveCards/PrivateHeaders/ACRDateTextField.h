//
//  ACRDateTextField
//  ACRDateTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRIBaseInputHandler.h>
#import <AdaptiveCards/ACRTextField.h>
#import <AdaptiveCards/BaseInputElement.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <UIKit/UIKit.h>

@interface ACRDateTextField : ACRTextField <ACRIBaseInputHandler>
@property NSDate *min;
@property NSDate *max;
@property NSRegularExpression *regularExpression;

- (instancetype)initWithTimeDateInput:(std::shared_ptr<AdaptiveCards::BaseInputElement> const &)elem
                            dateStyle:(NSDateFormatterStyle)dateStyle;
- (IBAction)update:(UIDatePicker *)picker;
- (IBAction)dismiss;
@end
