// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSErrorStatusCodeConvertor.h"

//cpp includes
#import "Enums.h"


#import "ACSAdaptiveCardParseException.h"
#import "AdaptiveCardParseException.h"


@implementation  ACSAdaptiveCardParseException {
    std::shared_ptr<AdaptiveCardParseException> mCppObj;
}

- (instancetype _Nonnull)initWithAdaptiveCardParseException:(const std::shared_ptr<AdaptiveCardParseException>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)what
{
 
    auto whatCpp = mCppObj->what();
    return [NSString stringWithUTF8String:whatCpp];

}

- (ACSErrorStatusCode)getStatusCode
{
 
    auto getStatusCodeCpp = mCppObj->GetStatusCode();
    return [ACSErrorStatusCodeConvertor convertCpp:getStatusCodeCpp];

}

- (NSString * _Nullable)getReason
{
 
    auto getReasonCpp = mCppObj->GetReason();
    return [NSString stringWithUTF8String:getReasonCpp.c_str()];

}


@end
