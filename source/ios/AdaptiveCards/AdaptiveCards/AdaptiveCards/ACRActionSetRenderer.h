//
//  ACRActionSetRenderer
//  ACRActionSetRenderer.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRIBaseCardElementRenderer.h"

@interface ACRActionSetRenderer : NSObject <ACRIBaseActionSetRenderer, ACRIBaseCardElementRenderer>

+ (ACRActionSetRenderer *)getInstance;

@end
