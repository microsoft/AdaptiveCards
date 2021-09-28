//
//  ACOPaddingHandler.h
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ACOBaseCardElement;
@class ACRSeparator;

extern const CGFloat kFillerViewLayoutConstraintPriority;

@interface ACOFillerSpaceManager : NSObject

/// tells if the owner of this object has padding
@property (nonatomic) BOOL hasPadding;

/// configures & adds padding for the `view`
/// having padding makes the owner of the object,
/// stretchable
- (UIView *)addPaddingFor:(UIView *)view;

/// configures for AdaptiveCards Height property
/// Image and Media gets their own padding since stretching them are not desirable
- (void)configureHeight:(UIView *)view correspondingElement:(ACOBaseCardElement *)correspondingElement;

/// activates the constraints together for performance
/// two stretchable views get same height
/// by setting low priority, the relationship can be overridden
/// if it's not possible
- (NSArray<NSLayoutConstraint *> *)activateConstraintsForPadding;

- (void)deactivateConstraintsForPadding;

- (BOOL)isPadding:(UIView *)padding;

- (NSArray<NSValue *> *)getFillerSpaceView:(UIView *)view;

- (void)associateSeparatorWithOwnerView:(UIView *)separator ownerView:(UIView *)ownerView;

- (ACRSeparator *)getSeparatorForOwnerView:(UIView *)ownerView;

+ (void)configureHugging:(UIView *)view;

@end
