//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardParseResult.h"

@interface ACOAdaptiveCard:NSObject

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;

@end    
