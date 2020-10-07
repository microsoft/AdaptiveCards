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
    CGSize intrinsicContentSize = CGSizeZero;
    if (!hasExplicitMeasurements) {
        size = imgElem->GetImageSize();
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig] -> GetImage().imageSize;
        }

        if (size == ImageSize::Stretch) {
            intrinsicContentSize = [acoConfig getImageSize:ImageSize::Small];
        } else if (size != ImageSize::Auto) {
            intrinsicContentSize = [acoConfig getImageSize:imgElem->GetImageSize()];
        }

    } else {
        if (pixelWidth) {
            intrinsicContentSize.width = pixelWidth;
            if (isAspectRatioNeeded) {
                intrinsicContentSize.height = pixelWidth;
            }
        }
        if (pixelHeight) {
            intrinsicContentSize.height = pixelHeight;
            if (isAspectRatioNeeded) {
                intrinsicContentSize.width = pixelHeight;
            }
        }
    }

    ACRContentHoldingUIView *wrappingview = nil;
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
        
        if (view && imgElem->GetImageStyle() == ImageStyle::Person) {
            wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
            [wrappingview addSubview:view];
            wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
            [wrappingview.widthAnchor constraintEqualToAnchor:view.widthAnchor].active = YES;
            [wrappingview.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
            wrappingview.desiredContentSize = intrinsicContentSize;
            wrappingview.isPersonStyle = YES;
        }
    }
    
    // ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];

//    if (!view) {
//        [viewGroup addSubview:wrappingview];
//        return wrappingview;
//    }
    // wrappingview.desiredContentSize = intrinsicContentSize;

    view.clipsToBounds = YES;

    std::string backgroundColor = imgElem->GetBackgroundColor();
    if (!backgroundColor.empty()) {
        view.backgroundColor = [ACOHostConfig convertHexColorCodeToUIColor:imgElem->GetBackgroundColor()];
    }

    //[wrappingview addSubview:view];

    //[viewGroup addArrangedSubview:wrappingview];
    view.contentMode = UIViewContentModeScaleAspectFit;
    UIStackView *stackview = [[UIStackView alloc] init];
    stackview.axis = UILayoutConstraintAxisHorizontal;
    stackview.distribution = UIStackViewDistributionFill;
    stackview.alignment = UIStackViewAlignmentFill;
    
    view.contentMode = UIViewContentModeScaleAspectFit;
    UIView *spacer1 = nil, *spacer2 = nil;
    HorizontalAlignment adaptiveAlignment = imgElem->GetHorizontalAlignment();
    if (size != AdaptiveCards::ImageSize::Stretch) {
        
        if (adaptiveAlignment == HorizontalAlignment::Right || adaptiveAlignment == HorizontalAlignment::Center) {
            spacer1 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 1, 1)];
            NSLayoutConstraint *a = [spacer1.widthAnchor constraintEqualToConstant:1];
            a.priority = 300;
            a.active = YES;
            NSLayoutConstraint *b = [spacer1.heightAnchor constraintEqualToConstant:1];
            b.priority = 300;
            b.active = YES;
            spacer1.translatesAutoresizingMaskIntoConstraints = NO;
            
            [stackview addArrangedSubview:spacer1];
            if (wrappingview) {
                [stackview addArrangedSubview:wrappingview];
            } else {
                [stackview addArrangedSubview:view];
            }
            [spacer1.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
            [spacer1 setContentCompressionResistancePriority:200 forAxis:UILayoutConstraintAxisHorizontal];
            if (adaptiveAlignment == AdaptiveCards::HorizontalAlignment::Center) {
                [spacer1 setContentHuggingPriority:248 forAxis:UILayoutConstraintAxisHorizontal];
            } else {
                [spacer1 setContentHuggingPriority:252 forAxis:UILayoutConstraintAxisHorizontal];
            }
        }
        
        if (adaptiveAlignment == HorizontalAlignment::Left || adaptiveAlignment == HorizontalAlignment::Center) {
            if (adaptiveAlignment == HorizontalAlignment::Left) {
            if (wrappingview) {
                [stackview addArrangedSubview:wrappingview];
            } else {
                [stackview addArrangedSubview:view];
            }
            }
            spacer2 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 1, 1)];
            NSLayoutConstraint *a = [spacer2.widthAnchor constraintEqualToConstant:1];
            a.priority = 300;
            a.active = YES;
            NSLayoutConstraint *b = [spacer2.heightAnchor constraintEqualToConstant:1];
            b.priority = 250;
            b.active = YES;
            spacer2.translatesAutoresizingMaskIntoConstraints = NO;
            [stackview addArrangedSubview:spacer2];
            [spacer2.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
            [spacer2 setContentCompressionResistancePriority:200 forAxis:UILayoutConstraintAxisHorizontal];
            if (adaptiveAlignment == AdaptiveCards::HorizontalAlignment::Center) {
                [spacer2 setContentHuggingPriority:248 forAxis:UILayoutConstraintAxisHorizontal];
                [spacer1.widthAnchor constraintEqualToAnchor:spacer2.widthAnchor].active = YES;
            } else {
                [spacer2 setContentHuggingPriority:252 forAxis:UILayoutConstraintAxisHorizontal];
            }
            
        }
        
        [viewGroup addArrangedSubview:stackview];
    } else {
        /*
        HorizontalAlignment adaptiveAlignment = imgElem->GetHorizontalAlignment();
        if (adaptiveAlignment == HorizontalAlignment::Left) {
            view.contentMode = UIViewContentModeLeft | UIViewContentModeScaleAspectFit;
        } else if (adaptiveAlignment == HorizontalAlignment::Right) {
            view.contentMode = UIViewContentModeRight;
        } else {
            view.contentMode = UIViewContentModeScaleAspectFit;
        }
        */
                
        if (wrappingview) {
            [viewGroup addArrangedSubview:wrappingview];
        } else {
            [viewGroup addArrangedSubview:view];
        }
    }
    
    if (hasExplicitMeasurements) {
        view.contentMode = UIViewContentModeScaleToFill;
    }
    
    
    /*
    HorizontalAlignment adaptiveAlignment = imgElem->GetHorizontalAlignment();
    if (adaptiveAlignment == HorizontalAlignment::Left) {
        UILayoutGuide *leftGuide = [[UILayoutGuide alloc] init];
        leftGuide.identifier = @"img-left-guide";
        [wrappingview addLayoutGuide:leftGuide];
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

    [wrappingview.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;
    [wrappingview.widthAnchor constraintGreaterThanOrEqualToAnchor:view.widthAnchor].active = YES;

    [view.topAnchor constraintEqualToAnchor:wrappingview.topAnchor].active = YES;
    */

    if (size != ImageSize::Stretch) {
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        
        if (imgElem->GetHeight() == HeightType::Stretch) {
//            UIView *blankTrailingSpace = [[UIView alloc] init];
//            [viewGroup addArrangedSubview:blankTrailingSpace];
//            blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
//            [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
//            [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow - 10 forAxis:UILayoutConstraintAxisVertical];
//            [blankTrailingSpace.widthAnchor constraintEqualToAnchor:view.widthAnchor].active = YES;
//            NSLayoutConstraint *blankHeightConstraint = [blankTrailingSpace.heightAnchor constraintEqualToConstant:1.0f];
//            blankHeightConstraint.priority = 200;
//            blankHeightConstraint.active = YES;
            /*
            blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
            [wrappingview addSubview:blankTrailingSpace];
            [blankTrailingSpace.topAnchor constraintEqualToAnchor:view.bottomAnchor].active = YES;
            [blankTrailingSpace.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
            [blankTrailingSpace.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
            [blankTrailingSpace.bottomAnchor constraintEqualToAnchor:wrappingview.bottomAnchor].active = YES;
            [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
            */
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
    //wrappingview.translatesAutoresizingMaskIntoConstraints = NO;

    view.isAccessibilityElement = YES;

    //configVisibility(wrappingview, elem);
    configVisibility(view, elem);

    //if (imgElem->GetImageStyle() == ImageStyle::Person) {
    //    wrappingview.isPersonStyle = YES;
    //}
    //return wrappingview;
    
    return wrappingview ? wrappingview : view;
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
        constraints[0].priority = 240;
        constraints[1].priority = 240;

        [NSLayoutConstraint activateConstraints:constraints];
        UIView *superview = imageView.superview;
        if ([superview isKindOfClass:[ACRContentHoldingUIView class]]) {
            ((ACRContentHoldingUIView *)imageView.superview).desiredContentSize = cgsize;
            [imageView.superview invalidateIntrinsicContentSize];
        }
    }
    

    if (size == AdaptiveCards::ImageSize::Auto) {
        NSLayoutConstraint *imageHeightConstraint = [imageView.heightAnchor constraintLessThanOrEqualToConstant:image.size.height];
        imageHeightConstraint.active = YES;
        imageHeightConstraint.priority = 245;
        NSLayoutConstraint *imageWidthConstraint = [imageView.widthAnchor constraintLessThanOrEqualToConstant:image.size.width];
        imageWidthConstraint.active = YES;
        imageWidthConstraint.priority = 245;
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
        constraints[0].priority = 651;
        constraints[1].priority = 651;

        [NSLayoutConstraint activateConstraints:constraints];

        if ([imageView.superview class] == [ACRContentHoldingUIView class]) {
            ((ACRContentHoldingUIView *)imageView.superview).desiredContentSize = imageView.image.size;
        }
    }
}

@end
