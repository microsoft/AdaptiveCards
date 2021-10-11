#include "ACRRegistration.h"
#include "FeatureRegistration.h"

using namespace AdaptiveCards;

@interface ACRRegistration ()

- (BOOL)shouldUseResourceResolverForOverridenDefaultElementRenderers:(ACRCardElementType)cardElementType;

- (BOOL)shouldUseResourceResolverForOverridenDefaultActionRenderers:(ACRActionType)actionType;

@end

@interface ACOFeatureRegistration ()

- (std::shared_ptr<FeatureRegistration>)getSharedFeatureRegistration;

@end
