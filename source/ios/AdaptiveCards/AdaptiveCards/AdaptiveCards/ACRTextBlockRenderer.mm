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
    //NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    //ACRUILabel *lab = [bundle loadNibNamed:@"ACRLabelView" owner:rootView options:nil][0];
    ACRUILabel *lab = [[ACRUILabel alloc] initWithFrame:CGRectMake(0,0,viewGroup.frame.size.width, 0)];
    lab.backgroundColor = [UIColor clearColor];

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
            lab.selectable = YES;
            lab.dataDetectorTypes = UIDataDetectorTypeLink;
            lab.userInteractionEnabled = YES;
        } else {
            // if html rendering is skipped, remove p tags from both ends (<p>, </p>)
            content = [[NSMutableAttributedString alloc] initWithString:text attributes:descriptor];
            [content deleteCharactersInRange:NSMakeRange(0, 3)];
            [content deleteCharactersInRange:NSMakeRange([content length] -4, 4)];
        }
        //CGRect boundingrect = [lab.layoutManager lineFragmentRectForGlyphAtIndex:0 effectiveRange:nil];
        //lab.frame = boundingrect;
        lab.editable = NO;
        lab.textContainer.lineFragmentPadding = 0;
        lab.textContainerInset = UIEdgeInsetsZero;
        lab.layoutManager.usesFontLeading = false;
        //lab.scrollEnabled = NO;
        
        // Set paragraph style such as line break mode and alignment
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        //paragraphStyle.lineBreakMode = NSLineBreakByTruncatingTail;
        paragraphStyle.alignment = [ACOHostConfig getTextBlockAlignment:txtBlck->GetHorizontalAlignment()];

        // Obtain text color to apply to the attributed string
        ACRContainerStyle style = lab.style;
        ColorsConfig &colorConfig = (style == ACREmphasis)? config->containerStyles.emphasisPalette.foregroundColors:
        config->containerStyles.defaultPalette.foregroundColors;
        // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
        [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle, NSForegroundColorAttributeName:[ACOHostConfig getTextBlockColor:txtBlck->GetTextColor() colorsConfig:colorConfig subtleOption:txtBlck->GetIsSubtle()],} range:NSMakeRange(0, content.length)];
        //lab.attributedText = content;

        //boundingrect.size.width = viewGroup.frame.size.width;
        //lab.frame = boundingrect;
        lab.textContainer.lineBreakMode = NSLineBreakByTruncatingTail;
        lab.attributedText = content;
    }
    [lab sizeToFit];
    
    lab.area = lab.frame.size.width * lab.frame.size.height;
    //lab.widthConstraint = [NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:lab.frame.size.width];
    //lab.heightConstraint = [NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:lab.frame.size.height];
    lab.widthConstraint.active = YES;
    lab.heightConstraint.active = YES;

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:lab.frame];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    lab.translatesAutoresizingMaskIntoConstraints = NO;
    [viewGroup addArrangedSubview:wrappingview];
    //[NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:viewGroup attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
    
    //[NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:viewGroup attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
    
    [wrappingview addSubview:lab];
    NSLayoutAttribute horizontalAlignment = NSLayoutAttributeLeading;
    if(txtBlck->GetHorizontalAlignment() == HorizontalAlignment::Right) {
        horizontalAlignment = NSLayoutAttributeTrailing;
    } else if (txtBlck->GetHorizontalAlignment() == HorizontalAlignment::Center) {
        horizontalAlignment = NSLayoutAttributeCenterX;
    }


    //[NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:viewGroup //attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
    
    //[NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:viewGroup attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
    
    [wrappingview addSubview:lab];
    
    [NSLayoutConstraint constraintWithItem:lab attribute:horizontalAlignment relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:horizontalAlignment multiplier:1.0 constant:0].active = YES;
    //[NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:lab attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:wrappingview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
    
    lab.textContainer.maximumNumberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.textContainer.maximumNumberOfLines and !txtBlck->GetWrap()){
        lab.textContainer.maximumNumberOfLines = 1;
    }
    //[viewGroup addArrangedSubview:lab];
    //lab.translatesAutoresizingMaskIntoConstraints = NO;
    if(txtBlck->GetHeight() == HeightType::Auto){
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    } else {
        [wrappingview setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        lab.isStretchable = YES;
    }
    
    [NSLayoutConstraint constraintWithItem:wrappingview attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationGreaterThanOrEqual toItem:lab attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0].active = YES;
    
    [lab setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    [wrappingview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];

    return wrappingview;
}

@end
