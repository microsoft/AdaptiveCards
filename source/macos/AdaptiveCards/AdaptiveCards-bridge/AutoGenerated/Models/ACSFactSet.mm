// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSFact.h"

//cpp includes
#import "Fact.h"


#import "ACSFactSet.h"
#import "FactSet.h"


@implementation  ACSFactSet {
    std::shared_ptr<FactSet> mCppObj;
}

- (instancetype _Nonnull)initWithFactSet:(const std::shared_ptr<FactSet>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSArray<ACSFact *> * _Nonnull)getFacts
{
 
    auto getFactsCpp = mCppObj->GetFacts();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getFactsCpp)
    {
        [objList addObject: [[ACSFact alloc] initWithFact:item]];
    }
    return objList;


}




@end
