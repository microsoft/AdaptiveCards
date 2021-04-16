// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSDateTimePreparsedToken.h"
#import "ACSDateTimePreparsedTokenFormatConvertor.h"

//cpp includes
#import "DateTimePreparsedToken.h"
#import "Enums.h"


#import "ACSDateTimePreparser.h"
#import "DateTimePreparser.h"


@implementation  ACSDateTimePreparser {
    std::shared_ptr<DateTimePreparser> mCppObj;
}

- (instancetype _Nonnull)initWithDateTimePreparser:(const std::shared_ptr<DateTimePreparser>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSArray<ACSDateTimePreparsedToken *> * _Nonnull)getTextTokens
{
 
    auto getTextTokensCpp = mCppObj->GetTextTokens();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getTextTokensCpp)
    {
        [objList addObject: [[ACSDateTimePreparsedToken alloc] initWithDateTimePreparsedToken:item]];
    }
    return objList;


}

- (bool)hasDateTokens
{
 
    auto hasDateTokensCpp = mCppObj->HasDateTokens();
    return hasDateTokensCpp;

}


@end
