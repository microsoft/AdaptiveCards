//
//  ACRChoiceSetViewDataSourceCompactStyle.mm
//  ACRChoiceSetViewDataSourceCompactStyle
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRChoiceSetViewDataSourceCompactStyle.h"
#import "ACRActionDelegate.h"
#import "ACRChoiceSetViewDataSource.h"
#import "ACRView.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;
const CGFloat padding = 16.0f;
const CGFloat accessoryViewWidth = 8.0f;
const NSInteger pickerViewId = 8321;
static NSString *pickerCell = @"pickerCell";
@implementation ACRChoiceSetViewDataSourceCompactStyle {
    std::shared_ptr<ChoiceSetInput> _choiceSetInput;
    NSObject<UITableViewDelegate> *_delegate;
    NSObject<UITableViewDataSource, ACRIBaseInputHandler> *_dataSource;
    NSArray<NSString *> *_titles;
    NSMutableDictionary<NSString *, NSString *> *_titlesMap;
    NSString *_defaultString;
    NSString *_userSelectedTitle;
    NSInteger _userSelectedRow;
    BOOL _showPickerView;
    CGFloat _pickerViewHeight;
    NSString *_textInCompactView;
    CGFloat _compactViewHeight;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const &)choiceSet
                              rootView:(ACRView *)rootView;
{
    self = [super init];
    if (self) {
        self.id = [[NSString alloc] initWithCString:choiceSet->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
        _isMultiChoicesAllowed = choiceSet->GetIsMultiSelect();
        _choiceSetInput = choiceSet;
        _rootView = rootView;
        _delegate = (NSObject<UITableViewDelegate> *)_dataSource;
        _showPickerView = NO;

        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        [bundle loadNibNamed:@"ACRPickerView" owner:rootView options:nil];
        _titlesMap = [[NSMutableDictionary alloc] init];
        NSMutableDictionary *valuesMap = [[NSMutableDictionary alloc] init];

        NSString *defaultValue = [NSString stringWithCString:_choiceSetInput->GetValue().c_str()
                                                    encoding:NSUTF8StringEncoding];
        NSMutableArray *mutableArrayStrings = [[NSMutableArray alloc] init];
        NSInteger index = 0;
        for (auto choice : _choiceSetInput->GetChoices()) {
            NSString *title = [NSString stringWithCString:choice->GetTitle().c_str() encoding:NSUTF8StringEncoding];
            NSString *value = [NSString stringWithCString:choice->GetValue().c_str() encoding:NSUTF8StringEncoding];
            _titlesMap[title] = value;
            if (_userSelectedRow != 0 && [defaultValue isEqualToString:value]) {
                _userSelectedRow = index;
            }
            valuesMap[value] = title;
            [mutableArrayStrings addObject:title];
            ++index;
        }

        if ([mutableArrayStrings count]) {
            _titles = [NSArray arrayWithArray:mutableArrayStrings];
        }

        _userSelectedTitle = valuesMap[defaultValue];
    }
    return self;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const &)choiceSet
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

    if (indexPath.row == 0) {
        static NSString *identifier = @"cellForCompactMode";
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if (!cell) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                          reuseIdentifier:identifier];
        }
        if ([_userSelectedTitle length] != 0) {
            cell.textLabel.text = _userSelectedTitle;
        } else {
            cell.textLabel.text = ([_defaultString length]) ? _defaultString : @"";
        }
        _textInCompactView = cell.textLabel.text;
        cell.textLabel.numberOfLines = 0;
        cell.textLabel.adjustsFontSizeToFitWidth = NO;
        cell.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
        cell.backgroundColor = UIColor.clearColor;
    } else {
        cell = [tableView dequeueReusableCellWithIdentifier:pickerCell];
        UIPickerView *pickerView = nil;
        if (cell == nil) {
            NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
            cell = [bundle loadNibNamed:@"ACRPickerView" owner:_rootView options:nil][0];
            pickerView = [cell viewWithTag:pickerViewId];
            _pickerViewHeight = pickerView.frame.size.height;
        } else {
            pickerView = [cell viewWithTag:pickerViewId];
        }
        pickerView.dataSource = self;
        pickerView.delegate = self;
        pickerView.hidden = NO;
        [pickerView selectRow:_userSelectedRow inComponent:0 animated:NO];
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

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView.dataSource tableView:tableView cellForRowAtIndexPath:indexPath];
    if (indexPath.row == 0) {
        CGSize labelStringSize = [cell.textLabel.text
                                     boundingRectWithSize:CGSizeMake(cell.contentView.frame.size.width - accessoryViewWidth, CGFLOAT_MAX)
                                                  options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                               attributes:@{NSFontAttributeName : cell.textLabel.font}
                                                  context:nil]
                                     .size;
        _compactViewHeight = labelStringSize.height;
        return _compactViewHeight + padding;
    } else {
        return _showPickerView ? _pickerViewHeight : 0.0f;
    }
}

// when cell is selected, create a tableView with a navigator control bar.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (self.rootView && indexPath.row == 0) {
        UITableViewCell *cell = [self tableView:tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0]];
        UIPickerView *pickerView = [cell viewWithTag:pickerViewId];
        CGRect oldFrame = tableView.frame;
        oldFrame.origin = [tableView convertPoint:tableView.frame.origin toView:nil];
        if (_showPickerView == YES) {
            _showPickerView = NO;
            pickerView.alpha = 0.0f;
            [UIView animateWithDuration:0.25
                animations:^{
                    pickerView.alpha = 1.0f;
                    [tableView invalidateIntrinsicContentSize];
                    [tableView setNeedsLayout];
                    [tableView.superview layoutIfNeeded];
                    if ([self.rootView.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
                        CGFloat newHeight = [self tableView:tableView heightForRowAtIndexPath:indexPath];
                        CGRect newFrame = CGRectMake(0, 0, 0, newHeight);
                        [self.rootView.acrActionDelegate didChangeViewLayout:oldFrame newFrame:newFrame];
                    }
                }
                completion:^(BOOL finished) {
                    ;
                    [tableView reloadData];
                    pickerView.hidden = YES;
                }];
        } else {
            _showPickerView = YES;
            pickerView.alpha = 0.0f;
            [tableView beginUpdates];
            [tableView endUpdates];
            [UIView animateWithDuration:0.25
                animations:^{
                    [tableView invalidateIntrinsicContentSize];
                    [tableView setNeedsLayout];
                    [tableView.superview layoutIfNeeded];
                    if ([self.rootView.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
                        CGFloat newHeight = oldFrame.size.height;
                        newHeight += [self tableView:tableView heightForRowAtIndexPath:[NSIndexPath indexPathForRow:1 inSection:0]];
                        CGRect newFrame = oldFrame;
                        newFrame.size.height = newHeight;
                        [self.rootView.acrActionDelegate didChangeViewLayout:oldFrame newFrame:newFrame];
                    }
                }
                completion:^(BOOL finished) {
                    [tableView reloadData];
                    pickerView.hidden = NO;
                }];
        }
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = _titlesMap[_userSelectedTitle];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    _userSelectedTitle = [_titles objectAtIndex:row];
    _userSelectedRow = row;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    return _choiceSetInput->GetChoices().size();
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    return [_titles objectAtIndex:row];
}
@end
