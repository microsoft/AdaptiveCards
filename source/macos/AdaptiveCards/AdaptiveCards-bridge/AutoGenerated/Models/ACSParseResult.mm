// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSAdaptiveCard.h"
#import "ACSAdaptiveCardParseWarning.h"

//cpp includes
#import "AdaptiveCardParseWarning.h"
#import "SharedAdaptiveCard.h"


#import "ACSParseResult.h"
#import "ParseResult.h"


@implementation  ACSParseResult {
    std::shared_ptr<ParseResult> mCppObj;
}

- (instancetype _Nonnull)initWithParseResult:(const std::shared_ptr<ParseResult>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSAdaptiveCard * _Nullable)getAdaptiveCard
{
 
    auto getAdaptiveCardCpp = mCppObj->GetAdaptiveCard();
    return [[ACSAdaptiveCard alloc] initWithAdaptiveCard:getAdaptiveCardCpp];

}

- (NSArray<ACSAdaptiveCardParseWarning *> * _Nonnull)getWarnings
{
 
    auto getWarningsCpp = mCppObj->GetWarnings();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getWarningsCpp)
    {
        [objList addObject: [[ACSAdaptiveCardParseWarning alloc] initWithAdaptiveCardParseWarning:item]];
    }
    return objList;


}


@end
