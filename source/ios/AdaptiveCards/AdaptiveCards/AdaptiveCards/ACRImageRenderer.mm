//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRUIImageView.h"
#import "ACRView.h"
#import "Enums.h"
#import "Image.h"
#import "ImageSet.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

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
    UIImageView *view;
    NSInteger pixelWidth = imgElem->GetPixelWidth(), pixelHeight = imgElem->GetPixelHeight();
    BOOL hasExplicitMeasurements = (pixelWidth || pixelHeight);
    BOOL isAspectRatioNeeded = !(pixelWidth && pixelHeight);
    CGSize cgsize = [acoConfig getImageSize:imgElem->GetImageSize()];

    NSString *key = [NSString stringWithCString:imgElem->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    NSMutableDictionary *imageViewMap = [rootView getImageMap];
    NSURL *url = [NSURL URLWithString:key];

    if (ACOImageViewIF == [acoConfig getResolverIFType:[url scheme]]) {
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)(elem.get())];
        key = [number stringValue];
    }

    UIImage *img = imageViewMap[key];
    ImageSize size = ImageSize::None;
    if (!hasExplicitMeasurements) {
        size = imgElem->GetImageSize();
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig] -> GetImage().imageSize;
        }
    }

    if (img) {
        ACRUIImageView *acrImageView = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
        acrImageView.image = img;
        if (imgElem->GetImageStyle() == ImageStyle::Person) {
            acrImageView.isPersonStyle = YES;
            [acrImageView setNeedsLayout];
        }
        view = acrImageView;
        [self configUpdateForUIImageView:acoElem config:acoConfig image:img imageView:view];
    } else {
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)imgElem.get()];
        NSString *key = [number stringValue];
        view = [rootView getImageView:key];
    }

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];

    if (!view) {
        return wrappingview;
    }

    view.clipsToBounds = YES;

    std::string backgroundColor = imgElem->GetBackgroundColor();
    if (!backgroundColor.empty()) {
        view.backgroundColor = [ACOHostConfig convertHexColorCodeToUIColor:imgElem->GetBackgroundColor()];
    }

    [wrappingview addSubview:view];

    [viewGroup addArrangedSubview:wrappingview];

    HorizontalAlignment adaptiveAlignment = imgElem->GetHorizontalAlignment();
    if (adaptiveAlignment == HorizontalAlignment::Left) {
        UILayoutGuide *leftGuide = [[UILayoutGuide alloc] init];
        leftGuide.identifier = @"img-left-guide";
        [wrappingview addLayoutGuide:leftGuide];
        [leftGuide.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor].active = YES;
        [leftGuide.trailingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
        [leftGuide.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
        [view.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor].active = YES;
    }

    if (adaptiveAlignment == HorizontalAlignment::Right) {
        UILayoutGuide *rightGuide = [[UILayoutGuide alloc] init];
        rightGuide.identifier = @"img-right-guide";
        [wrappingview addLayoutGuide:rightGuide];
        NSLayoutConstraint *constraint = [rightGuide.leadingAnchor constraintEqualToAnchor:view.trailingAnchor];
        constraint.priority = 998;
        constraint.active = YES;
        [rightGuide.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
        [rightGuide.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor].active = YES;
        [view.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor].active = YES;
    }

    if (adaptiveAlignment == HorizontalAlignment::Center) {
        [view.centerXAnchor constraintEqualToAnchor:wrappingview.centerXAnchor].active = YES;
    }

    [wrappingview.heightAnchor constraintGreaterThanOrEqualToAnchor:view.heightAnchor].active = YES;
    [wrappingview.widthAnchor constraintGreaterThanOrEqualToAnchor:view.widthAnchor].active = YES;

    [view.topAnchor constraintEqualToAnchor:wrappingview.topAnchor].active = YES;

    if (!isAspectRatioNeeded) {
        view.contentMode = UIViewContentModeScaleToFill;
    } else {
        view.contentMode = UIViewContentModeScaleAspectFit;
    }

    if (size != ImageSize::Stretch) {
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        if (imgElem->GetHeight() == HeightType::Stretch) {
            UIView *blankTrailingSpace = [[UIView alloc] init];
            blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
            [wrappingview addSubview:blankTrailingSpace];
            [blankTrailingSpace.topAnchor constraintEqualToAnchor:view.bottomAnchor].active = YES;
            [blankTrailingSpace.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
            [blankTrailingSpace.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
            [blankTrailingSpace.bottomAnchor constraintEqualToAnchor:wrappingview.bottomAnchor].active = YES;
            [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
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

    if (imgElem->GetImageStyle() == ImageStyle::Person) {
        wrappingview.isPersonStyle = YES;
    }
    return wrappingview;
}

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Image> imageElem = std::dynamic_pointer_cast<Image>(elem);
    NSInteger pixelWidth = imageElem->GetPixelWidth(), pixelHeight = imageElem->GetPixelHeight();
    BOOL hasExplicitMeasurements = (pixelWidth || pixelHeight);
    BOOL isAspectRatioNeeded = !(pixelWidth && pixelHeight);
    CGSize cgsize = [acoConfig getImageSize:imageElem->GetImageSize()];
    CGFloat heightToWidthRatio = 0.0f, widthToHeightRatio = 0.0f;

    if (image) {
        if (image.size.width > 0) {
            heightToWidthRatio = image.size.height / image.size.width;
        }

        if (image.size.height > 0) {
            widthToHeightRatio = image.size.width / image.size.height;
        }
    }

    if (hasExplicitMeasurements) {
        if (pixelWidth) {
            cgsize.width = pixelWidth;
            if (isAspectRatioNeeded) {
                cgsize.height = pixelWidth * heightToWidthRatio;
            }
        }
        if (pixelHeight) {
            cgsize.height = pixelHeight;
            if (isAspectRatioNeeded) {
                cgsize.width = pixelHeight * widthToHeightRatio;
            }
        }
    }

    ImageSize size = ImageSize::None;
    if (!hasExplicitMeasurements) {
        size = imageElem->GetImageSize();
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig] -> GetImage().imageSize;
        }
    }

    if (size != ImageSize::Auto && size != ImageSize::Stretch) {
        NSArray<NSLayoutConstraint *> *constraints =
            @[ [NSLayoutConstraint constraintWithItem:imageView
                                            attribute:NSLayoutAttributeWidth
                                            relatedBy:NSLayoutRelationEqual
                                               toItem:nil
                                            attribute:NSLayoutAttributeNotAnAttribute
                                           multiplier:1.0
                                             constant:cgsize.width],
               [NSLayoutConstraint constraintWithItem:imageView
                                            attribute:NSLayoutAttributeHeight
                                            relatedBy:NSLayoutRelationEqual
                                               toItem:nil
                                            attribute:NSLayoutAttributeNotAnAttribute
                                           multiplier:1.0
                                             constant:cgsize.height] ];
        constraints[0].priority = 1000;
        constraints[1].priority = 1000;

        [NSLayoutConstraint activateConstraints:constraints];

        if ([imageView class] == [ACRUIImageView class]) {
            ((ACRUIImageView *)imageView).desiredSize = cgsize;
        }
    }

    if (heightToWidthRatio && widthToHeightRatio && (size == ImageSize::Auto || size == ImageSize::Stretch)) {
        NSArray<NSLayoutConstraint *> *constraints =
            @[ [NSLayoutConstraint constraintWithItem:imageView
                                            attribute:NSLayoutAttributeHeight
                                            relatedBy:NSLayoutRelationEqual
                                               toItem:imageView
                                            attribute:NSLayoutAttributeWidth
                                           multiplier:heightToWidthRatio
                                             constant:0],
               [NSLayoutConstraint constraintWithItem:imageView
                                            attribute:NSLayoutAttributeWidth
                                            relatedBy:NSLayoutRelationEqual
                                               toItem:imageView
                                            attribute:NSLayoutAttributeHeight
                                           multiplier:widthToHeightRatio
                                             constant:0] ];
        constraints[0].priority = 999;
        constraints[1].priority = 1000;

        [NSLayoutConstraint activateConstraints:constraints];

        if ([imageView class] == [ACRUIImageView class]) {
            ((ACRUIImageView *)imageView).desiredSize = cgsize;
        }
    }
}

@end
