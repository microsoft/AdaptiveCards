//
//  ACORemoteResourceInformation.h
//  ACORemoteResourceInformation
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import <Foundation/Foundation.h>

@interface ACORemoteResourceInformation : NSObject

@property (readonly) NSURL *url;
@property (readonly) NSString *mimeType;

@end
