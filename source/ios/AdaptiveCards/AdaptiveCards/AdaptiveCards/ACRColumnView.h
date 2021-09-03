//
//  ACRColumnView
//  ACRColumnView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRContentStackView.h"
#import "ACRColumnSetView.h"
#import "ACRIBaseInputHandler.h"
#import "ACOVisibilityManager.h"

@interface ACRColumnView : ACRContentStackView<ACOIVisibilityManagerFacade>

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
@property (nonatomic) BOOL hasStretchableView;
@property BOOL isLastColumn;
@property NSMutableArray<ACRIBaseInputHandler> *inputHandlers;
@property (weak) ACRColumnSetView *columnsetView;

- (UIView *)addPaddingFor:(UIView *)view;

- (void)configureHeightFor:(UIView *)view acoElement:(ACOBaseCardElement *)element;

- (void)configureHeight:(ACRVerticalContentAlignment)verticalContentAlignment
              minHeight:(NSInteger)minHeight
             heightType:(ACRHeightType)heightType
                   type:(ACRCardElementType)type;


@end
