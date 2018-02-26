//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "Image.h"
#import "Enums.h"
#import "SharedAdaptiveCard.h"
#import "ACRContentHoldingUIView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRViewController.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRImageRenderer

+ (ACRImageRenderer *)getInstance
{
    static ACRImageRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::Image;
}

+ (CGSize)getImageSize:(ImageSize)imageSize
        withHostConfig:(std::shared_ptr<HostConfig> const &)hostConfig
{
    float sz = hostConfig->imageSizes.smallSize;
    switch (imageSize)
    {
        case ImageSize::Large:{
            sz = hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:{
            sz = hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:{
            sz = hostConfig->imageSizes.smallSize;
            break;
        }

        default:{
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}
// code clean-up in progress
- (NSArray *)setImageAlignment:(HorizontalAlignment)alignment
                 withSuperview:(UIView *)superview
                        toView:(UIView *)view
{
    NSMutableArray *constraints = [[NSMutableArray alloc] init];
    [constraints addObject:
        [NSLayoutConstraint constraintWithItem:superview
                                     attribute:NSLayoutAttributeCenterY
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:view
                                     attribute:NSLayoutAttributeCenterY
                                    multiplier:1
                                      constant:0]];

    switch (alignment)
    {
        case HorizontalAlignment::Center:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeCenterX
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeCenterX
                                            multiplier:1
                                              constant:0]];
                return constraints;
        }
        case HorizontalAlignment::Left:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        case HorizontalAlignment::Right:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeTrailing
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeTrailing
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        default:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
    }
    return constraints;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);

    CGSize cgsize = [ACRImageRenderer getImageSize:imgElem->GetImageSize() withHostConfig:config];
    UIImageView *view = [[UIImageView alloc]
                         initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];

    // Add width/height constraints so image is resized accordingly
    [view addConstraints:@[[NSLayoutConstraint constraintWithItem:view
                                                        attribute:NSLayoutAttributeWidth
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:nil
                                                        attribute:NSLayoutAttributeNotAnAttribute
                                                       multiplier:1.0
                                                         constant:cgsize.width],
                           [NSLayoutConstraint constraintWithItem:view
                                                        attribute:NSLayoutAttributeHeight
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:nil
                                                        attribute:NSLayoutAttributeNotAnAttribute
                                                       multiplier:1.0
                                                         constant:cgsize.height]]];
    NSMutableDictionary *imageViewMap = [(ACRViewController *)vc getImageMap];
    __block UIImage *img = nil;
    // Generate key for ImageViewMap
    NSString *key = [NSString stringWithCString:imgElem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
    // Syncronize access to imageViewMap
    dispatch_sync([(ACRViewController *)vc getSerialQueue], ^{
        // if image is available, get it, otherwise cache UIImageView, so it can be used once images are ready
        if(imageViewMap[key] && [imageViewMap[key] isKindOfClass:[UIImage class]]) {
            img = imageViewMap[key];
        }
        else {
            imageViewMap[key] = view;
        }
    });

    if(img) {// if image is ready, proceed to add it
        view.image = img;
        view.contentMode = UIViewContentModeScaleAspectFit;
        view.clipsToBounds = NO;
        if(imgElem->GetImageStyle() == ImageStyle::Person) {
            CALayer *imgLayer = view.layer;
            [imgLayer setCornerRadius:cgsize.width/2];
            [imgLayer setMasksToBounds:YES];
        }
        // remove postfix added for imageMap access
        std::string id = imgElem->GetId();
        std::size_t idx = id.find_last_of('_');
        imgElem->SetId(id.substr(0, idx));
    }

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
    [wrappingview addSubview:view];

    [viewGroup addArrangedSubview:wrappingview];

    [wrappingview addConstraints:[self setImageAlignment:imgElem->GetHorizontalAlignment()
                                           withSuperview:wrappingview
                                                  toView:view]];

    [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    std::shared_ptr<BaseActionElement> selectAction = imgElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    UILongPressGestureRecognizer * gestureRecognizer =
        [ACRLongPressGestureRecognizerFactory getLongPressGestureRecognizer:viewGroup
                                                         rootViewController:vc
                                                                 targetView:wrappingview
                                                              actionElement:selectAction
                                                                     inputs:inputs
                                                                 hostConfig:config];
    if(gestureRecognizer) {
        [view addGestureRecognizer:gestureRecognizer];
        view.userInteractionEnabled = YES;
    }
    view.translatesAutoresizingMaskIntoConstraints = NO;
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    return wrappingview;
}

@end
