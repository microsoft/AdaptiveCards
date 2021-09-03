//
//  ACOPaddingHandler.mm
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//

#import "ACOPaddingHandler.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACOPaddingHandler {
    NSMapTable<UIView *, NSMutableArray<NSValue *> *> *_paddingMap;
    NSHashTable<UIView *> *_stretchableViewSet;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _paddingMap = [NSMapTable mapTableWithKeyOptions:NSMapTableWeakMemory valueOptions:NSMapTableStrongMemory];
        _stretchableViewSet = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:5];
    }
    return self;
}

- (BOOL)hasPadding
{
    if (_stretchableViewSet) {
        return _stretchableViewSet.count != 0;
    }
    return NO;
}

- (UIView *)addPaddingFor:(UIView *)view
{
    if (!view) {
        return nil;
    }

    UIView *padding = [[UIView alloc] init];

    [self configureHugging:padding];

    NSMutableArray<NSValue *> *values = [_paddingMap objectForKey:view];
    if (!values) {
        values = [[NSMutableArray alloc] init];
        [_paddingMap setObject:values forKey:view];
    }

    [_stretchableViewSet addObject:padding];
    [values addObject:[NSValue valueWithNonretainedObject:padding]];

    return padding;
}

- (void)configureHugging:(UIView *)view
{
    view.translatesAutoresizingMaskIntoConstraints = NO;
    [view setContentHuggingPriority:UILayoutPriorityDefaultLow - 10 forAxis:UILayoutConstraintAxisVertical];
}

- (void)configureHeight:(UIView *)view correspondingElement:(ACOBaseCardElement *)correspondingElement
{
    if (!view || !correspondingElement || !correspondingElement.element) {
        return;
    }

    if ((HeightType::Stretch == correspondingElement.element->GetHeight()) &&
        (correspondingElement.type != ACRImage)) {
        [self configureHugging:view];
        [_stretchableViewSet addObject:view];
    }
}

- (NSArray<NSLayoutConstraint *> *)activateConstraintsForPadding
{
    if (_stretchableViewSet.count > 1) {
        NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
        UIView *prevPadding = nil;
        for (UIView *padding in _stretchableViewSet.objectEnumerator) {
            if (prevPadding) {
                [constraints addObject:[prevPadding.heightAnchor constraintEqualToAnchor:padding.heightAnchor]];
                constraints.lastObject.priority = UILayoutPriorityDefaultLow;
            }
            prevPadding = padding;
        }

        if (constraints && constraints.count) {
            [NSLayoutConstraint activateConstraints:constraints];
        }

        return constraints;
    }
    return nil;
}

- (BOOL)isPadding:(UIView *)padding
{
    return [_stretchableViewSet containsObject:padding];
}

@end
