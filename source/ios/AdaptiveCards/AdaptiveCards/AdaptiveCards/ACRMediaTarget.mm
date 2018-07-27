//
//  ACRMediaTarget
//  ACRMediaTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVMediaFormat.h>
#import "ACRMediaTarget.h"
#import "ACRAVPlayerViewHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ACRViewController.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"

const int playIconTag = 0x49434F4E;
const int posterTag = 0x504F5354;

@implementation ACRMediaTarget
{
    ACOMediaEvent *_mediaEvent;
    AVPlayerViewController *_mediaViewController;
    AVAudioPlayer *_audioPlayer;
    NSURL *_url;
    NSString *_mimeType;
    __weak ACRView *_view;
    __weak UIView *_containingview;
    __weak UIView<ACRIContentHoldingView> *_superview;
    BOOL isInline;
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                               url:(NSURL *)url
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview
                         superview:(UIView<ACRIContentHoldingView> *)superview
{
    self = [super init];
    if(self) {
        _mediaEvent = mediaEvent;
        _url = url;
        _view = rootView;
        _containingview = containingview;
        _superview = superview;
        isInline = [config getHostConfig]->media.allowInlinePlayback;
    }
    return self;
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config
{
    return [self initWithMediaEvent:mediaEvent url:nil rootView:rootView config:config containingview:nil superview:nil];
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview
                         superview:(UIView<ACRIContentHoldingView> *)superview
{
    return [self initWithMediaEvent:mediaEvent url:nil rootView:rootView config:config containingview:containingview superview:superview];
}

- (void)doSelectAction
{
    if(!isInline) {
        if([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaEvent: card:)]) {
            [_view.mediaDelegate didFetchMediaEvent:_mediaEvent card:[_view card]];
        } else {
            // TODO: implemented as a renderer warning -joswo
            NSLog(@"Warning: inline media play is disabled and host doesn't handles media event");
        }
    } else {
        BOOL validMediaTypeFound = NO;
        for(ACOMediaSource *source in _mediaEvent.sources){
            if(source.isValid){
                if(source.isVideo){
                    NSURL *url = [[NSURL alloc] initWithString:source.url];
                    AVURLAsset *asset = [AVURLAsset URLAssetWithURL:url options:nil];
                    _mimeType = source.mimeType;
                    [asset loadValuesAsynchronouslyForKeys:@[@"tracks"] completionHandler:^{
                        AVKeyValueStatus status = [asset statusOfValueForKey:@"tracks" error:nil];
                        if(status == AVKeyValueStatusLoaded) {
                            dispatch_async(dispatch_get_main_queue(), ^{[self getAVTrack:asset];});
                        }
                    }];
                    validMediaTypeFound = YES;
                    break;
                } else{
                    NSURL *url = [[NSURL alloc] initWithString:source.url];
                    AVPlayer *player = [AVPlayer playerWithURL:url];

                    self->_mediaViewController = [[AVPlayerViewController alloc] init];
                    self->_mediaViewController.player = player;

                    UIViewController *parentViewController = [_view.mediaDelegate didFetchMediaViewController:self->_mediaViewController card:nil];

                    self->_mediaViewController.videoGravity = AVLayerVideoGravityResizeAspectFill;
                    CGRect frame = self->_containingview.frame;
                    UIView *mediaView = self->_mediaViewController.view;
                    mediaView.frame = frame;
                    mediaView.translatesAutoresizingMaskIntoConstraints = NO;
                    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.width].active = YES;
                    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.height].active = YES;

                    ACRAVPlayerViewHoldingUIView *poster = [self->_containingview viewWithTag:posterTag];
                    poster.hidePlayIcon = YES;

                    [poster layoutSubviews];
                    UIView *playIconView = [poster viewWithTag:playIconTag];
                    if(playIconView){
                        [playIconView removeFromSuperview];
                    }
                    [poster removeFromSuperview];

                    [self->_containingview addSubview:mediaView];
                    UIView *overlayview = self->_mediaViewController.contentOverlayView;

                    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

                    overlayview.backgroundColor = UIColor.blackColor;
                    [overlayview addSubview:poster];
                    [overlayview bringSubviewToFront:poster];

                    [NSLayoutConstraint activateConstraints:@[[poster.topAnchor constraintEqualToAnchor:overlayview.topAnchor], [poster.bottomAnchor constraintEqualToAnchor:overlayview.bottomAnchor], [poster.leadingAnchor constraintEqualToAnchor:overlayview.leadingAnchor], [poster.trailingAnchor constraintEqualToAnchor:overlayview.trailingAnchor]]];

                    [parentViewController didMoveToParentViewController:self->_mediaViewController];

                    [player play];
                    validMediaTypeFound = YES;
                    break;
                }
            }
        }
        if(!validMediaTypeFound) {
            // TODO: implemented as a renderer warning -joswo
            NSLog(@"Warnig: supported media types not found");
        }
    }
}

- (void)getAVTrack:(AVURLAsset *)asset
{
    AVAssetTrack *track = [asset tracksWithMediaCharacteristic:AVMediaCharacteristicVisual][0];
    [track loadValuesAsynchronouslyForKeys:@[@"naturalSize"] completionHandler:^{
        AVKeyValueStatus status = [asset statusOfValueForKey:@"naturalSize" error:nil];
        if(status == AVKeyValueStatusLoaded) {
            dispatch_async(dispatch_get_main_queue(), ^{[self getNaturalSize:track asset:asset];});
        }
    }];
}

- (void) getNaturalSize:(AVAssetTrack *)track asset:(AVURLAsset *)asset
{
    CGSize size = track.naturalSize;
    AVPlayerItem *item = [AVPlayerItem playerItemWithAsset:asset];
    AVPlayer *player = [AVPlayer playerWithPlayerItem:item];
    UIViewController *parentViewController = nil;

    self->_mediaViewController = [[AVPlayerViewController alloc] init];
    self->_mediaViewController.player = player;

    if([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaViewController: card:)]){
        parentViewController = [_view.mediaDelegate didFetchMediaViewController:self->_mediaViewController card:nil];
    }

    self->_mediaViewController.videoGravity = AVLayerVideoGravityResizeAspectFill;
    CGRect frame = AVMakeRectWithAspectRatioInsideRect(size, CGRectMake(0, 0, self->_containingview.frame.size.width, self->_containingview.frame.size.height));
    UIView *mediaView = self->_mediaViewController.view;
    mediaView.frame = frame;
    mediaView.translatesAutoresizingMaskIntoConstraints = NO;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.width].active = YES;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.height].active = YES;
    
    ACRAVPlayerViewHoldingUIView *poster = [self->_containingview viewWithTag:posterTag];
    poster.hidden = YES;
    
    [self->_containingview addSubview:mediaView];
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

    if([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaViewController: card:)]){
        [parentViewController didMoveToParentViewController:self->_mediaViewController];
    }
    [player play];
}

@end
