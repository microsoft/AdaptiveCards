// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSWarningStatusCodeConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSAdaptiveCardParseWarning.h"
#import "../../../../../shared/cpp/ObjectModel/AdaptiveCardParseWarning.h"


@implementation  ACSAdaptiveCardParseWarning {
    std::shared_ptr<AdaptiveCardParseWarning> mCppObj;
}

- (instancetype _Nonnull)initWithAdaptiveCardParseWarning:(const std::shared_ptr<AdaptiveCardParseWarning>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSWarningStatusCode)getStatusCode
{
 
    auto getStatusCodeCpp = mCppObj->GetStatusCode();
    return [ACSWarningStatusCodeConvertor convertCpp:getStatusCodeCpp];

}

- (NSString * _Nullable)getReason
{
 
    auto getReasonCpp = mCppObj->GetReason();
    return [NSString stringWithUTF8String:getReasonCpp.c_str()];

}


@end
