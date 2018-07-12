//
//  ACOIResourceResolver.h
//  ACOIResourceResolver
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ACOIResourceResolver

- (UIImage *)resolveImageResource:(NSString *)url;
/*
typedef UIImage* (^ImageLoadBlock)(NSString *urlString);

@interface ACOIResourceResolver:NSObject

- (instancetype)init;
- (ImageLoadBlock)getResolverBlockForScheme:(NSString *)scheme;
- (void)setResolverBlock:(ImageLoadBlock)resolver scheme:(NSString *)scheme;
*/
@end    
