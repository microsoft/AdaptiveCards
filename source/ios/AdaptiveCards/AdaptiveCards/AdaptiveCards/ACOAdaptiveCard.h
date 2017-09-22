//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOParseResult.h"

@interface ACOAdaptiveCard:NSObject

+ (ACOParseResult *)fromJson:(NSString *)payload;

@end    
