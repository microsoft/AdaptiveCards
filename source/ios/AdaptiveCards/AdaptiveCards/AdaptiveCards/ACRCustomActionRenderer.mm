//
//  ACRCustomActionRenderer
//  ACRCustomActionRenderer.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACRCustomActionRenderer.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRRegistration.h"
#import "SharedAdaptiveCard.h"
#import "UnknownAction.h"
#import "UtiliOS.h"

// this renderer is entry point to custom parsing and rendering registered with host
// it will call custom parsing to deserialize json to object, then the object is renderred by calling
// the appropriate custom renderer
@implementation ACRCustomActionRenderer

+ (ACRCustomActionRenderer *)getInstance
{
    static ACRCustomActionRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRActionType)elemType
{
    return ACRUnknownAction;
}

- (UIButton *)renderButton:(ACRView *)view
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<UnknownAction> unknownAction = std::dynamic_pointer_cast<UnknownAction>([acoElem element]);
    // we get back deserialized action object back by running's host's registered parser
    ACOBaseActionElement *customAction = deserializeUnknowActionToCustomAction(unknownAction);
    if (customAction) {
        ACRRegistration *reg = [ACRRegistration getInstance];
        NSString *type = [NSString stringWithCString:unknownAction->GetElementTypeString().c_str() encoding:NSUTF8StringEncoding];

        ACRBaseActionElementRenderer *renderer = [reg getActionRenderer:[NSNumber numberWithLong:type.hash]];

        if (renderer) {
            // render a button by calling custom renderer
            return [renderer renderButton:view inputs:inputs superview:superview baseActionElement:customAction hostConfig:acoConfig];
        }
    }
    return nil;
}

@end
