//
//  ACRColumnView
//  ACRColumnView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRContentStackView.h"
#import "ACRIBaseInputHandler.h"

@interface ACRColumnView : ACRContentStackView

typedef NS_ENUM(NSInteger, ACRColumnWidthPriority) {
    ACRColumnWidthPriorityStretch = 249,
    ACRColumnWidthPriorityStretchAuto = 250,
    ACRColumnWidthPriorityAuto,
};

@property NSString *columnWidth;
@property CGFloat pixelWidth;
@property BOOL hasStretchableView;
@property BOOL isLastColumn;
@property NSMutableArray<ACRIBaseInputHandler> *inputHandlers;

- (UIView *)addPaddingSpace;

@end
