#ifdef SWIFT_PACKAGE
#import "ACRRegistration.h"
#import "FeatureRegistration.h"
#else
#import <AdaptiveCards/ACRRegistration.h>
#import <AdaptiveCards/FeatureRegistration.h>
#endif

using namespace AdaptiveCards;

@interface ACRRegistration ()

- (BOOL)shouldUseResourceResolverForOverridenDefaultElementRenderers:(ACRCardElementType)cardElementType;

- (BOOL)shouldUseResourceResolverForOverridenDefaultActionRenderers:(ACRActionType)actionType;

@end

@interface ACOFeatureRegistration ()

- (std::shared_ptr<FeatureRegistration>)getSharedFeatureRegistration;

@end
