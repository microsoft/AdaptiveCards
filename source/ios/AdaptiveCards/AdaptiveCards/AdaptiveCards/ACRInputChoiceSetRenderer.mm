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
    NSObject<UITableViewDelegate, UITableViewDataSource> *dataSource = nil;

    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:checkedCheckboxReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:uncheckedCheckboxReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:checkedRadioButtonReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:uncheckedRadioButtonReuseID];

    if (choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact && choiceSet->GetIsMultiSelect() == false) {
        dataSource = [[ACRChoiceSetViewDataSourceCompactStyle alloc] initWithInputChoiceSet:choiceSet rootView:rootView];
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    } else {
        dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:choiceSet WithHostConfig:config];
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    }

    choiceSetView.delegate = dataSource;
    choiceSetView.dataSource = dataSource;
    [inputs addObject:dataSource];

    if (elem->GetHeight() == HeightType::Stretch) {
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:choiceSetView];

        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview:textInputContainer];
    } else {
        [viewGroup addArrangedSubview:choiceSetView];
    }

    configVisibility(choiceSetView, elem);

    return choiceSetView;
}

@end
