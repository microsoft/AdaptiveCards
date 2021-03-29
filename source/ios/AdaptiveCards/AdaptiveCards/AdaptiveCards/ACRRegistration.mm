//
//  ACRRegistration
//  ACRRegistration.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRRegistration.h"
#import "ACOBaseActionElement.h"
#import "ACOHostConfigPrivate.h"
#import "ACOParseContextPrivate.h"
#import "ACRActionExecuteRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRActionSetRenderer.h"
#import "ACRActionShowCardRenderer.h"
#import "ACRActionSubmitRenderer.h"
#import "ACRActionToggleVisibilityRenderer.h"
#import "ACRColumnRenderer.h"
#import "ACRColumnSetRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRColumnView.h"
#import "ACRContainerRenderer.h"
#import "ACRCustomActionRenderer.h"
#import "ACRCustomRenderer.h"
#import "ACRFactSetRenderer.h"
#import "ACRImageRenderer.h"
#import "ACRImageSetRenderer.h"
#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputDateRenderer.h"
#import "ACRInputNumberRenderer.h"
#import "ACRInputRenderer.h"
#import "ACRInputTimeRenderer.h"
#import "ACRInputToggleRenderer.h"
#import "ACRMediaRenderer.h"
#import "ACRRichTextBlockRenderer.h"
#import "ACRTextBlockRenderer.h"
#import "BaseCardElement.h"
#import "FeatureRegistration.h"
#import "HostConfig.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACRRegistration {
    NSDictionary *typeToRendererDict;
    NSDictionary *actionRendererDict;

    NSMutableDictionary<NSString *, NSObject<ACOIBaseCardElementParser> *> *_elementParserDict;
    NSMutableDictionary<NSString *, NSObject<ACOIBaseActionElementParser> *> *_actionParserDict;
    id<ACRIBaseActionSetRenderer> _actionSetRenderer;
    NSMutableDictionary *overridenBaseElementRendererList;
    NSMutableDictionary *overridenBaseActionRendererList;
    NSMutableSet *_useResourceResolverElementsSet;
    NSMutableSet *_useResourceResolverActionsSet;
    id<ACRIBaseActionSetRenderer> _defaultActionSetRenderer;
    ACOParseContext *_parseContext;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        typeToRendererDict =
            [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                             [ACRMediaRenderer getInstance], [NSNumber numberWithInt:(int)[ACRMediaRenderer elemType]],
                                             [ACRImageRenderer getInstance], [NSNumber numberWithInt:(int)[ACRImageRenderer elemType]],
                                             [ACRImageSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRImageSetRenderer elemType]],
                                             [ACRTextBlockRenderer getInstance], [NSNumber numberWithInt:(int)[ACRTextBlockRenderer elemType]],
                                             [ACRRichTextBlockRenderer getInstance], [NSNumber numberWithInt:(int)[ACRRichTextBlockRenderer elemType]],
                                             [ACRInputRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputRenderer elemType]],
                                             [ACRInputToggleRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputToggleRenderer elemType]],
                                             [ACRInputChoiceSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputChoiceSetRenderer elemType]],
                                             [ACRInputDateRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputDateRenderer elemType]],
                                             [ACRInputTimeRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputTimeRenderer elemType]],
                                             [ACRInputNumberRenderer getInstance], [NSNumber numberWithInt:(int)[ACRInputNumberRenderer elemType]],
                                             [ACRFactSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRFactSetRenderer elemType]],
                                             [ACRContainerRenderer getInstance], [NSNumber numberWithInt:(int)[ACRContainerRenderer elemType]],
                                             [ACRColumnSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRColumnSetRenderer elemType]],
                                             [ACRColumnRenderer getInstance], [NSNumber numberWithInt:(int)[ACRColumnRenderer elemType]],
                                             [ACRActionSetRenderer getInstance], [NSNumber numberWithInt:(int)[ACRActionSetRenderer elemType]],
                                             [ACRCustomRenderer getInstance], [NSNumber numberWithInt:(int)[ACRCustomRenderer elemType]],
                                             nil];
        actionRendererDict =
            [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                             [ACRActionOpenURLRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::OpenUrl],
                                             [ACRActionShowCardRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::ShowCard],
                                             [ACRActionSubmitRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::Submit],
                                             [ACRActionExecuteRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::Execute],
                                             [ACRActionToggleVisibilityRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::ToggleVisibility],
                                             [ACRCustomActionRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::UnknownAction],
                                             nil];

        _elementParserDict = [[NSMutableDictionary alloc] init];
        _actionParserDict = [[NSMutableDictionary alloc] init];

        _actionSetRenderer = [ACRActionSetRenderer getInstance];
        _defaultActionSetRenderer = _actionSetRenderer;

        overridenBaseElementRendererList = [[NSMutableDictionary alloc] init];
        overridenBaseActionRendererList = [[NSMutableDictionary alloc] init];

        _useResourceResolverElementsSet = [[NSMutableSet alloc] init];
        _useResourceResolverActionsSet = [[NSMutableSet alloc] init];
    }
    return self;
}

+ (ACRRegistration *)getInstance
{
    static ACRRegistration *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *)cardElementType
{
    if ([overridenBaseElementRendererList objectForKey:cardElementType]) {
        return [overridenBaseElementRendererList objectForKey:cardElementType];
    }
    return [typeToRendererDict objectForKey:cardElementType];
}

- (ACRBaseActionElementRenderer *)getActionRendererByType:(ACRActionType)actionElementType
{
    return [self getActionRenderer:[NSNumber numberWithLong:actionElementType]];
}

- (ACRBaseActionElementRenderer *)getActionRenderer:(NSNumber *)cardElementType
{
    if ([overridenBaseActionRendererList objectForKey:cardElementType]) {
        return [overridenBaseActionRendererList objectForKey:cardElementType];
    }
    return [actionRendererDict objectForKey:cardElementType];
}

- (id<ACRIBaseActionSetRenderer>)getActionSetRenderer
{
    return (!_actionSetRenderer) ? _defaultActionSetRenderer : _actionSetRenderer;
}

- (void)setActionSetRenderer:(id<ACRIBaseActionSetRenderer>)actionsetRenderer
{
    _actionSetRenderer = actionsetRenderer;
}

- (void)setActionRenderer:(ACRBaseActionElementRenderer *)renderer actionElementType:(ACRActionType)actionElementType useResourceResolver:(BOOL)doUse
{
    // custom action must be registered through set custom action renderer method
    // standard actions element enum value must be higher than ACRUnknownAction
    if (actionElementType > ACRUnknownAction) {
        return;
    }
    NSNumber *key = @(actionElementType);
    if (!renderer) {
        [overridenBaseActionRendererList removeObjectForKey:key];
        [self removeElementFromResourceResolverSet:key isAction:YES];
    } else {
        [overridenBaseActionRendererList setObject:renderer forKey:key];
        [self addElementToResourceResolverSet:key isAction:YES doUse:doUse];
    }
}

- (void)setActionRenderer:(ACRBaseActionElementRenderer *)renderer actionElementType:(ACRActionType)actionElementType
{
    [self setActionRenderer:renderer actionElementType:actionElementType useResourceResolver:NO];
}

- (void)setActionRenderer:(ACRBaseActionElementRenderer *)renderer cardElementType:(NSNumber *)cardElementType
{
    [self setActionRenderer:renderer actionElementType:(ACRActionType)cardElementType.intValue useResourceResolver:NO];
}

- (void)removeElementFromResourceResolverSet:(NSNumber *)key isAction:(BOOL)isAction
{
    if (isAction) {
        if ([_useResourceResolverActionsSet containsObject:key]) {
            [_useResourceResolverActionsSet removeObject:key];
        }
    } else {
        if ([_useResourceResolverElementsSet containsObject:key]) {
            [_useResourceResolverElementsSet removeObject:key];
        }
    }
}

- (void)addElementToResourceResolverSet:(NSNumber *)key isAction:(BOOL)isAction doUse:(BOOL)doUse
{
    if (!doUse) {
        return;
    }
    if (isAction) {
        [_useResourceResolverActionsSet addObject:key];
    } else {
        [_useResourceResolverElementsSet addObject:key];
    }
}

- (void)setBaseCardElementRenderer:(ACRBaseCardElementRenderer *)renderer cardElementType:(ACRCardElementType)cardElementType useResourceResolver:(BOOL)doUse
{
    NSNumber *key = @(cardElementType);
    if (!renderer) {
        [overridenBaseElementRendererList removeObjectForKey:key];
        [self removeElementFromResourceResolverSet:key isAction:NO];
    } else {
        [overridenBaseElementRendererList setObject:renderer forKey:key];
        [self addElementToResourceResolverSet:key isAction:NO doUse:doUse];
    }
}

- (void)setBaseCardElementRenderer:(ACRBaseCardElementRenderer *)renderer cardElementType:(ACRCardElementType)cardElementType
{
    [self setBaseCardElementRenderer:renderer cardElementType:cardElementType useResourceResolver:NO];
}

- (void)setCustomElementParser:(NSObject<ACOIBaseCardElementParser> *)customElementParser
{
    ACRCustomRenderer *customRenderer = [ACRCustomRenderer getInstance];
    customRenderer.customElementParser = customElementParser;
}

- (void)setCustomElementParser:(NSObject<ACOIBaseCardElementParser> *)parser key:(NSString *)key
{
    if (!_parseContext) {
        _parseContext = [[ACOParseContext alloc] init];
    }
    if (parser && key) {
        _elementParserDict[key] = parser;
    }
}

- (NSObject<ACOIBaseCardElementParser> *)getCustomElementParser:(NSString *)key
{
    return _elementParserDict[key];
}

- (void)setCustomElementRenderer:(ACRBaseCardElementRenderer *)renderer key:(NSString *)key
{
    if (key) {
        if (renderer) {
            [overridenBaseElementRendererList setObject:renderer forKey:[NSNumber numberWithLong:key.hash]];
        } else {
            [overridenBaseElementRendererList removeObjectForKey:[NSNumber numberWithLong:key.hash]];
        }
    }
}

- (void)setCustomActionElementParser:(NSObject<ACOIBaseActionElementParser> *)parser key:(NSString *)key
{
    if (!_parseContext) {
        _parseContext = [[ACOParseContext alloc] init];
    }
    if (parser && key) {
        _actionParserDict[key] = parser;
    }
}

- (NSObject<ACOIBaseActionElementParser> *)getCustomActionElementParser:(NSString *)key
{
    return _actionParserDict[key];
}

- (ACOParseContext *)getParseContext
{
    return _parseContext;
}

- (void)setCustomActionRenderer:(ACRBaseActionElementRenderer *)renderer key:(NSString *)key
{
    if (key) {
        if (renderer) {
            [overridenBaseActionRendererList setObject:renderer forKey:[NSNumber numberWithLong:key.hash]];
        } else {
            [overridenBaseActionRendererList removeObjectForKey:[NSNumber numberWithLong:key.hash]];
        }
    }
}

- (BOOL)isActionRendererOverridden:(NSNumber *)cardElementType
{
    if ([overridenBaseActionRendererList objectForKey:cardElementType]) {
        return YES;
    }
    return NO;
}

- (BOOL)isElementRendererOverridden:(ACRCardElementType)cardElementType
{
    if ([overridenBaseElementRendererList objectForKey:[NSNumber numberWithInteger:cardElementType]]) {
        return YES;
    }
    return NO;
}

- (BOOL)shouldUseResourceResolverForOverridenDefaultElementRenderers:(ACRCardElementType)cardElementType
{
    if ([self isElementRendererOverridden:cardElementType]) {
        return [self checkResourceResolverSet:@(cardElementType) isAction:NO];
    } else {
        return YES;
    }
}

- (BOOL)shouldUseResourceResolverForOverridenDefaultActionRenderers:(ACRActionType)actionType
{
    NSNumber *key = @(actionType);
    if ([self isActionRendererOverridden:key]) {
        return [self checkResourceResolverSet:key isAction:YES];
    } else {
        return YES;
    }
}

- (BOOL)checkResourceResolverSet:(NSNumber *)key isAction:(BOOL)isAction
{
    return (isAction) ? [_useResourceResolverActionsSet containsObject:key] : [_useResourceResolverElementsSet containsObject:key];
}

@end

@implementation ACOFeatureRegistration {
    std::shared_ptr<FeatureRegistration> _featureRegistration;
}


- (instancetype)init
{
    self = [super init];
    if (self) {
        _featureRegistration = std::make_shared<FeatureRegistration>();
    }
    return self;
}

+ (ACOFeatureRegistration *)getInstance
{
    static ACOFeatureRegistration *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (void)addFeature:(NSString *)featureName featureVersion:(NSString *)version
{
    const std::string cstringFN = [featureName cStringUsingEncoding:NSUTF8StringEncoding];
    const std::string cstringFV = [version cStringUsingEncoding:NSUTF8StringEncoding];
    _featureRegistration->AddFeature(cstringFN, cstringFV);
}

- (void)removeFeature:(NSString *)featureName
{
    const std::string cstringFN = [featureName cStringUsingEncoding:NSUTF8StringEncoding];
    _featureRegistration->RemoveFeature(cstringFN);
}

- (NSString *)getFeatureVersion:(NSString *)featureName
{
    const std::string cstringFN = [featureName cStringUsingEncoding:NSUTF8StringEncoding];
    std::string version = _featureRegistration->GetFeatureVersion(cstringFN);
    return [NSString stringWithCString:version.c_str() encoding:NSUTF8StringEncoding];
}
- (std::shared_ptr<FeatureRegistration>)getSharedFeatureRegistration
{
    return _featureRegistration;
}
@end


@interface ACRActionTargetBuildersList : NSObject

@property ACRTargetCapability capability;

- (instancetype)init:(ACRTargetCapability)capability;

@end

@implementation ACRActionTargetBuildersList {
    NSDictionary<NSNumber *, ACRTargetBuilder *> *_builders;
    NSMutableDictionary<NSNumber *, ACRTargetBuilder *> *_overwrittenBuilders;
}

- (instancetype)init:(ACRTargetCapability)capability
{
    NSNumber *openUrl = [ACOBaseActionElement getKey:ACROpenUrl];
    NSNumber *submit = [ACOBaseActionElement getKey:ACRSubmit];
    NSNumber *showcard = [ACOBaseActionElement getKey:ACRShowCard];
    NSNumber *toggle = [ACOBaseActionElement getKey:ACRToggleVisibility];
    NSNumber *unknown = [ACOBaseActionElement getKey:ACRUnknownAction];
    NSNumber *execute = [ACOBaseActionElement getKey:ACRExecute];

    _overwrittenBuilders = [[NSMutableDictionary alloc] init];

    // target capability lists supported events and corresponding target builders
    switch (capability) {
        case ACRAction:
            _builders = @{
                openUrl : [ACRAggregateTargetBuilder getInstance],
                submit : [ACRAggregateTargetBuilder getInstance],
                execute : [ACRAggregateTargetBuilder getInstance],
                showcard : [ACRShowCardTargetBuilder getInstance],
                toggle : [ACRToggleVisibilityTargetBuilder getInstance]
            };
            break;
        case ACRSelectAction:
            _builders = @{
                openUrl : [ACRAggregateTargetBuilder getInstance],
                submit : [ACRAggregateTargetBuilder getInstance],
                execute : [ACRAggregateTargetBuilder getInstance],
                toggle : [ACRToggleVisibilityTargetBuilder getInstance],
                unknown : [ACRUnknownActionTargetBuilder getInstance]
            };
            break;
        case ACRQuickReply:
            _builders = @{
                openUrl : [ACRAggregateTargetBuilder getInstance],
                submit : [ACRAggregateTargetBuilder getInstance],
                execute : [ACRAggregateTargetBuilder getInstance],
                toggle : [ACRToggleVisibilityTargetBuilder getInstance]
            };
            break;
    }

    return self;
}

- (id<ACRITargetBuilder> _Nullable)getTargetBuilder:(ACRActionType)actionElementType
{
    NSNumber *key = [ACOBaseActionElement getKey:actionElementType];
    if ([_overwrittenBuilders objectForKey:key]) {
        return [_overwrittenBuilders objectForKey:key];
    }
    return [_builders objectForKey:key];
}
- (void)setTargetBuilder:(ACRTargetBuilder *_Nullable)targetBuilder actionElementType:(ACRActionType)actionElementType
{
    NSNumber *key = [ACOBaseActionElement getKey:actionElementType];
    if (!targetBuilder) {
        [_overwrittenBuilders removeObjectForKey:key];
    } else {
        [_overwrittenBuilders setObject:targetBuilder forKey:key];
    }
}

@end

@implementation
    ACRTargetBuilderRegistration {
    ACRActionTargetBuildersList *_actionsTargetBuildersList;
    ACRActionTargetBuildersList *_selectActionsTargetBuildersList;
    ACRActionTargetBuildersList *_quickReplyTargetBuildersList;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _actionsTargetBuildersList = [[ACRActionTargetBuildersList alloc] init:ACRAction];
        _selectActionsTargetBuildersList = [[ACRActionTargetBuildersList alloc] init:ACRSelectAction];
        _quickReplyTargetBuildersList = [[ACRActionTargetBuildersList alloc] init:ACRQuickReply];
    }
    return self;
}

+ (ACRTargetBuilderRegistration *_Nonnull)getInstance
{
    static ACRTargetBuilderRegistration *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (ACRActionTargetBuildersList *_Nullable)getActionTargetBuildersList:(ACRTargetCapability)capability
{
    if (capability == ACRAction) {
        return _actionsTargetBuildersList;
    } else if (capability == ACRSelectAction) {
        return _selectActionsTargetBuildersList;
    } else if (capability == ACRQuickReply) {
        return _quickReplyTargetBuildersList;
    } else {
        return nil;
    }
}

- (id<ACRITargetBuilder> _Nullable)getTargetBuilder:(ACRActionType)actionElementType capability:(ACRTargetCapability)capability
{
    ACRActionTargetBuildersList *buildersList = [self getActionTargetBuildersList:capability];
    if (!buildersList) {
        return nil;
    }

    return [buildersList getTargetBuilder:actionElementType];
}

- (void)setTargetBuilder:(ACRTargetBuilder *_Nullable)targetBuilder actionElementType:(ACRActionType)actionElementType capability:(ACRTargetCapability)capability;
{
    // custom action must be registered through set custom action renderer method
    // standard actions element enum value must be higher than ACRUnknownAction
    if (actionElementType > ACRUnknownAction) {
        return;
    }

    ACRActionTargetBuildersList *buildersList = [self getActionTargetBuildersList:capability];
    if (!buildersList) {
        return;
    }

    [buildersList setTargetBuilder:targetBuilder actionElementType:actionElementType];
}

@end
