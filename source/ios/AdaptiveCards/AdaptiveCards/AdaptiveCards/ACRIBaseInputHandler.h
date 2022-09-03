//
//  ACRIBaseInputHandler
//  ACRIBaseInputHandler.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRErrors.h"
#else
#import <AdaptiveCards/ACRErrors.h>
#endif
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ACRIBaseInputHandler

@property BOOL isRequired;
@property BOOL hasValidationProperties;
@property BOOL hasVisibilityChanged;
@property NSString *_Nonnull id;

- (BOOL)validate:(NSError *_Nullable *_Nullable)error;
- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *_Nullable)view;
- (void)getInput:(NSMutableDictionary *_Nonnull)dictionary;

@end
