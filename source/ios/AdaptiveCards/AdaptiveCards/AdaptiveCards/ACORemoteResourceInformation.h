//
//  ACORemoteResourceInformation.h
//  ACORemoteResourceInformation
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOBaseCardElement.h"

@interface ACORemoteResourceInformation:NSObject

@property (readonly) NSURL* url;
@property (readonly) ACRCardElementType resourceType;
@property (readonly) NSString* mimeType;

@end    
