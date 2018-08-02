//
//  ACRShowCardVisibilityHandler.h
//  AdaptiveCards
//
//  Created by Ankit Maurya on 8/2/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifndef ACRShowCardVisibilityHandler_h
#define ACRShowCardVisibilityHandler_h

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"

@protocol ACRShowCardVisibilityHandler <NSObject>

- (void) didChangeVisibility:(UIButton*)button isVisible:(BOOL)isVisible;

@end

#endif /* ACRShowCardVisibilityHandler_h */
