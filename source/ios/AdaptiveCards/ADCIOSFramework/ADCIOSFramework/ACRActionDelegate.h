//
//  ACRSubmitActionDelegate
//  ACRSubmitActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRActionDelegate

- (void)fetchUserResponses:(NSDictionary *)userResponses;

- (void)fetchHttpRequest:(NSURLRequest *)urlRequest;
@end
