// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSColumn.h"
#import "ACSParseContext.h"
#import "ACSRemoteResourceInformationConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Column.h"
#import "../../../../../shared/cpp/ObjectModel/json/json.h"
#import "../../../../../shared/cpp/ObjectModel/ParseContext.h"
#import "../../../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"


#import "ACSColumnSet.h"
#import "../../../../../shared/cpp/ObjectModel/ColumnSet.h"


@implementation  ACSColumnSet {
    std::shared_ptr<ColumnSet> mCppObj;
}

- (instancetype _Nonnull)initWithColumnSet:(const std::shared_ptr<ColumnSet>)cppObj
{
    if (self = [super initWithCollectionTypeElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}


- (NSArray<ACSColumn *> * _Nonnull)getColumns
{
 
    auto getColumnsCpp = mCppObj->GetColumns();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getColumnsCpp)
    {
        [objList addObject: [[ACSColumn alloc] initWithColumn:item]];
    }
    return objList;


}


- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo
{
    std::vector<AdaptiveCards::RemoteResourceInformation> resourceInfoVector;
    for (id resourceInfoObj in resourceInfo)
    {
        resourceInfoVector.push_back([ACSRemoteResourceInformationConvertor convertObj:resourceInfoObj]);
    }

 
    mCppObj->GetResourceInformation(resourceInfoVector);
    
}




@end
