//
//  ACRColumnSetRenderer
//  ACRColumnSetRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRColumnSetRenderer : ACRBaseCardElementRenderer

+ (ACRColumnSetRenderer *)getInstance;

@end
