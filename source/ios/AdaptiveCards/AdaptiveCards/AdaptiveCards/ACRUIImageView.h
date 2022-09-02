//
//  ACRUIImageView.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACREnums.h>
#import <UIKit/UIKit.h>

@interface ACRUIImageView : UIImageView
@property BOOL isPersonStyle;
@property CGSize desiredSize;
@property ACRImageSize adaptiveImageSize;
@end
