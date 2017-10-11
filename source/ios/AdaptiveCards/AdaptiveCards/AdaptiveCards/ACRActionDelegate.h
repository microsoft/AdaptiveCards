//
//  ACRActionDelegate 
//  ACRActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRActionDelegate

- (void)didFetchUserResponses:(NSData *)json error:(NSError *)error;

- (void)didFetchHttpRequest:(NSURLRequest *)urlRequest;
@end
