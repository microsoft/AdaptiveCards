//
//  ACRActionDelegate
//  ACRActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"

@protocol ACRActionDelegate <NSObject>

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action;

@optional
- (void)didLoadElements;
- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible;
- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame;

@end
