// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSOpenUrlAction.h"
#import "../../../../../shared/cpp/ObjectModel/OpenUrlAction.h"


@implementation  ACSOpenUrlAction {
    std::shared_ptr<OpenUrlAction> mCppObj;
}

- (instancetype _Nonnull)initWithOpenUrlAction:(const std::shared_ptr<OpenUrlAction>)cppObj
{
    if (self = [super initWithBaseActionElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getUrl
{
 
    auto getUrlCpp = mCppObj->GetUrl();
    return [NSString stringWithUTF8String:getUrlCpp.c_str()];

}

- (void)setUrl:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetUrl(valueCpp);
    
}




@end
