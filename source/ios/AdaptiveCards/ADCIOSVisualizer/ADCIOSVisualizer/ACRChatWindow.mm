//
//  ACRChatWindow.mm
//  ACRChatWindow
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRChatWindow.h"
#import "ADCResolver.h"
#import <AdaptiveCards/ACFramework.h>
#import <Foundation/Foundation.h>

@implementation ACRChatWindow {
    NSUInteger numberOfCards;
    NSMutableArray<NSString *> *adaptiveCardsPayloads;
    NSMutableArray<id> *adaptiveCardsViews;
    CGFloat adaptiveCardsWidth;
    NSString *hostConfig;
    ACOResourceResolvers *resolvers;
    ACOAdaptiveCardParseResult *errorCard;
}

- (instancetype)init
{
    return [self init:330];
}

- (instancetype)init:(CGFloat)width
{
    self = [super init];
    if (self) {
        adaptiveCardsWidth = 0;
        adaptiveCardsPayloads = [[NSMutableArray alloc] init];
        adaptiveCardsViews = [[NSMutableArray alloc] init];
        NSBundle *main = [NSBundle mainBundle];
        hostConfig = [NSString stringWithContentsOfFile:[main pathForResource:@"sample" ofType:@"json"]
                                               encoding:NSUTF8StringEncoding
                                                  error:nil];
        resolvers = [[ACOResourceResolvers alloc] init];
        ADCResolver *resolver = [[ADCResolver alloc] init];
        [resolvers setResourceResolver:resolver scheme:@"http"];
        [resolvers setResourceResolver:resolver scheme:@"https"];
        [resolvers setResourceResolver:resolver scheme:@"data"];
        // register a custom scheme bundle with resolver
        [resolvers setResourceResolver:resolver scheme:@"bundle"];

        NSString *errorMSG = @"{\"type\": \"AdaptiveCard\", \"$schema\": "
                             @"\"http://adaptivecards.io/schemas/adaptive-card.json\",\"version\": "
                             @"\"1.2\", \"body\": [ {"
                             @"\"type\": \"TextBlock\", \"text\": \"Rendering Failed\","
                             @"\"weight\": \"Bolder\", \"color\": "
                             @"\"Attention\", \"horizontalAlignment\": \"Center\""
                             @"} ] }";
        errorCard = [ACOAdaptiveCard fromJson:errorMSG];
    }
    return self;
}

- (void)insertCard:(NSString *)card
{
    [adaptiveCardsPayloads addObject:card];
    [self renderCards:card];
    numberOfCards += 1;
}

- (void)insertView:(UIView *)view
{
    [adaptiveCardsPayloads addObject:@""];
    [adaptiveCardsViews addObject:view];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return adaptiveCardsViews.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ACRView *adaptiveCardView = nil;
    id view = adaptiveCardsViews[indexPath.row];
    // view will be null when accessiblity event has occured in which case redraw the adaptive cards
    if (view == [NSNull null]) {
        adaptiveCardView = [self renderCard:adaptiveCardsPayloads[indexPath.row]];
        if (adaptiveCardView) {
            adaptiveCardsViews[indexPath.row] = adaptiveCardView;
        }
    } else {
        adaptiveCardView = (ACRView *)view;
    }

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"adaptiveCell" forIndexPath:indexPath];
    if (cell) {
        ((ACRChatWindowCell *)cell).adaptiveCardView = adaptiveCardView;
    }

    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return UITableViewAutomaticDimension;
}

- (void)deleteAllRows:(UITableView *)tableView
{
    [adaptiveCardsPayloads removeAllObjects];
    [adaptiveCardsViews removeAllObjects];
    numberOfCards = 0;
    [tableView reloadData];
}

- (ACRView *)renderCard:(NSString *)card
{
    NSString *jsonString = card;
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:hostConfig
                                                            resourceResolvers:resolvers];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:jsonString];

    ACRRenderResult *renderResult = nil;

    if (cardParseResult.isValid) {
        renderResult = [ACRRenderer render:cardParseResult.card
                                    config:hostconfigParseResult.config
                           widthConstraint:adaptiveCardsWidth
                                  delegate:self.adaptiveCardsDelegates];
    } else {
        renderResult = [ACRRenderer render:errorCard.card
                                    config:hostconfigParseResult.config
                           widthConstraint:adaptiveCardsWidth
                                  delegate:self.adaptiveCardsDelegates];
    }
    return renderResult.view;
}

- (void)renderCards:(NSString *)card
{
    [adaptiveCardsViews addObject:[self renderCard:card]];
}

// empty the cached adaptive cards views
// only visible adaptive card view will be drawn initially, and will cause to render adaptive cards when the cards in the invisible rows become visible.
- (void)prepareForRedraw
{
    if (adaptiveCardsViews) {
        for (NSInteger i = 0; i < adaptiveCardsViews.count; i++) {
            adaptiveCardsViews[i] = [NSNull null];
        }
    }
}
@end

// configure the content cell
@implementation ACRChatWindowCell {
    NSArray<NSLayoutConstraint *> *_contentViewConstraints;
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        _contentViewConstraints = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)setAdaptiveCardView:(ACRView *)adaptiveCardView
{
    _adaptiveCardView = adaptiveCardView;
    if (self.adaptiveCardView) {
        if (self.contentView.subviews && self.contentView.subviews.count) {
            [self.contentView.subviews[0] removeFromSuperview];
        }
        [self.contentView addSubview:self.adaptiveCardView];
        [self updateLayoutConstraints];
    }
}

- (void)updateLayoutConstraints
{
    _contentViewConstraints = @[
        [self.adaptiveCardView.centerXAnchor constraintEqualToAnchor:self.contentView.centerXAnchor],
        [self.adaptiveCardView.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],
        [self.contentView.heightAnchor constraintEqualToAnchor:self.adaptiveCardView.heightAnchor],
        [self.contentView.widthAnchor constraintEqualToAnchor:self.adaptiveCardView.widthAnchor]
    ];
    [NSLayoutConstraint activateConstraints:_contentViewConstraints];
}

@end
