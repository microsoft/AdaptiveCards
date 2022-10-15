//
//  ACRLongPressGestureRecognizerFactory
//  ACRLongPressGestureRecognizerFactory.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRTapGestureRecognizerFactory.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRAggregateTarget.h"
#import "ACRShowCardTarget.h"
#import "ACRToggleVisibilityTarget.h"
#import "ACRUILabel.h"
#import "OpenUrlAction.h"
#import "ShowCardAction.h"
#import "SubmitAction.h"
#import "ToggleVisibilityAction.h"
#import "UtiliOS.h"

using namespace AdaptiveCards;

@implementation ACRTapGestureRecognizerFactory

+ (ACRBaseTarget *)addTapGestureRecognizerToUIView:(UIView<ACRIContentHoldingView> *)viewGroup
                                          rootView:(ACRView *)rootView
                                     recipientView:(UIView *)recipientView
                                     actionElement:(ACOBaseActionElement *)action
                                        hostConfig:(ACOHostConfig *)config
{
    if (action != nullptr) {
        NSObject<ACRSelectActionDelegate> *target;
        if (ACRRenderingStatus::ACROk == buildTarget([rootView getSelectActionsTargetBuilderDirector], action, &target) && viewGroup) {
            UITapGestureRecognizer *recognizer = [ACRTapGestureRecognizerFactory getGestureRecognizer:viewGroup target:target];
            [recipientView addGestureRecognizer:recognizer];
            setAccessibilityTrait(recipientView, action);
            return (ACRBaseTarget *)target;
        }
    }

    return nil;
}

+ (void)addTapGestureRecognizerToUITextView:(UITextView *)textView
                                     target:(NSObject<ACRSelectActionDelegate> *)target
                                   rootView:(ACRView *)rootView
                                 hostConfig:(ACOHostConfig *)config
{
    if (target && textView) {
        UITapGestureRecognizer *recognizer = [[UITapGestureRecognizer alloc] initWithTarget:textView action:@selector(handleInlineAction:)];
        [textView addGestureRecognizer:recognizer];
        textView.userInteractionEnabled = YES;
    }
}

+ (UITapGestureRecognizer *)getGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                          target:(NSObject<ACRSelectActionDelegate> *)target
{
    ACRTapGestureRecognizerEventHandler *handler = [[ACRTapGestureRecognizerEventHandler alloc] init];
    // add the target to the viewGroup; life time of the target is as long as the viewGroup
    // add the handler to the viewGroup; life time of the target is as long as the viewGroup
    [viewGroup addTarget:target];
    [viewGroup addTarget:handler];
    UITapGestureRecognizer *recognizer = [[UITapGestureRecognizer alloc] initWithTarget:handler action:@selector(processTapGesture:)];
    handler.delegate = target;
    recognizer.delegate = handler;
    return recognizer;
}

@end
