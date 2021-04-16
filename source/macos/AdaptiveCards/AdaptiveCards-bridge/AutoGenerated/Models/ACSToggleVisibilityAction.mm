// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSToggleVisibilityTarget.h"

//cpp includes
#import "ToggleVisibilityTarget.h"


#import "ACSToggleVisibilityAction.h"
#import "ToggleVisibilityAction.h"


@implementation  ACSToggleVisibilityAction {
    std::shared_ptr<ToggleVisibilityAction> mCppObj;
}

- (instancetype _Nonnull)initWithToggleVisibilityAction:(const std::shared_ptr<ToggleVisibilityAction>)cppObj
{
    if (self = [super initWithBaseActionElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSArray<ACSToggleVisibilityTarget *> * _Nonnull)getTargetElements
{
 
    auto getTarElementsCpp = mCppObj->GetTargetElements();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getTarElementsCpp)
    {
        [objList addObject: [[ACSToggleVisibilityTarget alloc] initWithToggleVisibilityTarget:item]];
    }
    return objList;


}




@end
