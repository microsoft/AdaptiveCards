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
    NSHashTable<UIView *> *_paddingSet;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _paddingMap = [NSMapTable mapTableWithKeyOptions:NSMapTableWeakMemory valueOptions:NSMapTableStrongMemory];
        _paddingSet = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:5];
    }
    return self;
}

- (BOOL)hasPadding
{
    if (_paddingSet) {
        return _paddingSet.count != 0;
    }
    return NO;
}

- (void)configurePaddingFor:(UIView *)view
{
    UIView *blankTrailingSpace = view; //[[UIView alloc] init];
    blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
    [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow - 10 forAxis:UILayoutConstraintAxisVertical];
    NSMutableArray<NSValue *> *values = [_paddingMap objectForKey:view];
    if (!values) {
        values = [[NSMutableArray alloc] init];
        [_paddingMap setObject:values forKey:view];
    }

    [values addObject:[NSValue valueWithNonretainedObject:blankTrailingSpace]];
    [_paddingSet addObject:blankTrailingSpace];
    //return blankTrailingSpace;
}

- (UIView *)configurePaddingFor:(UIView *)view correspondingElement:(ACOBaseCardElement *)correspondingElement
{
    UIView *blankTrailingSpace = nil;

    if (HeightType::Stretch == correspondingElement.element->GetHeight()) {
        [self configurePaddingFor:view];
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow - 10 forAxis:UILayoutConstraintAxisVertical];
    }

    return blankTrailingSpace;
}

- (NSArray<NSLayoutConstraint *> *)activateConstraintsForPadding
{
    if (_paddingSet.count > 1) {
        NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
        UIView *prevPadding = nil;
        for (NSArray<NSValue *> *values in _paddingMap.objectEnumerator) {
            for (NSValue *value in values) {
                UIView *padding = [value nonretainedObjectValue];
                if (prevPadding && padding) {
                    [constraints addObject:[prevPadding.heightAnchor constraintEqualToAnchor:padding.heightAnchor]];
                    constraints.lastObject.priority = UILayoutPriorityDefaultLow;
                }

                prevPadding = padding;
            }
        }
        [NSLayoutConstraint activateConstraints:constraints];
        return constraints;
    }
    return nil;
}

- (BOOL)isPadding:(UIView *)padding
{
    return [_paddingSet containsObject:padding];
}

@end
