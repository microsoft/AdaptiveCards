//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import "ACRBaseCardElementRenderer.h"
#import "ACRBaseActionElementRenderer.h"

@interface ACRRegistration:NSObject 

+ (ACRRegistration *)getInstance;

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *) cardElementType;

- (ACRBaseActionElementRenderer *)getActionRenderer:(NSNumber *) cardElementType;

@end
