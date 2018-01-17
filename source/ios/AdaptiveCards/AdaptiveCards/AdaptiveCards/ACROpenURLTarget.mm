//
//  ACROpenURLTarget
//  ACROpenURLTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACROpenURLTarget.h"

@implementation ACROpenURLTarget
{
    __weak UIViewController *_vc;
    // view on that target will applies its action
    __weak UIView *_view;
    UIColor *_backgroundColor;
    NSURL *_url;
}

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc
{
    self = [self initWithURL:url viewController:vc targetView:nil];
    return self;
}

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc targetView:(UIView *)view
{
    self = [super init];
    if(self)
    {
        _vc = vc;
        _url = url;
        _view = view;
    }
    return self;
}

- (IBAction)openURL
{
    SFSafariViewController* svc = [[SFSafariViewController alloc] initWithURL:_url];
    svc.delegate = self;
    [_vc presentViewController:svc animated:YES completion:nil];
}

- (IBAction)openURL:(UILongPressGestureRecognizer *) recognizer
{
    // background color of a UIView object is changed to provide visual cue
    // that the object is activated
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        _backgroundColor = _view.backgroundColor;
        _view.backgroundColor = [UIColor colorWithRed:0xD4/255.0 green:0xD4/255.0 blue:0xD4/255.0 alpha:0x1];
;
        [self openURL];
    }
    else if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        _view.backgroundColor = _backgroundColor;
    }
}
// delegate that is called when safariViewController is finished
- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller
{
    if(_view)
    {
        _view.backgroundColor = _backgroundColor;
    }
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
       shouldReceiveTouch:(UITouch *)touch
{
    if([gestureRecognizer isKindOfClass:[UIPanGestureRecognizer class]])
    {
        return NO;
    }
    return YES;
}
@end
