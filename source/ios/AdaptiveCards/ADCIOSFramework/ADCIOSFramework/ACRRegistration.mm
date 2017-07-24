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
#import "ACRImageRenderer.h"
#import "ACRImageSetRenderer.h"
#import "ACRTextBlockRenderer.h"
#import "ACRFactSetRenderer.h"
#import "ACRContainerRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRColumnRenderer.h"
#import "ACRSeparator.h"
#import "BaseCardElement.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACRRegistration
{
    NSDictionary* typeToRendererDict;
}

- (instancetype) init
{
    self = [super init];
    if(self)
    {
        typeToRendererDict =
            [[NSDictionary alloc] initWithObjectsAndKeys:
             [ACRImageRenderer getInstance],     [NSNumber numberWithInt:(int)[ACRImageRenderer elemType]],
             [ACRImageSetRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRImageSetRenderer elemType]],
             [ACRTextBlockRenderer getInstance], [NSNumber numberWithInt:(int)[ACRTextBlockRenderer elemType]],
             [ACRFactSetRenderer getInstance],   [NSNumber numberWithInt:(int)[ACRFactSetRenderer elemType]],
             [ACRContainerRenderer getInstance], [NSNumber numberWithInt:(int)[ACRContainerRenderer elemType]],
             [ACRColumnSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRColumnSetRenderer elemType]],
             [ACRColumnRenderer getInstance],    [NSNumber numberWithInt:(int)[ACRColumnRenderer elemType]],
             nil];
    }
    return self;
}

+ (ACRRegistration* ) getInstance
{
    static ACRRegistration *singletonInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{singletonInstance = [[self alloc] init];});
    return singletonInstance;
}

- (ACRBaseCardElementRenderer* ) getRenderer:(NSNumber* )cardElementType
{ 
    return [typeToRendererDict objectForKey:cardElementType];
}

- (UIView* ) render:(UIView* )view
      withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
      andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    ACRColumnView* horizontalView = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height)];

    return [self render:view withContentView:horizontalView
                         withCardElems:elems
                         andHostConfig:config];

}

- (UIView* ) render:(UIView* )view
    withContentView:(UIView* )newView
      withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
      andHostConfig:(std::shared_ptr<HostConfig> const &)config
{   
   
    for(auto elem:elems)
    {
        [ACRSeparator renderSeparation:elem forSuperview:newView withHostConfig:config];
        
        ACRBaseCardElementRenderer* renderer =
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
        [(ACRContentStackView* )view addArrangedSubview:newView];
    }
    else
    {
        [view addSubview:newView];
        
        NSLayoutConstraint* constraint =
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeLeading
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeLeading
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeTrailing
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTrailing
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        [view addSubview:newView];
        
        constraint =
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeTop
                                     relatedBy:NSLayoutRelationLessThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeBottom
                                     relatedBy:NSLayoutRelationGreaterThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
    }
    return newView;
}
@end
