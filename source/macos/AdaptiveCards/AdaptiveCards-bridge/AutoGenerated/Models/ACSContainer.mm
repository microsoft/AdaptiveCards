// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSParseContext.h"
#import "ACSRemoteResourceInformationConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "json.h"
#import "ParseContext.h"
#import "RemoteResourceInformation.h"


#import "ACSContainer.h"
#import "Container.h"


@implementation  ACSContainer {
    std::shared_ptr<Container> mCppObj;
}

- (instancetype _Nonnull)initWithContainer:(const std::shared_ptr<Container>)cppObj
{
    if (self = [super initWithCollectionTypeElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}


- (NSArray<ACSBaseCardElement *> * _Nonnull)getItems
{
 
    auto getItemsCpp = mCppObj->GetItems();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getItemsCpp)
    {
        [objList addObject: [BridgeConverter convertFromBaseCardElement:item]];
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
