//
//  ACRImageRenderer
//  ACRImageRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRImageRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

+ (ACRImageRenderer *)getInstance;

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;

@end
