//
//  ACRImageSetUICollectionViewController.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRImageSetUICollectionView.h"
#import "ACRImageRenderer.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

using namespace AdaptiveCards;

@implementation ACRImageSetUICollectionView
{
    ACOBaseCardElement *_acoElem;
    ACOHostConfig *_acoConfig;
    std::shared_ptr<ImageSet> _imgSet;
    UIViewController* _vc;
}

- (instancetype)init:(std::shared_ptr<ImageSet> const&)imageSet
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
       WithSuperview:(UIView *)view
  rootViewController:(UIViewController *)vc
{
    self = [super initWithFrame:view.frame collectionViewLayout:[[UICollectionViewFlowLayout alloc] init]];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        _acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:imageSet];
        _acoConfig = [[ACOHostConfig alloc] initWithConfig:hostConfig];
        _imgSet = imageSet;
        _vc = vc;

        ((UICollectionViewFlowLayout *)self.collectionViewLayout).itemSize = [_acoConfig getImageSize:imageSet->GetImageSize()];
        ((UICollectionViewFlowLayout *)self.collectionViewLayout).scrollDirection = UICollectionViewScrollDirectionVertical;

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
    [_acoElem setElem:_imgSet->GetImages()[indexPath.row]];

    UIView *content = [[ACRImageRenderer getInstance] render:nil rootViewController:_vc inputs:nil baseCardElement:_acoElem hostConfig:_acoConfig];

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
