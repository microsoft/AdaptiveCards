//
//  ACRViewController.m
//  ACRViewController
//
//  Created by jwoo on 5/26/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ADCIOSAdaptiveHostConfig.h"
#import "AdaptiveCard.h"
#import "TextBlock.h"
#import "Image.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;

@implementation ACRViewController
std::shared_ptr<AdaptiveCard> adaptiveCards;
ADCIOSAdaptiveHostConfig* m_hostConfig;

-(id) init: (NSString*) str {
    self = [super init];
    if(self) {
        self.jsonString = str;
        m_hostConfig = [[ADCIOSAdaptiveHostConfig alloc] init];
    }
    
    return self;
}

- (void) loadView {
    [self createRootCardElement];
}

-(void) createRootCardElement {
    // work in progress
    // to-do add support for container / column set / columns 
    UIStackView* mainView = [[UIStackView alloc] init];
    mainView.axis = UILayoutConstraintAxisVertical;
    mainView.distribution = UIStackViewDistributionEqualSpacing;
    mainView.translatesAutoresizingMaskIntoConstraints = false;
    self.view = mainView;
}

-(void) viewDidLoad {
    [super viewDidLoad];
    [self buildViewFromADC: self.jsonString];
}

-(void) buildViewFromADC:(NSString*) str{
    adaptiveCards = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));
    UIStackView* mainView = (UIStackView*) self.view;
    
    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCards->GetBody();
    
    // work in progress; simplified version to verify TextBlock and Image
    // to-do add support for container / column set / columns 
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
    
    CGSize cgsize = [m_hostConfig getImageSize: blck];

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
                                           attributes:@{NSForegroundColorAttributeName: [m_hostConfig getTextBlockColor:blck],
                                                        NSStrokeWidthAttributeName: [m_hostConfig getTextBlockTextWeight:blck]}];
    NSMutableParagraphStyle* para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = blck->GetWrap() ? NSLineBreakByWordWrapping: NSLineBreakByTruncatingTail;
    para.alignment = [m_hostConfig getTextBlockAlignment:blck];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range: NSMakeRange(0,1)];
    lab.attributedText = content;
    lab.numberOfLines = int(blck->GetMaxLines());
    UIFontDescriptor* dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[m_hostConfig getTextBlockTexSize:blck]];
    
    return lab;
}
                                          
@end
