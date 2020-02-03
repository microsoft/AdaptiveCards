//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

const extern NSInteger eACRUILabelTag;
const extern NSInteger eACRUIFactSetTag;
const extern NSInteger eACRUIImageTag;

@interface ACRContentHoldingUIView : UIView

@property CGSize desiredContentSize;
@property BOOL isPersonStyle;
@property BOOL hidePlayIcon;
@property BOOL isMediaType;

@end
