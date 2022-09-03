//
//  ACRImageRenderer
//  ACRImageRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#endif

@interface ACRImageRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

+ (ACRImageRenderer *)getInstance;

- (void)configUpdateForUIImageView:(ACRView *)rootView acoElem:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;

@end
