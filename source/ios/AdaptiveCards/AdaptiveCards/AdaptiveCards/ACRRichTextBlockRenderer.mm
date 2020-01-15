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
                    lab.selectable = YES;
                    lab.dataDetectorTypes = UIDataDetectorTypeLink | UIDataDetectorTypePhoneNumber;
                    lab.userInteractionEnabled = YES;
                } else {
                    textRunContent = [[NSMutableAttributedString alloc] initWithString:text
                                                                            attributes:descriptor];
                    // text is preprocessed by markdown parser, and will wrapped by <p></P>
                    // lines below remove the p tags
                    [textRunContent deleteCharactersInRange:NSMakeRange(0, 3)];
                    [textRunContent
                        deleteCharactersInRange:NSMakeRange([textRunContent length] - 4, 4)];
                }
                // Set paragraph style such as line break mode and alignment
                NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
                paragraphStyle.alignment =
                    [ACOHostConfig getTextBlockAlignment:rTxtBlck->GetHorizontalAlignment()];

                // Obtain text color to apply to the attributed string
                ACRContainerStyle style = lab.style;
                auto foregroundColor = [acoConfig getTextBlockColor:style
                                                          textColor:textRun->GetTextColor()
                                                       subtleOption:textRun->GetIsSubtle()];

                // Config and add Select Action
                std::shared_ptr<BaseActionElement> baseAction = textRun->GetSelectAction();
                if (baseAction) {
                    NSObject *target;
                    if (ACRRenderingStatus::ACROk ==
                        buildTarget([rootView getSelectActionsTargetBuilderDirector], baseAction,
                                    &target)) {
                        NSRange selectActionRange = NSMakeRange(0, textRunContent.length - 1);

                        [textRunContent addAttribute:@"SelectAction"
                                               value:target
                                               range:selectActionRange];
                        [ACRLongPressGestureRecognizerFactory
                            addTapGestureRecognizerToUITextView:lab
                                                         target:(NSObject<ACRSelectActionDelegate>
                                                                     *)target
                                                       rootView:rootView
                                                     hostConfig:acoConfig];

                        [textRunContent addAttribute:NSUnderlineStyleAttributeName
                                               value:[NSNumber numberWithInt:NSUnderlineStyleSingle]
                                               range:selectActionRange];
                        [textRunContent addAttribute:NSUnderlineColorAttributeName
                                               value:foregroundColor
                                               range:selectActionRange];
                    }
                }

                // apply hightlight to textrun
                if (textRun->GetHighlight()) {
                    UIColor *highlightColor = [acoConfig getHighlightColor:style
                                                           foregroundColor:textRun->GetTextColor()
                                                              subtleOption:textRun->GetIsSubtle()];
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
                                        range:NSMakeRange(0, textRunContent.length - 1)];

                [content appendAttributedString:textRunContent];
            }
        }
    }

    lab.textContainer.lineBreakMode = NSLineBreakByTruncatingTail;
    lab.attributedText = content;
    lab.area = lab.frame.size.width * lab.frame.size.height;

    ACRContentHoldingUIView *wrappingview =
        [[ACRContentHoldingUIView alloc] initWithFrame:lab.frame];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    lab.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:wrappingview];
    [wrappingview addSubview:lab];

    NSLayoutAttribute horizontalAlignment = NSLayoutAttributeLeading;
    if (rTxtBlck->GetHorizontalAlignment() == HorizontalAlignment::Right) {
        horizontalAlignment = NSLayoutAttributeTrailing;
    } else if (rTxtBlck->GetHorizontalAlignment() == HorizontalAlignment::Center) {
        horizontalAlignment = NSLayoutAttributeCenterX;
    }

    [NSLayoutConstraint constraintWithItem:lab
                                 attribute:horizontalAlignment
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:wrappingview
                                 attribute:horizontalAlignment
                                multiplier:1.0
                                  constant:0]
        .active = YES;
    [NSLayoutConstraint constraintWithItem:lab
                                 attribute:NSLayoutAttributeBottom
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:wrappingview
                                 attribute:NSLayoutAttributeBottom
                                multiplier:1.0
                                  constant:0]
        .active = YES;
    [NSLayoutConstraint constraintWithItem:lab
                                 attribute:NSLayoutAttributeTop
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:wrappingview
                                 attribute:NSLayoutAttributeTop
                                multiplier:1.0
                                  constant:0]
        .active = YES;

    lab.textContainer.maximumNumberOfLines = 0;

    if (rTxtBlck->GetHeight() == HeightType::Auto) {
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                      forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultHigh
                                        forAxis:UILayoutConstraintAxisVertical];
    } else {
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultLow
                                        forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                      forAxis:UILayoutConstraintAxisVertical];
    }

    [NSLayoutConstraint constraintWithItem:wrappingview
                                 attribute:NSLayoutAttributeWidth
                                 relatedBy:NSLayoutRelationGreaterThanOrEqual
                                    toItem:lab
                                 attribute:NSLayoutAttributeWidth
                                multiplier:1.0
                                  constant:0]
        .active = YES;
    [lab setContentCompressionResistancePriority:UILayoutPriorityRequired
                                         forAxis:UILayoutConstraintAxisHorizontal];
    [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                  forAxis:UILayoutConstraintAxisHorizontal];

    configVisibility(wrappingview, elem);

    return wrappingview;
}

@end
