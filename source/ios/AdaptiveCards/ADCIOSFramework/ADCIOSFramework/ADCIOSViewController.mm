//
//  ADCIOS.m
//  ADCIOS
//
//  Created by jwoo on 5/26/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ADCIOSViewController.h"
#import "AdaptiveCard.h"
#import "TextBlock.h"
#import "Image.h"
#import "HostConfig.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;

@implementation ADCIOSViewController
std::shared_ptr<AdaptiveCard> adc;
std::shared_ptr<HostConfig> hostConfig;

-(id) init: (NSString*) str {
    self = [super init];
    if(self) {
        self.jsaonString = str;
        hostConfig = std::make_shared<HostConfig>();
    }
    
    return self;
}
- (void) loadView {
    UIStackView* mainView = [[UIStackView alloc] init];
    mainView.axis = UILayoutConstraintAxisVertical;
    mainView.distribution = UIStackViewDistributionEqualSpacing;
    mainView.translatesAutoresizingMaskIntoConstraints = false;
    self.view = mainView;
}

-(void) viewDidLoad {
    [super viewDidLoad];
    [self buildViewFromADC: self.jsaonString];
}

-(void) buildViewFromADC:(NSString*) str{
    adc = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));
    UIStackView* mainView = (UIStackView*) self.view;
    std::vector<std::shared_ptr<BaseCardElement>> body = adc->GetBody();
    
    for(auto elem: body)
    {
        switch(elem->GetElementType()){
            case CardElementType::TextBlock:
            {
                std::shared_ptr<TextBlock> tblock = std::dynamic_pointer_cast<TextBlock>(elem);
                [mainView addArrangedSubview:[self buildTextBlock:tblock]];
                break;
            }
            case CardElementType::Image:
            {
                std::shared_ptr<Image> iblock = std::dynamic_pointer_cast<Image>(elem);
                [mainView addArrangedSubview:[self buildImageBlock:iblock]];
                break;
            }
            default:;
        }
    }
}

-(UIImageView* ) buildImageBlock:(std::shared_ptr<Image>) blck{
   
    NSURL *url = [NSURL URLWithString:
                  [NSString stringWithCString: blck->GetUrl().c_str()
                                     encoding:[NSString defaultCStringEncoding]]];
    
    UIImage* img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    
    CGSize cgsize = [self UIImageMappingSize: blck];

    UIGraphicsBeginImageContext(cgsize);
    UIImageView* view = [[UIImageView alloc]
                         initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
    [img drawInRect:(CGRectMake(0, 0, cgsize.width, cgsize.height))];
    img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    view.image = img;

    if(blck->GetImageStyle() == ImageStyle::Person) {
        CALayer* imgLayer = view.layer;
        [imgLayer setCornerRadius:cgsize.width/2];
        [imgLayer setMasksToBounds:YES];
    }
    return view;
}

-(UILabel*) buildTextBlock:(std::shared_ptr<TextBlock>) blck{
    
    UILabel* lab = [[UILabel alloc] init];
    NSString* textBlockStr = [NSString stringWithCString:blck->GetText().c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    
    NSMutableAttributedString* content =
    [[NSMutableAttributedString alloc] initWithString:textBlockStr
                                           attributes:@{NSForegroundColorAttributeName: [self UIMappingColor:blck],
                                                        NSStrokeWidthAttributeName: [self UIMappingTextWeight:blck]}];
    NSMutableParagraphStyle* para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = blck->GetWrap() ? NSLineBreakByWordWrapping: NSLineBreakByTruncatingTail;
    para.alignment = [self UITextMappingAlignment:blck];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range: NSMakeRange(0,1)];
    lab.attributedText = content;
    lab.numberOfLines = int(blck->GetMaxLines());
    UIFontDescriptor* dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[self UITextMappingSize:blck]];
    
    return lab;
}

-(CGSize) UIImageMappingSize:(std::shared_ptr<Image>) imgBlock {
    float sz = hostConfig->imageSizes.mediumSize;
    switch (imgBlock->GetImageSize()){
        case ImageSize::Large:
        {
            sz = hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:
        {
            sz = hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:
        {
            sz = hostConfig->imageSizes.smallSize;
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

- (int) UITextMappingSize:(std::shared_ptr<TextBlock>)txtBlock {
    switch (txtBlock->GetTextSize()){
        case TextSize::Small:
            return hostConfig->fontSizes.smallFontSize;
        case TextSize::Normal:
            return hostConfig->fontSizes.normalFontSize;
        case TextSize::Medium:
            return hostConfig->fontSizes.mediumFontSize;
        case TextSize::Large:
            return hostConfig->fontSizes.largeFontSize;
        case TextSize::ExtraLarge:
            return hostConfig->fontSizes.extraLargeFontSize;
        default:
            return hostConfig->fontSizes.normalFontSize;
    }
}
    
-(NSTextAlignment) UITextMappingAlignment:(std::shared_ptr<TextBlock>) txtBlock {
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
     
-(NSNumber* ) UIMappingTextWeight:(std::shared_ptr<TextBlock>) txtBlock{
    switch (txtBlock->GetTextWeight()) { 
        case TextWeight::Normal:
            return [[NSNumber alloc] initWithInt:0];
        case TextWeight::Lighter:
            return [[NSNumber alloc] initWithInt:1];
        case TextWeight::Bolder:
            return [[NSNumber alloc] initWithInt:-2];
    }
}
                                          
-(UIColor* ) UIMappingColor:(std::shared_ptr<TextBlock>) txtBlock{
    u_int32_t num = 0;
    NSScanner* scanner;
    std::string str;
    switch (txtBlock->GetTextColor()) {
        case TextColor::Dark: 
        {	
            str = hostConfig->colors.dark.normal;
            break;
        }
        case TextColor::Light:
        {
            str = hostConfig->colors.light.normal;
            break;
        }
        case TextColor::Accent:
        {
            str = hostConfig->colors.accent.normal;
            break;
        }
        case TextColor::Good:
        {
            str = hostConfig->colors.good.normal;
            break;
        }
        case TextColor::Warning:
        {
            str = hostConfig->colors.warning.normal;
            break;
        }
        case TextColor::Attention:
        {
            str = hostConfig->colors.attention.normal;
            break;
        }
    default:
        {
            str = hostConfig->colors.good.normal;
            break;
        }
    }
    
    scanner = [NSScanner scannerWithString:
               [[NSString alloc] initWithCString:str.c_str()
                                        encoding:[NSString defaultCStringEncoding]]];
    [scanner setScanLocation:1];
    [scanner scanHexInt:&num];
    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255
                           green:((num & 0x0000FF00) >> 8)  / 255
                            blue:((num & 0x000000FF))       / 255
                           alpha:((num & 0xFF000000) >> 24) / 255];
}

@end
