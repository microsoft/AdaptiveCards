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

- (BOOL)validate:(NSError *_Nonnull*)error;
- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView * _Nullable)view;
- (void)getInput:(NSMutableDictionary *_Nonnull)dictionary;

@end
