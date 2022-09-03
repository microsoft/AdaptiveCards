//
//  ACRRichTextBlockRenderer
//  ACRRichTextBlockRenderer.h
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRRichTextBlockRenderer : ACRBaseCardElementRenderer

+ (ACRRichTextBlockRenderer *)getInstance;
@end
