//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRInputChoiceSetRenderer : ACRBaseCardElementRenderer

+ (ACRInputChoiceSetRenderer *)getInstance;

@end
