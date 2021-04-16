// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSHorizontalAlignmentConvertor.h"
#import "ACSInline.h"

//cpp includes
#import "Enums.h"
#import "Inline.h"


#import "ACSRichTextBlock.h"
#import "RichTextBlock.h"


@implementation  ACSRichTextBlock {
    std::shared_ptr<RichTextBlock> mCppObj;
}

- (instancetype _Nonnull)initWithRichTextBlock:(const std::shared_ptr<RichTextBlock>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
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

- (NSArray<ACSInline *> * _Nonnull)getInlines
{
 
    auto getInlinesCpp = mCppObj->GetInlines();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getInlinesCpp)
    {
        [objList addObject: [BridgeConverter convertFromInline:item]];
    }
    return objList;


}




@end
