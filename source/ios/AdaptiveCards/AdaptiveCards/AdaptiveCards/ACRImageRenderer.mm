//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "Image.h"
#import "ImageSet.h"
#import "Enums.h"
#import "SharedAdaptiveCard.h"
#import "ACRContentHoldingUIView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRUIImageView.h"

@implementation ACRImageRenderer

+ (ACRImageRenderer *)getInstance
{
    static ACRImageRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRImage;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);
    ACRUIImageView *view;
    CGSize cgsize = [acoConfig getImageSize:imgElem->GetImageSize()];
    view = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
    if(imgElem->GetImageSize() != ImageSize::Auto && imgElem->GetImageSize() != ImageSize::Stretch && imgElem->GetImageSize() != ImageSize::None){
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
    }
    NSMutableDictionary *imageViewMap = [rootView getImageMap];
    __block UIImage *img = nil;
    // Generate key for ImageViewMap
    NSString *key = [NSString stringWithCString:imgElem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
    // Syncronize access to imageViewMap
    dispatch_sync([rootView getSerialQueue], ^{
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
        if(imgElem->GetImageSize() == ImageSize::Auto || imgElem->GetImageSize() == ImageSize::Stretch || imgElem->GetImageSize() == ImageSize::None){
            CGFloat heightToWidthRatio = img.size.height / img.size.width;
            [view addConstraints:@[[NSLayoutConstraint constraintWithItem:view
                                                                    attribute:NSLayoutAttributeHeight
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:view
                                                                    attribute:NSLayoutAttributeWidth
                                                                   multiplier:heightToWidthRatio
                                                                     constant:0]]];
            CGFloat widthToHeightRatio = img.size.width/ img.size.height;
            [view addConstraints:@[[NSLayoutConstraint constraintWithItem:view
                                                                    attribute:NSLayoutAttributeWidth
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:view
                                                                    attribute:NSLayoutAttributeHeight
                                                                   multiplier:widthToHeightRatio
                                                                     constant:0]]];
        }
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

    [wrappingview addConstraints:[ACOHostConfig getConstraintsForImageAlignment:imgElem->GetHorizontalAlignment()
                                           withSuperview:wrappingview
                                                  toView:view]];
    // ImageSize::Auto should maintain its intrinsic size
    if(imgElem->GetImageSize() == ImageSize::Auto || imgElem->GetImageSize() == ImageSize::Stretch || imgElem->GetImageSize() == ImageSize::None){
        NSArray<NSString *> *visualFormats = [NSArray arrayWithObjects:@"H:[view(<=wrappingview)]", @"V:|-[view(<=wrappingview)]-|", nil];
        NSDictionary *viewMap = NSDictionaryOfVariableBindings(view, wrappingview);
        for(NSString *constraint in visualFormats){
            [NSLayoutConstraint activateConstraints:[NSLayoutConstraint constraintsWithVisualFormat:constraint options:0 metrics:nil views:viewMap]];
        }
    } else {
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    if(imgElem->GetImageSize() == ImageSize::Auto || imgElem->GetImageSize() == ImageSize::None){
        [view setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [wrappingview setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }
    std::shared_ptr<BaseActionElement> selectAction = imgElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    UILongPressGestureRecognizer * gestureRecognizer =
        [ACRLongPressGestureRecognizerFactory getLongPressGestureRecognizer:viewGroup
                                                                   rootView:rootView
                                                                 targetView:wrappingview
                                                              actionElement:selectAction
                                                                     inputs:inputs
                                                                 hostConfig:acoConfig];
    if(gestureRecognizer) {
        [view addGestureRecognizer:gestureRecognizer];
        view.userInteractionEnabled = YES;
    }
    view.translatesAutoresizingMaskIntoConstraints = NO;
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    return wrappingview;
}

@end
