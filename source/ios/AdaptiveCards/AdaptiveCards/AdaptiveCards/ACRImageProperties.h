//
//  ACRImageProperties
//  ACRImageProperties.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"
#import "ACREnums.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRImageProperties : NSObject

@property BOOL hasExplicitDimensions;
@property BOOL isAspectRatioNeeded;
@property CGSize contentSize;
@property ACRImageSize acrImageSize;
@property ACRHorizontalAlignment acrHorizontalAlignment;
@property CGFloat pixelWidth;
@property CGFloat pixelHeight;

- (instancetype)init:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image;

- (void)updateContentSize:(CGSize)size;

@end
