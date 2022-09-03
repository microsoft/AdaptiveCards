//
//  ACRTableRenderer
//  ACRTableRenderer.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRTableRenderer : ACRBaseCardElementRenderer

+ (ACRTableRenderer *)getInstance;

@end
