//
//  ACRFactSetRenderer
//  ACRFactSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRFactSetRenderer.h"
#import "FactSet.h"

@implementation ACRFactSetRenderer

+ (ACRFactSetRenderer* )getInstance
{
    static ACRFactSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::FactSet;
}

- (UILabel* )buildLabel:(NSString* )text
         withHostConfig:(std::shared_ptr<HostConfig> const &)config
         withTextConfig:(TextConfig const &)txtConfig
{
    UILabel* lab = [[UILabel alloc] init];
    NSMutableAttributedString* content =
    [[NSMutableAttributedString alloc] initWithString:text
                                           attributes:@{NSForegroundColorAttributeName:
                                                            [ACRTextBlockRenderer getTextBlockColor:txtConfig.color withHostConfig:config andSubtleOption:txtConfig.isSubtle],
                                                        NSStrokeWidthAttributeName:[ACRTextBlockRenderer getTextBlockTextWeight:txtConfig.weight withHostConfig:config]}];
    NSMutableParagraphStyle* para = [[NSMutableParagraphStyle alloc] init];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range:NSMakeRange(0,1)];
    lab.attributedText = content;
    UIFontDescriptor* dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[ACRTextBlockRenderer getTextBlockTextSize:txtConfig.size withHostConfig:config]];
    return lab;
}
- (UIView* )render:(UIStackView* )viewGroup
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<FactSet> fctSet = std::dynamic_pointer_cast<FactSet>(elem);
    
    UIStackView* titleStack = [[UIStackView alloc] init];
    titleStack.axis = UILayoutConstraintAxisVertical;

    UIStackView* valueStack = [[UIStackView alloc] init];
    valueStack.axis = UILayoutConstraintAxisVertical;
    
    for(auto fact :fctSet->GetFacts())
    {
        NSString* title = [NSString stringWithCString:fact->GetTitle().c_str()
                                                    encoding:NSUTF8StringEncoding];
        UILabel* titleLab = [self buildLabel:title 
                              withHostConfig:config
                              withTextConfig:config->factSet.title];

        NSString* value = [NSString stringWithCString:fact->GetValue().c_str()
                                                    encoding:NSUTF8StringEncoding];
        UILabel* valueLab = [self buildLabel:value 
                              withHostConfig:config
                              withTextConfig:config->factSet.value];
        
        [titleStack addArrangedSubview:titleLab];
        // spacing will be added -- need clarification
        [valueStack addArrangedSubview:valueLab];
    }
    
    UIStackView* factSetView = [[UIStackView alloc] init];
    
    [factSetView addArrangedSubview:titleStack];
    [factSetView addArrangedSubview:valueStack];
    if(viewGroup) [ viewGroup addArrangedSubview:factSetView];
    return factSetView;
}
@end
