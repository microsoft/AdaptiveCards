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
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                        WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                         WithSuperview:(UIView* )view
{
    self = [self initWithFrame:view.frame];
    if(self)
    {
        choiceSetDataSource = choiceSet;
        config = hostConfig;
    }
    return self;
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView* )pickerView
{
    return 1; 
}

- (NSInteger)pickerView:(UIPickerView* )pickerView numberOfRowsInComponent:(NSInteger)component
{
    return choiceSetDataSource->GetChoices().size();
}

- (UIView *)pickerView:(UIPickerView *)pickerView 
            viewForRow:(NSInteger)row 
                      forComponent:(NSInteger)component 
                                 reusingView:(UIView *)view
{
    UILabel* choice = [[UILabel alloc] init];
    NSString* choiceText = [NSString stringWithCString:choiceSetDataSource->GetChoices()[row]->GetTitle().c_str()
                               encoding:NSUTF8StringEncoding];
    choice.text = choiceText;
    return choice;
}
@end
