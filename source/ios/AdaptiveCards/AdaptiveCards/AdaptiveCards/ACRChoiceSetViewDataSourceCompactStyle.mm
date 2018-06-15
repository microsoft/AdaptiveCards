//
//  ACRChoiceSetViewDataSourceCompactStyle.mm
//  ACRChoiceSetViewDataSourceCompactStyle
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRChoiceSetViewDataSourceCompactStyle.h"
#import "ACRChoiceSetViewDataSource.h"
#import "ACRView.h"
#import "ACRActionDelegate.h"

using namespace AdaptiveCards;

@implementation ACRChoiceSetViewDataSourceCompactStyle
{
    std::shared_ptr<ChoiceSetInput> _choiceSetInput;
    NSIndexPath *_indexPath;
    UITableView *_tableView;
    UITableViewController *_tableViewController;
    NSObject<UITableViewDelegate> *_delegate;
    NSObject<UITableViewDataSource, ACRIBaseInputHandler> *_dataSource;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                              rootView:(ACRView *)rootView;
{
    self = [super init];
    if(self)
    {
        self.id = [[NSString alloc]initWithCString:choiceSet->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
        _isMultiChoicesAllowed = choiceSet->GetIsMultiSelect();
        _choiceSetInput = choiceSet;
        _rootView = rootView;
        _dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:_choiceSetInput];
        _delegate   = (NSObject<UITableViewDelegate> *)_dataSource;
        _tableView = nil;
        _indexPath = nil;
        _tableViewController = nil;
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
{
    return self = [self initWithInputChoiceSet:choiceSet rootView:nil];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return (_choiceSetInput->GetChoices().size() > 0) ? 1 : 0;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}
// creates top view that hides selection table
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"cellForCompactMode";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(!cell)
    {
        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        [tableView registerNib:[UINib nibWithNibName:@"ACRCellForCompactMode" bundle:bundle] forCellReuseIdentifier:identifier];
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    }

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

// when cell is selected, create a tableView with a navigator control bar.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.rootView)
    {
        _indexPath = indexPath;
        _tableView = tableView;
        _tableViewController = [[UITableViewController alloc] initWithStyle:UITableViewStyleGrouped];
        _tableViewController.tableView.dataSource = _dataSource;
        _tableViewController.tableView.delegate = _delegate;
        UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:_tableViewController];
        // button on the right of navigation bar that exits the table view when pressed
        _tableViewController.navigationItem.rightBarButtonItem =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                          target:self
                                                          action:@selector(handleUIBarButtonSystemItemDoneEvent)];
        if ([_rootView.acrActionDelegate respondsToSelector:@selector(didFetchSecondaryView:navigationController:)]){
            [_rootView.acrActionDelegate didFetchSecondaryView:[_rootView card] navigationController:navController];
        }
    }
}

- (void)handleUIBarButtonSystemItemDoneEvent
{
    [_tableViewController dismissViewControllerAnimated:YES completion:nil];
    if(_indexPath && _tableView)
    {
        [_tableView cellForRowAtIndexPath:_indexPath].selected = NO;
        _indexPath = nil;
        _tableView = nil;
    }
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    // gets inputs from datasource of the table view
    if(!_tableViewController) {
        [(ACRChoiceSetViewDataSource *)_dataSource getDefaultInput:dictionary];
    } else {
        [_dataSource getInput:dictionary];
    }
}

@end
