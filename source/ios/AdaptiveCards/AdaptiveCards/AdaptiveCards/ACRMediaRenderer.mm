//
//  ACRMediaRenderer
//  ACRMediaRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <AVKit/AVKit.h>
#import "ACRMediaRenderer.h"
#import "ACOMediaEventPrivate.h"
#import "ACRMediaTarget.h"
#import "SharedAdaptiveCard.h"
#import "ACRAggregateTarget.h"
#import "ACRView.h"
#import "ACRUIImageView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRContentHoldingUIView.h"
#import "ACRAVPlayerViewHoldingUIView.h"

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
    NSString *key = [NSString stringWithCString:mediaElem->GetPoster().c_str() encoding:[NSString defaultCStringEncoding]];
    UIImage *img = imageViewMap[key];
    ACRAVPlayerViewHoldingUIView *view = nil;
    CGFloat heightToWidthRatio = 0.0f;
    // if poster is available, restrict the image size to the width of superview, and adjust the height accordingly
    if(img) {
        view = [[ACRAVPlayerViewHoldingUIView alloc] initWithImage:img];
        view.translatesAutoresizingMaskIntoConstraints = NO;
        view.contentMode = UIViewContentModeScaleAspectFill;

        if(img.size.width > 0) {
            heightToWidthRatio = img.size.height / img.size.width;
        }
    } else { // if poster is not availabl, create a 4:3 blank black backgroudn poster view; 16:9 won't provide enough height in case the media is 4:3
        heightToWidthRatio = .75;
        view = [[ACRAVPlayerViewHoldingUIView alloc] init];
        view.backgroundColor = UIColor.blackColor;
        view.translatesAutoresizingMaskIntoConstraints = NO;
    }
    // process play icon image
    NSString *piikey = [NSString stringWithCString:[acoConfig getHostConfig]->media.playButton.c_str() encoding:[NSString defaultCStringEncoding]];
    UIImage *playIconImage = imageViewMap[piikey];
    UIImageView *playIconImageView = nil;
    BOOL drawDefaultPlayIcon = YES;

    if(playIconImage) {
        drawDefaultPlayIcon = NO;
        playIconImageView = [[UIImageView alloc] initWithImage:playIconImage];
        playIconImageView.tag = playIconTag;
        playIconImageView.translatesAutoresizingMaskIntoConstraints = NO;
    }

    view.frame = CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.width * heightToWidthRatio);
    view.tag = posterTag;
    ACRContentHoldingUIView *contentholdingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
    // if play icon is provided from hostconfig, disable play icon drawing in its sublayer, and invalidate the current sublayer, so it will be updated in the next drawring cycle
    if(!drawDefaultPlayIcon) {
        view.hidePlayIcon = YES;
        [view setNeedsLayout];
        [view addSubview:playIconImageView];
        [NSLayoutConstraint constraintWithItem:playIconImageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
        [NSLayoutConstraint constraintWithItem:playIconImageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

    }
    [contentholdingview addSubview:view];
    [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:contentholdingview attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:contentholdingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
    [viewGroup addArrangedSubview:contentholdingview];

    [NSLayoutConstraint constraintWithItem:contentholdingview attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:viewGroup attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:contentholdingview
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:contentholdingview
                                 attribute:NSLayoutAttributeWidth
                                multiplier:heightToWidthRatio
                                  constant:0].active = YES;

    [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:contentholdingview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:view
                                 attribute:NSLayoutAttributeWidth
                                multiplier:heightToWidthRatio
                                  constant:0].active = YES;

    if([acoConfig getHostConfig]->supportsInteractivity){
        ACRMediaTarget *mediaTarget = nil;
        ACOMediaEvent *mediaEvent = [[ACOMediaEvent alloc] initWithMedia:mediaElem];
        if(!mediaEvent.isValid) {
            NSLog(@"warning: invalid mimetype detected, and media element is dropped");
            return nil;
        }
        // create target for gesture recongnizer;
        if(![acoConfig getHostConfig]->media.allowInlinePlayback) {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig];
        } else {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig containingview:contentholdingview];
        }
        // config gesture recognizer and embed it to the poster.
        UILongPressGestureRecognizer *recognizer = [ACRLongPressGestureRecognizerFactory getGestureRecognizer:viewGroup target:mediaTarget];
        [view addGestureRecognizer:recognizer];
        view.userInteractionEnabled = YES;
    }

    return view;
}

@end
