//
//  ACRTableView.h
//  ACRTableView
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRView.h"

NS_ASSUME_NONNULL_BEGIN


@class ACOBaseCardElement;
@class ACOHostConfig;

@interface ACRTableView : UIView

@property BOOL showGridLines;
@property ACRContainerStyle gridStyle;
@property CGFloat spacing;

- (instancetype)init:(ACOBaseCardElement *)acoElement
           viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;

@end

NS_ASSUME_NONNULL_END
