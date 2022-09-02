//
//  ACRImageSetRenderer
//  ACRImageSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRImageSetRenderer.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRImageSetUICollectionView.h>
#import <AdaptiveCards/ImageSet.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <AdaptiveCards/UtiliOS.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACRImageSetRenderer

+ (ACRImageSetRenderer *)getInstance
{
    static ACRImageSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRImageSet;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ImageSet> imgSetElem = std::dynamic_pointer_cast<ImageSet>(elem);
    ACRImageSetUICollectionView *view = [[ACRImageSetUICollectionView alloc] init:imgSetElem
                                                                   WithHostConfig:acoConfig
                                                                    WithSuperview:viewGroup
                                                                         rootView:rootView];
    [view registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"cellId"];

    [viewGroup addArrangedSubview:view];

    configRtl(view, rootView.context);

    return view;
}

@end
