//
//  ACRLongPressGestureRecognizerFactory
//  ACRLongPressGestureRecognizerFactory.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRLongPressGestureRecognizerFactory.h"
#import "OpenUrlAction.h"
#import "ACRShowCardTarget.h"
#import "ACRToggleVisibilityTarget.h"
#import "ShowCardAction.h"
#import "SubmitAction.h"
#import "ToggleVisibilityAction.h"
#import "ACRAggregateTarget.h"
#import "ACOBaseActionElementPrivate.h"

using namespace AdaptiveCards;

@implementation ACRLongPressGestureRecognizerFactory
// instantiates a target for UILongPressGestureRecognizer object
// and instantiate a tap gesture reconginizer with target, and return it
// when failed, nil is returned
+ (void)addLongPressGestureRecognizerToUIView:(UIView<ACRIContentHoldingView> *)viewGroup
                                     rootView:(ACRView *)rootView
                                recipientView:(UIView *)recipientView
                                actionElement:(std::shared_ptr<BaseActionElement> const &)action
                                   hostConfig:(ACOHostConfig *)config
{
    if(action != nullptr){
        NSObject<ACRSelectActionDelegate> *target = nil;
        ACOBaseActionElement *actionElement = [[ACOBaseActionElement alloc] initWithBaseActionElement:action];

        switch(action->GetElementType()) {
            // instantiates a target that handles Submit action
            case ActionType::Submit:
            case ActionType::OpenUrl:
            {
                target = [[ACRAggregateTarget alloc] initWithActionElement:actionElement rootView:rootView];
                break;
            }
            // instantiates a target that handles ShowCard action
            case ActionType::ShowCard:
            {
                std::shared_ptr<ShowCardAction> showCardAction = std::dynamic_pointer_cast<ShowCardAction>(action);
                // instantiate a ShowCardTarget
                target = [[ACRShowCardTarget alloc] initWithActionElement:showCardAction config:config superview:viewGroup rootView:rootView button:nil];
                break;
            }
            case ActionType::ToggleVisibility:
            {
                std::shared_ptr<ToggleVisibilityAction> toggleAction = std::dynamic_pointer_cast<ToggleVisibilityAction>(action);
                
                target = [[ACRToggleVisibilityTarget alloc]
                             initWithActionElement:toggleAction config:config rootView:rootView];
                break;
            }
            // everything else is not valid request
            case ActionType::Unsupported: case ActionType::Custom:
            default:
            {
                NSLog(@"Unknown Action Type");
            }
        }

        if(target && viewGroup){
            UILongPressGestureRecognizer *recognizer = [ACRLongPressGestureRecognizerFactory getGestureRecognizer:viewGroup target:target];
            [recipientView addGestureRecognizer:recognizer];
            recipientView.userInteractionEnabled = YES;
        }
    }
}

+ (UILongPressGestureRecognizer *)getGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                                target:(NSObject<ACRSelectActionDelegate> *)target
{
    ACRLongPressGestureRecognizerEventHandler *handler = [[ACRLongPressGestureRecognizerEventHandler alloc] init];
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

@end
