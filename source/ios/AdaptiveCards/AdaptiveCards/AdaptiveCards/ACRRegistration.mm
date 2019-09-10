//
//  ACRRegistration
//  ACRRegistration.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRRegistration.h"
#import "ACOBaseActionElement.h"
#import "ACOParseContextPrivate.h"
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
                                             [ACRActionToggleVisibilityRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::ToggleVisibility],
                                             [ACRCustomActionRenderer getInstance], [NSNumber numberWithInt:(int)ActionType::UnknownAction],
                                             nil];

        _elementParserDict = [[NSMutableDictionary alloc] init];
        _actionParserDict = [[NSMutableDictionary alloc] init];

        _actionSetRenderer = [ACRActionSetRenderer getInstance];
        _defaultActionSetRenderer = _actionSetRenderer;

        overridenBaseElementRendererList = [[NSMutableDictionary alloc] init];
        overridenBaseActionRendererList = [[NSMutableDictionary alloc] init];
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

- (void)setActionRenderer:(ACRBaseActionElementRenderer *)renderer cardElementType:(NSNumber *)cardElementType
{
    // custom action must be registered through set custom action renderer method
    // standard actions element enum value must be higher than ACRUnknownAction
    if (cardElementType.longValue > ACRUnknownAction) {
        return;
    }

    if (!renderer) {
        [overridenBaseActionRendererList removeObjectForKey:cardElementType];
    } else {
        [overridenBaseActionRendererList setObject:renderer forKey:cardElementType];
    }
}

- (void)setBaseCardElementRenderer:(ACRBaseCardElementRenderer *)renderer cardElementType:(ACRCardElementType)cardElementType
{
    if (!renderer) {
        [overridenBaseElementRendererList removeObjectForKey:[NSNumber numberWithInteger:cardElementType]];
    } else {
        [overridenBaseElementRendererList setObject:renderer forKey:[NSNumber numberWithInteger:cardElementType]];
    }
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
;
