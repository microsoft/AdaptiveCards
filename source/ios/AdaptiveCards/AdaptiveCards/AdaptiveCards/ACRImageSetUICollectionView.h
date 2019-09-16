//
//  ACRImageSetUICollectionViewController
//  ACRImageSetUICollectionViewController.h
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRView.h"
#import "HostConfig.h"
#import "ImageSet.h"
#import "SharedAdaptiveCard.h"
#import <UIKit/UIKit.h>

@interface ACRImageSetUICollectionView : UICollectionView <UICollectionViewDataSource, UICollectionViewDelegateFlowLayout>
- (instancetype)init:(std::shared_ptr<AdaptiveCards::ImageSet> const &)imageSet
      WithHostConfig:(ACOHostConfig *)hostConfig
       WithSuperview:(UIView *)superview
            rootView:(ACRView *)rootView;
@end
