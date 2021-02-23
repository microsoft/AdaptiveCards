#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "SharedAdaptiveCard.h"
#import "BaseInputElement.h"

using namespace AdaptiveCards;
#endif

@class ACSBaseElement;
@class ACSBaseCardElement;
@class ACSBaseActionElement;
@class ACSBaseInputElement;
@class ACSCollectionTypeElement;
@class ACSParseResult;
@class ACSHostConfigParseResult;

@interface BridgeConverter : NSObject

#ifdef __cplusplus
+ (NSString *)getString:(std::string)stringCpp;
+ (std::string)getStringCpp:(NSString *)string;
+ (ACSBaseElement *)convertFromBaseElement:(std::shared_ptr<BaseElement>)baseElementCpp;
+ (ACSBaseCardElement *)convertFromBaseCardElement:(std::shared_ptr<BaseCardElement>)baseCardElementCpp;
+ (ACSBaseActionElement *)convertFromBaseActionElement:(std::shared_ptr<BaseActionElement>)baseActionElementCpp;
+ (ACSBaseInputElement *)convertFromBaseInputElement:(std::shared_ptr<BaseInputElement>)baseInputElementCpp;
+ (ACSCollectionTypeElement *)covertFromCollectionTypeElement:(std::shared_ptr<CollectionTypeElement>)collectionTypeElementCpp;
+ (ACSInline *)convertFromInline:(std::shared_ptr<Inline>)inlineCpp;
#endif
+ (ACSParseResult *)parseAdaptiveCardFromJSON:(NSString *)jsonString;
+ (ACSHostConfigParseResult *)parseHostConfigFromJSON:(NSString *)jsonString;

@end
