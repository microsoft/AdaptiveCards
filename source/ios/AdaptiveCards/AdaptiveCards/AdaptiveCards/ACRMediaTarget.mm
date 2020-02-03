//
//  ACRMediaTarget
//  ACRMediaTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRMediaTarget.h"
#import "ACOHostConfigPrivate.h"
#import "ACRAVPlayerViewHoldingUIView.h"
#import "ACRContentHoldingUIView.h"

// tags for easy accessing of subviews
const int playIconTag = 0x49434F4E;
const int posterTag = 0x504F5354;

@implementation ACRMediaTarget {
    ACOMediaEvent *_mediaEvent;
    AVPlayerViewController *_mediaViewController;
    NSURL *_url;
    NSString *_mimeType;
    __weak ACRView *_view;
    __weak UIView *_containingview;
    BOOL isInline;
}
// dedicated initializer
- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                               url:(NSURL *)url
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview
{
    self = [super init];
    if (self) {
        _mediaEvent = mediaEvent;
        _url = url;
        _view = rootView;
        _containingview = containingview;
        isInline = [config getHostConfig] -> GetMedia().allowInlinePlayback;
    }
    return self;
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config
{
    return [self initWithMediaEvent:mediaEvent url:nil rootView:rootView config:config containingview:nil];
}

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview
{
    return [self initWithMediaEvent:mediaEvent url:nil rootView:rootView config:config containingview:containingview];
}
// delegate for ACRSelectActionDelegate
- (void)doSelectAction
{
    if (!isInline) {
        // if inline media play is disabled, call media delegate, and let host to handle it.
        if ([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaEvent:card:)]) {
            [_view.mediaDelegate didFetchMediaEvent:_mediaEvent card:[_view card]];
        } else {
            // https://github.com/Microsoft/AdaptiveCards/issues/1834
            NSLog(@"Warning: inline media play is disabled and host doesn't handle media event");
        }
    } else {
        BOOL validMediaTypeFound = NO;
        // loop and find media source that can be played
        for (ACOMediaSource *source in _mediaEvent.sources) {
            if (source.isValid) {
                if (source.isVideo) {
                    NSURL *url = [[NSURL alloc] initWithString:source.url];
                    AVURLAsset *asset = [AVURLAsset URLAssetWithURL:url options:nil];
                    _mimeType = source.mimeType;
                    [asset loadValuesAsynchronouslyForKeys:@[ @"tracks" ]
                                         completionHandler:^{
                                             AVKeyValueStatus status = [asset statusOfValueForKey:@"tracks" error:nil];
                                             if (status == AVKeyValueStatusLoaded) {
                                                 dispatch_async(dispatch_get_main_queue(), ^{
                                                     [self playVideoWhenTrackIsReady:asset];
                                                 });
                                             }
                                         }];
                    validMediaTypeFound = YES;
                    break;
                } else { // audio type
                    NSURL *url = [[NSURL alloc] initWithString:source.url];
                    AVPlayer *player = [AVPlayer playerWithURL:url];

                    self->_mediaViewController = [[AVPlayerViewController alloc] init];
                    self->_mediaViewController.player = player;

                    // pass AVPlayerViewController to host; it is not neccessary step for playback test, but it's better, the vc is inside parent vc tree
                    [_view.mediaDelegate didFetchMediaViewController:self->_mediaViewController card:nil];

                    self->_mediaViewController.videoGravity = AVLayerVideoGravityResizeAspectFill;
                    // TODO AVPlayerViewController has some constraints conflicts internally; need to fix, so the warning will be turned off, but
                    // system is correctly breaking the ties.
                    UIView *mediaView = self->_mediaViewController.view;
                    mediaView.translatesAutoresizingMaskIntoConstraints = NO;

                    UIImageView *poster = [self->_containingview viewWithTag:posterTag];

                    UIView *playIconView = [poster viewWithTag:playIconTag];
                    if (playIconView) {
                        [playIconView removeFromSuperview];
                    }

                    ((ACRContentHoldingUIView *)self->_containingview).hidePlayIcon = YES;
                    [self->_containingview setNeedsLayout];
                    [self->_containingview addSubview:mediaView];

                    // poster and plyaIconView are removed from their superviews
                    [poster removeFromSuperview];

                    UIView *overlayview = self->_mediaViewController.contentOverlayView;
                    overlayview.backgroundColor = UIColor.blackColor;
                    [overlayview addSubview:poster];

                    // overlayview sit between AVPLayverViewController view's control view and content view, and here we add the poster.
                    CGFloat heightToWidthRatio = 0.0f;
                    UIImage *image = poster.image;

                    if (!image) {
                        heightToWidthRatio = .75;
                    } else {
                        poster.frame = CGRectMake(0, 0, image.size.width, image.size.height);
                        if (image.size.width > 0) {
                            heightToWidthRatio = image.size.height / image.size.width;
                        }
                    }

                    _containingview.translatesAutoresizingMaskIntoConstraints = NO;

                    [NSLayoutConstraint constraintWithItem:mediaView
                                                 attribute:NSLayoutAttributeCenterX
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:_containingview
                                                 attribute:NSLayoutAttributeCenterX
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:mediaView
                                                 attribute:NSLayoutAttributeCenterY
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:_containingview
                                                 attribute:NSLayoutAttributeCenterY
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:mediaView
                                                 attribute:NSLayoutAttributeWidth
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:_containingview
                                                 attribute:NSLayoutAttributeWidth
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:mediaView
                                                 attribute:NSLayoutAttributeHeight
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:_containingview
                                                 attribute:NSLayoutAttributeHeight
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:_containingview
                                                 attribute:NSLayoutAttributeHeight
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:_containingview
                                                 attribute:NSLayoutAttributeWidth
                                                multiplier:heightToWidthRatio
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:poster
                                                 attribute:NSLayoutAttributeWidth
                                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                                    toItem:overlayview
                                                 attribute:NSLayoutAttributeWidth
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;

                    [NSLayoutConstraint constraintWithItem:poster
                                                 attribute:NSLayoutAttributeHeight
                                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                                    toItem:overlayview
                                                 attribute:NSLayoutAttributeHeight
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    [_containingview setNeedsLayout];

                    [player play];
                    validMediaTypeFound = YES;
                    break;
                }
            }
        }
        if (!validMediaTypeFound) { // https://github.com/Microsoft/AdaptiveCards/issues/1834
            NSLog(@"Warning: supported media types not found");
        }
    }
}

- (void)playVideoWhenTrackIsReady:(AVURLAsset *)asset
{
    AVAssetTrack *track = [asset tracksWithMediaCharacteristic:AVMediaCharacteristicVisual][0];
    [track loadValuesAsynchronouslyForKeys:@[ @"naturalSize" ]
                         completionHandler:^{
                             AVKeyValueStatus status = [asset statusOfValueForKey:@"naturalSize" error:nil];
                             if (status == AVKeyValueStatusLoaded) {
                                 dispatch_async(dispatch_get_main_queue(), ^{
                                     [self playMedia:track asset:asset];
                                 });
                             }
                         }];
}

- (void)playMedia:(AVAssetTrack *)track asset:(AVURLAsset *)asset
{
    // video is ready to play, config AVPlayerViewController view dimension
    CGSize size = track.naturalSize;
    AVPlayerItem *item = [AVPlayerItem playerItemWithAsset:asset];
    AVPlayer *player = [AVPlayer playerWithPlayerItem:item];

    self->_mediaViewController = [[AVPlayerViewController alloc] init];
    self->_mediaViewController.player = player;

    if ([_view.mediaDelegate respondsToSelector:@selector(didFetchMediaViewController:card:)]) {
        [_view.mediaDelegate didFetchMediaViewController:self->_mediaViewController card:nil];
    }

    self->_mediaViewController.videoGravity = AVLayerVideoGravityResizeAspectFill;
    // get frame that is constrained by actual media size and the superview
    CGRect frame = AVMakeRectWithAspectRatioInsideRect(size, CGRectMake(0, 0, self->_containingview.frame.size.width, self->_containingview.frame.size.height));
    UIView *mediaView = self->_mediaViewController.view;
    mediaView.frame = frame;
    mediaView.translatesAutoresizingMaskIntoConstraints = NO;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.width].active = YES;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:frame.size.height].active = YES;

    UIImageView *poster = [self->_containingview viewWithTag:posterTag];
    poster.hidden = YES;
    ((ACRContentHoldingUIView *)self->_containingview).hidePlayIcon = YES;

    [self->_containingview addSubview:mediaView];
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:mediaView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self->_containingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;

    [player play];
}

@end
