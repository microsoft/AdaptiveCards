//
//  ACRMediaRenderer
//  ACRMediaRenderer.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRBaseCardElementRenderer.h>

@interface ACRMediaRenderer : ACRBaseCardElementRenderer <ACRIKVONotificationHandler>

+ (ACRMediaRenderer *)getInstance;

@end
