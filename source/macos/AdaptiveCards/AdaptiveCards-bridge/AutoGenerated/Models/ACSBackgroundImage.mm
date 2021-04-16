// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSHorizontalAlignmentConvertor.h"
#import "ACSImageFillModeConvertor.h"
#import "ACSVerticalAlignmentConvertor.h"

//cpp includes
#import "Enums.h"


#import "ACSBackgroundImage.h"
#import "BackgroundImage.h"


@implementation  ACSBackgroundImage {
    std::shared_ptr<BackgroundImage> mCppObj;
}

- (instancetype _Nonnull)initWithBackgroundImage:(const std::shared_ptr<BackgroundImage>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getUrl
{
 
    auto getUrlCpp = mCppObj->GetUrl();
    return [NSString stringWithUTF8String:getUrlCpp.c_str()];

}

- (void)setUrl:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetUrl(valueCpp);
    
}

- (ACSImageFillMode)getFillMode
{
 
    auto getFillModeCpp = mCppObj->GetFillMode();
    return [ACSImageFillModeConvertor convertCpp:getFillModeCpp];

}

- (void)setFillMode:(enum ACSImageFillMode)value
{
    auto valueCpp = [ACSImageFillModeConvertor convertObj:value];
 
    mCppObj->SetFillMode(valueCpp);
    
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

- (ACSVerticalAlignment)getVerticalAlignment
{
 
    auto getVerticalAlignmentCpp = mCppObj->GetVerticalAlignment();
    return [ACSVerticalAlignmentConvertor convertCpp:getVerticalAlignmentCpp];

}

- (void)setVerticalAlignment:(enum ACSVerticalAlignment)value
{
    auto valueCpp = [ACSVerticalAlignmentConvertor convertObj:value];
 
    mCppObj->SetVerticalAlignment(valueCpp);
    
}


@end
