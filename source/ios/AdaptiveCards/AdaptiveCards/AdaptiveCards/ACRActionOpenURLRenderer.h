//
//  ACRActionOpenURLRenderer
//  ACRActionOpenURLRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseActionElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#endif

@interface ACRActionOpenURLRenderer : ACRBaseActionElementRenderer

+ (ACRActionOpenURLRenderer *)getInstance;

@end
