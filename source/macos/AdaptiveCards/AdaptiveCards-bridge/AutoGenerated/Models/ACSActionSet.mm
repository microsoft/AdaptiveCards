// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSActionSet.h"
#import "../../../../../shared/cpp/ObjectModel/ActionSet.h"
#import "ACSHorizontalAlignmentConvertor.h"


@implementation  ACSActionSet {
    std::shared_ptr<ActionSet> mCppObj;
}

- (instancetype _Nonnull)initWithActionSet:(const std::shared_ptr<ActionSet>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSArray<ACSBaseActionElement *> * _Nonnull)getActions
{
 
    auto getActionsCpp = mCppObj->GetActions();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getActionsCpp)
    {
        [objList addObject: [BridgeConverter convertFromBaseActionElement:item]];
    }
    return objList;


}

- (ACSHorizontalAlignment)getHorizontalAlignment
{

    auto getHorizontalAlignmentCpp = mCppObj->GetHorizontalAlignment();
    return [ACSHorizontalAlignmentConvertor convertCpp:getHorizontalAlignmentCpp];

}

- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value
{
    auto valueCpp = [ACSHorizontalAlignmentConvertor convertObj:value];

    mCppObj->SetHorizontalAlignment(valueCpp);

}

@end
