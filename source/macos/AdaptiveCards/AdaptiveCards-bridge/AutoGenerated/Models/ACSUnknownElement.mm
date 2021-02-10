// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSUnknownElement.h"
#import "../../../../../shared/cpp/ObjectModel/UnknownElement.h"


@implementation  ACSUnknownElement {
    std::shared_ptr<UnknownElement> mCppObj;
}

- (instancetype _Nonnull)initWithUnknownElement:(const std::shared_ptr<UnknownElement>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}


@end
