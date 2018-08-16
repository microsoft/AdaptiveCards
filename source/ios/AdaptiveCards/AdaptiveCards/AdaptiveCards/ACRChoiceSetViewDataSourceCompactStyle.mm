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
    NSArray<NSString *> *_titles;
    NSString *_defaultString;
    UIPickerView *_pickerView;
    BOOL _showPickerView;
    CGFloat _pickerViewHeight;
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
        _showPickerView = NO;

        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        [bundle loadNibNamed:@"ACRPickerView" owner:rootView options:nil];
        NSMutableDictionary *valuesMap = [[NSMutableDictionary alloc] init];
        NSMutableArray *mutableArrayStrings = [[NSMutableArray alloc] init];
        for(auto choice : _choiceSetInput->GetChoices()){
            NSString *title = [NSString stringWithCString:choice->GetTitle().c_str() encoding:NSUTF8StringEncoding];
            NSString *value = [NSString stringWithCString:choice->GetValue().c_str() encoding:NSUTF8StringEncoding];
            valuesMap[value] = title;
            [mutableArrayStrings addObject:title];
        }

        if([mutableArrayStrings count]){
            _titles = [NSArray arrayWithArray:mutableArrayStrings];
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
    return _choiceSetInput->GetChoices().size() > 0 ? 2 : 0;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}
// creates top view that hides selection table
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = nil;
    
    if(indexPath.row == 0) {
        static NSString *identifier = @"cellForCompactMode";
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if(!cell) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                          reuseIdentifier:identifier];
        }
        cell.textLabel.text = ([_defaultString length])? _defaultString : @"";
        cell.textLabel.numberOfLines = 0;
        cell.textLabel.adjustsFontSizeToFitWidth = NO;
        cell.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    } else {
        cell = [tableView dequeueReusableCellWithIdentifier:pickerCell];
        BOOL bUpdateConstraint = NO;
        UIPickerView *pickerView = nil;
        if(cell == nil) {
            NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
            cell = [bundle loadNibNamed:@"ACRPickerView" owner:_rootView options:nil][0];
            pickerView = [cell viewWithTag:pickerViewId];
            _pickerViewHeight = pickerView.frame.size.height;
        } else {
            bUpdateConstraint = YES;
            pickerView = [cell viewWithTag:pickerViewId];
        }
        if(bUpdateConstraint) {
            [NSLayoutConstraint constraintWithItem:pickerView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:cell attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:pickerView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:cell attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
        }
        pickerView.dataSource = self;
        pickerView.delegate = self;
        pickerView.hidden = NO;
    }
    cell.backgroundColor = UIColor.groupTableViewBackgroundColor;    
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
    if(indexPath.row == 0) {
        CGSize labelStringSize = [cell.textLabel.text boundingRectWithSize:CGSizeMake(cell.contentView.frame.size.width - accessoryViewWidth, CGFLOAT_MAX)
                                                         options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                                      attributes:@{NSFontAttributeName:cell.textLabel.font}
                                                         context:nil].size;
        return labelStringSize.height + padding;
    } else {
        return _showPickerView ? _pickerViewHeight : 0.0f;
    }
}

// when cell is selected, create a tableView with a navigator control bar.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.rootView && indexPath.row == 0)
    {
        [tableView setNeedsLayout];
        UITableViewCell *cell = [self tableView:tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0]];
        UIPickerView *pickerView = [cell viewWithTag:pickerViewId];
        if(_showPickerView == YES){
            _showPickerView = NO;
            [tableView beginUpdates];
            [tableView endUpdates];
            pickerView.alpha = 0.0f;
            [UIView animateWithDuration:0.25
                             animations:^{
                                 pickerView.alpha = 1.0f;
                                 [tableView invalidateIntrinsicContentSize];
                                 [tableView.superview setNeedsLayout];
                                 [tableView.superview layoutIfNeeded];
                             } completion:^(BOOL finished){
                                 pickerView.hidden = YES;
                             }];
        } else {
            _showPickerView = YES;
            [tableView beginUpdates];
            [tableView endUpdates];
            [UIView animateWithDuration:0.25
                             animations:^{
                                 pickerView.alpha = 0.0f;
                                 [tableView invalidateIntrinsicContentSize];
                                 [tableView setNeedsLayout];
                                 [tableView.superview layoutIfNeeded];
                             } completion:^(BOOL finished){
                                 pickerView.hidden = NO;
                             }];
        }
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
    return title;
}

//// tell the picker the width of each row for a given component
//- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
//    return _maxTitleLength;
//}

@end
