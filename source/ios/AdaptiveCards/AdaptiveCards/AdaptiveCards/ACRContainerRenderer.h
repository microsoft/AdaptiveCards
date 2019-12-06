//
//  ACRContainerRenderer
//  ACRContainerRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRContainerRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

+ (ACRContainerRenderer *)getInstance;

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;

@end
