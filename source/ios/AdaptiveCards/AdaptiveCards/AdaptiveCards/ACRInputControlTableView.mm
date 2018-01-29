//
//  ACRInputControlTableView.mm
//  ACRInputControlTableView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRInputControlTableView.h"
#import "ACRInputTableViewController.h"

using namespace AdaptiveCards;

@implementation ACRInputControlTableView
{
    ACRInputTableViewController *_tableViewController;
}

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style viewController:(UIViewController *)vc
{
    self = [super initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) style:style];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.isSelected = NO;
        self.id = nil;
        self.vc = vc;
        _tableViewController = nil;
    }
    return self;
}
- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
{
    return [self initWithFrame:frame style:style viewController:nil];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
}
- (void)handleUIBarButtonSystemItemDoneEvent
{
    [_tableViewController dismissViewControllerAnimated:YES completion:nil];
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.vc)
    {
        _tableViewController = [[ACRInputTableViewController alloc] initWithInputChoiceSet:nil style:UITableViewStylePlain];
        UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:_tableViewController];
        _tableViewController.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(handleUIBarButtonSystemItemDoneEvent)];
        [self.vc presentViewController:navController animated:YES completion:nil];
    }
#if 0
    if([tableView cellForRowAtIndexPath:indexPath].accessoryType ==
       UITableViewCellAccessoryCheckmark)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
        self.isSelected = NO;
        self.results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
    else
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryCheckmark;
        self.isSelected = YES;
        self.results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:YES];
    }
#endif
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
}

- (CGSize)intrinsicContentSize
{
    [self layoutIfNeeded];
    return self.contentSize;
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
}
@end
