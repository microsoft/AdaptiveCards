//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"

const NSInteger eACRUILabelTag = 0x1234;
const NSInteger eACRUIFactSetTag = 0x1235;
const NSInteger eACRUIImageTag = 0x1236;

@interface ACRContentHoldingUIView: UIView

@property BOOL isPersonStyle;
@property BOOL hidePlayIcon;
@property BOOL isMediaType;

@end
