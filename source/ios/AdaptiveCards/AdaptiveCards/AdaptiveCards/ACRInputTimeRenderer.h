//
//  ACRInputTimeRenderer
//  ACRInputTimeRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRInputTimeRenderer : ACRBaseCardElementRenderer

+ (ACRInputTimeRenderer *)getInstance;

@end
