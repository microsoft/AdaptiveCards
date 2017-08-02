//
//  ACRDateTextField
//  ACRDateTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIBaseInputHandler.h"
#import "ACRTextField.h"

@interface ACRDateTextField:ACRTextField
@property NSDate *min;
@property NSDate *max;
@property NSDateFormatter *formatter;

- (IBAction)update:(UIDatePicker *)picker;
- (IBAction)dismiss;
@end
