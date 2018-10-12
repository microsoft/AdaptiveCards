//
//  ACOBaseActionElement
//  ACOBaseActionElement.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOBaseActionElement:NSObject

typedef NS_ENUM(NSInteger, ACRActionType) {
    ACRShowCard = 1,
    ACRSubmit,
    ACROpenUrl,
};

@property ACRActionType type;

- (NSString *)title;
- (NSString *)elementId;
- (NSString *)url;
- (NSString *)data;
- (NSData *)additionalProperty;

@end
