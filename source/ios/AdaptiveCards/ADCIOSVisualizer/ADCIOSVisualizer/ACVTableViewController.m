//
//  ACVTableViewController.m
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"

@implementation ACVTableViewController {
    NSArray<NSString *> *_pathsToFiles;
    CGFloat selectedRow;
    UITextView *_editor;
    ACEditorViewController *_editorViewController;
    NSString *_currentSelectedPath;
    NSString *_currentSelectedJSON;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.tableView.estimatedRowHeight = 100;

    // use automatic row height for payload labels, so the table can update its row size when
    // dynamic font type font size changes.
    self.tableView.rowHeight = UITableViewAutomaticDimension;
    NSBundle *main = [NSBundle mainBundle];

    selectedRow = -1;

    [_delegate source:self
           userconfig:[NSString stringWithContentsOfFile:[main pathForResource:@"sample" ofType:@"json"]
                                                encoding:NSUTF8StringEncoding
                                                   error:nil]];
    _editor = [[UITextView alloc] init];
    _editor.editable = YES;
    _editorViewController = [[NSBundle mainBundle] loadNibNamed:@"ACEditorViewController" owner:self options:nil][0];
    [_editorViewController configure:self delegate:self.delegate];
    _editorViewController.editorDelegate = self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_pathsToFiles count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *reuseKey = @"ACVTabVC";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseKey];
    NSString *path = [[NSFileManager defaultManager] displayNameAtPath:_pathsToFiles[indexPath.row]];
    NSAttributedString *attributedString = [[NSAttributedString alloc] initWithString:path attributes:@{NSParagraphStyleAttributeName : NSParagraphStyle.defaultParagraphStyle, NSFontAttributeName : [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];

    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseKey];
        cell.textLabel.numberOfLines = 0;
    }

    if ([_currentSelectedPath isEqualToString:path]) {
        if (self.IsCollapsed) {
            cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
            UIButton *editButton = [UIButton buttonWithType:UIButtonTypeSystem];
            [editButton setTitle:@"EDIT" forState:UIControlStateNormal];
            editButton.tag = indexPath.row;
            [editButton addTarget:self action:@selector(openEditor:) forControlEvents:UIControlEventTouchUpInside];
            [editButton sizeToFit];
            cell.accessoryView = editButton;
        }
    } else {
        cell.accessoryView = nil;
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    cell.textLabel.attributedText = attributedString;

    return cell;
}

- (void)openEditor:(UIButton *)button
{

    _editorViewController.editorView.text = _currentSelectedJSON ? _currentSelectedJSON : [NSString stringWithContentsOfFile:_pathsToFiles[button.tag] encoding:NSUTF8StringEncoding error:nil];
    [self presentViewController:_editorViewController animated:YES completion:nil];
}

- (void)updateTableVisual:(NSIndexPath *_Nonnull)indexPath payload:(NSString *)payload tableView:(UITableView *_Nonnull)tableView
{
    if (!self.IsCollapsed && payload && payload.length) {
        self.userSelectedJSon = payload;
        [_delegate fromACVTable:self userSelectedJson:self.userSelectedJSon];

        selectedRow = indexPath.row;
        _currentSelectedPath = [[NSFileManager defaultManager] displayNameAtPath:_pathsToFiles[indexPath.row]];
        self.IsCollapsed = YES;

        UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
        CGFloat height = cell.frame.size.height;

        self.tableHeight.active = NO;
        self.tableHeight = [tableView.heightAnchor constraintEqualToConstant:height];
        [UIView animateWithDuration:0.6
            animations:^{
                self.tableHeight.active = YES;
            }
            completion:^(BOOL finished) {
                [tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionTop animated:YES];
                [tableView reloadRowsAtIndexPaths:@[ indexPath ] withRowAnimation:UITableViewRowAnimationNone];
            }];

    } else {
        [UIView animateWithDuration:0.6
                         animations:^{
                             self.tableHeight.active = NO;
                             self.tableHeight = [self.tableView.heightAnchor constraintEqualToConstant:200];
                             self.tableHeight.active = YES;
                             UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
                             cell.accessoryType = UITableViewCellAccessoryNone;
                             cell.accessoryView = nil;
                         }];
        self.IsCollapsed = NO;
        _currentSelectedJSON = nil;
    }
}

- (NSString *)getFileNameOfCurrentRow:(NSIndexPath *_Nonnull)indexPath
{
    NSString *path = [[NSFileManager defaultManager] displayNameAtPath:_pathsToFiles[indexPath.row]];
    return path;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    NSString *payload =
        [NSString stringWithContentsOfFile:_pathsToFiles[indexPath.row]
                                  encoding:NSUTF8StringEncoding
                                     error:nil];

    NSString *path = [self getFileNameOfCurrentRow:indexPath];

    if (![_currentSelectedPath isEqualToString:path]) {
        _currentSelectedJSON = nil;
    }

    // we don't want to re-render card when a row is selected for selection
    // we don't want to go through the whole logic when payload is nil or empty
    [self updateTableVisual:indexPath payload:payload tableView:tableView];
}

- (void)updateTable:(NSArray<NSString *> *)data
{
    _pathsToFiles = data;
    if (self.tableView.hidden) {
        if (data) {
            [UIView animateWithDuration:0.6
                             animations:^{
                                 self.tableView.hidden = NO;
                                 self.tableHeight.active = NO;
                                 self.tableHeight = [self.tableView.heightAnchor constraintEqualToConstant:200];
                                 self.tableHeight.active = YES;
                             }];
            self.IsCollapsed = NO;
        }
    } else if (!data) {
        [UIView animateWithDuration:0.6
                         animations:^{
                             self.tableView.hidden = YES;
                         }];
    }
    [self.tableView reloadData];
}

- (void)userIsDoneWithEditing:(ACEditorViewController *)editorViewController
{
    _currentSelectedJSON = editorViewController.editorView.text;
}

- (void)userRequestForDelete:(ACEditorViewController *)editorViewControoler
{
}

@end
