// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMediaSource.h"
#import "ACSRemoteResourceInformationConvertor.h"

//cpp includes
#import "MediaSource.h"
#import "RemoteResourceInformation.h"


#import "ACSMedia.h"
#import "Media.h"


@implementation  ACSMedia {
    std::shared_ptr<Media> mCppObj;
}

- (instancetype _Nonnull)initWithMedia:(const std::shared_ptr<Media>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getPoster
{
 
    auto getPosterCpp = mCppObj->GetPoster();
    return [NSString stringWithUTF8String:getPosterCpp.c_str()];

}

- (void)setPoster:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetPoster(valueCpp);
    
}

- (NSString * _Nullable)getAltText
{
 
    auto getAltTextCpp = mCppObj->GetAltText();
    return [NSString stringWithUTF8String:getAltTextCpp.c_str()];

}

- (void)setAltText:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetAltText(valueCpp);
    
}

- (NSArray<ACSMediaSource *> * _Nonnull)getSources
{
 
    auto getSourcesCpp = mCppObj->GetSources();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getSourcesCpp)
    {
        [objList addObject: [[ACSMediaSource alloc] initWithMediaSource:item]];
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
