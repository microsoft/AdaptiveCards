//
//  ACRBaseActionElementRenderer
//  ACRBaseActionElementRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"

@implementation ACRBaseActionElementRenderer

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{ 
   return nil;
}

@end
