//
//  ACOPaddingHandler.mm
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//

#import "ACOFillerSpaceManager.h"
#import "ACOBaseCardElementPrivate.h"

const CGFloat kFillerViewLayoutConstraintPriority = UILayoutPriorityDefaultLow - 10;

@implementation ACOFillerSpaceManager {
    NSMapTable<UIView *, NSMutableArray<NSValue *> *> *_paddingMap;
    NSMapTable<UIView *, NSValue *> *_separatorMap;
    NSHashTable<UIView *> *_stretchableViewSet;
    NSMutableArray<NSValue *> *_stretchableViews;
    NSHashTable<UIView *> *_paddingSet;
    NSMutableArray<NSLayoutConstraint *> *_paddingConstraints;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _paddingMap = [NSMapTable mapTableWithKeyOptions:NSMapTableWeakMemory valueOptions:NSMapTableStrongMemory];
        _separatorMap = [NSMapTable mapTableWithKeyOptions:NSMapTableWeakMemory valueOptions:NSMapTableStrongMemory];
        _stretchableViewSet = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:5];
        _stretchableViews = [[NSMutableArray alloc] init];
        _paddingSet = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:5];
    }
    return self;
}

/// tells if the owner of this object has padding
- (BOOL)hasPadding
{
    if (_stretchableViews) {
        if (_stretchableViews.count) {
            for (NSValue *value in _stretchableViews) {
                UIView *view = value.nonretainedObjectValue;
                if (!view.isHidden) {
                    return YES;
                }
            }
        }
    }
    return NO;
}

/// configures & adds padding for the `view`
/// having padding makes the owner of the object,
/// stretchable
- (UIView *)addPaddingFor:(UIView *)view
{
    if (!view) {
        return nil;
    }

    UIView *padding = [[UIView alloc] init];

    [ACOFillerSpaceManager configureHugging:padding];

    NSMutableArray<NSValue *> *values = [_paddingMap objectForKey:view];
    if (!values) {
        values = [[NSMutableArray alloc] init];
        [_paddingMap setObject:values forKey:view];
    }

    [_stretchableViewSet addObject:padding];
    [_stretchableViews addObject:[NSValue valueWithNonretainedObject:padding]];
    [_paddingSet addObject:padding];
    [values addObject:[NSValue valueWithNonretainedObject:padding]];

    return padding;
}

+ (void)configureHugging:(UIView *)view
{
    view.translatesAutoresizingMaskIntoConstraints = NO;
    [view setContentHuggingPriority:kFillerViewLayoutConstraintPriority forAxis:UILayoutConstraintAxisVertical];
}

/// configures for AdaptiveCards Height property
/// Image and Media gets their own padding since stretching them are not desirable
- (void)configureHeight:(UIView *)view correspondingElement:(ACOBaseCardElement *)correspondingElement
{
    if (!view || !correspondingElement || !correspondingElement.element) {
        return;
    }

    if ((HeightType::Stretch == correspondingElement.element->GetHeight()) &&
        (correspondingElement.type != ACRImage &&
         correspondingElement.type != ACRMedia)) {
        [ACOFillerSpaceManager configureHugging:view];
        [_stretchableViewSet addObject:view];
        [_stretchableViews addObject:[NSValue valueWithNonretainedObject:view]];
    }
}

/// activates the constraints together for performance
/// two stretchable views get same height
/// by setting low priority, the relationship can be overridden
/// if it's not possible
- (NSArray<NSLayoutConstraint *> *)activateConstraintsForPadding
{
    if (_stretchableViews.count > 1) {
        NSMutableArray<NSLayoutConstraint *> *_paddingConstraints = [[NSMutableArray alloc] init];
        UIView *prevPadding = nil;
        for (NSValue *paddingValue in _stretchableViews) {
            UIView *padding = paddingValue.nonretainedObjectValue;
            if (prevPadding && !padding.isHidden) {
                [_paddingConstraints addObject:[prevPadding.heightAnchor constraintEqualToAnchor:padding.heightAnchor]];
                _paddingConstraints.lastObject.priority = UILayoutPriorityDefaultLow;
            }
            if (!padding.isHidden) {
                prevPadding = padding;
            }
        }

        if (_paddingConstraints && _paddingConstraints.count) {
            [NSLayoutConstraint activateConstraints:_paddingConstraints];
        }

        return _paddingConstraints;
    }
    return nil;
}

- (void)deactivateConstraintsForPadding
{
    if (_paddingConstraints && _paddingConstraints.count) {
        [NSLayoutConstraint deactivateConstraints:_paddingConstraints];
    }
}

- (BOOL)isPadding:(UIView *)padding
{
    if (!padding) {
        return NO;
    }
    return [_paddingSet containsObject:padding];
}

- (NSArray<NSValue *> *)getFillerSpaceView:(UIView *)view
{
    if (_paddingMap) {
        return [_paddingMap objectForKey:view];
    }
    return nil;
}

- (void)associateSeparatorWithOwnerView:(UIView *)separator ownerView:(UIView *)ownerView
{
    [_separatorMap setObject:[NSValue valueWithNonretainedObject:separator] forKey:ownerView];
}

- (ACRSeparator *)getSeparatorForOwnerView:(UIView *)ownerView
{
    if (!ownerView) {
        return nil;
    }
    NSValue *value = [_separatorMap objectForKey:ownerView];
    if (value) {
        return value.nonretainedObjectValue;
    }
    return nil;
}

@end
