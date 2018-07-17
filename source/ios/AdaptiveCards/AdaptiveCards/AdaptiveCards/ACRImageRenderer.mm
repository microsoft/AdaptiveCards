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
    NSInteger pixelWidth = imgElem->GetPixelWidth(), pixelHeight = imgElem->GetPixelHeight();
    BOOL hasExplicitMeasurements = (pixelWidth || pixelHeight);
    BOOL isAspectRatioNeeded = !(pixelWidth && pixelHeight);
    CGSize cgsize = [acoConfig getImageSize:imgElem->GetImageSize()];

    NSMutableDictionary *imageViewMap = [rootView getImageMap];
    // Syncronize access to imageViewMap
    NSString *key = [NSString stringWithCString:imgElem->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    UIImage *img = imageViewMap[key];

    CGFloat heightToWidthRatio = 0.0f, widthToHeightRatio = 0.0f;
    if(img){
        if(img.size.width > 0) {
            heightToWidthRatio = img.size.height / img.size.width;
        }

        if(img.size.height > 0) {
            widthToHeightRatio =img.size.width / img.size.height;
        }
    }

    if(hasExplicitMeasurements) {
        if(pixelWidth){
            cgsize.width = pixelWidth;
            if(isAspectRatioNeeded) {
                cgsize.height = pixelWidth * heightToWidthRatio;
            }
        }
        if(pixelHeight){
            cgsize.height = pixelHeight;
            if(isAspectRatioNeeded) {
                cgsize.width = pixelHeight * widthToHeightRatio;
            }
        }
    }
    view = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
    view.image = img;

    ImageSize size = ImageSize::None;
    if (!hasExplicitMeasurements){
        size = imgElem->GetImageSize();
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig]->image.imageSize;
        }
    }

    if(size != ImageSize::Auto && size != ImageSize::Stretch){
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

    if(heightToWidthRatio && widthToHeightRatio && (size == ImageSize::Auto || size == ImageSize::Stretch)){
        [view addConstraints:@[[NSLayoutConstraint constraintWithItem:view
                                                                attribute:NSLayoutAttributeHeight
                                                                relatedBy:NSLayoutRelationEqual
                                                                   toItem:view
                                                                attribute:NSLayoutAttributeWidth
                                                               multiplier:heightToWidthRatio
                                                                 constant:0]]];
        [view addConstraints:@[[NSLayoutConstraint constraintWithItem:view
                                                                attribute:NSLayoutAttributeWidth
                                                                relatedBy:NSLayoutRelationEqual
                                                                   toItem:view
                                                                attribute:NSLayoutAttributeHeight
                                                               multiplier:widthToHeightRatio
                                                                 constant:0]]];
    }

    if(!isAspectRatioNeeded){
        view.contentMode = UIViewContentModeScaleToFill;
    } else {
        view.contentMode = UIViewContentModeScaleAspectFit;
    }
    view.clipsToBounds = NO;
    if(imgElem->GetImageStyle() == ImageStyle::Person) {
        CALayer *imgLayer = view.layer;
        [imgLayer setCornerRadius:cgsize.width/2];
        [imgLayer setMasksToBounds:YES];
    }

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
    [wrappingview addSubview:view];

    [viewGroup addArrangedSubview:wrappingview];

    [wrappingview addConstraints:[ACOHostConfig getConstraintsForImageAlignment:imgElem->GetHorizontalAlignment()
                                           withSuperview:wrappingview
                                                  toView:view]];
    // ImageSize::Auto should maintain its intrinsic size
    if(size == ImageSize::Auto || size == ImageSize::Stretch) {
        NSArray<NSString *> *visualFormats = [NSArray arrayWithObjects:@"H:[view(<=wrappingview)]", @"V:|-[view(<=wrappingview)]-|", nil];
        NSDictionary *viewMap = NSDictionaryOfVariableBindings(view, wrappingview);
        for(NSString *constraint in visualFormats){
            [NSLayoutConstraint activateConstraints:[NSLayoutConstraint constraintsWithVisualFormat:constraint options:0 metrics:nil views:viewMap]];
        }
    } else {
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    if(size == ImageSize::Auto) {
        [view setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [wrappingview setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

        if(imgElem->GetHeight() == HeightType::Stretch) {
            UIView *blankTrailingSpace = [[UIView alloc] init];
            [blankTrailingSpace setContentHuggingPriority:(UILayoutPriorityDefaultLow) forAxis:UILayoutConstraintAxisVertical];
            [viewGroup addArrangedSubview:blankTrailingSpace];
        }
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
