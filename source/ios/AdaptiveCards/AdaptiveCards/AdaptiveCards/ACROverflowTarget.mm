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

NSString *const ACROverflowTargetIsRootLevelKey = @"isAtRootLevel";

@implementation ACROverflowMenuItem {
    __weak ACRView *_rootView;
    std::shared_ptr<AdaptiveCards::BaseActionElement> _action;
    NSObject<ACRSelectActionDelegate> *_target;
    void (^_onIconLoaded)(UIImage *);
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

- (void)loadIconImageWithSize:(CGSize)size
                 onIconLoaded:(void (^)(UIImage *))onIconLoaded
{
    [self loadIconImage:^(UIImage *image) {
        if (image) {
            image = scaleImageToSize(image, size);
            if (onIconLoaded) {
                onIconLoaded(image);
            }
        }
    }];
}

- (void)loadIconImage:(void (^)(UIImage *))completion
{
    auto &iconUrl = _action->GetIconUrl();
    NSDictionary *imageViewMap = [_rootView getImageMap];
    NSString *key = [NSString stringWithCString:iconUrl.c_str()
                                       encoding:[NSString defaultCStringEncoding]];
    UIImage *img = imageViewMap[key];

    if (img) {
        completion(img);
    } else if (key.length) {
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)_action.get()];
        NSString *key = [number stringValue];
        UIImageView *view = [_rootView getImageView:key];
        if (view.image) {
            completion(view.image);
        } else {
            _onIconLoaded = completion;
            [view addObserver:self
                   forKeyPath:@"image"
                      options:NSKeyValueObservingOptionNew
                      context:_action.get()];
        }
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary<NSKeyValueChangeKey, id> *)change
                       context:(void *)key
{
    if ([keyPath isEqualToString:@"image"] && key == _action.get()) {
        // image that was loaded
        UIImage *image = [change objectForKey:NSKeyValueChangeNewKey];
        if (_onIconLoaded) {
            _onIconLoaded(image);
        }
        [object removeObserver:self forKeyPath:@"image"];
    }
}
@end

@implementation ACROverflowTarget {
    __weak ACRView *_rootView;
    UIAlertController *_alert;
    NSMutableArray<ACROverflowMenuItem *> *_menuItems;
    BOOL _isAtRootLevel;
}

- (instancetype)initWithActionElement:(ACOActionOverflow *)actionElement
                             rootView:(ACRView *)rootView
{
    self = [super init];
    if (self) {
        _rootView = rootView;
        _isAtRootLevel = actionElement.isAtRootLevel;
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
                [menuItem loadIconImageWithSize:CGSizeMake(40, 40)
                                   onIconLoaded:^(UIImage *image) {
                                       [menuAction setValue:[image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]
                                                     forKey:@"image"];
                                   }];
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
    BOOL shouldDisplay = YES;
    if ([_rootView.acrActionDelegate
            respondsToSelector:@selector(onDisplayOverflowActionMenu:alertController:additionalData:)]) {
        NSDictionary *additionalData = @{ACROverflowTargetIsRootLevelKey : [NSNumber numberWithBool:_isAtRootLevel]};
        shouldDisplay = ![_rootView.acrActionDelegate onDisplayOverflowActionMenu:_menuItems
                                                                  alertController:_alert
                                                                   additionalData:additionalData];
    }

    if (shouldDisplay) {
        // find first UIViewController responds to rootView as default controller
        UIViewController *controller = traverseResponderChainForUIViewController(_rootView);
        if (controller) {
            [controller presentViewController:_alert animated:TRUE completion:nil];
        }
    }
}

@end
