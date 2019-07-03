//
//  CustomActionNewType
//  CustomActionNewType.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "CustomActionNewType.h"
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
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

@interface AlertTarget : NSObject

@property (weak) ACRView *rootView;
@property CustomActionNewType *action;

- (instancetype)init:(ACRView *)rootView action:(CustomActionNewType *)action;

- (IBAction)send:(UIButton *)sender;

@end

@implementation AlertTarget

- (instancetype)init:(ACRView *)rootView action:(CustomActionNewType *)action
{
    self = [super init];
    if (self) {
        self.rootView = rootView;
        self.action = action;
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"successfully rendered new button type" message:_action.alertMessage preferredStyle:UIAlertControllerStyleAlert];
    [alertController addAction:[UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil]];
    _action.alertController = alertController;
    [_rootView.acrActionDelegate didFetchUserResponses:nil action:_action];
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

    AlertTarget *target = [[AlertTarget alloc] init:rootView action:newType];

    [button addTarget:target action:@selector(send:) forControlEvents:UIControlEventTouchUpInside];
    [superview addTarget:target];
    return button;
}

@end
