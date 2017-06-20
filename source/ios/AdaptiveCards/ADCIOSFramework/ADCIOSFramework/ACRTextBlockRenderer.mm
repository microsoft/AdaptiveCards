//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "TextBlock.h"

@implementation ACRTextBlockRenderer

+ (ACRTextBlockRenderer* ) getInstance
{
    static ACRTextBlockRenderer *singletonInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{singletonInstance = [[self alloc] init];});
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::TextBlock;
}

- (UIView* ) render: (UIView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
       andHostCofig: (std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
    UILabel* lab = [[UILabel alloc] init];
    NSString* textBlockStr = [NSString stringWithCString:txtBlck->GetText().c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    
    NSMutableAttributedString* content =
    [[NSMutableAttributedString alloc] initWithString:textBlockStr
                                           attributes:@{NSForegroundColorAttributeName: [self getTextBlockColor:txtBlck withHostConfig:config ],
                                                        NSStrokeWidthAttributeName: [self getTextBlockTextWeight:txtBlck withHostConfig:config]}];
    NSMutableParagraphStyle* para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = txtBlck->GetWrap() ? NSLineBreakByWordWrapping: NSLineBreakByTruncatingTail;
    para.alignment = [self getTextBlockAlignment:txtBlck withHostConfig:config];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range: NSMakeRange(0,1)];
    lab.attributedText = content;
    lab.numberOfLines = int(txtBlck->GetMaxLines());
    UIFontDescriptor* dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[self getTextBlockTextSize:txtBlck withHostConfig:config]];
    
    return lab;
}

- (UIColor* ) getTextBlockColor:(std::shared_ptr<TextBlock> const &) txtBlock
                 withHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    long num = 0;
    std::string str;
    switch (txtBlock->GetTextColor()) {
        case TextColor::Dark: {	
            str = config->colors.dark.normal;
            break;
        }
        case TextColor::Light: {
            str = config->colors.light.normal;
            break;
        }
        case TextColor::Accent: {
            str = config->colors.accent.normal;
            break;
        }
        case TextColor::Good: {
            str = config->colors.good.normal;
            break;
        }
        case TextColor::Warning: {
            str = config->colors.warning.normal;
            break;
        }
        case TextColor::Attention: {
            str = config->colors.attention.normal;
            break;
        }
        default: {
            str = config->colors.good.normal;
            break;
        }
    }
    
    num = std::stoul(str.substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                           green:((num & 0x0000FF00) >> 8)  / 255.0
                            blue:((num & 0x000000FF))       / 255.0
                           alpha:((num & 0xFF000000) >> 24) / 255.0];

}

- (int) getTextBlockTextSize:(std::shared_ptr<TextBlock> const &) txtBlock 
              withHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    switch (txtBlock->GetTextSize()){
        case TextSize::Small:
            return config->fontSizes.smallFontSize;
        case TextSize::Normal:
            return config->fontSizes.normalFontSize;
        case TextSize::Medium:
            return config->fontSizes.mediumFontSize;
        case TextSize::Large:
            return config->fontSizes.largeFontSize;
        case TextSize::ExtraLarge:
            return config->fontSizes.extraLargeFontSize;
        default:
            return config->fontSizes.normalFontSize;
    }
}

-(NSTextAlignment) getTextBlockAlignment:(std::shared_ptr<TextBlock> const &) txtBlock 
                          withHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    switch (txtBlock->GetHorizontalAlignment()){
        case HorizontalAlignment::Center:
            return NSTextAlignmentCenter;
        case HorizontalAlignment::Left:
            return NSTextAlignmentLeft;
        case HorizontalAlignment::Right:
            return NSTextAlignmentRight;
        default:
            return NSTextAlignmentLeft;
    }
}
     
-(NSNumber* ) getTextBlockTextWeight:(std::shared_ptr<TextBlock> const &) txtBlock
                      withHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    switch (txtBlock->GetTextWeight()) { 
        case TextWeight::Normal:
            return @0;
        case TextWeight::Lighter:
            return @1;
        case TextWeight::Bolder:
            return @-2;
    }
}

@end
