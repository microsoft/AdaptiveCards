//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputTableView.h"
#import "ChoiceSetInput.h"
#import "ACRChoiceSetViewDataSource.h"
#import "ACRChoiceSetViewDataSourceCompactStyle.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

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

- (UIView *)render:(UIView *)viewGroup
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
    if(!bundle){ // https://github.com/Microsoft/AdaptiveCards/issues/1834
        return nil;
    }
    ACRInputTableView *choiceSetView = [bundle loadNibNamed:@"ACRInputTableView" owner:self options:nil][0];
    choiceSetView.frame = CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.height);
    NSObject<UITableViewDelegate, UITableViewDataSource> *dataSource = nil;

<<<<<<< HEAD
    if(choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact)
    {
=======
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:checkedCheckboxReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:uncheckedCheckboxReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:checkedRadioButtonReuseID];
    [choiceSetView registerClass:[ACRChoiceSetCell class] forCellReuseIdentifier:uncheckedRadioButtonReuseID];

    if(choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact && choiceSet->GetIsMultiSelect() == false) {
>>>>>>> master
        dataSource = [[ACRChoiceSetViewDataSourceCompactStyle alloc] initWithInputChoiceSet:choiceSet rootView:rootView];
    }
    else
    {
        dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:choiceSet];
<<<<<<< HEAD
=======
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
>>>>>>> master
    }

    choiceSetView.delegate = dataSource;
    choiceSetView.dataSource = dataSource;
    [inputs addObject:dataSource];
<<<<<<< HEAD
=======

    if(elem->GetHeight() == HeightType::Stretch){
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:choiceSetView];
>>>>>>> master

    UIView *inputView = (UIView *)choiceSetView;

    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview:inputView];
    }

<<<<<<< HEAD
    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:inputView
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeLeading
                                 multiplier:1.0
                                   constant:0]];
    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:inputView
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1.0
                                   constant:0]];
=======
    [NSLayoutConstraint constraintWithItem:choiceSetView
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0].active = YES;

    [NSLayoutConstraint constraintWithItem:choiceSetView
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0].active = YES;
>>>>>>> master

    return inputView;
}

@end
