//
//  AdaptiveFileBrowser.m
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 8/8/19.
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "AdaptiveFileBrowserSource.h"
#import <AdaptiveCards/AdaptiveCards.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/Fact.h>
#import <AdaptiveCards/FactSet.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <AdaptiveCards/SubmitAction.h>

using namespace std;
using namespace AdaptiveCards;

bool compare(shared_ptr<BaseActionElement> const &a, shared_ptr<BaseActionElement> const &b)
{
    return a->GetTitle() < b->GetTitle();
}

@implementation AdaptiveFileBrowserSource {
    NSString *_rootPath;
    NSFileManager *_fileManager;
    __weak UIView *_adaptiveView;
    __weak id<ACVTableViewControllerFetchDataDelegate> _tableFetchDataDelegate;
    ACOHostConfig *_hostConfig;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        NSBundle *main = [NSBundle mainBundle];
        NSString *resourcePath = [main resourcePath];
        _rootPath = [resourcePath stringByAppendingPathComponent:@"samples"];
        _fileManager = [NSFileManager defaultManager];
        NSString *hostConfigAsString = [NSString stringWithContentsOfFile:[main pathForResource:@"filebrowserHostConfig" ofType:@"json"]
                                                                 encoding:NSUTF8StringEncoding
                                                                    error:nil];
        ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:hostConfigAsString resourceResolvers:nil];
        if (hostconfigParseResult.isValid) {
            _hostConfig = hostconfigParseResult.config;
        }

        [self updateAdaptiveViewWithNewPath:_rootPath];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame WithDataDelegate:(id<ACVTableViewControllerFetchDataDelegate>)delegate
{
    self = [self initWithFrame:frame];
    if (self) {
        _tableFetchDataDelegate = delegate;
    }
    return self;
}

- (UIView *)getAdaptiveFileBrowserView:(NSArray<NSString *> *)directory parentDir:(NSString *)parentDir
{
    AdaptiveCard card{};
    card.SetVersion("1.2");
    auto &body{card.GetBody()};
    shared_ptr<TextBlock> currentDirectoryLabel{make_shared<TextBlock>()};
    currentDirectoryLabel->SetText("Available Sample JSONs");
    currentDirectoryLabel->SetTextSize(TextSize::Large);
    currentDirectoryLabel->SetHorizontalAlignment(HorizontalAlignment::Center);
    currentDirectoryLabel->SetTextWeight(TextWeight::Bolder);
    body.push_back(currentDirectoryLabel);

    shared_ptr<FactSet> directoryIndicator{make_shared<FactSet>()};
    directoryIndicator->SetSeparator(true);
    shared_ptr<Fact> directoryName{make_shared<Fact>()};
    directoryName->SetTitle("current directory:");
    directoryName->SetValue([_fileManager displayNameAtPath:parentDir].UTF8String);
    directoryIndicator->GetFacts().push_back(directoryName);
    body.push_back(directoryIndicator);

    auto &actions{card.GetActions()};
    auto backAction{buildAction([parentDir stringByDeletingLastPathComponent].UTF8String, "Back")};
    backAction->SetStyle("destructive");

    BOOL isAtRoot = [parentDir isEqualToString:_rootPath];
    if (!isAtRoot) {
        actions.push_back(backAction);
    }

    NSMutableArray *filesList = [[NSMutableArray alloc] init];

    for (NSString *path in directory) {
        BOOL isDirectory = NO;
        NSString *resourcePath = [parentDir stringByAppendingPathComponent:path];
        if ([_fileManager fileExistsAtPath:resourcePath isDirectory:&isDirectory]) {
            if (isDirectory && ![[_fileManager displayNameAtPath:path] isEqualToString:@"HostConfig"]) {
                actions.push_back(buildAction(resourcePath.UTF8String, [_fileManager displayNameAtPath:path].UTF8String));
            } else if ([[resourcePath pathExtension] isEqualToString:@"json"]) {
                [filesList addObject:resourcePath];
            }
        }
    }

    sort(actions.begin(), actions.end(), compare);

    if (!isAtRoot && actions.size() > 1) {
        actions.push_back(backAction);
    }

    if ([filesList count]) {
        NSArray<NSString *> *immutableFilesList;
        immutableFilesList = [filesList sortedArrayUsingComparator:^NSComparisonResult(id _Nonnull obj1, id _Nonnull obj2) {
            NSString *path1 = obj1, *path2 = obj2;
            NSComparisonResult result = [[[NSFileManager defaultManager] displayNameAtPath:path1] compare:[[NSFileManager defaultManager] displayNameAtPath:path2]];
            return result;
        }];

        [_tableFetchDataDelegate updateTable:immutableFilesList];
    }

    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:[NSString stringWithUTF8String:card.Serialize().c_str()]];
    ACRRenderResult *renderResult;
    if (cardParseResult.isValid) {
        renderResult = [ACRRenderer render:cardParseResult.card config:_hostConfig widthConstraint:self.frame.size.width delegate:self];
    }

    if (renderResult.succeeded) {
        return renderResult.view;
    }

    return nil;
}

shared_ptr<SubmitAction> buildAction(const string &path, const string &title)
{
    shared_ptr<SubmitAction> action{make_shared<SubmitAction>()};
    action->SetTitle(title);
    stringstream dataCString;
    dataCString << "{\"path\":\"" << path << "\"}";
    action->SetDataJson(dataCString.str());

    return action;
}

- (void)updateAdaptiveViewWithNewPath:(NSString *)path
{
    NSError *error;
    NSArray *directoryContents = [_fileManager contentsOfDirectoryAtPath:path error:&error];
    UIView *view = [self getAdaptiveFileBrowserView:directoryContents parentDir:path];
    [self addSubview:view];
    [_adaptiveView removeFromSuperview];
    _adaptiveView = view;
    [self.topAnchor constraintEqualToAnchor:_adaptiveView.topAnchor].active = YES;
    [self.bottomAnchor constraintEqualToAnchor:_adaptiveView.bottomAnchor].active = YES;
    [_adaptiveView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
    [_adaptiveView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
}

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
    [_tableFetchDataDelegate updateTable:nil];
    if (action.type == ACRSubmit) {
        NSData *data = [[action data] dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&err];
        if (!err) {
            [self updateAdaptiveViewWithNewPath:dictionary[@"path"]];
        }
    }
}

@end
