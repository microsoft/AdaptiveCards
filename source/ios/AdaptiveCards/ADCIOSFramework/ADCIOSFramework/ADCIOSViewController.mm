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

using namespace AdaptiveCards;

@implementation ADCIOSViewController
std::shared_ptr<AdaptiveCard> adc;

-(id) init: (NSString*) str {
    self = [super init];
    if(self) {
        self.jsaonString = str;
    }
    
    return self;
}
- (void) loadView {
    UIStackView* mainView = [[UIStackView alloc] init];
    mainView.axis = UILayoutConstraintAxisHorizontal;
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
    
    std::vector<std::shared_ptr<BaseCardElement>> body = adc->GetBody();
    for(auto elem: body)
    {
        if(elem->GetElementType() == CardElementType::TextBlock)
        {
            std::shared_ptr<TextBlock> pblock = std::dynamic_pointer_cast<TextBlock>(elem);
            UIStackView* mainView = (UIStackView*) self.view;
            [mainView addArrangedSubview:[self buildTextBlock:pblock]];
        }
    }
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

- (int) UITextMappingSize:(std::shared_ptr<TextBlock>)txtBlock {
    switch (txtBlock->GetTextSize()){
        case TextSize::Small:
            return 10;
        case TextSize::Normal:
            return 12;
        case TextSize::Medium:
            return 14;
        case TextSize::Large:
            return 17;
        case TextSize::ExtraLarge:
            return 20;
        default:
            return 12;
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
    switch (txtBlock->GetTextColor()) {
        case TextColor::Dark:
            return [UIColor blackColor];
        case TextColor::Light:
            return [UIColor clearColor];
        case TextColor::Accent:
            return [UIColor greenColor];
        case TextColor::Good:
            return [UIColor purpleColor];
        case TextColor::Warning:
            return [UIColor magentaColor];
        case TextColor::Attention:
            return [UIColor brownColor];
    default:
            return [UIColor blackColor];
    }
}

@end
