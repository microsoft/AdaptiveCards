// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSForegroundColorConvertor.h"
#import "ACSSeparatorThicknessConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSSeparator.h"
#import "../../../../../shared/cpp/ObjectModel/Separator.h"


@implementation  ACSSeparator {
    std::shared_ptr<Separator> mCppObj;
}

- (instancetype _Nonnull)initWithSeparator:(const std::shared_ptr<Separator>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSSeparatorThickness)getThickness
{
 
    auto getThicknessCpp = mCppObj->GetThickness();
    return [ACSSeparatorThicknessConvertor convertCpp:getThicknessCpp];

}

- (void)setThickness:(enum ACSSeparatorThickness)value
{
    auto valueCpp = [ACSSeparatorThicknessConvertor convertObj:value];
 
    mCppObj->SetThickness(valueCpp);
    
}

- (ACSForegroundColor)getColor
{
 
    auto getColorCpp = mCppObj->GetColor();
    return [ACSForegroundColorConvertor convertCpp:getColorCpp];

}

- (void)setColor:(enum ACSForegroundColor)value
{
    auto valueCpp = [ACSForegroundColorConvertor convertObj:value];
 
    mCppObj->SetColor(valueCpp);
    
}


@end
