//
//  ACRInputToggleView.h
//  AdaptiveCards
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRToggleInputView : UIView
@property (strong, nonatomic) IBOutlet UIStackView *contentview;
@property (weak, nonatomic) IBOutlet UILabel *title;
@property (weak, nonatomic) IBOutlet UISwitch *toggle;
@property IBInspectable UIColor *switchOffStateColor;
@end
