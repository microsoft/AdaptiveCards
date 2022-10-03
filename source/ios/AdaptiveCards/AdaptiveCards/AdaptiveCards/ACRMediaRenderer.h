//
//  ACRMediaRenderer
//  ACRMediaRenderer.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRMediaRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

+ (ACRMediaRenderer *)getInstance;

@end
