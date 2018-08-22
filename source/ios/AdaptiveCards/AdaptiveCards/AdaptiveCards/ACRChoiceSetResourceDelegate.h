//
//  ACRChoiceSetResourceDelegate.h
//  AdaptiveCards
//
//  Created by Ankit Maurya on 8/22/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"

@protocol ACRChoiceSetResourceDelegate <NSObject>

- (UIImage*) getRadioButtonForSelectedState;
- (UIImage*) getRadioButtonForUnselectedState;

- (UIImage*) getCheckBoxButtonSelectedState;
- (UIImage*) getCheckBoxButtonUnselectedState;

@end
