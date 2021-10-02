//
//  ACROverflowTarget
//  ACROverflowTarget.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOActionOverflow.h"
#import "ACRBaseTarget.h"
#import "ACRIContentHoldingView.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

@interface ACROverflowMenuItem : NSObject

@property (readonly) NSString *title;
@property (readonly) NSString *iconUrl;
@property (readonly) NSObject<ACRSelectActionDelegate> *target;
- (void)loadIconImageWithSize:(CGSize)size
                 onIconLoaded:(void (^)(UIImage *))onIconLoaded;

@end

@interface ACROverflowTarget : ACRBaseTarget

- (instancetype)initWithActionElement:(ACOActionOverflow *)actionElement
                             rootView:(ACRView *)rootView;

- (void)setInputs:(NSMutableArray *)inputs
        superview:(UIView<ACRIContentHoldingView> *)superview;

@property (readonly) NSArray<ACROverflowMenuItem *> *menuItems;

@end
