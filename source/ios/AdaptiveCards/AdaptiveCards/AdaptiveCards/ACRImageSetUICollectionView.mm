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
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACRImageSetUICollectionView {
    ACOBaseCardElement *_acoElem;
    ACOHostConfig *_acoConfig;
    std::shared_ptr<ImageSet> _imgSet;
    ImageSize _imageSize;
    ACRView *_rootView;
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
        ((UICollectionViewFlowLayout *)self.collectionViewLayout).itemSize = [_acoConfig getImageSize:_imageSize];
        self.scrollEnabled = NO;
        self.translatesAutoresizingMaskIntoConstraints = NO;
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

    UIView *content = [imageRenderer render:nil rootView:_rootView inputs:nil baseCardElement:_acoElem hostConfig:_acoConfig];

    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];

    if (!cell) {
        cell = [[UICollectionViewCell alloc] initWithFrame:content.frame];
    } else {
        cell.contentView.frame = content.frame;
    }

    [cell.contentView addSubview:content];

    [NSLayoutConstraint constraintWithItem:cell.contentView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:content attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;

    [NSLayoutConstraint constraintWithItem:cell.contentView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:content attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

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
    size_t cellCounts = _imgSet->GetImages().size();
    CGSize imageSize = ((UICollectionViewFlowLayout *)self.collectionViewLayout).itemSize;
    float spacing = ((UICollectionViewFlowLayout *)self.collectionViewLayout).minimumInteritemSpacing;
    float lineSpacing = ((UICollectionViewFlowLayout *)self.collectionViewLayout).minimumLineSpacing;

    // sanity check
    if (!imageSize.width || !self.frame.size.width || !cellCounts) {
        return CGSizeMake(0, 0);
    }
    float frameWidth = self.frame.size.width;
    float imageWidthWithSpacing = imageSize.width + spacing;

    // if there is spacing to the right edge, it's o.k.
    int numbersOfItemsInRow = frameWidth / imageWidthWithSpacing;
    // if addtional image can be fit by removing spacing, do so
    if (numbersOfItemsInRow * imageWidthWithSpacing + imageSize.width <= frameWidth) {
        numbersOfItemsInRow++;
    }

    int numbersOfRows = ceil(((float)cellCounts) / numbersOfItemsInRow);
    return CGSizeMake(self.frame.size.width, (numbersOfRows) * (imageSize.height) + (numbersOfRows - 1) * lineSpacing);
}
@end
