//
//  ACRInputTableView.mm
//  ACRInputTableView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRInputTableView.h"

using namespace AdaptiveCards;

@implementation ACRInputTableView

- (instancetype)initWithSuperview:(UIView *)view
{
    self = [super initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height) style:UITableViewStyleGrouped ];
    if(self)
    {
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.scrollEnabled = false;
    }
    return self;
}

- (CGSize)intrinsicContentSize
{    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:0];
    float height = [self.delegate tableView:self heightForRowAtIndexPath:indexPath] * [self.dataSource tableView:self numberOfRowsInSection:0];
    return CGSizeMake(self.frame.size.width, height);
}

@end
