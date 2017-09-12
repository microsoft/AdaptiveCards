//
//  ACRImageSetUICollectionViewController
//  ACRImageSetUICollectionViewController.h
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "ImageSet.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRImageSetUICollectionView:UICollectionView<UICollectionViewDataSource, UICollectionViewDelegateFlowLayout>
- (instancetype)init:(std::shared_ptr<AdaptiveCards::ImageSet> const&)imageSet
      WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
       WithSuperview:(UIView* )superview;
@end
