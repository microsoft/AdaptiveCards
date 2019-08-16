//
//  ACOMediaEvent.h
//  ACOMediaEvent
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOMediaSource : NSObject
@property NSString *url;
@property NSString *mimeType;
@property BOOL isVideo;
@property NSString *mediaFormat;
@property BOOL isValid;

@end

@interface ACOMediaEvent : NSObject
@property NSArray<ACOMediaSource *> *sources;
@property BOOL isValid;
@end
