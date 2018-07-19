//
//  ACRMediaRenderer
//  ACRMediaRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRMediaRenderer.h"
#import "ACOMediaEventPrivate.h"
#import "ACRMediaTarget.h"
#import "Enums.h"
#import "SharedAdaptiveCard.h"
#import "ACRContentHoldingUIView.h"
#import "ACRAggregateTarget.h"
#import "ACRView.h"
#import "ACRUIImageView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

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
    // Syncronize access to imageViewMap
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)mediaElem.get()];
    NSString *key = [number stringValue];
    UIImage *img = imageViewMap[key];

    ACRUIImageView *view = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, img.size.width, img.size.height)];
    view.image = img;

    view.contentMode = UIViewContentModeCenter;

    [viewGroup addArrangedSubview:view];

    if([acoConfig getHostConfig]->supportsInteractivity){
        ACRMediaTarget *mediaTarget = nil;
        ACOMediaEvent *mediaEvent = [[ACOMediaEvent alloc] initWithMedia:mediaElem];
        if(![acoConfig getHostConfig]->media.allowInlinePlayback) {
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaEvent:mediaEvent rootView:rootView config:acoConfig];
        } else
        {
            AVPlayerViewController *mediaPlayerViewController = [[AVPlayerViewController alloc] init];
            NSURL *url = [[NSURL alloc] initWithString:mediaEvent.sources[0].url];
            AVPlayer *player = [AVPlayer playerWithURL:url];
            mediaPlayerViewController.player = player;
            mediaPlayerViewController.view.frame = view.frame;
            mediaTarget = [[ACRMediaTarget alloc] initWithMediaViewController:mediaPlayerViewController rootView:rootView config:acoConfig poster:view superview:viewGroup];
        }
    [ACRLongPressGestureRecognizerFactory getGestureRecognizer:viewGroup
                                                target:mediaTarget];
    }
    view.translatesAutoresizingMaskIntoConstraints = NO;
    return view;
}

@end
