//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//
@class ACRBaseCardElementRenderer;

#import "ACRBaseActionElementRenderer.h"

@interface ACRRegistration:NSObject 

+ (ACRRegistration *)getInstance;

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *) cardElementType;

- (ACRBaseActionElementRenderer *)getActionRenderer:(NSNumber *) cardElementType;

- (void) setActionRenderer:(ACRBaseActionElementRenderer *)renderer cardElementType:(NSNumber *)cardElementType;

@end
