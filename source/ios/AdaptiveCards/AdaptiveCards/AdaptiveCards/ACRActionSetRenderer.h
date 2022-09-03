//
//  ACRActionSetRenderer
//  ACRActionSetRenderer.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseActionElementRenderer.h"
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRActionSetRenderer : ACRBaseCardElementRenderer <ACRIBaseActionSetRenderer>

+ (ACRActionSetRenderer *)getInstance;

@end
