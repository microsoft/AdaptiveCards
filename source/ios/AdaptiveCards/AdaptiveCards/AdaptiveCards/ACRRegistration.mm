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
#import "ACRColumnSetView.h"
#import "ACRImageRenderer.h"
#import "ACRImageSetRenderer.h"
#import "ACRMediaRenderer.h"
#import "ACRTextBlockRenderer.h"
#import "ACRInputRenderer.h"
#import "ACRInputToggleRenderer.h"
#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputDateRenderer.h"
#import "ACRInputTimeRenderer.h"
#import "ACRInputNumberRenderer.h"
#import "ACRFactSetRenderer.h"
#import "ACRContainerRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRColumnRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRActionShowCardRenderer.h"
#import "ACRActionSubmitRenderer.h"
#import "ACRActionSetRenderer.h"
#import "ACRCustomRenderer.h"
#import "BaseCardElement.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACRRegistration
{
    NSDictionary *typeToRendererDict;
    NSDictionary *actionRendererDict;
    id<ACRIBaseActionSetRenderer> _actionSetRenderer;
    NSMutableDictionary *overridenBaseElementRendererList;
    NSMutableDictionary *overridenBaseActionRendererList;
    id<ACRIBaseActionSetRenderer> _defaultActionSetRenderer;
}

- (instancetype) init
{
    self = [super init];
    if(self)
    {
        typeToRendererDict =
            [[NSMutableDictionary alloc] initWithObjectsAndKeys:
             [ACRMediaRenderer getInstance],      [NSNumber numberWithInt:(int)[ACRMediaRenderer elemType]],
             [ACRImageRenderer getInstance],      [NSNumber numberWithInt:(int)[ACRImageRenderer elemType]],
             [ACRImageSetRenderer getInstance],   [NSNumber numberWithInt:(int)[ACRImageSetRenderer elemType]],
             [ACRTextBlockRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRTextBlockRenderer elemType]],
             [ACRInputRenderer     getInstance],  [NSNumber numberWithInt:(int)[ACRInputRenderer elemType]],
             [ACRInputToggleRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputToggleRenderer elemType]],
             [ACRInputChoiceSetRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputChoiceSetRenderer elemType]],
             [ACRInputDateRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRInputDateRenderer elemType]],
             [ACRInputTimeRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRInputTimeRenderer elemType]],
             [ACRInputNumberRenderer getInstance],[NSNumber numberWithInt:(int)[ACRInputNumberRenderer elemType]],
             [ACRFactSetRenderer getInstance],    [NSNumber numberWithInt:(int)[ACRFactSetRenderer elemType]],
             [ACRContainerRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRContainerRenderer elemType]],
             [ACRColumnSetRenderer getInstance],  [NSNumber numberWithInt:(int)[ACRColumnSetRenderer elemType]],
             [ACRColumnRenderer getInstance],     [NSNumber numberWithInt:(int)[ACRColumnRenderer elemType]],
             [ACRCustomRenderer getInstance],     [NSNumber numberWithInt:(int)[ACRCustomRenderer elemType]],
             nil];
        actionRendererDict =
            [[NSMutableDictionary alloc] initWithObjectsAndKeys:
             [ACRActionOpenURLRenderer  getInstance], [NSNumber numberWithInt:(int)ActionType::OpenUrl],
             [ACRActionShowCardRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::ShowCard],
             [ACRActionSubmitRenderer   getInstance], [NSNumber numberWithInt:(int)ActionType::Submit],
             nil];
        _actionSetRenderer = [ACRActionSetRenderer getInstance];
        _defaultActionSetRenderer = _actionSetRenderer;
        
        overridenBaseElementRendererList = [[NSMutableDictionary alloc] init];
        overridenBaseActionRendererList  = [[NSMutableDictionary alloc] init];
    }
    return self;
}

+ (ACRRegistration *)getInstance
{
    static ACRRegistration *singletonInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{singletonInstance = [[self alloc] init];});
    return singletonInstance;
}

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *)cardElementType
{
    if([overridenBaseElementRendererList objectForKey:cardElementType]){
        return [overridenBaseElementRendererList objectForKey:cardElementType];
    }
    return [typeToRendererDict objectForKey:cardElementType];
}

- (ACRBaseActionElementRenderer *)getActionRenderer:(NSNumber *)cardElementType
{
    if([overridenBaseActionRendererList objectForKey:cardElementType]){
        return [overridenBaseActionRendererList objectForKey:cardElementType];
    }
    return [actionRendererDict objectForKey:cardElementType];
}

- (id<ACRIBaseActionSetRenderer>)getActionSetRenderer
{
    return (!_actionSetRenderer)? _defaultActionSetRenderer : _actionSetRenderer;
}

- (void)setActionSetRenderer:(id<ACRIBaseActionSetRenderer>)actionsetRenderer
{
    _actionSetRenderer = actionsetRenderer;
}

- (void) setActionRenderer:(ACRBaseActionElementRenderer *)renderer cardElementType:(NSNumber *)cardElementType
{
    if(!renderer) {
        [overridenBaseActionRendererList removeObjectForKey:cardElementType];
    } else {
        [overridenBaseActionRendererList setObject:renderer forKey:cardElementType];
    }
}

- (void) setBaseCardElementRenderer:(ACRBaseCardElementRenderer *)renderer cardElementType:(ACRCardElementType)cardElementType
{
    if(!renderer) {
        [overridenBaseElementRendererList removeObjectForKey:[NSNumber numberWithInteger:cardElementType]];
    } else {
        [overridenBaseElementRendererList setObject:renderer forKey:[NSNumber numberWithInteger:cardElementType]];
    }
}

- (void) setCustomElementParser:(NSObject<ACOIBaseCardElementParser> *)customElementParser
{
    ACRCustomRenderer *customRenderer = [ACRCustomRenderer getInstance];
    customRenderer.customElementParser = customElementParser;
}

- (BOOL) isActionRendererOverriden:(NSNumber *)cardElementType
{
    if([overridenBaseActionRendererList objectForKey:cardElementType]){
        return YES;
    }
    return NO;
}

- (BOOL) isElementRendererOverriden:(ACRCardElementType)cardElementType
{
    if([overridenBaseElementRendererList objectForKey:[NSNumber numberWithInteger:cardElementType]]){
        return YES;
    }
    return NO;
}

@end
