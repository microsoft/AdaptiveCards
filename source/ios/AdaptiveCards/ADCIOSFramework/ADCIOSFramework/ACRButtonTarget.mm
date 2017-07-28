//
//  ACRButtonTarget
//  ACRButtonTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SafariServices/SafariServices.h>
#import "ACRButtonTarget.h"

@implementation ACRButtonTarget
{
    __weak UIViewController* _vc;
    NSURL* _url;
}

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *) vc
{
    self = [super init];
    if(self)
    {
        _vc = vc;
        _url = url;
    }
    return self;
}

- (IBAction)openURL
{ 
    SFSafariViewController* svc = [[SFSafariViewController alloc] initWithURL:_url];
    [_vc presentViewController:svc animated:YES completion:nil];
}
@end
