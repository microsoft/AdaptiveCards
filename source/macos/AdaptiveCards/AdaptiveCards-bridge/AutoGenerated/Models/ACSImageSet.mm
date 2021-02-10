// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSImage.h"
#import "ACSImageSizeConvertor.h"
#import "ACSRemoteResourceInformationConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/Image.h"
#import "../../../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"


#import "ACSImageSet.h"
#import "../../../../../shared/cpp/ObjectModel/ImageSet.h"


@implementation  ACSImageSet {
    std::shared_ptr<ImageSet> mCppObj;
}

- (instancetype _Nonnull)initWithImageSet:(const std::shared_ptr<ImageSet>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSImageSize)getImageSize
{
 
    auto getImageSizeCpp = mCppObj->GetImageSize();
    return [ACSImageSizeConvertor convertCpp:getImageSizeCpp];

}

- (void)setImageSize:(enum ACSImageSize)value
{
    auto valueCpp = [ACSImageSizeConvertor convertObj:value];
 
    mCppObj->SetImageSize(valueCpp);
    
}

- (NSArray<ACSImage *> * _Nonnull)getImages
{
 
    auto getImagesCpp = mCppObj->GetImages();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getImagesCpp)
    {
        [objList addObject: [[ACSImage alloc] initWithImage:item]];
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
