//
//  ACRTableRow.h
//  ACRTableRow
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "AdaptiveCards.h"
#import "ACRContentStackView.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACRColumnDefinition : NSObject

// if pixel, numeric has the pixel width, else has the fraction, 
// the width / total relative width
@property CGFloat numeric;
// sum of all pixel width in a row
@property CGFloat totalPixelWidth;
// the column definition was invalid; will be skipped in rendering
@property BOOL isValid;
// the column has pixel width;
@property BOOL isPixelWidth;

- (instancetype)initWithPixelWidth:(CGFloat)numeric;

- (instancetype)initWithRelativeWidth:(CGFloat)numeric
                      totalPixelWidth:(CGFloat)totalPixelWidth;

@end

@interface ACRTableRowView : ACRContentStackView

- (instancetype)init:(ACOBaseCardElement *)acoElem
    columnDefinitions:(NSArray<ACRColumnDefinition *> *)columnDefinition
             rootView:(ACRView *)rootView
               inputs:(NSMutableArray *)inputs
           hostConfig:(ACOHostConfig *)acoConfig;

@end

NS_ASSUME_NONNULL_END
