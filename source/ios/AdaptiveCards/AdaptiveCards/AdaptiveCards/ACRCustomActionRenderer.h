//
//  ACRCustomActionRenderer
//  ACRCustomActionRenderer.h
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseActionElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#endif

@interface ACRCustomActionRenderer : ACRBaseActionElementRenderer

+ (ACRCustomActionRenderer *)getInstance;

@end
