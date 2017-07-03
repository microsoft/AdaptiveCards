//
//  ACRRegistration
//  ACRRegistration.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRRegistration.h"
#import "ACRImageRenderer.h"
#import "ACRTextBlockRenderer.h"
#import "ACRContainerRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRColumnRenderer.h"
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
             [ACRImageRenderer getInstance],     [NSNumber numberWithInt: (int)[ACRImageRenderer elemType]],
             [ACRTextBlockRenderer getInstance], [NSNumber numberWithInt: (int)[ACRTextBlockRenderer elemType]],
             [ACRContainerRenderer getInstance], [NSNumber numberWithInt: (int)[ACRContainerRenderer elemType]],
             [ACRColumnSetRenderer getInstance], [NSNumber numberWithInt: (int)[ACRColumnSetRenderer elemType]],
             [ACRColumnRenderer getInstance],    [NSNumber numberWithInt: (int)[ACRColumnRenderer elemType]],
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

- (ACRBaseCardElementRenderer* ) getRenderer:(NSNumber* ) cardElementType
{ 
    return [typeToRendererDict objectForKey: cardElementType];
}

- (UIView* ) render: (UIView*) view
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{ 
    UIStackView* childView = [[UIStackView alloc] init];
    childView.axis = UILayoutConstraintAxisVertical;
    childView.alignment = UIStackViewAlignmentLeading;
    //childView.alignment = UIStackViewAlignmentFill;//UIStackViewAlignmentCenter;
    childView.distribution = UIStackViewDistributionEqualSpacing;
    childView.translatesAutoresizingMaskIntoConstraints = false;

    return [self render: view withContentView: childView
                         withCardElems: elems
                         andHostConfig: config];

}

- (UIView* ) render: (UIView*) view
    withContentView: (UIStackView*) newView
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{ 
    
    if([view isKindOfClass:[UIStackView class]]){
        [(UIStackView* )view addArrangedSubview: newView];
    }else
    {
        [view addSubview: newView];

        NSLayoutConstraint* constraint = 
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeLeft
                                     relatedBy:NSLayoutRelationLessThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeLeft
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeRight
                                     relatedBy:NSLayoutRelationLessThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeRight
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];
        [view addSubview: newView];
        
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
                                     relatedBy:NSLayoutRelationLessThanOrEqual
                                        toItem:newView
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0];
        [view addConstraint:constraint];

        
    }

    for(auto elem: elems)
    {
        ACRBaseCardElementRenderer* renderer =
            [typeToRendererDict objectForKey:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        //NSLog(@"card element type: %@\n", [NSNumber numberWithInt:(int)elem->GetElementType()]);
        if(renderer == nil)
        { 
            NSLog(@"Unsupported card element type: %d\n", (int) elem->GetElementType());
            continue;
        }

        [renderer render:newView withCardElem:elem andHostConfig:config];
    }

    return newView;
}

@end
