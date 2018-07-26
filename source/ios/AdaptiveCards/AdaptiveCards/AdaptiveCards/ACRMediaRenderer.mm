//
//  ACRMediaRenderer
//  ACRMediaRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import "ACRMediaRenderer.h"
#import "ACOMediaEventPrivate.h"
#import "ACRMediaTarget.h"
#import "Enums.h"
#import "SharedAdaptiveCard.h"
#import "ACRAVPlayerViewHoldingUIView.h"
#import "ACRAggregateTarget.h"
#import "ACRView.h"
#import "ACRUIImageView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRContentHoldingUIView.h"

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
    if(img) {
        view = [[ACRAVPlayerViewHoldingUIView alloc] initWithImage:img];
        view.translatesAutoresizingMaskIntoConstraints = NO;
        view.contentMode = UIViewContentModeScaleAspectFill;
        
        if(img.size.width > 0) {
            heightToWidthRatio = img.size.height / img.size.width;
        }
    } else {
        heightToWidthRatio = .75;
        view = [[ACRAVPlayerViewHoldingUIView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.width * heightToWidthRatio)];
        view.backgroundColor = UIColor.blackColor;
        view.translatesAutoresizingMaskIntoConstraints = NO;
    }
    view.frame = CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.width * heightToWidthRatio);
    ACRContentHoldingUIView *contentholdingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
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
        if(![acoConfig getHostConfig]->media.allowInlinePlayback) {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig];
        } else {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig containingview:contentholdingview superview:viewGroup];
        }
        UILongPressGestureRecognizer *recognizer = [ACRLongPressGestureRecognizerFactory getGestureRecognizer:viewGroup target:mediaTarget];
        [view addGestureRecognizer:recognizer];
        view.userInteractionEnabled = YES;
    }

    return view;
}

@end
