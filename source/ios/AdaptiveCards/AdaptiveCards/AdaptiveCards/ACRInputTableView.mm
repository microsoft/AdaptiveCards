//
//  ACRInputTableView.mm
//  ACRInputTableView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRInputTableView.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACRInputTableView

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.backgroundColor = UIColor.clearColor;
    }
    return self;
}

- (instancetype)initWithSuperview:(UIView *)view
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    self = [bundle loadNibNamed:@"ACRInputTableView" owner:self options:nil][0];
    if (self) {
        self.frame = CGRectMake(0, 0, view.frame.size.width, view.frame.size.height);
    } else {
        self = [super initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height) style:UITableViewStyleGrouped];
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.scrollEnabled = false;
    }
    return self;
}

- (CGSize)intrinsicContentSize
{
    NSInteger numberOfRows = [self.dataSource tableView:self numberOfRowsInSection:0];
    CGFloat height = 0.0f;
    for (int i = 0; i < numberOfRows; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:i inSection:0];
        height += [self.delegate tableView:self heightForRowAtIndexPath:indexPath];
    }
    return CGSizeMake(self.frame.size.width, height);
}

@end
