//
//  ACRSearchBar.m
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 12/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRSearchBar.h"
#import <UIKit/UIKit.h>

@implementation ACRSearchBar

-(UITextField *)buildCustomSearchBarWithPlaceholder:(NSString *)placeholder {
    UITextField *searchTextField = [[UITextField alloc] initWithFrame:CGRectZero];
    searchTextField.delegate = self;
    searchTextField.accessibilityTraits = UIAccessibilityTraitSearchField;
    searchTextField.enablesReturnKeyAutomatically = YES;
    searchTextField.returnKeyType = UIReturnKeySearch;
    [searchTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    searchTextField.translatesAutoresizingMaskIntoConstraints = NO;
    
    searchTextField.text = [_delegate getSelectedText];
    if (placeholder!= nil)
    {
        searchTextField.placeholder = placeholder;
    }
    
    // configure right and left icon view
    UIImageView *searchIconView = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"magnifyingglass"]];
    searchIconView.frame = CGRectMake(5, 5, 26, 26);
    searchIconView.contentMode = UIViewContentModeCenter;
    UIView *searchLeftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 32, 32)];
    [searchLeftView addSubview:searchIconView];
    
    UIImageView *clearIconView = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"xmark.circle"]];
    clearIconView.frame = CGRectMake(0, 5, 26, 26);
    clearIconView.contentMode = UIViewContentModeCenter;
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(clearButtonTapped)];
    singleTap.numberOfTapsRequired = 1;
    [clearIconView setUserInteractionEnabled:YES];
    [clearIconView addGestureRecognizer:singleTap];
    UIView *rightView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 32, 32)];
    [rightView addSubview:clearIconView];
    
    searchTextField.rightViewMode = UITextFieldViewModeAlways;
    searchTextField.rightView = rightView;
    searchTextField.leftViewMode = UITextFieldViewModeAlways;
    searchTextField.leftView = searchLeftView;
    [searchTextField becomeFirstResponder];
    return searchTextField;
}

-(void)clearButtonTapped
{
    _customSearchBar.text = @"";
    [_customSearchBar resignFirstResponder];
    [_filteredDataSource resetFilter];
    [self updateListViewLayout];
}

#pragma mark - UITextFieldDelegate methods for handling search

-(void)textFieldDidChange:(UITextField*)textField
{
    NSLog(@"new search text %@", textField.text);
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    NSString *newSearchText = [textField.text stringByReplacingCharactersInRange:range
                                                                  withString:string];
    switch (_dataSourceType) {
        case staticDataSource:
            [_filteredDataSource updatefilteredListForStaticTypeahead:newSearchText];
            [self updateListViewLayout];
            break;
        case dynamicDataSource:
            _searchStateTitleLabel.text = @"Loading options";
            _searchStateTitleLabel.hidden = NO;
            _searchStateImageView.hidden = YES;
            [_filteredDataSource clearList];
            [self updateListViewLayout];
            if (![_loader isAnimating])
            {
                [_loader startAnimating];
            }
         //   [_debouncer postInput:newSearchText];
            break;
        default:
            break;
    }
    return YES;
}

@end
