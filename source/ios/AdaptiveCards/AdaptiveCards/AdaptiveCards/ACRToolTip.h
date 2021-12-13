//
//  ACRToolTip
//  ACRToolTip.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElement.h"
#import "ACRTapGestureRecognizerEventHandler.h"
#import <UIKit/UIKit.h>

@interface ACRToolTip : NSObject

+ (void)showToolTip:(UILongPressGestureRecognizer *)recognizer toolTip:(NSString *)toolTip;


@end
