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
#import "Util.h"

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
    ACRUILabel *lab = [[ACRUILabel alloc] initWithFrame:CGRectMake(0,0,viewGroup.frame.size.width, 0)];
    lab.backgroundColor = [UIColor clearColor];

    lab.style = [viewGroup style];
    NSMutableAttributedString *content = nil;
    if(rootView){
        NSMutableDictionary *textMap = [rootView getTextMap];
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
            lab.selectable = YES;
            lab.dataDetectorTypes = UIDataDetectorTypeLink;
            lab.userInteractionEnabled = YES;
        } else {
            // if html rendering is skipped, remove p tags from both ends (<p>, </p>)
            content = [[NSMutableAttributedString alloc] initWithString:text attributes:descriptor];
            [content deleteCharactersInRange:NSMakeRange(0, 3)];
            [content deleteCharactersInRange:NSMakeRange([content length] -4, 4)];
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
        [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle, NSForegroundColorAttributeName:foregroundColor,} range:NSMakeRange(0, content.length)];
        
        lab.textContainer.lineBreakMode = NSLineBreakByTruncatingTail;
        lab.attributedText = content;
    }

    lab.area = lab.frame.size.width * lab.frame.size.height;

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:lab.frame];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    lab.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:wrappingview];
    [wrappingview addSubview:lab];

    NSLayoutAttribute horizontalAlignment = NSLayoutAttributeLeading;
    //if(txtBlck->GetHorizontalAlignment() == HorizontalAlignment::Right) {
    //    horizontalAlignment = NSLayoutAttributeTrailing;
    //} else if (txtBlck->GetHorizontalAlignment() == HorizontalAlignment::Center) {
    //    horizontalAlignment = NSLayoutAttributeCenterX;
    //}

    //[NSLayoutConstraint constraintWithItem:lab attribute:horizontalAlignment relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:horizontalAlignment multiplier:1.0 constant:0].active = YES;
    //[NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
    //[NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;

    lab.textContainer.maximumNumberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.textContainer.maximumNumberOfLines && !txtBlck->GetWrap()){
        lab.textContainer.maximumNumberOfLines = 1;
    }

    if(txtBlck->GetHeight() == HeightType::Auto){
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    } else {
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    //[NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationGreaterThanOrEqual toItem:lab attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0].active = YES;
    [lab setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    //[wrappingview setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];


    UILayoutGuide *leftGuide = nil;
    UILayoutGuide *rightGuide = nil;
    HorizontalAlignment adaptiveAlignment = txtBlck->GetHorizontalAlignment();

    if (adaptiveAlignment == HorizontalAlignment::Left || adaptiveAlignment == HorizontalAlignment::Center) {
        leftGuide = [[UILayoutGuide alloc] init];
        leftGuide.identifier = @"text-left-guide";
        [wrappingview addLayoutGuide:leftGuide];
        [leftGuide.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor].active = YES;
        NSLayoutConstraint *constraint = [leftGuide.trailingAnchor constraintEqualToAnchor:lab.leadingAnchor];
        constraint.priority = 998;
        constraint.active = YES;
        [leftGuide.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
        //NSLayoutConstraint *leadingConstraint = [lab.leadingAnchor constraintEqualToAnchor:wrappingview.leadingAnchor];
        //leadingConstraint.priority = 1000;
        //leadingConstraint.active = YES;
    }

    if (adaptiveAlignment == HorizontalAlignment::Right || adaptiveAlignment == HorizontalAlignment::Center) {
        rightGuide = [[UILayoutGuide alloc] init];
        rightGuide.identifier = @"text-right-guide";
        [wrappingview addLayoutGuide:rightGuide];
        NSLayoutConstraint *constraint = [rightGuide.leadingAnchor constraintEqualToAnchor:lab.trailingAnchor];
        constraint.priority = 998;
        constraint.active = YES;
        [rightGuide.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
        [rightGuide.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor].active = YES;
        //NSLayoutConstraint *trailingConstraint = [lab.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor];
        //trailingConstraint.priority = 1000;
        //trailingConstraint.active = YES;
    }
    
    //if (adaptiveAlignment == HorizontalAlignment::Right) {
    //    NSLayoutConstraint *trailingConstraint = [lab.trailingAnchor constraintEqualToAnchor:wrappingview.trailingAnchor];
    //    trailingConstraint.priority = 1000;
    //    trailingConstraint.active = YES;
    //}
    
    if (leftGuide && rightGuide) {
        [leftGuide.widthAnchor constraintEqualToAnchor:rightGuide.widthAnchor multiplier:1.0].active = YES;
    }

    [wrappingview.heightAnchor constraintEqualToAnchor:lab.heightAnchor].active = YES;
    [wrappingview.widthAnchor constraintGreaterThanOrEqualToAnchor:lab.widthAnchor].active = YES;
    
    [lab.centerYAnchor constraintEqualToAnchor:wrappingview.centerYAnchor].active = YES;

    configVisibility(wrappingview, elem);

    return wrappingview;
}

@end
