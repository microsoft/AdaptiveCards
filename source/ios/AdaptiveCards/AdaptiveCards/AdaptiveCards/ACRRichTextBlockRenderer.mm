//
//  ACRRichTextBlockRenderer
//  ACRRichTextBlockRenderer.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACRRichTextBlockRenderer.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRAggregateTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRRegistration.h"
#import "ACRUILabel.h"
#import "ACRView.h"
#import "DateTimePreparsedToken.h"
#import "DateTimePreparser.h"
#import "HostConfig.h"
#import "MarkDownParser.h"
#import "RichTextBlock.h"
#import "TextRun.h"
#import "UtiliOS.h"

@implementation ACRRichTextBlockRenderer

+ (ACRRichTextBlockRenderer *)getInstance
{
    static ACRRichTextBlockRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRRichTextBlock;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<RichTextBlock> rTxtBlck = std::dynamic_pointer_cast<RichTextBlock>(elem);
    ACRUILabel *lab =
        [[ACRUILabel alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
    lab.backgroundColor = [UIColor clearColor];
    lab.style = [viewGroup style];
    lab.editable = NO;
    lab.textContainer.lineFragmentPadding = 0;
    lab.textContainerInset = UIEdgeInsetsZero;
    lab.layoutManager.usesFontLeading = false;

    NSMutableAttributedString *content = [[NSMutableAttributedString alloc] init];
    if (rootView) {
        NSMutableDictionary *textMap = [rootView getTextMap];

        for (const auto &inlineText : rTxtBlck->GetInlines()) {
            std::shared_ptr<TextRun> textRun = std::static_pointer_cast<TextRun>(inlineText);
            if (textRun) {
                NSNumber *number =
                    [NSNumber numberWithUnsignedLongLong:(unsigned long long)textRun.get()];
                NSString *key = [number stringValue];
                NSData *htmlData = nil;
                NSDictionary *options = nil;
                NSDictionary *descriptor = nil;
                NSString *text = nil;

                if (![textMap objectForKey:key]) {
                    RichTextElementProperties textProp;
                    TextRunToRichTextElementProperties(textRun, textProp);
                    buildIntermediateResultForText(rootView, acoConfig, textProp, key);
                }

                NSDictionary *data = textMap[key];
                if (data) {
                    htmlData = data[@"html"];
                    options = data[@"options"];
                    descriptor = data[@"descriptor"];
                    text = data[@"nonhtml"];
                }

                NSMutableAttributedString *textRunContent = nil;
                // Initializing NSMutableAttributedString for HTML rendering is very slow
                if (htmlData) {
                    textRunContent = [[NSMutableAttributedString alloc] initWithData:htmlData
                                                                             options:options
                                                                  documentAttributes:nil
                                                                               error:nil];
                    UpdateFontWithDynamicType(textRunContent);

                    lab.selectable = YES;
                    lab.dataDetectorTypes = UIDataDetectorTypeLink | UIDataDetectorTypePhoneNumber;
                    lab.userInteractionEnabled = YES;
                } else {
                    textRunContent = [[NSMutableAttributedString alloc] initWithString:text
                                                                            attributes:descriptor];
                }
                // Set paragraph style such as line break mode and alignment
                NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
                paragraphStyle.alignment =
                    [ACOHostConfig getTextBlockAlignment:rTxtBlck->GetHorizontalAlignment().value_or(HorizontalAlignment::Left)
                                                 context:rootView.context];

                // Obtain text color to apply to the attributed string
                ACRContainerStyle style = lab.style;
                auto textColor = textRun->GetTextColor().value_or(ForegroundColor::Default);
                auto foregroundColor = [acoConfig getTextBlockColor:style
                                                          textColor:textColor
                                                       subtleOption:textRun->GetIsSubtle().value_or(false)];

                // Config and add Select Action
                std::shared_ptr<BaseActionElement> baseAction = textRun->GetSelectAction();
                ACOBaseActionElement *acoAction = [[ACOBaseActionElement alloc] initWithBaseActionElement:baseAction];
                if (baseAction && [acoAction isEnabled]) {
                    NSObject *target;
                    if (ACRRenderingStatus::ACROk ==
                        buildTarget([rootView getSelectActionsTargetBuilderDirector], acoAction,
                                    &target)) {
                        NSRange selectActionRange = NSMakeRange(0, textRunContent.length);

                        [textRunContent addAttribute:@"SelectAction"
                                               value:target
                                               range:selectActionRange];

                        [ACRLongPressGestureRecognizerFactory
                            addTapGestureRecognizerToUITextView:lab
                                                         target:(NSObject<ACRSelectActionDelegate>
                                                                     *)target
                                                       rootView:rootView
                                                     hostConfig:acoConfig];

                        if (@available(iOS 13.0, *)) {
                            foregroundColor = UIColor.linkColor;
                        } else {
                            // Fallback on earlier versions
                            foregroundColor = [ACOHostConfig convertHexColorCodeToUIColor:"#007affff"];
                        }
                    }
                }

                // apply hightlight to textrun
                if (textRun->GetHighlight()) {
                    UIColor *highlightColor = [acoConfig getHighlightColor:style
                                                           foregroundColor:textRun->GetTextColor().value_or(ForegroundColor::Default)
                                                              subtleOption:textRun->GetIsSubtle().value_or(false)];
                    [textRunContent addAttribute:NSBackgroundColorAttributeName
                                           value:highlightColor
                                           range:NSMakeRange(0, textRunContent.length)];
                }

                if (textRun->GetStrikethrough()) {
                    [textRunContent addAttribute:NSStrikethroughStyleAttributeName
                                           value:[NSNumber numberWithInteger:NSUnderlineStyleSingle]
                                           range:NSMakeRange(0, textRunContent.length)];
                }

                if (textRun->GetUnderline()) {
                    [textRunContent addAttribute:NSUnderlineStyleAttributeName
                                           value:[NSNumber numberWithInteger:NSUnderlineStyleSingle]
                                           range:NSMakeRange(0, textRunContent.length)];
                }

                // Add paragraph style, text color, text weight as attributes to a
                // NSMutableAttributedString, content.
                [textRunContent addAttributes:@{
                    NSParagraphStyleAttributeName : paragraphStyle,
                    NSForegroundColorAttributeName : foregroundColor,
                }
                                        range:NSMakeRange(0, textRunContent.length)];

                [content appendAttributedString:textRunContent];
            }
        }
    }

    lab.textContainer.lineBreakMode = NSLineBreakByTruncatingTail;
    lab.attributedText = content;
    lab.isAccessibilityElement = YES;
    if ([content.string stringByTrimmingCharactersInSet:NSCharacterSet.whitespaceCharacterSet].length == 0) {
        lab.accessibilityElementsHidden = YES;
    }
    lab.area = lab.frame.size.width * lab.frame.size.height;

    lab.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:lab];

    HorizontalAlignment adaptiveAlignment = rTxtBlck->GetHorizontalAlignment().value_or(HorizontalAlignment::Left);

    if (adaptiveAlignment == HorizontalAlignment::Left) {
        lab.textAlignment = NSTextAlignmentLeft;
    }
    if (adaptiveAlignment == HorizontalAlignment::Right) {
        lab.textAlignment = NSTextAlignmentRight;
    }
    if (adaptiveAlignment == HorizontalAlignment::Center) {
        lab.textAlignment = NSTextAlignmentCenter;
    }

    lab.textContainer.maximumNumberOfLines = 0;

    if (rTxtBlck->GetHeight() == HeightType::Auto) {
        [lab setContentCompressionResistancePriority:UILayoutPriorityRequired
                                             forAxis:UILayoutConstraintAxisVertical];
        [lab setContentHuggingPriority:UILayoutPriorityDefaultHigh
                               forAxis:UILayoutConstraintAxisVertical];
    } else {
        [lab setContentHuggingPriority:UILayoutPriorityDefaultLow
                               forAxis:UILayoutConstraintAxisVertical];
        [lab setContentCompressionResistancePriority:UILayoutPriorityRequired
                                             forAxis:UILayoutConstraintAxisVertical];
    }

    [lab setContentCompressionResistancePriority:UILayoutPriorityRequired
                                         forAxis:UILayoutConstraintAxisHorizontal];

    [lab setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    configRtl(lab, rootView.context);

    return lab;
}

@end
