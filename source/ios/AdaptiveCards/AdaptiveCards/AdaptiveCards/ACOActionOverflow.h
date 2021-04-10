//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElement.h"
#import <Foundation/Foundation.h>

@interface ACOActionOverflow : ACOBaseActionElement

@property NSArray<ACOBaseActionElement *> *menuActions;
@property (readonly) BOOL isAtRootLevel;

@end
