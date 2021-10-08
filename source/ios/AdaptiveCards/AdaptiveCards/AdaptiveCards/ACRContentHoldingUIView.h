//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRImageProperties.h"
#import "ACRContentStackView.h"

const extern NSInteger eACRUILabelTag;
const extern NSInteger eACRUIFactSetTag;
const extern NSInteger eACRUIImageTag;

@interface ACRContentHoldingUIView : UIView

@property ACRImageProperties *imageProperties;
@property BOOL isPersonStyle;
@property BOOL hidePlayIcon;
@property BOOL isMediaType;
@property (weak, readonly) UIView *contentView;

- (instancetype)initWithImageProperties:(ACRImageProperties *)imageProperties imageView:(UIImageView *)imageView viewGroup:(ACRContentStackView *)viewGroup;
- (void)update:(ACRImageProperties *)imageProperties;

@end
