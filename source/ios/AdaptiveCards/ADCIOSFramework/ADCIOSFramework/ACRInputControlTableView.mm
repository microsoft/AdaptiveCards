//
//  ACRInputControlTableView.mm
//  ACRInputControlTableView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRInputControlTableView.h"
#import "ToggleInput.h"
#import "ChoiceSetInput.h"

using namespace AdaptiveCards;

@implementation ACRInputControlTableView
{
    std::shared_ptr<ToggleInput> toggleInputDataSource;
    std::shared_ptr<ChoiceSetInput>   choiceSetDataSource;
    std::shared_ptr<HostConfig>  config;
    bool isMultichoiceAllowed;
}

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
{
    self = [super initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) style:style];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        isMultichoiceAllowed = false;
    }
    return self;
}

- (instancetype)initWithInputToggle:(std::shared_ptr<ToggleInput> const&)toggleInput
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
       WithSuperview:(UIView *)view
{
    self = [self initWithFrame:view.frame style:UITableViewStylePlain];
    if(self)
    {
        toggleInputDataSource = toggleInput;
        choiceSetDataSource   = nullptr;
        config = hostConfig;
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                        WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                         WithSuperview:(UIView *)view
{
    self = [self initWithFrame:view.frame style:UITableViewStyleGrouped];
    if(self)
    {
        choiceSetDataSource   = choiceSet;
        toggleInputDataSource = nullptr;
        config = hostConfig;
        isMultichoiceAllowed = choiceSetDataSource->GetIsMultiSelect();
    }
    return self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(toggleInputDataSource)
        return 1;
    else
        return choiceSetDataSource->GetChoices().size();
}
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"tabCellId";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
    }

    NSString *title = nil;

    if(toggleInputDataSource)
    {
        title = [NSString stringWithCString:toggleInputDataSource->GetTitle().c_str()
                           encoding:NSUTF8StringEncoding];
    }
    else
    {
        title = [NSString stringWithCString:choiceSetDataSource->GetChoices()[indexPath.row]->GetTitle().c_str()
                                   encoding:NSUTF8StringEncoding];
    }
    
    cell.textLabel.text = title;
    
    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if([tableView cellForRowAtIndexPath:indexPath].accessoryType ==
       UITableViewCellAccessoryCheckmark)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
    }
    else
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryCheckmark;
    }
}

- (void) tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if(isMultichoiceAllowed == false)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
    }
}

- (CGSize)intrinsicContentSize
{
    [self layoutIfNeeded];
    return self.contentSize;
}
@end
