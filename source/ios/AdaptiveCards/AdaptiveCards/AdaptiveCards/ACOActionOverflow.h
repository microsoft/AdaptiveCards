//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOBaseActionElement.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOBaseActionElement.h>
#endif
#import <Foundation/Foundation.h>

@interface ACOActionOverflow : ACOBaseActionElement

@property NSArray<ACOBaseActionElement *> *menuActions;
@property (readonly) BOOL isAtRootLevel;

@end
