//
//  ACVTableViewController.m
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"

@implementation ACVTableViewController {
    NSArray<NSString *> *pathsToFiles;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    NSBundle *main = [NSBundle mainBundle];

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
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseKey];
    }

    cell.textLabel.text = [[NSFileManager defaultManager] displayNameAtPath:pathsToFiles[indexPath.row]];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    self.userSelectedJSon =
        [NSString stringWithContentsOfFile:pathsToFiles[indexPath.row]
                                  encoding:NSUTF8StringEncoding
                                     error:nil];
    [_delegate fromACVTable:self userSelectedJson:self.userSelectedJSon];
    if (!self.IsCollapsed) {
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
