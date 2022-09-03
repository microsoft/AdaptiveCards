//
//  ACORemoteResourceInformation.h
//  ACORemoteResourceInformation
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseCardElement.h"
#else
#import <AdaptiveCards/ACOBaseCardElement.h>
#endif
#import <Foundation/Foundation.h>

@interface ACORemoteResourceInformation : NSObject

@property (readonly) NSURL *url;
@property (readonly) NSString *mimeType;

@end
