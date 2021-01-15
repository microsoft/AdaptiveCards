//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRImageProperties.h"

const extern NSInteger eACRUILabelTag;
const extern NSInteger eACRUIFactSetTag;
const extern NSInteger eACRUIImageTag;

@interface ACRContentHoldingUIView : UIView

@property BOOL isPersonStyle;
@property BOOL hidePlayIcon;
@property BOOL isMediaType;

- (instancetype)initWithImageProperties:(ACRImageProperties *)imageProperties imageView:(UIImageView *)imageView;
- (void)update:(ACRImageProperties *)imageProperties;

@end
