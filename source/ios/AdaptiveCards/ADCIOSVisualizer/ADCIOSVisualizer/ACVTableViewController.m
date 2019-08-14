//
//  ACVTableViewController.m
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"

@implementation ACVTableViewController
{    
    NSArray<NSString*> *pathsToFiles;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    NSBundle *main = [NSBundle mainBundle];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTapOnTableView:)];
    [self.tableView addGestureRecognizer:tap];
    [_delegate source:self userconfig:[NSString stringWithContentsOfFile:[main pathForResource:@"sample" ofType:@"json"]
                                                                encoding:NSUTF8StringEncoding
                                                                   error:nil]];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [pathsToFiles count];
}

- (UITableViewCell* )tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString* reuseKey = @"ACVTabVC";
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:reuseKey];
    if(!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseKey];
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = [[NSFileManager defaultManager] displayNameAtPath:pathsToFiles[indexPath.row]];
    
    return cell;
}

- (void)tableView:(UITableView* )tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if (self.IsCollapsed == YES) {
        self.IsCollapsed = NO;
        return;
    }
    self.userSelectedJSon =
    [NSString stringWithContentsOfFile:pathsToFiles[indexPath.row]
                              encoding:NSUTF8StringEncoding
                                 error:nil];
    [tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionTop animated:YES];
    self.IsCollapsed = YES;
    [_delegate fromACVTable:self userSelectedJson:self.userSelectedJSon];
}

- (void)updateTable:(NSArray<NSString *> *)data {
    pathsToFiles = data;
    if (self.tableView.hidden) {
        if (data) {
            [UIView animateWithDuration:0.6 animations:^{
                self.tableView.hidden = NO;
                self.tableHeight.active = NO;
                self.tableHeight = [self.tableView.heightAnchor constraintEqualToConstant:200];
                self.tableHeight.active = YES;
            }];
            self.IsCollapsed = NO;

        }
    } else if (!data) {
        [UIView animateWithDuration:0.6 animations:^{self.tableView.hidden = YES;}];
    }
    [self.tableView reloadData];
}

- (void) didTapOnTableView:(UIGestureRecognizer*) recognizer {
    if (self.IsCollapsed == NO || self.tableView.hidden) {
        recognizer.cancelsTouchesInView = NO;
    } else { // anywhere else, do what is needed for your case
        [UIView animateWithDuration:0.6 animations:^{
            self.tableView.hidden = NO;
            self.tableHeight.active = NO;
            self.tableHeight = [self.tableView.heightAnchor constraintEqualToConstant:200];
            self.tableHeight.active = YES;
        }];
    }
}

@end
