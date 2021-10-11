//
//  ACRTableCell.h
//  ACRTableCell
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRContentStackView.h"
#import "AdaptiveCards.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACRTableCellDefinition : NSObject

@property ACRContainerStyle style;
@property ACRVerticalContentAlignment verticalAlignment;
@property ACRHorizontalAlignment horizontalAlignment;
@property CGFloat cellSpacing;

@end

@interface ACRTableCellView : ACRColumnView

- (instancetype)init:(ACOBaseCardElement *)baseCardElement
      cellDefinition:(ACRTableCellDefinition *)definition
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;
@end

NS_ASSUME_NONNULL_END
