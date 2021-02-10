// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSDateTimePreparser.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/DateTimePreparser.h"


#import "ACSFact.h"
#import "../../../../../shared/cpp/ObjectModel/Fact.h"


@implementation  ACSFact {
    std::shared_ptr<Fact> mCppObj;
}

- (instancetype _Nonnull)initWithFact:(const std::shared_ptr<Fact>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getTitle
{
 
    auto getTitleCpp = mCppObj->GetTitle();
    return [NSString stringWithUTF8String:getTitleCpp.c_str()];

}

- (void)setTitle:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetTitle(valueCpp);
    
}

- (NSString * _Nullable)getValue
{
 
    auto getValueCpp = mCppObj->GetValue();
    return [NSString stringWithUTF8String:getValueCpp.c_str()];

}

- (void)setValue:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetValue(valueCpp);
    
}

- (ACSDateTimePreparser * _Nullable)getTitleForDateParsing
{
 
    auto getTitleForDateParsingCpp = mCppObj->GetTitleForDateParsing();
//    return [[ACSDateTimePreparser alloc] initWithDateTimePreparser:getTitleForDateParsingCpp];
    return [[ACSDateTimePreparser alloc] init];

}

- (ACSDateTimePreparser * _Nullable)getValueForDateParsing
{
 
    auto getValueForDateParsingCpp = mCppObj->GetValueForDateParsing();
//    return [[ACSDateTimePreparser alloc] initWithDateTimePreparser:getValueForDateParsingCpp];
    return [[ACSDateTimePreparser alloc] init];

}

- (void)setLanguage:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetLanguage(valueCpp);
    
}

- (NSString * _Nullable)getLanguage
{
 
    auto getLanguageCpp = mCppObj->GetLanguage();
    return [NSString stringWithUTF8String:getLanguageCpp.c_str()];

}


@end
