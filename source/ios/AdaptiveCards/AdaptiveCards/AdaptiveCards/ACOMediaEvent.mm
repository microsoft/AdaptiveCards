//
//  ACOMediaEvent.mm
//  ACOMediaEvent.h
//  ACOMediaEventPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOMediaEventPrivate.h"

@implementation ACOMediaSource
static NSSet<NSString *> *validAudioFormats = [[NSSet alloc] initWithObjects:@"mpeg", @"mp3", nil];
static NSSet<NSString *> *validVideoFormats = [[NSSet alloc] initWithObjects:@"mp4", nil];
static NSSet<NSString *> *validMediaTypes   = [[NSSet alloc] initWithObjects:@"audio", @"video", nil];

- (instancetype)initWithMediaSource:(const std::shared_ptr<MediaSource> &)mediaSource
{
    self = [super init];
    if(self){
        _url = [NSString stringWithCString:mediaSource->GetUrl().c_str() encoding:NSUTF8StringEncoding];
        _mimeType = [NSString stringWithCString:mediaSource->GetMimeType().c_str() encoding:NSUTF8StringEncoding];
        _isValid = NO;
        if([_mimeType length]){
            NSArray<NSString *> *components = [_mimeType componentsSeparatedByString:@"/"];
            if([validMediaTypes containsObject:components[0]]) {
                _isVideo = ([components[0] compare:@"video"] == NSOrderedSame) ? YES : NO;
                _mediaFormat = components[1];
                if(_isVideo){
                    _isValid = [validVideoFormats containsObject:_mediaFormat];
                } else {
                    _isValid = [validAudioFormats containsObject:_mediaFormat];
                }
            }
        }
    }
    return self;
}

@end

@implementation ACOMediaEvent

- (instancetype)initWithMedia:(std::shared_ptr<Media> const &)media
{
    self = [super init];
    if(self){
        NSMutableArray *mediaSources = [[NSMutableArray alloc] init];
        for(auto &mediasource : media->GetSources()){
            [mediaSources addObject:[[ACOMediaSource alloc] initWithMediaSource:mediasource]];
        }
        _sources = [NSArray arrayWithArray:mediaSources];
    }
    return self;
}

@end
