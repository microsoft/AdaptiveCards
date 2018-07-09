//
//  ACOResourceResolvers.h
//  ACOResourceResolvers
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef UIImage* (^ImageLoadBlock)(NSString *urlString);

@interface ACOResourceResolvers:NSObject

- (instancetype)init;
- (ImageLoadBlock)getResolverBlockForScheme:(NSString *)scheme;
- (void)setResolverBlock:(ImageLoadBlock)resolver scheme:(NSString *)scheme;

@end    
