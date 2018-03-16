//
//  ACRIBaseActionElementRenderer
//  ACRIBaseActionElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ACOHostConfig.h"
#import "ACOBaseActionElement.h"
#import "ACRView.h"

@protocol ACRIBaseActionElementRenderer

- (UIButton* )renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
@end
