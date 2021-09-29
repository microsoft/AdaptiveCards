//
//  ACRTableCell.m
//  ACRTableCell
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableCellView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"

@implementation ACRTableCellView {
    ACRTableCellDefinition *_definition;
}

- (instancetype)init:(ACOBaseCardElement *)baseCardElement
      cellDefinition:(ACRTableCellDefinition *)definition
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    NSDictionary *attributes = @{@"padding-spacing" : [NSNumber numberWithFloat:definition.cellSpacing],
                                 @"horizontal-alignment" : [NSNumber numberWithInt:(int)definition.horizontalAlignment]};
    self = [self initWithFrame:CGRectZero attributes:attributes];
    self.translatesAutoresizingMaskIntoConstraints = NO;
    if (self) {
        if (definition) {
            _definition = definition;
        } else {
            _definition = [[ACRTableCellDefinition alloc] init];
        }

        [self configureForStyle:acoConfig];

        if (rootView.context.isFirstRowAsHeaders) {
            self.accessibilityTraits |= UIAccessibilityTraitHeader;
        }
    }
    return self;
}

- (void)configureForStyle:(ACOHostConfig *)acoConfig
{
    self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:_definition.style];
}

@end

@implementation ACRTableCellDefinition

@end
