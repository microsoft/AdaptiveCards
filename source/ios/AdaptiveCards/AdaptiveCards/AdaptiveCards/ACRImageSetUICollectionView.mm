//
//  ACRImageSetUICollectionViewController.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRImageSetUICollectionView.h"
#import "ACRImageRenderer.h"

using namespace AdaptiveCards;

@implementation ACRImageSetUICollectionView
{
    std::shared_ptr<ImageSet> imgSet;
    std::shared_ptr<HostConfig> config;
}

- (instancetype)init:(std::shared_ptr<ImageSet> const&)imageSet
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
       WithSuperview:(UIView* )view
{
    self = [super initWithFrame:view.frame collectionViewLayout:[[UICollectionViewFlowLayout alloc] init]];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        imgSet = imageSet;
        config = hostConfig;
        CGSize sz = [self getImageSize];

        ((UICollectionViewFlowLayout* )self.collectionViewLayout).itemSize = sz;
        ((UICollectionViewFlowLayout* )self.collectionViewLayout).scrollDirection = UICollectionViewScrollDirectionVertical;

        self.translatesAutoresizingMaskIntoConstraints = NO;
        CGSize target = [view systemLayoutSizeFittingSize:sz];
        self.frame = CGRectMake(0, 0, (target.width / sz.width) * sz.width, sz.height);
    }
    return self;
}
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    if(!self->imgSet.get())
        return 0;
    return self->imgSet->GetImages().size();
}
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"cellId";

    for(auto img :imgSet->GetImages())
    {
        img->SetImageSize(imgSet->GetImageSize());
    }

    UIView* content = [[ACRImageRenderer getInstance] render:nil
                                          rootViewController:nil
                                                      inputs:nil
                                                withCardElem:imgSet->GetImages()[indexPath.row]
                                               andHostConfig:config];

    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];
    if(!cell)
    {
        cell = [[UICollectionViewCell alloc] initWithFrame:content.frame];
    }
    cell.contentView.frame = content.frame;
    [cell.contentView addSubview:content];
    return cell;
}
- (CGFloat)collectionView:(UICollectionView *)collectionView
                   layout:(UICollectionViewLayout *)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section
{
    return 0;
}
- (CGSize)getImageSize
{
    float sz = config->imageSizes.smallSize;
    switch (imgSet->GetImageSize()){
        case ImageSize::Large:{
            sz = config->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:{
            sz = config->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:{
            sz = config->imageSizes.smallSize;
            break;
        }

        default:{
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}
- (CGSize)intrinsicContentSize
{
    return [self.collectionViewLayout collectionViewContentSize];
}
@end
