//
//  ACRInputTableViewController
//  ACRInputTableViewController.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRInputTableViewController.h"
//#import "ChoiceInput.h"
//#import "ChoiceSetInput.h"

@implementation ACRInputTableViewController
{
    std::shared_ptr<AdaptiveCards::ChoiceSetInput> _choices;
    NSMutableDictionary *_userSelections;
    BOOL _isMultiChoicesAllowed;
    BOOL _isSelected;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                            //hostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                                 style:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if(self)
    {
        _choices = choiceSet;
        //config = hostConfig;
        _isMultiChoicesAllowed = _choices->GetIsMultiSelect();
        _isSelected = NO;
        _userSelections = [[NSMutableDictionary alloc]init];
    }
    return self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return _choices->GetChoices().size();
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if([tableView cellForRowAtIndexPath:indexPath].accessoryType ==
       UITableViewCellAccessoryCheckmark)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType = UITableViewCellAccessoryNone;
        _isSelected = NO;
        _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
    else
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryCheckmark;
        _isSelected = YES;
        _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:YES];
    }
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

    NSString *title = [NSString stringWithCString:_choices->GetChoices()[indexPath.row]->GetTitle().c_str()
                               encoding:NSUTF8StringEncoding];
    cell.textLabel.text = title;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}

- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if(_isMultiChoicesAllowed == NO)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
        _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
}
/*
*/

/*
- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSMutableArray *values = [[NSMutableArray alloc] init];
    for(NSInteger i = 0; i < [self.results count]; i++)
    {
        if([self.results[[NSNumber numberWithInteger:i]] boolValue] == YES)
        {
            [values addObject:
             [NSString stringWithCString:choiceSetDataSource->GetChoices()[i]->GetValue().c_str()
                                encoding:NSUTF8StringEncoding]];

        }
    }
    dictionary[self.id] = [values componentsJoinedByString:@";"];
}
 */
@end
