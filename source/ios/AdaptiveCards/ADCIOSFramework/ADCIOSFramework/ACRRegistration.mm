//
//  ACRRegistration
//  ACRRegistration.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRRegistration.h"
#import "ACRColumnView.h"
#import "ACRColumnSetView.h"
#import "ACRImageRenderer.h"
#import "ACRImageSetRenderer.h"
#import "ACRTextBlockRenderer.h"
#import "ACRInputRenderer.h"
#import "ACRInputToggleRenderer.h"
#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputDateRenderer.h"
#import "ACRInputTimeRenderer.h"
#import "ACRInputNumberRenderer.h"
#import "ACRFactSetRenderer.h"
#import "ACRContainerRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRColumnRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRSeparator.h"
#import "BaseCardElement.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACRRegistration
{
    NSDictionary *typeToRendererDict;
    NSDictionary *actionRendererDict;
}

- (instancetype) init
{
    self = [super init];
    if(self)
    {
        typeToRendererDict =
            [[NSDictionary alloc] initWithObjectsAndKeys:
             [ACRImageRenderer getInstance],      [NSNumber numberWithInt:(int)[ACRImageRenderer elemType]],
             [ACRImageSetRenderer getInstance],   [NSNumber numberWithInt:(int)[ACRImageSetRenderer elemType]],
             [ACRTextBlockRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRTextBlockRenderer elemType]],
             [ACRInputRenderer getInstance],      [NSNumber numberWithInt:(int)[ACRInputRenderer elemType]],
             [ACRInputToggleRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputToggleRenderer elemType]],
             [ACRInputChoiceSetRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputChoiceSetRenderer elemType]],
             [ACRInputDateRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRInputDateRenderer elemType]],
             [ACRInputTimeRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRInputTimeRenderer elemType]],
             [ACRInputNumberRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputNumberRenderer elemType]],
             [ACRFactSetRenderer getInstance],    [NSNumber numberWithInt:(int)[ACRFactSetRenderer elemType]],
             [ACRContainerRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRContainerRenderer elemType]],
             [ACRColumnSetRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRColumnSetRenderer elemType]],
             [ACRColumnRenderer getInstance],     [NSNumber numberWithInt:(int)[ACRColumnRenderer elemType]],
             nil];
        actionRendererDict = 
            [[NSDictionary alloc] initWithObjectsAndKeys:
             [ACRActionOpenURLRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::OpenUrl], 
            nil];
    }
    return self;
}

+ (ACRRegistration *) getInstance
{
    static ACRRegistration *singletonInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{singletonInstance = [[self alloc] init];});
    return singletonInstance;
}

- (ACRBaseCardElementRenderer *) getRenderer:(NSNumber *)cardElementType
{ 
    return [typeToRendererDict objectForKey:cardElementType];
}

- (UIView<ACRIContentHoldingView> *) render:(UIView *)view
      withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
      andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    ACRColumnView *verticalView = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height)];

    [self render:view withContentView:verticalView
                         withCardElems:elems
                         andHostConfig:config];
    return verticalView;
}

- (UIView<ACRIContentHoldingView> *)renderButton:(UIViewController *)vc
               superview:(UIView<ACRIContentHoldingView> *)superview
             actionElems:(std::vector<std::shared_ptr<BaseActionElement>> const &)elems
              hostConfig:(std::shared_ptr<HostConfig> const &)config
 {
     UIView<ACRIContentHoldingView> *childview = nil;
    if(ActionsOrientation::Horizontal == config->actions.actionsOrientation)
    {
        childview = [[ACRColumnSetView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height)];
    }
    else
    {
        childview = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height)];
    }

    for(auto elem:elems)
    {
        ACRBaseActionElementRenderer *actionRenderer =
            [actionRendererDict objectForKey:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(actionRenderer == nil)
        { 
            NSLog(@"Unsupported card action type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [actionRenderer renderButton:vc superview:childview baseActionElement:elem andHostConfig:config];
    }

    return childview;
 }

- (UIView *) render:(UIView *)view
    withContentView:(UIView *)newView
      withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
      andHostConfig:(std::shared_ptr<HostConfig> const &)config
{   
   
    for(auto elem:elems)
    {
        [ACRSeparator renderSeparation:elem forSuperview:newView withHostConfig:config];
        
        ACRBaseCardElementRenderer *renderer =
            [typeToRendererDict objectForKey:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(renderer == nil)
        { 
            NSLog(@"Unsupported card element type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [renderer render:newView withCardElem:elem andHostConfig:config];
    }
   
    if([view isKindOfClass:[ACRContentStackView class]])
    {
        [(ACRContentStackView *)view addArrangedSubview:newView];
    }
    else
    {
        [view addSubview:newView];
        
        NSLayoutConstraint *constraint =
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeLeading
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeLeading
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        
        constraint =
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeTrailing
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTrailing
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        
        constraint =
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeTop
                                     relatedBy:NSLayoutRelationLessThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        
        constraint = 
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeBottom
                                     relatedBy:NSLayoutRelationGreaterThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeBottom
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
    }
    return newView;
}
@end
