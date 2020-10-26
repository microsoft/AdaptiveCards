//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnSetView.h"
#import "ACRContentHoldingUIView.h"
#import "ACRInputLabelViewPrivate.h"
#import "ACRInputTableView.h"
#import "ACRSeparator.h"
#import "ACRToggleInputDataSource.h"
#import "ACRToggleInputView.h"
#import "ToggleInput.h"
#import "UtiliOS.h"

@implementation ACRInputToggleRenderer

+ (ACRInputToggleRenderer *)getInstance
{
    static ACRInputToggleRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRToggleInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ToggleInput> adaptiveToggleInput = std::dynamic_pointer_cast<ToggleInput>(elem);

    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    if (!bundle) { // https://github.com/Microsoft/AdaptiveCards/issues/1834
        return nil;
    }

    ACRToggleInputView *toggleView = [[ACRToggleInputView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.height)];

    toggleView.title.text = [NSString stringWithCString:adaptiveToggleInput->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    toggleView.title.textColor = getForegroundUIColorFromAdaptiveAttribute(config, viewGroup.style);
    toggleView.title.adjustsFontSizeToFitWidth = NO;
    toggleView.title.isAccessibilityElement = NO;

    if (!adaptiveToggleInput->GetWrap()) {
        toggleView.title.numberOfLines = 1;
        toggleView.title.lineBreakMode = NSLineBreakByTruncatingTail;
    }

    if (adaptiveToggleInput->GetValue() != adaptiveToggleInput->GetValueOn()) {
        toggleView.toggle.on = NO;
    }

    ACRToggleInputDataSource *dataSource = [[ACRToggleInputDataSource alloc] initWithInputToggle:adaptiveToggleInput WithHostConfig:config];
    dataSource.toggleSwitch = toggleView.toggle;

    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:adaptiveToggleInput inputView:toggleView accessibilityItem:toggleView.toggle viewGroup:viewGroup dataSource:dataSource];
    
    toggleView.isAccessibilityElement = NO;
    if (toggleView.title.text) {
        toggleView.toggle.accessibilityLabel = [NSString stringWithFormat:@"%@, %@,", toggleView.toggle.accessibilityLabel, toggleView.title.text];
    }

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
