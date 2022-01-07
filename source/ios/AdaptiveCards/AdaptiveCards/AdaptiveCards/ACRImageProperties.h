//
//  ACRImageProperties
//  ACRImageProperties.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACOHostConfig.h>
#import <AdaptiveCards/ACREnums.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

struct ACRAspectRatio {
    CGFloat widthToHeight;
    CGFloat heightToWidth;
};
typedef struct ACRAspectRatio ACRAspectRatio;

@interface ACRImageProperties : NSObject

@property BOOL hasExplicitDimensions;
@property BOOL isAspectRatioNeeded;
@property CGSize contentSize;
@property ACRImageSize acrImageSize;
@property ACRHorizontalAlignment acrHorizontalAlignment;
@property ACRHeightType height;
@property CGFloat pixelWidth;
@property CGFloat pixelHeight;

- (instancetype)init:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image;

- (void)updateContentSize:(CGSize)size;

+ (ACRAspectRatio)convertToAspectRatio:(CGSize)cgsize;
@end
