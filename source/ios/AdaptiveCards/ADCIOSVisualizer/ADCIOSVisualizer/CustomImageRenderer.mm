//
//  CustomImageRenderer
//  CustomImageRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "CustomImageRenderer.h"
#import <AdaptiveCards/ACFramework.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <AdaptiveCards/TextBlock.h>
#import <AdaptiveCards/ACRTextBlockRenderer.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACRContentHoldingUIView.h>
#import <AdaptiveCards/MarkDownParser.h>
#import <AdaptiveCards/HostConfig.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRUIImageView.h>
#import <AdaptiveCards/Image.h>
#import <AdaptiveCards/ACRLongPressGestureRecognizerFactory.h>
#import <AdaptiveCards/UtiliOS.h>

@implementation CustomImageRenderer

+ (CustomImageRenderer *)getInstance
{
    static CustomImageRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
            inputs:(NSArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);
    ACRUIImageView *view;
    NSInteger pixelWidth = imgElem->GetPixelWidth(), pixelHeight = imgElem->GetPixelHeight();
    BOOL hasExplicitMeasurements = (pixelWidth || pixelHeight);
    BOOL isAspectRatioNeeded = !(pixelWidth && pixelHeight);
    CGSize cgsize = [acoConfig getImageSize:imgElem->GetImageSize()];

    NSString *urlStr = [NSString stringWithCString:imgElem->GetUrl().c_str()
                                          encoding:[NSString defaultCStringEncoding]];
    NSURL *nsurl = [NSURL URLWithString:urlStr];
    // download image
    UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:nsurl]];

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
            size = [acoConfig getHostConfig]->GetImage().imageSize;
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
    [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:viewGroup
                                                                       rootView:rootView
                                                                  recipientView:view
                                                                  actionElement:selectAction
                                                                     hostConfig:acoConfig];
    view.translatesAutoresizingMaskIntoConstraints = NO;
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    configVisibility(wrappingview, elem);

    return wrappingview;
}

@end
