//
//  ACOMediaEventPrivate.h
//  ACOMediaEventPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOMediaEvent.h"
#import "Media.h"
#import "MediaSource.h"
#import "SharedAdaptiveCard.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@interface ACOMediaSource ()

- (instancetype)initWithMediaSource:(std::shared_ptr<MediaSource> const &)mediaSource;

@end

@interface ACOMediaEvent ()

- (instancetype)initWithMedia:(std::shared_ptr<Media> const &)media;

@end
