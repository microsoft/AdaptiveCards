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
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    self = [bundle loadNibNamed:@"ACRInputTableView" owner:self options:nil][0];
    if(self) {
        self.frame = CGRectMake(0, 0, view.frame.size.width, view.frame.size.height);
    } else {
        self = [super initWithFrame:CGRectMake(0, 0, view.frame.size.width, view.frame.size.height) style:UITableViewStyleGrouped ];
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        self.scrollEnabled = false;
    }
    return self;
}

- (CGSize)intrinsicContentSize
{
    return self.contentSize;
}

@end
