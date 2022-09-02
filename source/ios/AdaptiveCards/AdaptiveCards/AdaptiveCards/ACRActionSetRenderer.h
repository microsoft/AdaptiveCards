//
//  ACRActionSetRenderer
//  ACRActionSetRenderer.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>

@interface ACRActionSetRenderer : ACRBaseCardElementRenderer <ACRIBaseActionSetRenderer>

+ (ACRActionSetRenderer *)getInstance;

@end
