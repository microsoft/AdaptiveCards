// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSUnknownAction.h"
#import "UnknownAction.h"


@implementation  ACSUnknownAction {
    std::shared_ptr<UnknownAction> mCppObj;
}

- (instancetype _Nonnull)initWithUnknownAction:(const std::shared_ptr<UnknownAction>)cppObj
{
    if (self = [super initWithBaseActionElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}


@end
