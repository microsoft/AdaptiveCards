//
//  ACRMediaTarget
//  ACRMediaTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRMediaTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ACRViewController.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"

@implementation ACRMediaTarget
{
    ACOMediaEvent *_mediaEvent;
    AVPlayerViewController *_mediaViewController;
    __weak ACRView *_view;
    __weak UIView *_poster;
    __weak UIView<ACRIContentHoldingView> *_superview;
    BOOL isInline;
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
               mediaViewController:(AVPlayerViewController *)mediaViewController
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                            poster:(UIView *)poster
                         superview:(UIView<ACRIContentHoldingView> *)superview
{
    self = [super init];
    if(self) {
        _mediaEvent = mediaEvent;
        _mediaViewController = mediaViewController;
        _view = rootView;
        _poster = poster;
        _superview = superview;
        isInline = [config getHostConfig]->media.allowInlinePlayback;
    }
    return self;
    
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config
{
    return [self initWithMediaEvent:mediaEvent mediaViewController:nil rootView:rootView config:config poster:nil superview:nil];
}

- (instancetype)initWithMediaViewController:(AVPlayerViewController *)mediaViewController
                                   rootView:(ACRView *)rootView
                                     config:(ACOHostConfig *)config
                                     poster:(UIView *)poster
                                  superview:(UIView<ACRIContentHoldingView> *)superview
{
    return [self initWithMediaEvent:nil mediaViewController:mediaViewController rootView:rootView config:config poster:poster superview:superview];
}

- (void)doSelectAction
{
    if(!isInline) {
        if([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaEvent: card:)]) {
            [_view.mediaDelegate didFetchMediaEvent:_mediaEvent card:[_view card]];
        } else
        {
            NSLog(@"Warning inline media play is disabled and host doesn't handles media event");
        }
    } else {
        [_view.mediaDelegate didFetchMediaViewController:_mediaViewController card:[_view card]];
        _poster.hidden = YES;
        [_superview addArrangedSubview:_mediaViewController.view];
    }
}

@end
