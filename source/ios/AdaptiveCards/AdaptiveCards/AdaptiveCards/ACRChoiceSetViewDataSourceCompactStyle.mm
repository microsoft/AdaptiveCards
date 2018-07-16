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
const CGFloat padding = 16.0f;
const CGFloat accessoryViewWidth = 8.0f;

@implementation ACRChoiceSetViewDataSourceCompactStyle
{
    std::shared_ptr<ChoiceSetInput> _choiceSetInput;
    NSIndexPath *_indexPath;
    UITableView *_tableView;
    UITableViewController *_tableViewController;
    NSObject<UITableViewDelegate> *_delegate;
    NSObject<UITableViewDataSource, ACRIBaseInputHandler> *_dataSource;
    NSString *_defaultString;
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

        NSMutableDictionary *valuesMap = [[NSMutableDictionary alloc] init];
        for(auto choice : _choiceSetInput->GetChoices()){
            NSString *title = [NSString stringWithCString:choice->GetTitle().c_str() encoding:NSUTF8StringEncoding];
            NSString *value = [NSString stringWithCString:choice->GetValue().c_str() encoding:NSUTF8StringEncoding];
            valuesMap[value] = title;
        }
        NSString *defaultValues = [NSString stringWithCString:_choiceSetInput->GetValue().c_str()
                                                     encoding:NSUTF8StringEncoding];
        if([defaultValues length]){
            NSArray *defaultValuesArray = [defaultValues componentsSeparatedByCharactersInSet:
                                   [NSCharacterSet characterSetWithCharactersInString:@","]];
            NSMutableArray<NSString *> *titleArray = [[NSMutableArray alloc] init];
            for(id defaultValue in defaultValuesArray) {
                [titleArray addObject:valuesMap[defaultValue]];
            }
            _defaultString = [titleArray componentsJoinedByString:@", "];
        } else {
            NSString *firstChoice = nil;
            if(!_choiceSetInput->GetChoices().empty()){
                firstChoice = [NSString stringWithCString:(_choiceSetInput->GetChoices()[0])->GetTitle().c_str() encoding:NSUTF8StringEncoding];
                _defaultString = firstChoice;
            } else {
                _defaultString = @"";
            }
        }
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
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
    }

    cell.textLabel.text = ([_defaultString length])? _defaultString : @"";
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.adjustsFontSizeToFitWidth = NO;
    cell.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
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

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView.dataSource tableView:tableView cellForRowAtIndexPath:indexPath];
    CGSize labelStringSize = [cell.textLabel.text boundingRectWithSize:CGSizeMake(cell.contentView.frame.size.width - accessoryViewWidth, CGFLOAT_MAX)
                                                     options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                                  attributes:@{NSFontAttributeName:cell.textLabel.font}
                                                     context:nil].size;
    return labelStringSize.height + padding;
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
        NSString *choice = [(ACRChoiceSetViewDataSource *)_dataSource getTitlesOfChoices];
        [_tableView cellForRowAtIndexPath:_indexPath].textLabel.text = (choice)? choice : @"";
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
