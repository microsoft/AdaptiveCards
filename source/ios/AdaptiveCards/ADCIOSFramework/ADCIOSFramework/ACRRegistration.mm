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
             [ACRImageRenderer getInstance], [ACRImageRenderer elemType],
             [ACRTextBlockRenderer getInstance], [ACRTextBlockRenderer elemType],
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

- (ACRBaseCardElementRenderer* ) getRenderer:(NSString*) cardElementType
{ 
    return [typeToRendererDict objectForKey: cardElementType];
}

- (UIView* ) render: (UIView*) view
       withCardElem: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
       andHostCofig: (std::shared_ptr<HostConfig> const &) config
{ 
    UIStackView* childView = [[UIStackView alloc] init];
    childView.axis = UILayoutConstraintAxisVertical;
    childView.distribution = UIStackViewDistributionEqualSpacing;
    childView.translatesAutoresizingMaskIntoConstraints = false;
    [view addSubview: childView];

    //for(auto elem: elems)
    //{
    //    ACRBaseCardElementRenderer* renderer = [typeToRendererDict objectForKey:elem->GetElementType()];
    //}

    [NSLayoutConstraint activateConstraints:@[[childView.centerXAnchor constraintEqualToAnchor:view.centerXAnchor],
                                              [childView.centerYAnchor constraintEqualToAnchor:view.centerYAnchor]]];
    return nil;
}

@end
