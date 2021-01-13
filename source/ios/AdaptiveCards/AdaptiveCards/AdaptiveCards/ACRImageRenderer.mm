//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnView.h"
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
    ACRUIImageView *view;
    NSInteger pixelWidth = imgElem->GetPixelWidth(), pixelHeight = imgElem->GetPixelHeight();
    BOOL hasExplicitMeasurements = (pixelWidth || pixelHeight);
    BOOL isAspectRatioNeeded = !(pixelWidth && pixelHeight);
    CGSize cgsize = [acoConfig getImageSize:imgElem->GetImageSize()];

    // makes parts for building a key to UIImage, there are different interfaces for loading the images
    // we list all the parts that are needed in building the key.
    NSString *number = [[NSNumber numberWithUnsignedLongLong:(unsigned long long)(elem.get())] stringValue];
    NSString *urlString = [NSString stringWithCString:imgElem->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    NSDictionary *pieces = @{
        @"number" : number,
        @"url" : urlString
    };

    NSString *key = makeKeyForImage(acoConfig, @"image", pieces);
    NSMutableDictionary *imageViewMap = [rootView getImageMap];
    UIImage *img = imageViewMap[key];

    // try get an UIImageView
    view = [rootView getImageView:key];
    CGSize intrinsicContentSize = CGSizeZero;
    if (!view && img) {
        // if an UIImage is available, but UIImageView is missing, create one
        ACRUIImageView *acrImageView = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
        acrImageView.image = img;
        if (imgElem->GetImageStyle() == ImageStyle::Person) {
            acrImageView.isPersonStyle = YES;
            [acrImageView setNeedsLayout];
        }
        view = acrImageView;
        intrinsicContentSize = img.size;
    }

    if (view && img) {
        // if we already have UIImageView and UIImage, configures the constraints and turn off the notification
        [rootView removeObserverOnImageView:@"image" onObject:view keyToImageView:key];
        [self configUpdateForUIImageView:acoElem config:acoConfig image:img imageView:view];
    }

    ImageSize size = ImageSize::None;
    if (!hasExplicitMeasurements) {
        size = imgElem->GetImageSize();
        view.adaptiveImageSize = getImageSize(size);
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig] -> GetImage().imageSize;
        }

        if (size == ImageSize::Stretch) {
            intrinsicContentSize = [acoConfig getImageSize:ImageSize::Small];
        } else if (size != ImageSize::Auto) {
            intrinsicContentSize = [acoConfig getImageSize:imgElem->GetImageSize()];
        }

    } else {
        view.adaptiveImageSize = ACRImageSizeExplicit;
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

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];

    if (!view) {
        [viewGroup addSubview:wrappingview];
        return wrappingview;
    }
    
    view.desiredSize = intrinsicContentSize;

    //view.clipsToBounds = YES;

    std::string backgroundColor = imgElem->GetBackgroundColor();
    if (!backgroundColor.empty()) {
        view.backgroundColor = [ACOHostConfig convertHexColorCodeToUIColor:imgElem->GetBackgroundColor()];
    }

    //[wrappingview addSubview:view];

    //[viewGroup addArrangedSubview:wrappingview];
    [viewGroup addArrangedSubview:view];

    /*
    HorizontalAlignment adaptiveAlignment = imgElem->GetHorizontalAlignment();
    if (adaptiveAlignment == HorizontalAlignment::Left || adaptiveAlignment == HorizontalAlignment::Center) {
        UILayoutGuide *leftGuide = [[UILayoutGuide alloc] init];
        leftGuide.identifier = @"img-left-guide";
        //[wrappingview addLayoutGuide:leftGuide];
        [viewGroup addLayoutGuide:leftGuide];
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
    }*/

//    if (adaptiveAlignment == HorizontalAlignment::Center) {
//        [view.centerXAnchor constraintEqualToAnchor:wrappingview.centerXAnchor].active = YES;
//    }

    //NSLayoutConstraint *heightAnchor = [wrappingview.heightAnchor constraintEqualToAnchor:view.heightAnchor];
    //heightAnchor.active = YES;
    /*
    if (size == ImageSize::Stretch) {
        [wrappingview.widthAnchor constraintEqualToAnchor:view.widthAnchor].active = YES;
    } else {
        [wrappingview.widthAnchor constraintGreaterThanOrEqualToAnchor:view.widthAnchor].active = YES;
    }*/

    //[view.topAnchor constraintEqualToAnchor:wrappingview.topAnchor].active = YES;

    //if (!isAspectRatioNeeded) {
        //view.contentMode = UIViewContentModeScaleToFill;
//    } else {
    view.contentMode = UIViewContentModeScaleAspectFit;
//    }

    UILayoutPriority imagePriority = [ACRImageRenderer getImageUILayoutPriority:view];
    if (size != ImageSize::Stretch) {
        [view setContentHuggingPriority:imagePriority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        [view setContentCompressionResistancePriority:imagePriority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:imagePriority forAxis:UILayoutConstraintAxisVertical];
        //heightAnchor.priority = imagePriority + 2;
        //[wrappingview setContentCompressionResistancePriority:760 forAxis:UILayoutConstraintAxisVertical];
        /*
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
         */
    }
    std::shared_ptr<BaseActionElement> selectAction = imgElem->GetSelectAction();
    ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];
    // instantiate and add tap gesture recognizer
    [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:viewGroup
                                                                       rootView:rootView
                                                                  recipientView:view
                                                                  actionElement:acoSelectAction
                                                                     hostConfig:acoConfig];
    view.translatesAutoresizingMaskIntoConstraints = NO;
    //wrappingview.translatesAutoresizingMaskIntoConstraints = NO;

    view.isAccessibilityElement = YES;
    NSString *stringForAccessiblilityLabel = [NSString stringWithCString:imgElem->GetAltText().c_str() encoding:NSUTF8StringEncoding];
    if (stringForAccessiblilityLabel.length) {
        view.accessibilityLabel = stringForAccessiblilityLabel;
    }

    //configVisibility(wrappingview, elem);

//    if (imgElem->GetImageStyle() == ImageStyle::Person) {
//        wrappingview.isPersonStyle = YES;
//    }
    //return wrappingview;
    return view;
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

    ((ACRUIImageView *)imageView).widthToHeightRatio = widthToHeightRatio;
    ((ACRUIImageView *)imageView).heightToWidthRatio = widthToHeightRatio;
    ImageSize size = ImageSize::None;
    if (!hasExplicitMeasurements) {
        size = imageElem->GetImageSize();
        if (size == ImageSize::None) {
            size = [acoConfig getHostConfig] -> GetImage().imageSize;
        }
    }
    
    if (size == ImageSize::Auto || size == ImageSize::Stretch) {
        cgsize = image.size;
    }

        //UILayoutPriority priority = [ACRImageRenderer getImageUILayoutPriority:imageView.superview];
        UILayoutPriority priority = [ACRImageRenderer getImageUILayoutPriority:imageView];
    NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc]init];
           [constraints addObjectsFromArray:

            @[
                [NSLayoutConstraint constraintWithItem:imageView
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
                                             constant:cgsize.height]
            ]];
        constraints[0].priority = priority;
        constraints[1].priority = priority;
    if (ImageSize::Auto == size) {
        [constraints addObjectsFromArray:@[
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeHeight
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:imageView
                                         attribute:NSLayoutAttributeWidth
                                        multiplier:cgsize.height / cgsize.width
                                          constant:0],
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeWidth
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:imageView
                                         attribute:NSLayoutAttributeHeight
                                        multiplier:cgsize.width / cgsize.height
                                          constant:0]]];
        if (ImageSize::Stretch == size){//} && priority == ACRColumnWidthPriorityStretch) {
            constraints[1].priority = priority + 1;
            constraints[2].priority = priority;
            constraints[3].priority = priority;
        } else {
            constraints[2].priority = priority + 2;
            constraints[3].priority = priority + 2;
        }
    }
        

        [NSLayoutConstraint activateConstraints:constraints];
//        UIView *superview = imageView.superview;
//        if ([superview isKindOfClass:[ACRContentHoldingUIView class]]) {
//            ((ACRContentHoldingUIView *)imageView.superview).desiredContentSize = cgsize;
//            [imageView.superview invalidateIntrinsicContentSize];
//        }    
}

+ (UILayoutPriority)getImageUILayoutPriority:(UIView *)wrappingview
{
    UILayoutPriority priority = [wrappingview contentHuggingPriorityForAxis:UILayoutConstraintAxisHorizontal];
    return (!wrappingview || priority > ACRColumnWidthPriorityStretch) ? UILayoutPriorityDefaultHigh  : priority;
}

@end
