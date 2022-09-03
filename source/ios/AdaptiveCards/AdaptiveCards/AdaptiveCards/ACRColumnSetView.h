//
//  ACRColumnSetView
//  ACRColumnSetView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
#import "ACRContentStackView.h"
#else
#import <AdaptiveCards/ACRContentStackView.h>
#endif

@interface ACRColumnSetView : ACRContentStackView

@property BOOL isLastColumn;
@property BOOL hasMoreThanOneColumnWithRelatvieWidth;

- (void)setAlignmentForColumnStretch;

@end
