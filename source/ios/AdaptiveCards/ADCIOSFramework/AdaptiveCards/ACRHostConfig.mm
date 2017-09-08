//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRHostConfig.h"

using namespace AdaptiveCards;

@implementation ACRHostConfig

- (id) init {
    self = [super init];

    if(self)
    { 
        _m_hostConfig = std::make_shared<HostConfig>();
    }

    return self;
}

- (UIColor* ) getTextBlockColor:(std::shared_ptr<TextBlock> const &) txtBlock{
    long num = 0;
    std::string str;
    switch (txtBlock->GetTextColor()) {
        case TextColor::Dark: {	
            str = self.m_hostConfig->colors.dark.normal;
            break;
        }
        case TextColor::Light: {
            str = self.m_hostConfig->colors.light.normal;
            break;
        }
        case TextColor::Accent: {
            str = self.m_hostConfig->colors.accent.normal;
            break;
        }
        case TextColor::Good: {
            str = self.m_hostConfig->colors.good.normal;
            break;
        }
        case TextColor::Warning: {
            str = self.m_hostConfig->colors.warning.normal;
            break;
        }
        case TextColor::Attention: {
            str = self.m_hostConfig->colors.attention.normal;
            break;
        }
        default: {
            str = self.m_hostConfig->colors.good.normal;
            break;
        }
    }
    
    num = std::stoul(str.substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                           green:((num & 0x0000FF00) >> 8)  / 255.0
                            blue:((num & 0x000000FF))       / 255.0
                           alpha:((num & 0xFF000000) >> 24) / 255.0];

}

- (CGSize) getImageSize:(std::shared_ptr<Image> const &) imgBlock {
    float sz = self.m_hostConfig->imageSizes.mediumSize;
    switch (imgBlock->GetImageSize()){
        case ImageSize::Large: {
            sz = self.m_hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium: {
            sz = self.m_hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small: {
            sz = self.m_hostConfig->imageSizes.smallSize;
            break;
        }

        default: {
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}

- (int) getTextBlockTextSize:(std::shared_ptr<TextBlock> const &) txtBlock {
    switch (txtBlock->GetTextSize()){
        case TextSize::Small:
            return self.m_hostConfig->fontSizes.smallFontSize;
        case TextSize::Normal:
            return self.m_hostConfig->fontSizes.normalFontSize;
        case TextSize::Medium:
            return self.m_hostConfig->fontSizes.mediumFontSize;
        case TextSize::Large:
            return self.m_hostConfig->fontSizes.largeFontSize;
        case TextSize::ExtraLarge:
            return self.m_hostConfig->fontSizes.extraLargeFontSize;
        default:
            return self.m_hostConfig->fontSizes.normalFontSize;
    }
}
    
-(NSTextAlignment) getTextBlockAlignment:(std::shared_ptr<TextBlock> const &) txtBlock {
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
     
-(NSNumber* ) getTextBlockTextWeight:(std::shared_ptr<TextBlock> const &) txtBlock{
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
