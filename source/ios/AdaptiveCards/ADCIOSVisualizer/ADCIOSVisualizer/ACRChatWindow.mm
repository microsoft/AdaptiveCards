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
    NSMutableArray<UIView *> *adaptiveCardsViews;
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
        adaptiveCardsWidth = width;
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

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return adaptiveCardsPayloads.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = nil;

    UIView *adaptiveCardView = adaptiveCardsViews[indexPath.row];
    NSString *identifier = @"Hello"; //[NSString stringWithFormat:@"%p", adaptiveCardView];

    //cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell) {
        return cell;
    } else {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
        [cell.contentView addSubview:adaptiveCardView];
    }

    //[adaptiveCardView.centerXAnchor constraintEqualToAnchor:cell.contentView.centerXAnchor].active = YES;
    //[adaptiveCardView.centerYAnchor constraintEqualToAnchor:cell.contentView.centerYAnchor].active = YES;
    [cell.contentView.topAnchor constraintEqualToAnchor:adaptiveCardView.topAnchor].active = YES;
    [cell.contentView.bottomAnchor constraintEqualToAnchor:adaptiveCardView.bottomAnchor].active = YES;
    [cell.contentView.widthAnchor constraintEqualToAnchor:adaptiveCardView.widthAnchor].active = YES;
    
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

- (void)renderCards:(NSString *)card
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
    
    [adaptiveCardsViews addObject:renderResult.view];
}

@end
