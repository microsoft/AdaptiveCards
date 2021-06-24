//
//  ACOBundle
//  ACOBundle.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOBundle : NSObject

+ (ACOBundle *)getInstance;

- (NSBundle *)getBundle;

@end
