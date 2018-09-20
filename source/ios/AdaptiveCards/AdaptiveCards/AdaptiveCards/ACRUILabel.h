//
//  ACRUILable.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACOBaseCardElement.h"

@interface ACRUILabel:UILabel

@property ACRContainerStyle style;
@property BOOL isFactSetLabel;
@property BOOL isTitle;
@property BOOL isStretchable;

@end
