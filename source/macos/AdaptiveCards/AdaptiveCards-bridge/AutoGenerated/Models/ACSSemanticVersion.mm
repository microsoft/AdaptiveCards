// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSSemanticVersion.h"
#import "SemanticVersion.h"


@implementation  ACSSemanticVersion {
    std::shared_ptr<SemanticVersion> mCppObj;
}

- (instancetype _Nonnull)initWithSemanticVersion:(const std::shared_ptr<SemanticVersion>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSNumber * _Nullable)getMajor
{
 
    auto getMajorCpp = mCppObj->GetMajor();
    return [NSNumber numberWithUnsignedInt:getMajorCpp];

}

- (NSNumber * _Nullable)getMinor
{
 
    auto getMinorCpp = mCppObj->GetMinor();
    return [NSNumber numberWithUnsignedInt:getMinorCpp];

}

- (NSNumber * _Nullable)getBuild
{
 
    auto getBuildCpp = mCppObj->GetBuild();
    return [NSNumber numberWithUnsignedInt:getBuildCpp];

}

- (NSNumber * _Nullable)getRevision
{
 
    auto getRevisionCpp = mCppObj->GetRevision();
    return [NSNumber numberWithUnsignedInt:getRevisionCpp];

}


@end
