//
//  ACRSubmitActionDelegate
//  ACRSubmitActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRSubmitActionDelegate

- (void)fetchUserResponses:(NSDictionary *)userResponses;
@end
