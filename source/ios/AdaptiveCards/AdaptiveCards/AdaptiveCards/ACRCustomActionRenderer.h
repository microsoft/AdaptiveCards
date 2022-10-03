//
//  ACRCustomActionRenderer
//  ACRCustomActionRenderer.h
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACRBaseActionElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#endif

@interface ACRCustomActionRenderer : ACRBaseActionElementRenderer

+ (ACRCustomActionRenderer *)getInstance;

@end
