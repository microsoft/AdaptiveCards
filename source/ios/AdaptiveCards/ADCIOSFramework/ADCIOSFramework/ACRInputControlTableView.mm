//
//  ACRInputControlTableView.mm
//  ACRInputControlTableView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRInputControlTableView.h"

using namespace AdaptiveCards;

@implementation ACRInputControlTableView

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
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
    }
    return self;
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

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
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
