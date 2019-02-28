//
//  ACRUILable.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACOBaseCardElement.h"
#import "ACRView.h"

@interface ACRUILabel:UITextView
@property ACRContainerStyle style;
@property CGFloat area;
@property __weak ACRView* rootView;
@end
