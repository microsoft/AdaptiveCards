//
//  ACRIBaseInputHandler
//  ACRIBaseInputHandler.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRErrors.h"

@protocol ACRIBaseInputHandler

- (BOOL)validate:(NSError **)error;

- (void)getInput:(NSMutableDictionary *)dictionary;

@end
