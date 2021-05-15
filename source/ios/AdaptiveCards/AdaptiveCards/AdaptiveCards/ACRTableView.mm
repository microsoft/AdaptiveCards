//
//  ACRTableView.m
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import "ACRTableView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRTableRow.h"
#import "Table.h"
#import "TableCell.h"
#import "TableColumnDefinition.h"
#import "TableRow.h"

@implementation ACRTableView {
    NSMutableArray<ACRColumnDefinition *> *_columnDefinitions;
}

- (instancetype)init:(ACOBaseCardElement *)acoElement config:(ACOHostConfig *)acoConfig
{
    self = [super init];
    if (self) {
        std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
        std::shared_ptr<Table> table = std::dynamic_pointer_cast<Table>([acoElement element]);
        _columnDefinitions = [[NSMutableArray alloc] init];
        [self defineColumnDefinitions:table];
    }
    return self;
}

- (void)defineColumnDefinitions:(const std::shared_ptr<Table> &)table
{
    CGFloat minNumericWidth = CGFLOAT_MAX;
    NSInteger i = 0;
    NSInteger baseIndex = -1;
    for (const auto &columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        if (optionalNumericValue.has_value()) {
            if (optionalNumericValue.value_or(1) < minNumericWidth) {
                minNumericWidth = optionalNumericValue.value_or(1);
                baseIndex = i;
            }
        }
        i++;
    }

    for (auto columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        if (optionalNumericValue.has_value()) {
            [_columnDefinitions addObject:[[ACRColumnDefinition alloc] init:optionalNumericValue.value_or(1) / minNumericWidth baseIndex:baseIndex]];
        } else if (auto optionalPixelValue = columnDefinition->GetPixelWidth(); optionalPixelValue.has_value()) {
            [_columnDefinitions addObject:[[ACRColumnDefinition alloc] init:optionalPixelValue.value_or(1)]];
        } else {
            ACRColumnDefinition *invalidColumnDefintion = [[ACRColumnDefinition alloc] init];
            invalidColumnDefintion.isValid = NO;
            [_columnDefinitions addObject:invalidColumnDefintion];
        }
    }
}

- (void)buildRowView:(const std::shared_ptr<Table> &)table
{
    ACOBaseCardElement *acoRowWrapper = [[ACOBaseCardElement alloc] init];
    for (const auto &row : table->GetRows()) {
        [acoRowWrapper setElem:row];
        ACRTableRowView *rowView = [[ACRTableRowView alloc] init:acoRowWrapper columnDefinitions:_columnDefinitions];
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
