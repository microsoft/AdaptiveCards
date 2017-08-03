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
    std::shared_ptr<ChoiceSetInput> choiceSetDataSource;
    std::shared_ptr<HostConfig> config;
    NSString *id;
    NSString *valueOn;
    NSString *valueOff;
    BOOL isMultichoiceAllowed;
    BOOL isToggleInput;
    BOOL isSelected;
    NSMutableDictionary *results;
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
        isMultichoiceAllowed = YES;
        isSelected = NO;
        results = nil;
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
        isToggleInput = YES;
        config = hostConfig;
        id = [[NSString alloc]initWithCString:toggleInputDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        if(toggleInputDataSource->GetValue() == toggleInputDataSource->GetValueOn())
        {
            isSelected = YES;
        }
        valueOn  = [[NSString alloc]initWithCString:toggleInputDataSource->GetValueOn().c_str()
                                           encoding:NSUTF8StringEncoding];
        valueOff = [[NSString alloc]initWithCString:toggleInputDataSource->GetValueOff().c_str()
                                           encoding:NSUTF8StringEncoding];
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
        choiceSetDataSource = choiceSet;
        isToggleInput = NO;
        config = hostConfig;
        id = [[NSString alloc]initWithCString:choiceSetDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        isMultichoiceAllowed = choiceSetDataSource->GetIsMultiSelect();
        results = [[NSMutableDictionary alloc]init];
    }
    return self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(isToggleInput)
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

    if(isToggleInput)
    {
        title = [NSString stringWithCString:toggleInputDataSource->GetTitle().c_str()
                           encoding:NSUTF8StringEncoding];
        if(isSelected)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
        }
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
        isSelected = NO;
        results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
    else
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryCheckmark;
        isSelected = YES;
        results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:YES];
    }
}

- (void) tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if(isMultichoiceAllowed == NO)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
        results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
}

- (CGSize)intrinsicContentSize
{
    [self layoutIfNeeded];
    return self.contentSize;
}

- (bool)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    if(isToggleInput)
    {
        dictionary[id] = isSelected? valueOn : valueOff;
    }
    else
    {
        NSMutableArray* values = [[NSMutableArray alloc] init];
        for(NSInteger i = 0; i < [results count]; i++)
        {
            if([results[[NSNumber numberWithInteger:i]] boolValue] == YES)
            {
                [values addObject:
                 [NSString stringWithCString:choiceSetDataSource->GetChoices()[i]->GetValue().c_str()
                                    encoding:NSUTF8StringEncoding]];
                 
            }
        }
        dictionary[id] = [values componentsJoinedByString:@";"];
    }
    
}
@end
