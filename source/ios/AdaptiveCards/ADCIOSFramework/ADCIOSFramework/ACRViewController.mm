//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACRHostConfig.h"
#import "AdaptiveCard.h"
#import "TextBlock.h"
#import "Image.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;

@implementation ACRViewController
{
    std::shared_ptr<AdaptiveCard> adaptiveCard;
    ACRHostConfig* hostConfig;
}

-(instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        self.jsonString = nil;
        hostConfig = [[ACRHostConfig alloc] init];
    }
    return self;
}

-(instancetype) init: (NSString*) str {
    self = [self initWithNibName:nil bundle:nil];
    if(self) {
        self.jsonString = str;
    }
    
    return self;
}

-(void) viewDidLoad {
    [super viewDidLoad];
    [self buildViewFromADC: self.jsonString];
}

-(void) buildViewFromADC:(NSString*) str{
    adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));

    UIStackView* mainView = [[UIStackView alloc] init];
    mainView.axis = UILayoutConstraintAxisVertical;
    mainView.distribution = UIStackViewDistributionEqualSpacing;
    mainView.translatesAutoresizingMaskIntoConstraints = false;
    
    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCard->GetBody();
    
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
                [mainView addArrangedSubview:[self buildImage:iblock]];
                break;
            }
            default:;
        }
    }

    [self.view addSubview: mainView];

    [NSLayoutConstraint activateConstraints:@[[mainView.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], 
                                              [mainView.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
}

-(UIImageView* ) buildImage:(std::shared_ptr<Image>) blck{
   
    NSURL *url = [NSURL URLWithString:
                  [NSString stringWithCString: blck->GetUrl().c_str()
                                     encoding:[NSString defaultCStringEncoding]]];
    
    UIImage* img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    
    CGSize cgsize = [hostConfig getImageSize: blck];

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
                                           attributes:@{NSForegroundColorAttributeName: [hostConfig getTextBlockColor:blck],
                                                        NSStrokeWidthAttributeName: [hostConfig getTextBlockTextWeight:blck]}];
    NSMutableParagraphStyle* para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = blck->GetWrap() ? NSLineBreakByWordWrapping: NSLineBreakByTruncatingTail;
    para.alignment = [hostConfig getTextBlockAlignment:blck];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range: NSMakeRange(0,1)];
    lab.attributedText = content;
    lab.numberOfLines = int(blck->GetMaxLines());
    UIFontDescriptor* dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[hostConfig getTextBlockTextSize:blck]];
    
    return lab;
}                                          
@end
