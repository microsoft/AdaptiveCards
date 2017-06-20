//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRRegistration : NSObject 

+ (ACRRegistration* ) getInstance;

- (ACRBaseCardElementRenderer* ) getRenderer:(NSString*) cardElementType;

@end
