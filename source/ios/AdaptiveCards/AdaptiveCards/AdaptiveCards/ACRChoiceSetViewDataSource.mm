//
//  ACRChoiceSetViewDataSource.mm
//  ACRChoiceSetViewDataSource
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRChoiceSetViewDataSource.h"

using namespace AdaptiveCards;

const CGFloat padding = 16.0f;
const CGFloat accessoryViewWidth = 50.0f;
typedef NS_ENUM(NSInteger, ACRCellSelected) {
    ACRCellSelectedYES = 0,
    ACRCellSelectedNO = 1
};

@implementation ACRChoiceSetViewDataSource
{
    std::shared_ptr<ChoiceSetInput> _choiceSetDataSource;
    NSMutableDictionary *_userSelections;
    NSIndexPath *_lastSelectedIndexPath;
    NSMutableSet *_defaultValuesSet;
    NSArray *_defaultValuesArray;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
{
    self = [super init];
    if(self)
    {
        self.id = [[NSString alloc]initWithCString:choiceSet->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
        _isMultiChoicesAllowed = choiceSet->GetIsMultiSelect();
        _choiceSetDataSource = choiceSet;
        _userSelections = [[NSMutableDictionary alloc] init];
        _lastSelectedIndexPath = nil;
        NSString *defaultValues = [NSString stringWithCString:_choiceSetDataSource->GetValue().c_str()
                                                     encoding:NSUTF8StringEncoding];
        _defaultValuesArray = [defaultValues componentsSeparatedByCharactersInSet:
                               [NSCharacterSet characterSetWithCharactersInString:@","]];

        if (_isMultiChoicesAllowed || [_defaultValuesArray count] == 1){
            _defaultValuesSet = [NSMutableSet setWithArray:_defaultValuesArray];
        }

        NSUInteger index = 0;
        for(const auto& choice : _choiceSetDataSource->GetChoices()) {
            NSString *keyForDefaultValue = [NSString stringWithCString:choice->GetValue().c_str()
                                                              encoding:NSUTF8StringEncoding];

            if([_defaultValuesSet containsObject:keyForDefaultValue]){
                _userSelections[[NSNumber numberWithInteger:index]] = [NSNumber numberWithBool:YES];
            }
            ++index;
        }
    }
    return self;
}

// ChoiceSetView is a parent view that leads to child view that handles input selection
// so the size is always 1 when there are more than one choices
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return (_choiceSetDataSource->GetChoices().size());
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"tabCellId";
    [tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:identifier];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
    }
    NSString *title = [NSString stringWithCString:_choiceSetDataSource->GetChoices()[indexPath.row]->GetTitle().c_str()
                               encoding:NSUTF8StringEncoding];
    cell.textLabel.text = title;
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    cell.textLabel.adjustsFontSizeToFitWidth = NO;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    UIImage *radioImage = nil;

    if(_userSelections[[NSNumber numberWithInteger:indexPath.row]] == [NSNumber numberWithBool:YES]){
        if(cell.tag == ACRCellSelectedNO) {
            if(_isMultiChoicesAllowed) {
                radioImage = [self getCheckBoxButtonSelectedState];
            } else {
                radioImage = [self getRadioButtonForSelectedState];
            }
        }
        cell.tag = ACRCellSelectedYES;
    } else {
        if(cell.tag == ACRCellSelectedYES) {
            if(_isMultiChoicesAllowed) {
                radioImage = [self getCheckBoxButtonUnselectedState];
            } else {
                radioImage = [self getRadioButtonForUnselectedState];
            }
            cell.tag = ACRCellSelectedNO;
        }
    }

    cell.imageView.image = radioImage;

    return cell;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    // if this tableView was used before for gathering input,
    // load the tableView with user selection
    if([_userSelections count] &&
       [_userSelections objectForKey:[NSNumber numberWithInteger:indexPath.row]] &&
       [[_userSelections objectForKey:[NSNumber numberWithInteger:indexPath.row]] boolValue] == YES)
    {
        [cell setSelected:YES animated:NO];
        UIImage *radioImage = nil;
        if(_isMultiChoicesAllowed) {
            radioImage = [self getCheckBoxButtonSelectedState];
        } else {
            radioImage = [self getRadioButtonForSelectedState];
        }
        cell.imageView.image = radioImage;
        _lastSelectedIndexPath = indexPath;
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

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (!_isMultiChoicesAllowed) {
        UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
        UIImage *radioImage = [self getRadioButtonForSelectedState];
        cell.imageView.image = radioImage;
        cell.tag = ACRCellSelectedYES;

        _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:YES];
        if (_lastSelectedIndexPath && _lastSelectedIndexPath != indexPath) {
            [self tableView:tableView didDeselectRowAtIndexPath:_lastSelectedIndexPath];
            _lastSelectedIndexPath = nil;
        }
    } else {
        if ([tableView cellForRowAtIndexPath:indexPath].tag == ACRCellSelectedYES) {
            UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
            _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
            UIImage *radioImage = [self getCheckBoxButtonUnselectedState];
            cell.imageView.image = radioImage;
            cell.tag = ACRCellSelectedNO;
        } else {
            UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
            _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:YES];
            UIImage *radioImage = [self getCheckBoxButtonSelectedState];
            cell.imageView.image = radioImage;
            cell.tag = ACRCellSelectedYES;
        }
    }
}

- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    // uncheck selection if multi choice is not allowed
    if (!_isMultiChoicesAllowed) {
        _userSelections[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
        UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
        UIImage *radioImage = [self getRadioButtonForUnselectedState];
        cell.imageView.image = radioImage;
        cell.tag = ACRCellSelectedNO;
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView.dataSource tableView:tableView cellForRowAtIndexPath:indexPath];
    CGSize labelStringSize =
        [cell.textLabel.text boundingRectWithSize:CGSizeMake(cell.contentView.frame.size.width - accessoryViewWidth, CGFLOAT_MAX)
                                          options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                       attributes:@{NSFontAttributeName:cell.textLabel.font}
                                          context:nil].size;
    return labelStringSize.height + padding;
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getDefaultInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = [_defaultValuesArray componentsJoinedByString:@";"];
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSMutableArray *values = [[NSMutableArray alloc] init];
    NSEnumerator *enumerator = [_userSelections keyEnumerator];
    NSNumber *key;
    while(key = [enumerator nextObject])
    {
        if([_userSelections[key] boolValue] == YES)
        {
            [values addObject:
             [NSString stringWithCString:_choiceSetDataSource->GetChoices()[[key integerValue]]->GetValue().c_str()
                                encoding:NSUTF8StringEncoding]];
        }
    }
    dictionary[self.id] = [values componentsJoinedByString:@";"];
}

- (NSString *)getTitlesOfChoices
{
    NSMutableArray *values = [[NSMutableArray alloc] init];
    NSEnumerator *enumerator = [_userSelections keyEnumerator];
    NSNumber *key;
    while(key = [enumerator nextObject])
    {
        if([_userSelections[key] boolValue] == YES)
        {
            [values addObject:
             [NSString stringWithCString:_choiceSetDataSource->GetChoices()[[key integerValue]]->GetTitle().c_str()
                                encoding:NSUTF8StringEncoding]];
        }
    }
    if([values count] == 0) {
        return nil;
    }
    return [values componentsJoinedByString:@", "];
}

- (UIImage*) getRadioButtonForSelectedState{
    UIImage *image = nil;
    if (self.acrChoiceSetResourceDelegate){
        image =  [self.acrChoiceSetResourceDelegate getRadioButtonForSelectedState];
    }
    else{
        image = [UIImage imageNamed:@"checked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
        
    }
    return image;
}

- (UIImage*) getRadioButtonForUnselectedState{
    UIImage *image = nil;
    if (self.acrChoiceSetResourceDelegate){
        image =  [self.acrChoiceSetResourceDelegate getRadioButtonForUnselectedState];
    }
    else{
        image = [UIImage imageNamed:@"unchecked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
    }
    return image;
}

- (UIImage*) getCheckBoxButtonSelectedState{
    UIImage *image = nil;
    if (self.acrChoiceSetResourceDelegate){
        image =  [self.acrChoiceSetResourceDelegate getCheckBoxButtonSelectedState];
    }
    else{
        image = [UIImage imageNamed:@"checked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
        
    }
    return image;
}

- (UIImage*) getCheckBoxButtonUnselectedState{
    UIImage *image = nil;
    if (self.acrChoiceSetResourceDelegate){
        image =  [self.acrChoiceSetResourceDelegate getCheckBoxButtonUnselectedState];
    }
    else{
        image = [UIImage imageNamed:@"unchecked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
        
    }
    return image;
}

@end
