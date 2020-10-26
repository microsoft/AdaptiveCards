//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRInputChoiceSetRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRChoiceSetViewDataSource.h"
#import "ACRChoiceSetViewDataSourceCompactStyle.h"
#import "ACRInputLabelViewPrivate.h"
#import "ACRInputTableView.h"
#import "ChoiceSetInput.h"
#import "UtiliOS.h"

@implementation ACRInputChoiceSetRenderer

+ (ACRInputChoiceSetRenderer *)getInstance
{
    static ACRInputChoiceSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRChoiceSetInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    // creates a tableview with pre-defined style
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    if (!bundle) { // https://github.com/Microsoft/AdaptiveCards/issues/1834
        return nil;
    }
    ACRInputTableView *choiceSetView = [bundle loadNibNamed:@"ACRInputTableView" owner:self options:nil][0];
    choiceSetView.frame = CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.height);
    NSObject<UITableViewDelegate, UITableViewDataSource, ACRIBaseInputHandler> *dataSource = nil;

    if (choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact && choiceSet->GetIsMultiSelect() == false) {
        dataSource = [[ACRChoiceSetViewDataSourceCompactStyle alloc] initWithInputChoiceSet:choiceSet rootView:rootView];
    } else {
        dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:choiceSet WithHostConfig:config];
        ((ACRChoiceSetViewDataSource *)dataSource).spacing = choiceSetView.inputTableViewSpacing;
    }

    [choiceSetView registerNib:[UINib nibWithNibName:@"ACRChoiceSetCellUnchecked" bundle:bundle] forCellReuseIdentifier:uncheckedCheckboxReuseID];
    [choiceSetView registerNib:[UINib nibWithNibName:@"ACRChoiceSetCellChecked" bundle:bundle] forCellReuseIdentifier:checkedCheckboxReuseID];
    [choiceSetView registerNib:[UINib nibWithNibName:@"ACRChoiceSetCellCompactChecked" bundle:bundle] forCellReuseIdentifier:checkedRadioButtonReuseID];
    [choiceSetView registerNib:[UINib nibWithNibName:@"ACRChoiceSetCellCompactUnchecked" bundle:bundle] forCellReuseIdentifier:uncheckedRadioButtonReuseID];

    choiceSetView.delegate = dataSource;
    choiceSetView.dataSource = dataSource;
    
    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:choiceSet inputView:choiceSetView accessibilityItem:choiceSetView viewGroup:viewGroup dataSource:dataSource];
    choiceSetView.isAccessibilityElement = NO;
    choiceSetView.shouldGroupAccessibilityChildren = YES;
    [inputs addObject:inputLabelView];

    if (elem->GetHeight() == HeightType::Stretch) {
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:inputLabelView];

        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview:textInputContainer];
    } else {
        [viewGroup addArrangedSubview:inputLabelView];
    }

    configVisibility(inputLabelView, elem);

    return inputLabelView;
}

@end
