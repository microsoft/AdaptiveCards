//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRRegistration.h"
#import "ACRUILabel.h"
#import "ACRView.h"
#import "DateTimePreparsedToken.h"
#import "DateTimePreparser.h"
#import "HostConfig.h"
#import "MarkDownParser.h"
#import "TextBlock.h"
#import "UtiliOS.h"

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
    ACRUILabel *lab = [[ACRUILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
    lab.backgroundColor = [UIColor clearColor];

    lab.style = [viewGroup style];
    NSMutableAttributedString *content = nil;
    if (rootView) {
        NSMutableDictionary *textMap = [rootView getTextMap];
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)txtBlck.get()];
        NSString *key = [number stringValue];
        NSDictionary *data = nil;
        NSData *htmlData = nil;
        NSDictionary *options = nil;
        NSDictionary *descriptor = nil;
        NSString *text = nil;

        if (![textMap objectForKey:key]) {
            RichTextElementProperties textProp;
            TextBlockToRichTextElementProperties(txtBlck, textProp);
            buildIntermediateResultForText(rootView, acoConfig, textProp, key);
        }

        data = textMap[key];
        htmlData = data[@"html"];
        options = data[@"options"];
        descriptor = data[@"descriptor"];
        text = data[@"nonhtml"];

        // Initializing NSMutableAttributedString for HTML rendering is very slow
        if (htmlData) {
            content = [[NSMutableAttributedString alloc] initWithData:htmlData options:options documentAttributes:nil error:nil];
            // Drop newline char
            [content deleteCharactersInRange:NSMakeRange([content length] - 1, 1)];
            lab.selectable = YES;
            lab.dataDetectorTypes = UIDataDetectorTypeLink | UIDataDetectorTypePhoneNumber;
            lab.userInteractionEnabled = YES;
        } else {
            // if html rendering is skipped, remove p tags from both ends (<p>, </p>)
            content = [[NSMutableAttributedString alloc] initWithString:text attributes:descriptor];
            [content deleteCharactersInRange:NSMakeRange(0, 3)];
            [content deleteCharactersInRange:NSMakeRange([content length] - 4, 4)];
        }
        lab.editable = NO;
        lab.textContainer.lineFragmentPadding = 0;
        lab.textContainerInset = UIEdgeInsetsZero;
        lab.layoutManager.usesFontLeading = false;

        // Set paragraph style such as line break mode and alignment
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        paragraphStyle.alignment = [ACOHostConfig getTextBlockAlignment:txtBlck->GetHorizontalAlignment()];

        // Obtain text color to apply to the attributed string
        ACRContainerStyle style = lab.style;
        auto foregroundColor = [acoConfig getTextBlockColor:style textColor:txtBlck->GetTextColor() subtleOption:txtBlck->GetIsSubtle()];

        // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
        [content addAttributes:@{
            NSParagraphStyleAttributeName : paragraphStyle,
            NSForegroundColorAttributeName : foregroundColor,
        }
                         range:NSMakeRange(0, content.length)];

        lab.textContainer.lineBreakMode = NSLineBreakByTruncatingTail;
        lab.attributedText = content;
        lab.isAccessibilityElement = YES;
    }

    lab.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:lab];

    lab.textContainer.maximumNumberOfLines = int(txtBlck->GetMaxLines());
    if (!lab.textContainer.maximumNumberOfLines && !txtBlck->GetWrap()) {
        lab.textContainer.maximumNumberOfLines = 1;
    }

    [lab setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    if (txtBlck->GetHeight() == HeightType::Auto) {
        [lab setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    } else {
        [lab setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    }

    HorizontalAlignment adaptiveAlignment = txtBlck->GetHorizontalAlignment();

    if (adaptiveAlignment == HorizontalAlignment::Left) {
        lab.textAlignment = NSTextAlignmentLeft;
    }
    if (adaptiveAlignment == HorizontalAlignment::Right) {
        lab.textAlignment = NSTextAlignmentRight;
    }
    if (adaptiveAlignment == HorizontalAlignment::Center) {
        lab.textAlignment = NSTextAlignmentCenter;
    }

    configVisibility(lab, elem);

    return lab;
}

@end
