//
//  ACRActionDelegate 
//  ACRActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"

@protocol ACRActionDelegate <NSObject>

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action;

- (void)didFetchSecondaryView:(ACOAdaptiveCard *)card navigationController:(UINavigationController *)naviationController;

@optional
- (void)didLoadElements;

@end
