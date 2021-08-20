//
//  ACVTableViewController.m
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"

@implementation ACVTableViewController {
    NSArray<NSString *> *pathsToFiles;
    CGFloat selectedRow;
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
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [pathsToFiles count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *reuseKey = @"ACVTabVC";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseKey];
	NSAttributedString *attributedString = [[NSAttributedString alloc] initWithString:[[NSFileManager defaultManager] displayNameAtPath:pathsToFiles[indexPath.row]] attributes:@{NSParagraphStyleAttributeName : NSParagraphStyle.defaultParagraphStyle, NSFontAttributeName : [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseKey];
        cell.textLabel.numberOfLines = 0;
    } 
    cell.textLabel.attributedText = attributedString;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    NSString *payload =
        [NSString stringWithContentsOfFile:pathsToFiles[indexPath.row]
                                  encoding:NSUTF8StringEncoding
                                     error:nil];
    // we don't want to re-render card when a row is selected for selection
    // we don't want to go through the whole logic when payload is nil or empty
    if (!self.IsCollapsed && payload && payload.length) {
        self.userSelectedJSon = payload;
        [_delegate fromACVTable:self userSelectedJson:self.userSelectedJSon];

        selectedRow = indexPath.row;
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
            }];
        self.IsCollapsed = YES;

    } else {
        [UIView animateWithDuration:0.6
                         animations:^{
                             self.tableHeight.active = NO;
                             self.tableHeight = [self.tableView.heightAnchor constraintEqualToConstant:200];
                             self.tableHeight.active = YES;
                         }];
        self.IsCollapsed = NO;
    }
}

- (void)updateTable:(NSArray<NSString *> *)data
{
    pathsToFiles = data;
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

@end
