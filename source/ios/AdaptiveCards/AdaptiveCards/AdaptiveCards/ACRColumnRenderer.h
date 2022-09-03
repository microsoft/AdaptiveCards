//
//  ACRColumnRenderer
//  ACRColumnRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRColumnRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

@property BOOL fillAlignment;

+ (ACRColumnRenderer *)getInstance;

- (void)configUpdateForUIImageView:(ACRView *)rootView acoElem:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;

@end
