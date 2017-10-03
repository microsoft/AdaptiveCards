//
//  ACRColumnRenderer
//  ACRColumnRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "Column.h"
#import "SharedAdaptiveCard.h"

@implementation ACRColumnRenderer

+ (ACRColumnRenderer *)getInstance
{
    static ACRColumnRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::Column;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<Column> columnElem = std::dynamic_pointer_cast<Column>(elem);

    ContainerStyle style = ContainerStyle::Default;

    // Not set; apply parent's style
    if(columnElem->GetStyle() == ContainerStyle::None)
    {
        style = [viewGroup getStyle];
    }
    // apply elem's style if custom style is allowed
    else if (config->adaptiveCard.allowCustomStyle)
    {
        style = columnElem->GetStyle();
    }
    else
    {
        style = ContainerStyle::Default;
    }

    ACRColumnView* column = [[ACRColumnView alloc] initWithStyle:style hostConfig:config];
    [viewGroup addArrangedSubview:column];
    [ACRRenderer render:column
                 inputs:inputs
          withCardElems:columnElem->GetItems()
          andHostConfig:config];

    [column setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    [column setClipsToBounds:TRUE];
    if(columnElem->GetWidth() == "stretch")
    {
        [column setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    }

    [column adjustHuggingForLastElement];

    return column;
}

@end

