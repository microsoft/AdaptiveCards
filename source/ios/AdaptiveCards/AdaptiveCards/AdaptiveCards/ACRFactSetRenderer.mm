//
//  ACRFactSetRenderer
//  ACRFactSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRFactSetRenderer.h"
#import "ACRSeparator.h"
#import "ACRColumnSetView.h"
#import "FactSet.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRFactSetRenderer

+ (ACRFactSetRenderer *)getInstance
{
    static ACRFactSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::FactSet;
}

- (UILabel *)buildLabel:(NSString *)text
            hostConfig:(std::shared_ptr<HostConfig> const &)config
            textConfig:(TextConfig const &)txtConfig
        containerStyle:(ContainerStyle)style
{
    UILabel *lab = [[UILabel alloc] init];

    ColorsConfig &colorConfig = (style == ContainerStyle::Emphasis)?
        config->containerStyles.emphasisPalette.foregroundColors:
        config->containerStyles.defaultPalette.foregroundColors;

    NSMutableAttributedString *content =
    [[NSMutableAttributedString alloc] initWithString:text
                                           attributes:@{NSForegroundColorAttributeName:
                                                            [ACRTextBlockRenderer getTextBlockColor:txtConfig.color
                                                                                        colorsConfig:colorConfig
                                                                                       subtleOption:txtConfig.isSubtle],
                                                            NSStrokeWidthAttributeName:[ACRTextBlockRenderer getTextBlockTextWeight:txtConfig.weight
                                                                                                                     withHostConfig:config]}];
    NSMutableParagraphStyle *para = [[NSMutableParagraphStyle alloc] init];
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range:NSMakeRange(0,1)];
    lab.attributedText = content;
    UIFontDescriptor *dec = lab.font.fontDescriptor;
    lab.font = [UIFont fontWithDescriptor:dec size:[ACRTextBlockRenderer getTextBlockTextSize:txtConfig.size withHostConfig:config]];
    return lab;
}
- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<FactSet> fctSet = std::dynamic_pointer_cast<FactSet>(elem);

    UIStackView *titleStack = [[UIStackView alloc] init];
    titleStack.axis = UILayoutConstraintAxisVertical;

    UIStackView *valueStack = [[UIStackView alloc] init];
    valueStack.axis = UILayoutConstraintAxisVertical;
    ContainerStyle style = [viewGroup getStyle];

    for(auto fact :fctSet->GetFacts())
    {
        NSString *title = [NSString stringWithCString:fact->GetTitle().c_str()
                                                    encoding:NSUTF8StringEncoding];
        UILabel *titleLab = [self buildLabel:title
                                  hostConfig:config
                                  textConfig:config->factSet.title
                              containerStyle:style];

        NSString *value = [NSString stringWithCString:fact->GetValue().c_str()
                                             encoding:NSUTF8StringEncoding];
        UILabel *valueLab = [self buildLabel:value
                                  hostConfig:config
                                  textConfig:config->factSet.value
                              containerStyle:style];

        [titleStack addArrangedSubview:titleLab];
        [valueStack addArrangedSubview:valueLab];
    }

    ACRColumnSetView *factSetView = [[ACRColumnSetView alloc] init];

    [factSetView addArrangedSubview:titleStack];
    [titleStack setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];

    [ACRSeparator renderSeparationWithFrame:CGRectMake(0, 0, config->factSet.spacing, config->factSet.spacing)
                                  superview:factSetView
                                       axis:UILayoutConstraintAxisHorizontal];
    [factSetView addArrangedSubview:valueStack];

    [ACRSeparator renderSeparationWithFrame:CGRectMake(0, 0, config->factSet.spacing, config->factSet.spacing)
                                  superview:factSetView
                                       axis:UILayoutConstraintAxisHorizontal];

    [factSetView adjustHuggingForLastElement];

    [viewGroup addArrangedSubview:factSetView];

    return factSetView;
}
@end
