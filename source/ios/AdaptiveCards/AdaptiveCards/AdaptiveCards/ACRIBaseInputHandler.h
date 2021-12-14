//
//  ACRIBaseInputHandler
//  ACRIBaseInputHandler.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRErrors.h"
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
