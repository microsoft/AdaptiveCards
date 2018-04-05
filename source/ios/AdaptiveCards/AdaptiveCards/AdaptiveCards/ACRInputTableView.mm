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

-(instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if(self){
        self.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return self;
}

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
    //[self layoutIfNeeded];
    return self.contentSize;
}

@end
