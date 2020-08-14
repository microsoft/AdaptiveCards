//
//  CustomActionNewType
//  CustomActionNewType.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "CustomActionNewType.h"
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>

@implementation CustomActionNewType

- (ACOBaseActionElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;
{
    if (json) {

        NSDictionary *data = [NSJSONSerialization JSONObjectWithData:json options:NSJSONReadingMutableLeaves error:nil];
        NSNumber *red = data[@"Red"];
        NSNumber *green = data[@"Green"];
        NSNumber *blue = data[@"Blue"];
        NSNumber *cornerRadius = data[@"CornerRadius"];

        CustomActionNewType *newTypeAction = nil;
        // this is an optional step
        std::shared_ptr<AdaptiveCards::BaseActionElement> actionElement = std::make_shared<AdaptiveCards::BaseActionElement>(ActionType::UnknownAction);
        actionElement->SetTitle(std::string([data[@"title"] UTF8String]));
        actionElement->SetElementTypeString([data[@"type"] UTF8String]);
        newTypeAction = [[CustomActionNewType alloc] initWithBaseActionElement:actionElement];

        newTypeAction.color = [UIColor colorWithRed:red.doubleValue / 255.0 green:green.doubleValue / 255.0 blue:blue.doubleValue / 255.0 alpha:1.0];
        newTypeAction.cornerradius = cornerRadius.integerValue;
        newTypeAction.alertMessage = data[@"alertMessage"];

        newTypeAction.type = ACRUnknownAction;

        return newTypeAction;
    }
    return nil;
}

@end

@implementation CustomActionNewTypeRenderer : ACRBaseActionElementRenderer

+ (CustomActionNewTypeRenderer *)getInstance
{
    static CustomActionNewTypeRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton *)renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    ACRButton *button = [bundle loadNibNamed:@"ACRButton" owner:rootView options:nil][0];
    [button setTitle:acoElem.title forState:UIControlStateNormal];
    CustomActionNewType *newType = (CustomActionNewType *)acoElem;
    button.backgroundColor = newType.color;
    button.layer.cornerRadius = newType.cornerradius;

    // ACRAggregateTarget relays signal (event) back to host app via ACRActionDelegate
    ACRAggregateTarget *target = [[ACRAggregateTarget alloc] initWithActionElement:newType rootView:rootView];

    [button addTarget:target action:@selector(send:) forControlEvents:UIControlEventTouchUpInside];
    [superview addTarget:target];
    return button;
}

@end
