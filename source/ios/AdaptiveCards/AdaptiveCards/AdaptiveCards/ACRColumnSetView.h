//
//  ACRColumnSetView
//  ACRColumnSetView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRContentStackView.h"

@interface ACRColumnSetView : ACRContentStackView

@property BOOL isLastColumn;
@property BOOL hasMoreThanOneColumnWithRelatvieWidth;

- (void)setAlignmentForColumnStretch;

@end
