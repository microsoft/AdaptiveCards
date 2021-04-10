//
//  ACROverflowTarget
//  ACROverflowTarget.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOActionOverflow.h"
#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

@interface ACROverflowMenuItem : NSObject

@property (readonly) NSString *title;
@property (readonly) NSString *iconUrl;
@property (readonly) NSObject<ACRSelectActionDelegate> *target;
- (UIImage *)iconImageWithSize:(CGSize)size;

@end

@interface ACROverflowTarget : NSObject <ACRSelectActionDelegate>

- (instancetype)initWithActionElement:(ACOActionOverflow *)actionElement
                             rootView:(ACRView *)rootView;

- (void)setInputs:(NSMutableArray *)inputs
        superview:(UIView<ACRIContentHoldingView> *)superview;

@property (readonly) NSArray<ACROverflowMenuItem *> *menuItems;

@end
