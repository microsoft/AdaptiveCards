//
//  ACRImageSetUICollectionViewController.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageSetUICollectionView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRImageRenderer.h"
#import "ACRRegistration.h"
#import "UtiliOS.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACRImageSetUICollectionView {
    ACOBaseCardElement *_acoElem;
    ACOHostConfig *_acoConfig;
    std::shared_ptr<ImageSet> _imgSet;
    ImageSize _imageSize;
    ACRView *_rootView;
    __weak UIView<ACRIContentHoldingView> *_viewGroup;
    CGSize _size;
}

- (instancetype)init:(std::shared_ptr<ImageSet> const &)imageSet
      WithHostConfig:(ACOHostConfig *)hostConfig
       WithSuperview:(UIView *)view
            rootView:(ACRView *)rootView
{
    self = [super initWithFrame:view.frame collectionViewLayout:[[UICollectionViewFlowLayout alloc] init]];
    if (self) {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        _acoElem = [[ACOBaseCardElement alloc] initWithBaseCardElement:imageSet];
        _acoConfig = hostConfig;
        _imgSet = imageSet;
        _rootView = rootView;
        _imageSize = _imgSet->GetImageSize();
        if (_imgSet->GetImageSize() == ImageSize::Auto || _imgSet->GetImageSize() == ImageSize::Stretch || _imgSet->GetImageSize() == ImageSize::None) {
            _imageSize = ImageSize::Medium;
        }

        ACRImageSize acrImageSize = getACRImageSize(_imageSize, NO);
        CGSize itemSize = [_acoConfig getImageSizeAsCGSize:acrImageSize width:0.0f height:0.0f];
        _size = itemSize;
        ((UICollectionViewFlowLayout *)self.collectionViewLayout).itemSize = itemSize;
        self.scrollEnabled = NO;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        _viewGroup = (UIView<ACRIContentHoldingView> *)view;
    }
    return self;
}
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    if (!self->_imgSet.get())
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
    ImageSize cellSize = _imgSet->GetImageSize();

    if (cellSize == ImageSize::Auto || cellSize == ImageSize::Stretch || cellSize == ImageSize::None) {
        _imgSet->GetImages()[indexPath.row]->SetImageSize(_imageSize);
    }

    ACRBaseCardElementRenderer *imageRenderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInteger:ACRImage]];

    UIView *content = [imageRenderer render:_viewGroup rootView:_rootView inputs:nil baseCardElement:_acoElem hostConfig:_acoConfig];

    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];

    if (!cell) {
        cell = [[UICollectionViewCell alloc] initWithFrame:CGRectMake(0, 0, _size.width, _size.height)];
    } else {
        cell.contentView.frame = CGRectMake(0, 0, _size.width, _size.height);
    }

    [cell.contentView addSubview:content];

    return cell;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView
                                      layout:(UICollectionViewLayout *)collectionViewLayout
    minimumInteritemSpacingForSectionAtIndex:(NSInteger)section
{
    return 0;
}

- (CGSize)intrinsicContentSize
{
    return [self collectionViewContentSize];
}

- (CGSize)collectionViewContentSize
{
    NSUInteger cellCounts = _imgSet->GetImages().size();
    CGSize imageSize = ((UICollectionViewFlowLayout *)self.collectionViewLayout).itemSize;
    CGFloat spacing = ((UICollectionViewFlowLayout *)self.collectionViewLayout).minimumInteritemSpacing;
    CGFloat lineSpacing = ((UICollectionViewFlowLayout *)self.collectionViewLayout).minimumLineSpacing;

    // sanity check
    if (!imageSize.width || !cellCounts) {
        return CGSizeMake(0, 0);
    }
    CGFloat frameWidth = self.frame.size.width;
    CGFloat imageWidthWithSpacing = imageSize.width + spacing;

    // if there is spacing to the right edge, it's o.k.
    NSUInteger numbersOfItemsInRow = (frameWidth) ? (frameWidth) / imageWidthWithSpacing : cellCounts;
    // if addtional image can be fit by removing spacing, do so
    if (numbersOfItemsInRow * imageWidthWithSpacing + imageSize.width <= frameWidth) {
        numbersOfItemsInRow++;
    }

    NSUInteger numbersOfRows = numbersOfItemsInRow <= 0 ? 1 : ceil(((CGFloat)cellCounts) / numbersOfItemsInRow);
    return (frameWidth) ? CGSizeMake(frameWidth, (numbersOfRows) * (imageSize.height) + (numbersOfRows - 1) * lineSpacing) : CGSizeMake(cellCounts * imageWidthWithSpacing - ((cellCounts > 1) ? spacing : 0), imageSize.height);
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    // with the width set, re-measure the intrinsic content size
    // update the height if the height is not enough
    CGSize size = [self intrinsicContentSize];
    if (floor(self.frame.size.height) < floor(size.height)) {
        [self invalidateIntrinsicContentSize];
    }
}
@end
