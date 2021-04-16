// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSDateTimePreparsedTokenFormatConvertor.h"

//cpp includes
#import "Enums.h"


#import "ACSDateTimePreparsedToken.h"
#import "DateTimePreparsedToken.h"


@implementation  ACSDateTimePreparsedToken {
    std::shared_ptr<DateTimePreparsedToken> mCppObj;
}

- (instancetype _Nonnull)initWithDateTimePreparsedToken:(const std::shared_ptr<DateTimePreparsedToken>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getText
{
 
    auto getTextCpp = mCppObj->GetText();
    return [NSString stringWithUTF8String:getTextCpp.c_str()];

}

- (ACSDateTimePreparsedTokenFormat)getFormat
{
 
    auto getFormatCpp = mCppObj->GetFormat();
    return [ACSDateTimePreparsedTokenFormatConvertor convertCpp:getFormatCpp];

}

- (NSNumber * _Nullable)getDay
{
 
    auto getDayCpp = mCppObj->GetDay();
    return [NSNumber numberWithInt:getDayCpp];

}

- (NSNumber * _Nullable)getMonth
{
 
    auto getMonthCpp = mCppObj->GetMonth();
    return [NSNumber numberWithInt:getMonthCpp];

}

- (NSNumber * _Nullable)getYear
{
 
    auto getYearCpp = mCppObj->GetYear();
    return [NSNumber numberWithInt:getYearCpp];

}


@end
