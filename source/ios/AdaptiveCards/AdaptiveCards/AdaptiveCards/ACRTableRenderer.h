//
//  ACRTableRenderer
//  ACRTableRenderer.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRTableRenderer : ACRBaseCardElementRenderer

+ (ACRTableRenderer *)getInstance;

@end
