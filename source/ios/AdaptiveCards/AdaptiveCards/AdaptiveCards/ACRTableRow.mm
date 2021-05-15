//
//  ACRTableRow.m
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import "ACRTableRow.h"
#import "ACRTableCellView.h"

@implementation ACRColumnDefinition

- (instancetype)init
{
    self = [super init];
    if (self) {
        _numeric = 0;
        _baseIndex = -1;
        _isValid = YES;
    }

    return self;
}

- (instancetype)init:(CGFloat)numeric
{
    self = [self init];
    if (self) {
        _numeric = numeric;
    }
    return self;
}

- (instancetype)init:(CGFloat)numeric baseIndex:(NSInteger)baseIndex
{
    self = [self init];
    if (self) {
        _numeric = numeric;
        _baseIndex = baseIndex;
    }
    return self;
}

@end

@implementation ACRTableRowView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.translatesAutoresizingMaskIntoConstraints = NO;
        NSBundle *mainBundle = [NSBundle mainBundle];
        NSString *payload0 = [NSString stringWithContentsOfFile:[mainBundle pathForResource:@"TextBlock" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];

        NSString *payload1 = [NSString stringWithContentsOfFile:[mainBundle pathForResource:@"Input" ofType:@"json"] encoding:NSUTF8StringEncoding error:nil];

        ACOHostConfigParseResult *configParseResult = [ACOHostConfig fromJson:nil];

        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:payload0];
        ACOAdaptiveCardParseResult *cardParseResult1 = [ACOAdaptiveCard fromJson:payload1];

        if (cardParseResult.isValid) {
            ACRRenderResult *result = [ACRRenderer render:cardParseResult.card config:configParseResult.config widthConstraint:0 delegate:self];

            result.view.translatesAutoresizingMaskIntoConstraints = NO;
            result.view.backgroundColor = UIColor.clearColor;
            ACRTableCellView *cellView = [[ACRTableCellView alloc] init:result.view cellDefinition:[[ACRTableCellDefinition alloc] init:ACRLeft]];
            [cellView.widthAnchor constraintEqualToConstant:100.0].active = YES;
            cellView.translatesAutoresizingMaskIntoConstraints = NO;
            ACRRenderResult *result1 = [ACRRenderer render:cardParseResult1.card config:configParseResult.config widthConstraint:0 delegate:self];

            result1.view.translatesAutoresizingMaskIntoConstraints = NO;
            result1.view.backgroundColor = UIColor.clearColor;
            ACRTableCellView *cellView1 = [[ACRTableCellView alloc] init:result1.view cellDefinition:[[ACRTableCellDefinition alloc] init:ACRLeft]];
            [cellView1.widthAnchor constraintEqualToConstant:200.0].active = YES;
            cellView1.translatesAutoresizingMaskIntoConstraints = NO;
            [self addSubview:cellView];
            [self addSubview:cellView1];

            [self.heightAnchor constraintGreaterThanOrEqualToAnchor:cellView.heightAnchor].active = YES;
            [self.heightAnchor constraintGreaterThanOrEqualToAnchor:cellView1.heightAnchor].active = YES;

            NSLayoutConstraint *h0 = [cellView.heightAnchor constraintGreaterThanOrEqualToConstant:0.0];
            NSLayoutConstraint *h1 = [cellView1.heightAnchor constraintGreaterThanOrEqualToConstant:0.0];
            h0.priority = UILayoutPriorityDefaultLow;
            h1.priority = UILayoutPriorityDefaultLow;
            h0.active = YES;
            h1.active = YES;

            [cellView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
            [cellView1.leadingAnchor constraintEqualToAnchor:cellView.trailingAnchor constant:8.0f].active = YES;
            [self.trailingAnchor constraintEqualToAnchor:cellView1.trailingAnchor].active = YES;

            [cellView.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
            [cellView1.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
        }
    }

    return self;
}

- (instancetype)init:(ACOBaseCardElement *)acoElem columnDefinitions:(NSArray<ACRColumnDefinition *> *)columnDefinition
{
    
}

- (CGSize)intrinsicContentSize
{
    return CGSizeMake(UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric);
}
@end
