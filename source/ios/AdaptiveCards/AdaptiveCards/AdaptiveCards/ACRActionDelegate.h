//
//  ACRActionDelegate 
//  ACRActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRActionDelegate

- (void)didFetchUserResponses:(NSDictionary *)userResponses;

- (void)didFetchHttpRequest:(NSURLRequest *)urlRequest;
@end
