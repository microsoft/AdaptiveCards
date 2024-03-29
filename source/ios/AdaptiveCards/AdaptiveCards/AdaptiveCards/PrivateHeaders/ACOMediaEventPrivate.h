//
//  ACOMediaEventPrivate.h
//  ACOMediaEventPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOMediaEvent.h"
#import "Media.h"
#import "MediaSource.h"
#import "SharedAdaptiveCard.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOMediaEvent.h>
#import <AdaptiveCards/Media.h>
#import <AdaptiveCards/MediaSource.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#endif
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@interface ACOMediaSource ()

- (instancetype)initWithMediaSource:(std::shared_ptr<MediaSource> const &)mediaSource;

@end

@interface ACOMediaEvent ()

- (instancetype)initWithMedia:(std::shared_ptr<Media> const &)media;

@end
