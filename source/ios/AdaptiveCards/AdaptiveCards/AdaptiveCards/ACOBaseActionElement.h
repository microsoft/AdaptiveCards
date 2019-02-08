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
    ACRToggleVisibility,
};

typedef NS_ENUM(NSInteger, ACRIconPlacement) {
    ACRAboveTitle = 0,
    ACRLeftOfTitle,
    ACRNoTitle,
};

@property ACRActionType type;
@property NSString *sentiment;

- (NSString *)title;
- (NSString *)elementId;
- (NSString *)url;
- (NSString *)data;
- (NSData *)additionalProperty;

@end
