//
//  ACRInputLabelView
//  ACRInputLabelView.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRInputLabelView : UIView 
@property (weak, nonatomic) IBOutlet UILabel *errorMessage;
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) IBOutlet UIStackView *stack;
@end
