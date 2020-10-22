//
//  ACRMediaRenderer
//  ACRMediaRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRMediaRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACOMediaEventPrivate.h"
#import "ACRAggregateTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRMediaTarget.h"
#import "ACRUIImageView.h"
#import "ACRView.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"
#import <AVKit/AVKit.h>
#import <CoreGraphics/CoreGraphics.h>

@implementation ACRMediaRenderer

+ (ACRMediaRenderer *)getInstance
{
    static ACRMediaRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRMedia;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Media> mediaElem = std::dynamic_pointer_cast<Media>(elem);

    NSMutableDictionary *imageViewMap = [rootView getImageMap];

    // makes parts for building a key to UIImage, there are different interfaces for loading the images
    // we list all the parts that are needed in building the key.
    NSString *urlString = [NSString stringWithCString:mediaElem->GetPoster().c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *numberString = [[NSNumber numberWithUnsignedLongLong:(unsigned long long)(elem.get())] stringValue];
    NSString *piikey = [NSString stringWithCString:[acoConfig getHostConfig] -> GetMedia().playButton.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *piikeyViewIF = [NSString stringWithFormat:@"%llu_playIcon", (unsigned long long)elem.get()];

    NSDictionary *pieces = @{
        @"number" : numberString,
        @"url" : urlString,
        @"playicon-url-imageView" : piikey,
        @"playicon-url-viewIF" : piikeyViewIF
    };

    NSString *mediaKey = makeKeyForImage(acoConfig, @"media-poster", pieces);
    UIImage *img = imageViewMap[mediaKey];
    UIImageView *view = nil;
    ACRContentHoldingUIView *contentholdingview = nil;

    // if poster is available, restrict the image size to the width of superview, and adjust the height accordingly
    if (img) {
        contentholdingview = (ACRContentHoldingUIView *)[rootView getImageView:mediaKey];
        if (contentholdingview) {
            view = contentholdingview.subviews[0];
        } else {
            view = [[UIImageView alloc] initWithImage:img];
            contentholdingview = [[ACRContentHoldingUIView alloc] init];
            [contentholdingview addSubview:view];
        }
        // if we already have UIImageView and UIImage, configures the constraints and turn off the notification
        [self configUpdateForUIImageView:acoElem config:acoConfig image:img imageView:view];
        [rootView removeObserverOnImageView:@"image" onObject:view keyToImageView:mediaKey];
    } else {
        contentholdingview = (ACRContentHoldingUIView *)[rootView getImageView:mediaKey];
        if (contentholdingview) {
            view = contentholdingview.subviews[0];
        }
    }

    if (!view) {
        // if poster is not availabl, create a 4:3 blank black backgroudn poster view; 16:9 won't provide enough height in case the media is 4:3
        view = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.width * .75)];
        view.backgroundColor = UIColor.blackColor;
        contentholdingview = [[ACRContentHoldingUIView alloc] init];
        [contentholdingview addSubview:view];
        [self configUpdateForUIImageView:acoElem config:acoConfig image:nil imageView:view];
    }

    view.translatesAutoresizingMaskIntoConstraints = NO;
    view.contentMode = UIViewContentModeScaleAspectFill;
    contentholdingview.isMediaType = YES;


    // process play icon image
    NSString *playIconKey = makeKeyForImage(acoConfig, @"media-playicon-image", pieces);
    UIImage *playIconImage = imageViewMap[playIconKey];
    UIImageView *playIconImageView = nil;
    BOOL hideDefaultPlayIcon = NO;

    playIconImageView = [rootView getImageView:playIconKey];

    if (playIconImage && !playIconImageView) {
        playIconImageView = [[UIImageView alloc] initWithImage:playIconImage];
    }

    if (playIconImageView) {
        hideDefaultPlayIcon = YES;
        playIconImageView.tag = playIconTag;
        playIconImageView.translatesAutoresizingMaskIntoConstraints = NO;
    }

    view.tag = posterTag;
    // if play icon is provided from hostconfig, disable play icon drawing in its sublayer, and invalidate the current sublayer, so it will be updated in the next drawring cycle
    if (hideDefaultPlayIcon) {
        [contentholdingview setNeedsLayout];
        [view addSubview:playIconImageView];
        [NSLayoutConstraint constraintWithItem:playIconImageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
        [NSLayoutConstraint constraintWithItem:playIconImageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
    }

    contentholdingview.hidePlayIcon = hideDefaultPlayIcon;

    [viewGroup addArrangedSubview:contentholdingview];

    if ([acoConfig getHostConfig] -> GetSupportsInteractivity()) {
        ACRMediaTarget *mediaTarget = nil;
        ACOMediaEvent *mediaEvent = [[ACOMediaEvent alloc] initWithMedia:mediaElem];
        if (!mediaEvent.isValid) {
            NSLog(@"warning: invalid mimetype detected, and media element is dropped");
            return nil;
        }
        // create target for gesture recongnizer;
        if (![acoConfig getHostConfig] -> GetMedia().allowInlinePlayback) {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig];
        } else {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig containingview:contentholdingview];
        }
        // config gesture recognizer and embed it to the poster.
        UILongPressGestureRecognizer *recognizer = [ACRLongPressGestureRecognizerFactory getGestureRecognizer:viewGroup target:mediaTarget];
        [view addGestureRecognizer:recognizer];
        view.userInteractionEnabled = YES;
    }

    configVisibility(contentholdingview, elem);

    return view;
}

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    ACRContentHoldingUIView *contentholdingview = (ACRContentHoldingUIView *)imageView.superview;
    CGFloat heightToWidthRatio = 0.0f;

    if (!image) {
        heightToWidthRatio = .75;
    } else {
        imageView.frame = CGRectMake(0, 0, image.size.width, image.size.height);
        if (image.size.width > 0) {
            heightToWidthRatio = image.size.height / image.size.width;
        }
    }

    contentholdingview.frame = imageView.frame;

    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:contentholdingview attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:contentholdingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

    [NSLayoutConstraint constraintWithItem:imageView
                                 attribute:NSLayoutAttributeWidth
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:contentholdingview
                                 attribute:NSLayoutAttributeWidth
                                multiplier:1.0
                                  constant:0]
        .active = YES;

    [NSLayoutConstraint constraintWithItem:contentholdingview
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:imageView
                                 attribute:NSLayoutAttributeHeight
                                multiplier:1.0
                                  constant:0]
        .active = YES;

    [NSLayoutConstraint constraintWithItem:imageView
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:imageView
                                 attribute:NSLayoutAttributeWidth
                                multiplier:heightToWidthRatio
                                  constant:0]
        .active = YES;
    [contentholdingview setNeedsLayout];
}

@end
