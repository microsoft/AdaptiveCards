//
//  ACRLongPressGestureRecognizerFactory
//  ACRLongPressGestureRecognizerFactory.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "OpenUrlAction.h"
#import "ACRShowCardTarget.h"
#import "ShowCardAction.h"
#import "SubmitAction.h"
#import "ACRAggregateTarget.h"
#import "ACOBaseActionElementPrivate.h"

using namespace AdaptiveCards;

@implementation ACRLongPressGestureRecognizerFactory
// instantiates a target for UILongPressGestureRecognizer object
// and instantiate a tap gesture reconginizer with target, and return it
// when failed, nil is returned
+ (UILongPressGestureRecognizer *)getLongPressGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                             rootViewController:(UIViewController *)vc
                                                     targetView:(UIView *)view
                                                  actionElement:(std::shared_ptr<BaseActionElement> const &)action
                                                         inputs:(NSMutableArray *)inputs
                                                     hostConfig:(ACOHostConfig *)config
{
    if(action != nullptr)
    {
        NSObject<ACRSelectActionDelegate> *target;
        ACRLongPressGestureRecognizerEventHandler *handler = [[ACRLongPressGestureRecognizerEventHandler alloc] init];
        ACOBaseActionElement *actionElement = [[ACOBaseActionElement alloc] initWithBaseActionElement:action];

        switch(action->GetElementType())
        {
            // instantiates a target that handles Submit action
            case ActionType::Submit:
            case ActionType::OpenUrl:
            {
                target = [[ACRAggregateTarget alloc] initWithActionElement:actionElement rootViewController:(ACRViewController *)vc];
                break;
            }
            // instantiates a target that handles ShowCard action
            case ActionType::ShowCard:
            {
                std::shared_ptr<ShowCardAction> showCardAction = std::dynamic_pointer_cast<ShowCardAction>(action);
                // instantiate a ShowCardTarget
                target = [[ACRShowCardTarget alloc] initWithAdaptiveCard:showCardAction->GetCard() config:config superview:viewGroup vc:vc];
                break;
            }
            // everything else is not valid request
            case ActionType::Unsupported: case ActionType::Custom:
            default:
            {
                NSLog(@"Unknown Action Type");
                return nil;
            }
        }

        if(target && handler)
        {
            // add the target to the viewGroup; life time of the target is as long as the viewGroup
            // add the handler to the viewGroup; life time of the target is as long as the viewGroup
            [viewGroup addTarget:target];
            [viewGroup addTarget:handler];
            UILongPressGestureRecognizer *recognizer = [[UILongPressGestureRecognizer alloc] initWithTarget:handler action:@selector(processLongPressGesture:)];
            handler.delegate = target;
            recognizer.delegate = handler;
            recognizer.minimumPressDuration = 0.01;
            recognizer.allowableMovement = 1;
            return recognizer;
        }
    }
    return nil;
}

@end
