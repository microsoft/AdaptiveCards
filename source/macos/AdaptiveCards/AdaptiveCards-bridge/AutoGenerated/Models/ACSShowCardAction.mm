// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSAdaptiveCard.h"
#import "ACSRemoteResourceInformationConvertor.h"

//cpp includes
#import "RemoteResourceInformation.h"
#import "SharedAdaptiveCard.h"


#import "ACSShowCardAction.h"
#import "ShowCardAction.h"


@implementation  ACSShowCardAction {
    std::shared_ptr<ShowCardAction> mCppObj;
}

- (instancetype _Nonnull)initWithShowCardAction:(const std::shared_ptr<ShowCardAction>)cppObj
{
    if (self = [super initWithBaseActionElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSAdaptiveCard * _Nullable)getCard
{
 
    auto getCardCpp = mCppObj->GetCard();
    return [[ACSAdaptiveCard alloc] initWithAdaptiveCard:getCardCpp];

}

- (void)setCard:(ACSAdaptiveCard * _Nonnull)card
{
//    auto Cpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->SetCard(Cpp);
    
}

- (void)setLanguage:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetLanguage(valueCpp);
    
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
