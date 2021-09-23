//
//  ACRColumnView
//  ACRColumnView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOVisibilityManager.h"
#import "ACRColumnSetView.h"
#import "ACRContentStackView.h"
#import "ACRIBaseInputHandler.h"

@class ACRSeparator;

@interface ACRColumnView : ACRContentStackView <ACOIVisibilityManagerFacade>

typedef NS_ENUM(NSInteger, ACRColumnWidthPriority) {
    ACRColumnWidthPriorityStretch = 249,
    ACRColumnWidthPriorityStretchAuto = 251,
    ACRColumnWidthPriorityAuto,
};

@property (nonatomic) NSString *columnWidth;
@property CGFloat pixelWidth;
@property CGFloat relativeWidth;
@property ACRHeightType heightType;
@property BOOL hasMoreThanOneRelativeWidth;
@property BOOL isLastColumn;
@property NSMutableArray<ACRIBaseInputHandler> *inputHandlers;
@property (weak) ACRColumnSetView *columnsetView;

@end
