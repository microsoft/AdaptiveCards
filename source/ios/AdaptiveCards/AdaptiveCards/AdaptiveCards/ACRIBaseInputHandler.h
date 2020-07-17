//
//  ACRIBaseInputHandler
//  ACRIBaseInputHandler.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRErrors.h"
#import <Foundation/Foundation.h>

@protocol ACRIBaseInputHandler

@property BOOL isRequired;

- (BOOL)validate:(NSError **)error;
- (void)setFocus:(BOOL)shouldBecomeFirstResponder;
- (void)getInput:(NSMutableDictionary *)dictionary;

@end
