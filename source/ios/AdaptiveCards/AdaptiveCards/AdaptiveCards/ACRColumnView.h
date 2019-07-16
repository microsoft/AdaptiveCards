//
//  ACRColumnView
//  ACRColumnView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRContentStackView.h"

@interface ACRColumnView:ACRContentStackView

typedef NS_ENUM(NSInteger, ACRColumnWidthPriority) {
    ACRColumnWidthPriorityStretch = 250,
    ACRColumnWidthPriorityAuto = ACRColumnWidthPriorityStretch + 1
};

@property NSString *columnWidth;
@property CGFloat pixelWidth;
@property BOOL hasStretchableView;

- (UIView *)addPaddingSpace;

@end
