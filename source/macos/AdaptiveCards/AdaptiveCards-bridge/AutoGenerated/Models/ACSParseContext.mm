// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSCollectionTypeElement.h"
#import "ACSContainerBleedDirectionConvertor.h"
#import "ACSContainerStyleConvertor.h"
#import "ACSInternalId.h"

//cpp includes
#import "BaseElement.h"
#import "CollectionTypeElement.h"
#import "Enums.h"


#import "ACSParseContext.h"
#import "ParseContext.h"


@implementation  ACSParseContext {
    std::shared_ptr<ParseContext> mCppObj;
}

- (instancetype _Nonnull)initWithParseContext:(const std::shared_ptr<ParseContext>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (void)pushElement:(NSString * _Nonnull)idJsonProperty internalId:(ACSInternalId * _Nonnull)internalId isFallback:(bool)isFallback
{
//    auto idJsonPropertyCpp = std::string([idJsonProperty UTF8String]);
//    auto internalIdCpp = // NEED TO INSERT CODE //;
//    auto isFallbackCpp = isFallback;
//
//    mCppObj->PushElement(idJsonPropertyCpp,internalIdCpp,isFallbackCpp);
    
}

- (void)popElement
{
 
    mCppObj->PopElement();
    
}

- (bool)getCanFallbackToAncestor
{
 
    auto getCanFallbackToAncestorCpp = mCppObj->GetCanFallbackToAncestor();
    return getCanFallbackToAncestorCpp;

}

- (void)setCanFallbackToAncestor:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetCanFallbackToAncestor(valueCpp);
    
}

- (void)setLanguage:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetLanguage(valueCpp);
    
}

- (NSString * _Nullable)getLanguage
{
 
    auto getLanguageCpp = mCppObj->GetLanguage();
    return [NSString stringWithUTF8String:getLanguageCpp.c_str()];

}

- (ACSContainerStyle)getParentalContainerStyle
{
 
    auto getParentalContainerStyleCpp = mCppObj->GetParentalContainerStyle();
    return [ACSContainerStyleConvertor convertCpp:getParentalContainerStyleCpp];

}

- (void)setParentalContainerStyle:(enum ACSContainerStyle)style
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
 
    mCppObj->SetParentalContainerStyle(styleCpp);
    
}

- (ACSInternalId * _Nullable)paddingParentInternalId
{
 
    auto paddingParentInternalIdCpp = mCppObj->PaddingParentInternalId();
    return [[ACSInternalId alloc] init];

}

- (void)saveContextForCollectionTypeElement:(ACSCollectionTypeElement * _Nonnull)current
{
//    auto currentCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->SaveContextForCollectionTypeElement(currentCpp);
    
}

- (void)restoreContextForCollectionTypeElement:(ACSCollectionTypeElement * _Nonnull)current
{
//    auto currentCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->RestoreContextForCollectionTypeElement(currentCpp);
    
}

- (ACSContainerBleedDirection)getBleedDirection
{
 
    auto getBleedDirectionCpp = mCppObj->GetBleedDirection();
    return [ACSContainerBleedDirectionConvertor convertCpp:getBleedDirectionCpp];

}

- (void)pushBleedDirection:(enum ACSContainerBleedDirection)direction
{
    auto directionCpp = [ACSContainerBleedDirectionConvertor convertObj:direction];
 
    mCppObj->PushBleedDirection(directionCpp);
    
}

- (void)popBleedDirection
{
 
    mCppObj->PopBleedDirection();
    
}

- (ACSInternalId * _Nullable)getNearestFallbackId:(ACSInternalId * _Nonnull)skipId
{
//    auto skipIdCpp = // NEED TO INSERT CODE //;
 
//    auto getNearestFallbackIdCpp = mCppObj->GetNearestFallbackId(skipIdCpp);
    return [[ACSInternalId alloc] init];

}


@end
