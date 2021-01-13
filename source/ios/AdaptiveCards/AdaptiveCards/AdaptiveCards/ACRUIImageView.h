//
//  ACRUIImageView.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACREnums.h"
#import <UIKit/UIKit.h>

@interface ACRUIImageView : UIImageView
@property BOOL isPersonStyle;
@property CGSize desiredSize;
@property CGFloat widthToHeightRatio;
@property CGFloat heightToWidthRatio;
@property ACRImageSize adaptiveImageSize;
@end
