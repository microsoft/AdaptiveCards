//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#import "ACRIBaseInputHandler.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#endif

@interface ACRInputToggleRenderer : ACRBaseCardElementRenderer

+ (ACRInputToggleRenderer *)getInstance;

@end
