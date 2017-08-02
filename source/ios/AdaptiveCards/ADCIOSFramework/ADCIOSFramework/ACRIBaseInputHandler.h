//
//  ACRIBaseInputHandler
//  ACRIBaseInputHandler.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRIBaseInputHandler

- (bool)validate;

- (void)getInput:(NSMutableDictionary *)dictionary;

@end
