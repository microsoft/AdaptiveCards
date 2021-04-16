// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSAdaptiveCardParseWarning.h"
#import "ACSParseContext.h"
#import "ACSRemoteResourceInformationConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "AdaptiveCardParseWarning.h"
#import "json.h"
#import "ParseContext.h"
#import "RemoteResourceInformation.h"


#import "ACSColumn.h"
#import "Column.h"


@implementation  ACSColumn {
    std::shared_ptr<Column> mCppObj;
}

- (instancetype _Nonnull)initWithColumn:(const std::shared_ptr<Column>)cppObj
{
    if (self = [super initWithCollectionTypeElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}


- (NSString * _Nullable)getWidth
{
 
    auto getWidthCpp = mCppObj->GetWidth();
    return [NSString stringWithUTF8String:getWidthCpp.c_str()];

}

- (void)setWidth:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetWidth(valueCpp);
    
}

- (void)setWidth:(NSString * _Nonnull)value warnings:(NSArray<ACSAdaptiveCardParseWarning *>* _Nonnull)warnings
{
//    auto valueCpp = std::string([value UTF8String]);
//    std::vector<AdaptiveCards::AdaptiveCardParseWarning> warningsVector;
//    for (id warningsObj in warnings)
//    {
//        warningsVector.push_back(// NEED TO INSERT CODE //);
//    }

 
//    mCppObj->SetWidth(valueCpp,warningsVector);
    
}

- (NSNumber * _Nullable)getPixelWidth
{
 
    auto getPixelWidthCpp = mCppObj->GetPixelWidth();
    return [NSNumber numberWithInt:getPixelWidthCpp];

}

- (void)setPixelWidth:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value intValue];
 
    mCppObj->SetPixelWidth(valueCpp);
    
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
