//
//  ADCIOSAdaptiveHostConfig.m
//  ADCIOSFramework
//
//  Created by jwoo on 6/7/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

//#include "HostConfig.h"
#import "ADCIOSAdaptiveHostConfig.h"

using namespace AdaptiveCards;

@implementation ADCIOSAdaptiveHostConfig

- (id) init {
    self = [super init];

    if(self)
    { 
        _m_hostConfig = std::make_shared<HostConfig>();
    }

    return self;
}

- (u_int32_t) retrieveIntFromHostConfigString: (NSString *) str{
    u_int32_t num = 0;
    NSScanner* scanner;
    scanner = [NSScanner scannerWithString: str];
    [scanner setScanLocation:1];
    [scanner scanHexInt:&num];
    return num;
}

- (UIColor* ) getTextBlockColor:(std::shared_ptr<TextBlock>) txtBlock{
    u_int32_t num = 0;
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
    
    num = [self retrieveIntFromHostConfigString:[[NSString alloc] initWithCString:str.c_str()
                                encoding:[NSString defaultCStringEncoding]]];

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255
                           green:((num & 0x0000FF00) >> 8)  / 255
                            blue:((num & 0x000000FF))       / 255
                           alpha:((num & 0xFF000000) >> 24) / 255];

}

- (CGSize) getImageSize:(std::shared_ptr<Image>) imgBlock {
    float sz = self.m_hostConfig->imageSizes.mediumSize;
    switch (imgBlock->GetImageSize()){
        case ImageSize::Large:
        {
            sz = self.m_hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:
        {
            sz = self.m_hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:
        {
            sz = self.m_hostConfig->imageSizes.smallSize;
            break;
        }

        default:
        {
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}

- (int) getTextBlockTexSize:(std::shared_ptr<TextBlock>)txtBlock {
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
    
-(NSTextAlignment) getTextBlockAlignment:(std::shared_ptr<TextBlock>) txtBlock {
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
     
-(NSNumber* ) getTextBlockTextWeight:(std::shared_ptr<TextBlock>) txtBlock{
    switch (txtBlock->GetTextWeight()) { 
        case TextWeight::Normal:
            return [[NSNumber alloc] initWithInt:0];
        case TextWeight::Lighter:
            return [[NSNumber alloc] initWithInt:1];
        case TextWeight::Bolder:
            return [[NSNumber alloc] initWithInt:-2];
    }
}
@end
