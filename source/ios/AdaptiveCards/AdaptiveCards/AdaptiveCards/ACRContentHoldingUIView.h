//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRContentStackView.h"
#import "ACRImageProperties.h"
#else
#import <AdaptiveCards/ACRContentStackView.h>
#import <AdaptiveCards/ACRImageProperties.h>
#endif
#import <UIKit/UIKit.h>

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
