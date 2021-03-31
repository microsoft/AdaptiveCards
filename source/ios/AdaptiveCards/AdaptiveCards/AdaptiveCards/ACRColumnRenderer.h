//
//  ACRColumnRenderer
//  ACRColumnRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRColumnRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

@property BOOL fillAlignment;

+ (ACRColumnRenderer *)getInstance;

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;

@end
