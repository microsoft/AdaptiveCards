//
//  ACRChoiceSetView.mm
//  ACRChoiceSetView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRChoiceSetView.h"
#import "ACRInputTableViewController.h"

using namespace AdaptiveCards;

@implementation ACRChoiceSetView
{
    std::shared_ptr<ChoiceSetInput> _choiceSetDataSource;
    std::shared_ptr<HostConfig> _config;
    BOOL _isMultichoicesAllowed;
    ACRInputTableViewController *_tableViewController;
    NSIndexPath *_indexPath;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                             superview:(UIView *)view
                        viewController:(UIViewController *)vc
{
    self = [super initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height) style:UITableViewStyleGrouped ];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.isSelected = NO;
        self.vc = vc;
        self.id = [[NSString alloc]initWithCString:choiceSet->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
        _isMultichoicesAllowed = choiceSet->GetIsMultiSelect();
        _tableViewController = nil;
        _choiceSetDataSource = choiceSet;
        _config = hostConfig;
        _indexPath = nil;
        self.results = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                             superview:(UIView *)view
{
    return [self initWithInputChoiceSet:choiceSet
                             hostConfig:hostConfig
                              superview:view
                         viewController:nil];
}

// ChoiceSetView is a parent view that leads to child view that handles input selection
// so the size is always 1 when there are more than one choices
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return (_choiceSetDataSource->GetChoices().size() > 0) ? 1 : 0;
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
    NSString *title = @"Make Choices";
    cell.textLabel.text = title;
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    cell.selectionStyle = UITableViewCellSelectionStyleBlue;
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
}
- (void)handleUIBarButtonSystemItemDoneEvent
{
    [_tableViewController dismissViewControllerAnimated:YES completion:nil];
    if(_indexPath)
    {
        [self cellForRowAtIndexPath:_indexPath].selected = NO;
        _indexPath = nil;
    }
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.vc)
    {
        _tableViewController = [[ACRInputTableViewController alloc] initWithInputChoiceSet:_choiceSetDataSource style:UITableViewStyleGrouped];
        _indexPath = indexPath;
        UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:_tableViewController];
        _tableViewController.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(handleUIBarButtonSystemItemDoneEvent)];
        [self.vc presentViewController:navController animated:YES completion:nil];
    }
}

- (CGSize)intrinsicContentSize
{
    [self layoutIfNeeded];
    return self.contentSize;
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSMutableArray *values = [[NSMutableArray alloc] init];
    for(NSInteger i = 0; i < [self.results count]; i++)
    {
        if([self.results[[NSNumber numberWithInteger:i]] boolValue] == YES)
        {
            [values addObject:
             [NSString stringWithCString:_choiceSetDataSource->GetChoices()[i]->GetValue().c_str()
                                encoding:NSUTF8StringEncoding]];

        }
    }
    dictionary[self.id] = [values componentsJoinedByString:@";"];
}

@end
