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
             [ACRImageRenderer getInstance], [NSNumber numberWithInt: (int)[ACRImageRenderer elemType]],
             [ACRTextBlockRenderer getInstance], [NSNumber numberWithInt: (int)[ACRTextBlockRenderer elemType]],
             [ACRContainerRenderer getInstance], [NSNumber numberWithInt: (int)[ACRContainerRenderer elemType]],
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
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{ 
    UIStackView* childView = [[UIStackView alloc] init];
    childView.axis = UILayoutConstraintAxisVertical;
    childView.distribution = UIStackViewDistributionEqualSpacing;
    childView.translatesAutoresizingMaskIntoConstraints = false;
    
    ([view class] == [UIStackView class])?
        [(UIStackView* )view addArrangedSubview: childView]:
        [view addSubview: childView];

    for(auto elem: elems)
    {
        ACRBaseCardElementRenderer* renderer =
            [typeToRendererDict objectForKey:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        NSLog(@"card element type: %@\n", [NSNumber numberWithInt:(int)elem->GetElementType()]);
        if(renderer == nil)
        { 
            NSLog(@"Unsupported card element type: %d\n", (int) elem->GetElementType());
            continue;
        }

        [renderer render:childView withCardElem:elem andHostConfig:config];
    }

    return childView;
}

@end
