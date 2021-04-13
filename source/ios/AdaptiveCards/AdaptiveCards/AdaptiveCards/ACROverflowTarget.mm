//
//  ACROverflowTarget
//  ACROverflowTarget.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACROverflowTarget.h"
#import "ACOActionOverflow.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRShowCardTarget.h"
#import "ACRViewPrivate.h"
#import "UtiliOS.h"

@implementation ACROverflowMenuItem {
    __weak ACRView *_rootView;
    std::shared_ptr<AdaptiveCards::BaseActionElement> _action;
    NSObject<ACRSelectActionDelegate> *_target;
}

+ (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement
                               target:(NSObject<ACRSelectActionDelegate> *)target
                             rootView:(ACRView *)rootView
{
    ACROverflowMenuItem *item = [[ACROverflowMenuItem alloc] init];
    item->_action = actionElement.element;
    item->_target = target;
    item->_rootView = rootView;
    return item;
}

- (NSString *)title
{
    return [NSString stringWithUTF8String:_action->GetTitle().c_str()];
}

- (NSString *)iconUrl
{
    return [NSString stringWithUTF8String:_action->GetIconUrl().c_str()];
}

- (NSObject<ACRSelectActionDelegate> *)target
{
    return _target;
}

- (UIImage *)iconImageWithSize:(CGSize)size
{
    UIImage *image = [self loadIconImage];
    if (image) {
        image = scaleImageToSize(image, size);
        return image;
    }
    return nil;
}

- (UIImage *)loadIconImage
{
    auto &iconUrl = _action->GetIconUrl();
    NSDictionary *imageViewMap = [_rootView getImageMap];
    NSString *key = [NSString stringWithCString:iconUrl.c_str()
                                       encoding:[NSString defaultCStringEncoding]];
    UIImage *img = imageViewMap[key];

    if (img) {
        return img;
    } else if (key.length) {
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)_action.get()];
        NSString *key = [number stringValue];
        UIImageView *view = [_rootView getImageView:key];
        if (view.image) {
            return view.image;
        }
    }
    return nil;
}

@end

@implementation ACROverflowTarget {
    __weak ACRView *_rootView;
    UIAlertController *_alert;
    NSMutableArray<ACROverflowMenuItem *> *_menuItems;
}

- (instancetype)initWithActionElement:(ACOActionOverflow *)actionElement
                             rootView:(ACRView *)rootView
{
    self = [super init];
    if (self) {
        _rootView = rootView;
        [self createMenu:actionElement];
    }
    return self;
}

- (void)createMenu:(ACOActionOverflow *)actionElement
{
    NSArray *menuItems = actionElement.menuActions;
    _alert = [UIAlertController alertControllerWithTitle:@""
                                                 message:@""
                                          preferredStyle:UIAlertControllerStyleActionSheet];

    _menuItems = [[NSMutableArray<ACROverflowMenuItem *> alloc] init];

    for (ACOBaseActionElement *action : menuItems) {
        NSString *title = [NSString stringWithUTF8String:action.element->GetTitle().c_str()];
        NSObject<ACRSelectActionDelegate> *target = nil;
        ACRTargetBuilderDirector *director = [_rootView getActionsTargetBuilderDirector];

        // To support Action.ShowCard in overflow action:
        // call buildTargetForButton since ACRShowCardTargetBuilder only responds to this callback
        // set nil button since the action is triggered from alert action not from a real button
        if (ACRRenderingStatus::ACROk == buildTargetForButton(director, action, nil, &target)) {
            ACROverflowMenuItem *menuItem = [ACROverflowMenuItem initWithActionElement:action
                                                                                target:target
                                                                              rootView:_rootView];
            [_menuItems addObject:menuItem];
            UIAlertAction *menuAction = [UIAlertAction actionWithTitle:title
                                                                 style:UIAlertActionStyleDefault
                                                               handler:^(UIAlertAction *_Nonnull action) {
                                                                   [target doSelectAction];
                                                               }];

            auto &iconUrl = action.element->GetIconUrl();
            if (!iconUrl.empty()) {
                UIImage *image = [menuItem iconImageWithSize:CGSizeMake(40, 40)];
                [menuAction setValue:[image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]
                              forKey:@"image"];
            }

            [_alert addAction:menuAction];
        }
    }

    [_alert addAction:[UIAlertAction actionWithTitle:@"Cancel"
                                               style:UIAlertActionStyleCancel
                                             handler:nil]];
}

- (void)setInputs:(NSMutableArray *)inputs
        superview:(UIView<ACRIContentHoldingView> *)superview
{
    for (ACROverflowMenuItem *menuItem : _menuItems) {
        auto *target = menuItem.target;
        if ([target isKindOfClass:[ACRShowCardTarget class]]) {
            ACRShowCardTarget *showCardTarget = (ACRShowCardTarget *)target;
            [showCardTarget createShowCard:inputs superview:superview];
        }
    }
}

- (NSArray<ACROverflowMenuItem *> *)menuItems
{
    return _menuItems;
}

- (void)doSelectAction
{
    if ([_rootView.acrActionDelegate respondsToSelector:@selector(displayOverflowActionMenu:alertController:)]) {
        [_rootView.acrActionDelegate displayOverflowActionMenu:_menuItems
                                               alertController:_alert];
    } else {
        // find first UIViewController responds to rootView as default controller
        UIViewController *controller = [self traverseResponderChainForUIViewController:_rootView];
        if (controller) {
            [controller presentViewController:_alert animated:TRUE completion:nil];
        }
    }
}

- (id)traverseResponderChainForUIViewController:(UIView *)view
{
    id nextResponder = [view nextResponder];
    if ([nextResponder isKindOfClass:[UIViewController class]]) {
        return nextResponder;
    } else if ([nextResponder isKindOfClass:[UIView class]]) {
        return [self traverseResponderChainForUIViewController:nextResponder];
    } else {
        return nil;
    }
}

@end
