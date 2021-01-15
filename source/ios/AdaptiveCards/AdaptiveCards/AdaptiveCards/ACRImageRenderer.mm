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
#import "ACRImageProperties.h"
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

    ACRImageProperties *imageProps = [[ACRImageProperties alloc] init:acoElem config:acoConfig];
    // try get an UIImageView
    UIImageView *view = [rootView getImageView:key];
    if (!view && img) {
        CGSize cgsize = imageProps.contentSize;
        // if an UIImage is available, but UIImageView is missing, create one
        ACRUIImageView *acrImageView = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
        acrImageView.image = img;
        if (imgElem->GetImageStyle() == ImageStyle::Person) {
            acrImageView.isPersonStyle = YES;
            [acrImageView setNeedsLayout];
        }
        view = acrImageView;
    }

    if (view && img) {
        // if we already have UIImageView and UIImage, configures the constraints and turn off the notification
        [rootView removeObserverOnImageView:@"image" onObject:view keyToImageView:key];
        [self configUpdateForUIImageView:acoElem config:acoConfig image:img imageView:view];
    }

    ACRContentHoldingUIView *wrappingView = [[ACRContentHoldingUIView alloc] initWithImageProperties:imageProps imageView:view];

    if (!view || !wrappingView) {
        [viewGroup addSubview:wrappingView];
        return wrappingView;
    }

    view.clipsToBounds = YES;

    std::string backgroundColor = imgElem->GetBackgroundColor();
    if (!backgroundColor.empty()) {
        view.backgroundColor = [ACOHostConfig convertHexColorCodeToUIColor:imgElem->GetBackgroundColor()];
    }

    [wrappingView addSubview:view];

    [viewGroup addArrangedSubview:wrappingView];

    switch (imageProps.acrHorizontalAlignment) {
        case ACRCenter:
            [view.centerXAnchor constraintEqualToAnchor:wrappingView.centerXAnchor].active = YES;
            break;
        case ACRRight:
            [view.trailingAnchor constraintEqualToAnchor:wrappingView.trailingAnchor].active = YES;
            break;
        case ACRLeft:
        default:
            break;
    }

    [wrappingView.heightAnchor constraintEqualToAnchor:view.heightAnchor].active = YES;

    if (imageProps.acrImageSize == ACRImageSizeStretch) {
        [wrappingView.widthAnchor constraintEqualToAnchor:view.widthAnchor].active = YES;
    } else {
        [wrappingView.widthAnchor constraintGreaterThanOrEqualToAnchor:view.widthAnchor].active = YES;
    }

    [view.topAnchor constraintEqualToAnchor:wrappingView.topAnchor].active = YES;
 
    if (!imageProps.isAspectRatioNeeded) {
        view.contentMode = UIViewContentModeScaleToFill;
    } else {
        view.contentMode = UIViewContentModeScaleAspectFit;
    }

    UILayoutPriority imagePriority = [ACRImageRenderer getImageUILayoutPriority:wrappingView];
    if (imageProps.acrImageSize != ACRImageSizeStretch) {
        [view setContentHuggingPriority:imagePriority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        [view setContentCompressionResistancePriority:imagePriority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:imagePriority forAxis:UILayoutConstraintAxisVertical];
        
        if (imgElem->GetHeight() == HeightType::Stretch) {
            [(ACRColumnView *)viewGroup addPaddingSpace];
//            UIView *blankTrailingSpace = [[UIView alloc] init];
//            blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
//            [wrappingView addSubview:blankTrailingSpace];
//            [blankTrailingSpace.topAnchor constraintEqualToAnchor:view.bottomAnchor].active = YES;
//            [blankTrailingSpace.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
//            [blankTrailingSpace.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
//            [blankTrailingSpace.bottomAnchor constraintEqualToAnchor:wrappingView.bottomAnchor].active = YES;
//            [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
        }
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
    wrappingView.translatesAutoresizingMaskIntoConstraints = NO;

    view.isAccessibilityElement = YES;
    NSString *stringForAccessiblilityLabel = [NSString stringWithCString:imgElem->GetAltText().c_str() encoding:NSUTF8StringEncoding];
    if (stringForAccessiblilityLabel.length) {
        view.accessibilityLabel = stringForAccessiblilityLabel;
    }

    configVisibility(wrappingView, elem);

    if (imgElem->GetImageStyle() == ImageStyle::Person) {
        wrappingView.isPersonStyle = YES;
    }
    return wrappingView;
}

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    ACRImageProperties *imageProps = [[ACRImageProperties alloc] init:acoElem config:acoConfig];
    [imageProps updateContentSize:image.size];
    CGSize cgsize = imageProps.contentSize;

    UILayoutPriority priority = [ACRImageRenderer getImageUILayoutPriority:imageView.superview];
    NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
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
    if (imageProps.acrImageSize == ACRImageSizeAuto) {
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
                                          constant:0]
        ]];
        if (imageProps.acrImageSize == ACRImageSizeStretch) {
            constraints[1].priority = priority + 1;
            constraints[2].priority = priority;
            constraints[3].priority = priority;
        } else {
            constraints[2].priority = priority + 2;
            constraints[3].priority = priority + 2;
        }
    }
    [NSLayoutConstraint activateConstraints:constraints];

    if ([imageView.superview isKindOfClass:[ACRContentHoldingUIView class]]) {
        ACRContentHoldingUIView *superview = (ACRContentHoldingUIView *)imageView.superview;
        imageProps.contentSize = cgsize;
        [superview update:imageProps];
    }
}

+ (UILayoutPriority)getImageUILayoutPriority:(UIView *)wrappingView
{
    UILayoutPriority priority = [wrappingView contentHuggingPriorityForAxis:UILayoutConstraintAxisHorizontal];
    return (!wrappingView || priority > ACRColumnWidthPriorityStretch) ? UILayoutPriorityDefaultHigh : priority;
}

@end
