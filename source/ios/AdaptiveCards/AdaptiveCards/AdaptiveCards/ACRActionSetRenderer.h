//
//  ACRActionSetRenderer
//  ACRActionSetRenderer.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRBaseCardElementRenderer.h"

@interface ACRActionSetRenderer : ACRBaseCardElementRenderer<ACRIBaseActionSetRenderer>

+ (ACRActionSetRenderer *)getInstance;

@end
