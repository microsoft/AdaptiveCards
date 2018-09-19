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
#import "ACRView.h"
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
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    ACRUILabel *lab = [bundle loadNibNamed:@"ACRLabelView" owner:rootView options:nil][0];

    lab.style = [viewGroup style];
    NSMutableAttributedString *content = nil;
    if(rootView){
        NSMutableDictionary *textMap = [rootView getTextMap];
        // Generate key for ImageViewMap
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)txtBlck.get()];
        NSString *key = [number stringValue];
        NSDictionary* data = textMap[key];
        NSData *htmlData = data[@"html"];
        NSDictionary *options = data[@"options"];
        NSDictionary *descriptor = data[@"descriptor"];
        NSString *text = data[@"nonhtml"];

        // Initializing NSMutableAttributedString for HTML rendering is very slow
        if(htmlData) {
            content = [[NSMutableAttributedString alloc] initWithData:htmlData options:options documentAttributes:nil error:nil];
            // Drop newline char
            [content deleteCharactersInRange:NSMakeRange([content length] -1, 1)];
        } else {
            // if html rendering is skipped, remove p tags from both ends (<p>, </p>)
            content = [[NSMutableAttributedString alloc] initWithString:text attributes:descriptor];
            [content deleteCharactersInRange:NSMakeRange(0, 3)];
            [content deleteCharactersInRange:NSMakeRange([content length] -4, 4)];
        }

        // Set paragraph style such as line break mode and alignment
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        paragraphStyle.lineBreakMode = NSLineBreakByTruncatingTail;
        paragraphStyle.alignment = [ACOHostConfig getTextBlockAlignment:txtBlck->GetHorizontalAlignment()];

        // Obtain text color to apply to the attributed string
        ACRContainerStyle style = lab.style;
        ColorsConfig &colorConfig = (style == ACREmphasis)? config->containerStyles.emphasisPalette.foregroundColors:
        config->containerStyles.defaultPalette.foregroundColors;
        // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
        [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle, NSForegroundColorAttributeName:[ACOHostConfig getTextBlockColor:txtBlck->GetTextColor() colorsConfig:colorConfig subtleOption:txtBlck->GetIsSubtle()],} range:NSMakeRange(0, content.length)];
        lab.attributedText = content;
    }

    lab.numberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.numberOfLines and !txtBlck->GetWrap()){
        lab.numberOfLines = 1;
    }

    if(txtBlck->GetHeight() == HeightType::Auto){
        [lab setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [lab setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    } else {
        [lab setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [lab setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        lab.isStretchable = YES;
    }

    [viewGroup addArrangedSubview:lab];
    return lab;
}

@end
