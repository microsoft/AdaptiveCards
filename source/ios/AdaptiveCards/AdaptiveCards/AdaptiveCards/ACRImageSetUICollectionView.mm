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
    std::shared_ptr<ImageSet> _imgSet;
    std::shared_ptr<HostConfig> _config;
    UIViewController* _vc;
}

- (instancetype)init:(std::shared_ptr<ImageSet> const&)imageSet
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
       WithSuperview:(UIView* )view
  rootViewController:(UIViewController *)vc
{
    self = [super initWithFrame:view.frame collectionViewLayout:[[UICollectionViewFlowLayout alloc] init]];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        _imgSet = imageSet;
        _config = hostConfig;
        _vc = vc;
        CGSize sz = [ACRImageRenderer getImageSize:imageSet->GetImageSize() withHostConfig:_config];

        ((UICollectionViewFlowLayout* )self.collectionViewLayout).itemSize = sz;
        ((UICollectionViewFlowLayout* )self.collectionViewLayout).scrollDirection = UICollectionViewScrollDirectionVertical;

        self.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return self;
}
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    if(!self->_imgSet.get())
        return 0;
    return self->_imgSet->GetImages().size();
}
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"cellId";

    UIView* content = [[ACRImageRenderer getInstance] render:nil
                                          rootViewController:_vc
                                                      inputs:nil
                                                withCardElem:_imgSet->GetImages()[indexPath.row]
                                               andHostConfig:_config];

    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];
    if(!cell) {
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

- (CGSize)intrinsicContentSize
{
    return [self.collectionViewLayout collectionViewContentSize];
}
@end
