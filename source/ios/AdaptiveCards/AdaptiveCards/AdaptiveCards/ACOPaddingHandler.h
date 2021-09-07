//
//  ACOPaddingHandler.h
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class ACOBaseCardElement;

@interface ACOPaddingHandler : NSObject

@property (nonatomic) BOOL hasPadding;

- (UIView *)addPaddingFor:(UIView *)view;

- (void)configureHeight:(UIView *)view correspondingElement:(ACOBaseCardElement *)correspondingElement;

- (NSArray<NSLayoutConstraint *> *)activateConstraintsForPadding;

- (BOOL)isPadding:(UIView *)padding;

+ (void)configureHugging:(UIView *)view;

@end
