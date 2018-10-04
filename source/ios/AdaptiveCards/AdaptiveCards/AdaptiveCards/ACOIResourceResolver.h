//
//  ACOIResourceResolver.h
//  ACOIResourceResolver
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ACOIResourceResolver

@optional
- (UIImage *)resolveImageResource:(NSURL *)url;
- (UIImage*) getRadioButtonForSelectedState;
- (UIImage*) getRadioButtonForUnselectedState;
- (UIImage*) getCheckBoxButtonSelectedState;
- (UIImage*) getCheckBoxButtonUnselectedState;

@end    
