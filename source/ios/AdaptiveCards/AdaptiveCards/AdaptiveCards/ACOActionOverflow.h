//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseActionElement.h"
#else
#import <AdaptiveCards/ACOBaseActionElement.h>
#endif
#import <Foundation/Foundation.h>

@interface ACOActionOverflow : ACOBaseActionElement

@property NSArray<ACOBaseActionElement *> *menuActions;
@property (readonly) BOOL isAtRootLevel;

@end
