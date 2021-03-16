//
//  ACOAuthCardButton
//  ACOAuthCardButton.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOAuthCardButton : NSObject

@property NSString *type;
@property NSString *title;
@property NSString *image;
@property NSString *value;

- (instancetype)init:(NSString *)type title:(NSString *)title image:(NSString *)image value:(NSString *)value;

@end
