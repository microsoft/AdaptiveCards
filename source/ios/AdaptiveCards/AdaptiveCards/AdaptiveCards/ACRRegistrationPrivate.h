#include "ACRRegistration.h"
#include "FeatureRegistration.h"

using namespace AdaptiveCards;

@interface ACOFeatureRegistration ()

- (std::shared_ptr<FeatureRegistration>)getSharedFeatureRegistration;

@end
