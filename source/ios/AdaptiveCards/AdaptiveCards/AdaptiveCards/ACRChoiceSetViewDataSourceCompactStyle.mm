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
const NSInteger pickerViewId = 8321;
static NSString *pickerCell = @"pickerCell";
@implementation ACRChoiceSetViewDataSourceCompactStyle
{
    std::shared_ptr<ChoiceSetInput> _choiceSetInput;
    NSIndexPath *_indexPath;
    UITableView *_tableView;
    UITableViewController *_tableViewController;
    NSObject<UITableViewDelegate> *_delegate;
    NSObject<UITableViewDataSource, ACRIBaseInputHandler> *_dataSource;
    NSString *_defaultString;
    UIPickerView *_pickerView;
    BOOL _showPickerView;
    NSLayoutConstraint *_pickerViewHeightConstraint;
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
        //_pickerView = [[UIPickerView alloc] initWithFrame:CGRectMake(0, 0, 200, 216)];
        //_pickerView.translatesAutoresizingMaskIntoConstraints = NO;
        //_pickerView.hidden = NO;
        //_pickerView.tag = pickerViewId;
        //_pickerViewHeightConstraint = [NSLayoutConstraint constraintWithItem:_pickerView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:216];
         //_pickerViewHeightConstraint = [NSLayoutConstraint constraintWithItem:_pickerView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:200];
        //[_pickerView setDataSource:self];
        //[_pickerView setDelegate:self];
        //_pickerView.showsSelectionIndicator = YES;
        _showPickerView = NO;
        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        [bundle loadNibNamed:@"ACRPickerView" owner:rootView options:nil];
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
    return 2;//(_choiceSetInput->GetChoices().size() > 0) ? 2 : 0;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}
// creates top view that hides selection table
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(indexPath.row == 0) {
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
    } else {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:pickerCell];
        if(cell == nil) {
            NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
            cell = [bundle loadNibNamed:@"ACRPickerView" owner:_rootView options:nil][0];
        }
        UIPickerView *pickerView = [cell viewWithTag:pickerViewId];
        pickerView.dataSource = self;
        pickerView.delegate = self;
        pickerView.hidden = NO;
        /*
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
        if(![cell viewWithTag:pickerViewId]){
            [cell addSubview:_pickerView];
            [NSLayoutConstraint constraintWithItem:_pickerView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:cell attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:_pickerView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:cell attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            NSLog(@"picker view = %@", _pickerView);
        }
         */
        return cell;
    }
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
    if(indexPath.row == 0) {
        CGSize labelStringSize = [cell.textLabel.text boundingRectWithSize:CGSizeMake(cell.contentView.frame.size.width - accessoryViewWidth, CGFLOAT_MAX)
                                                         options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                                      attributes:@{NSFontAttributeName:cell.textLabel.font}
                                                         context:nil].size;
        return labelStringSize.height + padding;
    } else {
        return _showPickerView ? 216.0f : 0.0f;
    }
}

// when cell is selected, create a tableView with a navigator control bar.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.rootView && indexPath.row == 0)
    {
        [tableView beginUpdates];
        [tableView endUpdates];
        if(_showPickerView == NO){
            _showPickerView = YES;
            UITableViewCell *cell = [self tableView:tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0]];

            UIPickerView *pickerView = [cell viewWithTag:pickerViewId];
            pickerView.alpha = 0.0f;
            [tableView invalidateIntrinsicContentSize];
            [UIView animateWithDuration:0.25
                             animations:^{
                                 pickerView.alpha = 1.0f;
                             } completion:^(BOOL finished){
                                 pickerView.hidden = NO;
                             }];
        } else {
            _showPickerView = NO;
            [tableView invalidateIntrinsicContentSize];
        }
        /*
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
        */
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
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

- (void)pickerView:(UIPickerView *)pickerView didSelectRow: (NSInteger)row inComponent:(NSInteger)component
{
    // Handle the selection
    //selectedCategory = [NSString stringWithFormat:@"%@",[dataArray objectAtIndex:row]];
}
// tell the picker how many rows are available for a given component
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    NSLog(@"num choices %d", _choiceSetInput->GetChoices().size());
    return _choiceSetInput->GetChoices().size();
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

// tell the picker the title for a given component
- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    NSString *title = [NSString stringWithCString:_choiceSetInput->GetChoices()[row]->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    NSLog(@"title = %@", title);
    return title;
}

// tell the picker the width of each row for a given component
- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
    int sectionWidth = 300;

    return sectionWidth;
}
@end
