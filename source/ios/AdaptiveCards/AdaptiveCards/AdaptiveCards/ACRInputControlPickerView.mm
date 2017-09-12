//
//  ACRInputControlPickerView.mm
//  ACRInputControlPickerView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRInputControlPickerView.h"
#import "ChoiceInput.h"

using namespace AdaptiveCards;

@implementation ACRInputControlPickerView
{
    std::shared_ptr<ChoiceSetInput> choiceSetDataSource;
    std::shared_ptr<HostConfig> config;
    NSInteger defaultIdx;
    NSString *id;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.showsSelectionIndicator = YES;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        defaultIdx = 0;
        id = nil;
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                             superview:(UIView *)view
{
    self = [self initWithFrame:view.frame];
    if(self)
    {
        choiceSetDataSource = choiceSet;
        // get default choice
        for(defaultIdx = 0; defaultIdx < choiceSetDataSource->GetChoices().size(); defaultIdx++)
            if(choiceSetDataSource->GetChoices()[defaultIdx]->GetIsSelected())
                break;

        defaultIdx %= choiceSetDataSource->GetChoices().size();

        config = hostConfig;
    }
    id = [NSString stringWithCString:choiceSetDataSource->GetId().c_str() encoding:NSUTF8StringEncoding];
    return self;
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    return choiceSetDataSource->GetChoices().size();
}

- (UIView *)pickerView:(UIPickerView *)pickerView
            viewForRow:(NSInteger)row
          forComponent:(NSInteger)component
           reusingView:(UIView *)view
{
    std::shared_ptr<ChoiceInput> choiceInput = choiceSetDataSource->GetChoices()[row];

    UILabel *choice = (view)?(UILabel *)view : [[UILabel alloc] init];
    NSString *choiceText = [NSString stringWithCString:choiceInput->GetTitle().c_str()
                               encoding:NSUTF8StringEncoding];
    choice.text = choiceText;

    return choice;
}

- (void)setDefaultView
{
    [self selectRow:defaultIdx inComponent:0 animated:NO];
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSInteger idx;
    idx = [self selectedRowInComponent:0];
    dictionary[id] =
    [NSString stringWithCString:choiceSetDataSource->GetChoices()[(int) idx]->GetValue().c_str()
                       encoding:NSUTF8StringEncoding];

}

@end
