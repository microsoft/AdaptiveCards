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
    ACRUILabel *lab = [[ACRUILabel alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
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

    lab.area = lab.frame.size.width * lab.frame.size.height;

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:lab.frame];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    lab.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:wrappingview];
    [wrappingview addSubview:lab];

    lab.textContainer.maximumNumberOfLines = int(txtBlck->GetMaxLines());
    if (!lab.textContainer.maximumNumberOfLines && !txtBlck->GetWrap()) {
        lab.textContainer.maximumNumberOfLines = 1;
    }

    if (txtBlck->GetHeight() == HeightType::Auto) {
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    } else {
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    [lab setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];

    UILayoutGuide *leftGuide = nil;
    UILayoutGuide *rightGuide = nil;
    HorizontalAlignment adaptiveAlignment = txtBlck->GetHorizontalAlignment();

    if (adaptiveAlignment == HorizontalAlignment::Right) {
        leftGuide = [[UILayoutGuide alloc] init];
        leftGuide.identifier = @"text-left-guide";
        [wrappingview addLayoutGuide:leftGuide];
        [leftGuide.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor].active = YES;
        [leftGuide.trailingAnchor constraintEqualToAnchor:lab.leadingAnchor].active = YES;
        [leftGuide.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
        [lab.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor].active = YES;
    }

    if (adaptiveAlignment == HorizontalAlignment::Left) {
        rightGuide = [[UILayoutGuide alloc] init];
        rightGuide.identifier = @"text-right-guide";
        [wrappingview addLayoutGuide:rightGuide];
        NSLayoutConstraint *constraint = [rightGuide.leadingAnchor constraintEqualToAnchor:lab.trailingAnchor];
        constraint.active = YES;
        [rightGuide.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
        [rightGuide.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor].active = YES;
        [lab.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor].active = YES;
    }

    if (adaptiveAlignment == HorizontalAlignment::Center) {
        [lab.centerXAnchor constraintEqualToAnchor:wrappingview.centerXAnchor].active = YES;
    }

    [wrappingview.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
    [wrappingview.widthAnchor constraintGreaterThanOrEqualToAnchor:lab.widthAnchor].active = YES;

    [lab.centerYAnchor constraintEqualToAnchor:wrappingview.centerYAnchor].active = YES;

    configVisibility(wrappingview, elem);

    return wrappingview;
}

@end
