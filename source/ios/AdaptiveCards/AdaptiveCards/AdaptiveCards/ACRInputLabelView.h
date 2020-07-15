//
//  ACRInputLabelView
//  ACRInputLabelView.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIBaseInputHandler.h"

@interface ACRInputLabelView : UIView <ACRIBaseInputHandler>
@property (weak, nonatomic) IBOutlet UILabel *errorMessage;
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) IBOutlet UIStackView *stack;
@property BOOL isRequired;
@property BOOL hasErrorMessage;
@end
