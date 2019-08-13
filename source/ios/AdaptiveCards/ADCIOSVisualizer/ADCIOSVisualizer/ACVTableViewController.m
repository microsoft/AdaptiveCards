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
    
    cell.textLabel.text = [[NSFileManager defaultManager] displayNameAtPath:pathsToFiles[indexPath.row]];
    
    return cell;
}

- (void)tableView:(UITableView* )tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    self.userSelectedJSon =
    [NSString stringWithContentsOfFile:pathsToFiles[indexPath.row]
                              encoding:NSUTF8StringEncoding
                                 error:nil];
    [_delegate fromACVTable:self userSelectedJson:self.userSelectedJSon];
}

- (void)updateTable:(NSArray<NSString *> *)data {
    pathsToFiles = data;
    [self.tableView reloadData];
}

@end
