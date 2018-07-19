//
//  ACOMediaEvent.mm
//  ACOMediaEvent.h
//  ACOMediaEventPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOMediaEventPrivate.h"

@implementation ACOMediaSource

- (instancetype)initWithMediaSource:(const std::shared_ptr<MediaSource> &)mediaSource
{
    self = [super init];
    if(self){
        _url = [NSString stringWithCString:mediaSource->GetUrl().c_str() encoding:NSUTF8StringEncoding];
        _mimeType = [NSString stringWithCString:mediaSource->GetMimeType().c_str() encoding:NSUTF8StringEncoding];
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
