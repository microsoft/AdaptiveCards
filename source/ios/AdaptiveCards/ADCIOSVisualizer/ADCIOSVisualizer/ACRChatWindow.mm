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
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        adaptiveCardsWidth = 330;
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
    }

    return self;
}

- (void)insertCard:(NSString *)card
{
    [adaptiveCardsPayloads addObject:card];
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

    static NSString *identifier = @"AdaptiveCardsCell";

    cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell && cell.contentView.subviews.count) {
        [cell.contentView.subviews[0] removeFromSuperview];
    } else {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
    }

    if (indexPath.row >= numberOfCards) {
        numberOfCards += 1;
        NSString *jsonString = adaptiveCardsPayloads[indexPath.row];
        ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:hostConfig
                                                                resourceResolvers:resolvers];
        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:jsonString];

        ACRRenderResult *renderResult = [ACRRenderer render:cardParseResult.card
                                                     config:hostconfigParseResult.config
                                            widthConstraint:adaptiveCardsWidth
                                                   delegate:self.adaptiveCardsDelegates];
        [adaptiveCardsViews addObject:renderResult.view];
    }

    UIView *adaptiveCardView = adaptiveCardsViews[indexPath.row];
    [cell.contentView addSubview:adaptiveCardView];
    [adaptiveCardView.topAnchor constraintEqualToAnchor:cell.contentView.topAnchor constant:0].active = YES;
    [adaptiveCardView.centerXAnchor constraintEqualToAnchor:cell.contentView.centerXAnchor constant:0].active = YES;
    [cell.contentView.bottomAnchor constraintGreaterThanOrEqualToAnchor:adaptiveCardView.bottomAnchor constant:0]
        .active = YES;
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

//
//- (void)tableView:(UITableView *)tableView
//commitEditingStyle:(UITableViewCellEditingStyle)editingStyle
//forRowAtIndexPath:(NSIndexPath *)indexPath
//{
//
//}

@end
