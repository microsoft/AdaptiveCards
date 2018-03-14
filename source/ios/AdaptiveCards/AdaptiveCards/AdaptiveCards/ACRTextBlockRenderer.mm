//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "TextBlock.h"
#import "HostConfig.h"
#import "MarkDownParser.h"
#import "ACRViewController.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRUILabel.h"
#import "DateTimePreparsedToken.h"
#import "DateTimePreparser.h"

@implementation ACRTextBlockRenderer

+ (ACRTextBlockRenderer *)getInstance
{
    static ACRTextBlockRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTextBlock;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
    ACRUILabel *lab = [[ACRUILabel alloc] init];
    lab.style = [viewGroup style];
    __block NSMutableAttributedString *content = nil;
    if(vc)
    {
        NSMutableDictionary *textMap = [(ACRViewController *)vc getTextMap];
        // Generate key for ImageViewMap
        NSString *key = [NSString stringWithCString:elem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
        // Syncronize access to imageViewMap
        dispatch_sync([(ACRViewController *)vc getSerialTextQueue], ^{
            if(textMap[key]) { // if content is available, get it, otherwise cache label, so it can be used used later
                content = textMap[key];
            } else {
                textMap[key] = lab;
            }
        });
    }

    if(content)
    {
        // Set paragraph style such as line break mode and alignment
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        paragraphStyle.lineBreakMode = txtBlck->GetWrap() ? NSLineBreakByWordWrapping:NSLineBreakByTruncatingTail;
        paragraphStyle.alignment = [ACOHostConfig getTextBlockAlignment:txtBlck->GetHorizontalAlignment()];

        // Obtain text color to apply to the attributed string
        ACRContainerStyle style = lab.style;
        ColorsConfig &colorConfig = (style == ACREmphasis)? config->containerStyles.emphasisPalette.foregroundColors:
                                                                         config->containerStyles.defaultPalette.foregroundColors;

        // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
        [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle,
                                NSForegroundColorAttributeName:[ACOHostConfig getTextBlockColor:txtBlck->GetTextColor() colorsConfig:colorConfig subtleOption:txtBlck->GetIsSubtle()],
                                    NSStrokeWidthAttributeName:[ACOHostConfig getTextStrokeWidthForWeight:txtBlck->GetTextWeight()]} range:NSMakeRange(0, content.length - 1)];
        lab.attributedText = content;

        std::string id = txtBlck->GetId();
        std::size_t idx = id.find_last_of('_');
        txtBlck->SetId(id.substr(0, idx));
    }

    lab.numberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.numberOfLines and !txtBlck->GetWrap())
    {
        lab.numberOfLines = 1;
    }

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] init];

    [wrappingview addSubview:lab];

    [wrappingview setAlignmentForSubview:txtBlck->GetHorizontalAlignment()];

    [viewGroup addArrangedSubview:wrappingview];

    wrappingview.translatesAutoresizingMaskIntoConstraints = false;

    lab.translatesAutoresizingMaskIntoConstraints = false;

    return wrappingview;
}

@end
