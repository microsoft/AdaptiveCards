// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSInternalId.h"
#import "BaseElement.h"


@implementation  ACSInternalId {
    std::shared_ptr<InternalId> mCppObj;
}

- (instancetype _Nonnull)initWithInternalId:(const std::shared_ptr<InternalId>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSNumber * _Nullable)hash
{
 
    auto hashCpp = mCppObj->Hash();
    return [NSNumber numberWithUnsignedLongLong:hashCpp];

}


@end
