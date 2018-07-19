//
//  ACOMediaEvent.h
//  ACOMediaEvent
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOMediaSource:NSObject
@property NSString *url;
@property NSString *mimeType;

@end

@interface ACOMediaEvent:NSObject

@property NSArray<ACOMediaSource *> *sources;

@end    
