//
//  ACRChoiceSetView.mm
//  ACRChoiceSetView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRChoiceSetView.h"
#import "ChoiceSetInput.h"

using namespace AdaptiveCards;

@implementation ACRChoiceSetView
{
    std::shared_ptr<ChoiceSetInput> choiceSetDataSource;
    std::shared_ptr<HostConfig> config;
    BOOL isMultichoiceAllowed;
}

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
                             superview:(UIView *)view
{
    self = [super initWithFrame:view.frame style:UITableViewStyleGrouped];
    if(self)
    {
        choiceSetDataSource = choiceSet;
        config = hostConfig;
        super.id = [[NSString alloc]initWithCString:choiceSetDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        isMultichoiceAllowed = choiceSetDataSource->GetIsMultiSelect();
        super.results = [[NSMutableDictionary alloc]init];
    }
    return self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return choiceSetDataSource->GetChoices().size();
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"tabCellId";

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
    }

    NSString *title = nil;

    title = [NSString stringWithCString:choiceSetDataSource->GetChoices()[indexPath.row]->GetTitle().c_str()
                               encoding:NSUTF8StringEncoding];

    cell.textLabel.text = title;

    return cell;
}

- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if(isMultichoiceAllowed == NO)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType =
        UITableViewCellAccessoryNone;
        self.results[[NSNumber numberWithInteger:indexPath.row]] = [NSNumber numberWithBool:NO];
    }
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSMutableArray *values = [[NSMutableArray alloc] init];
    for(NSInteger i = 0; i < [self.results count]; i++)
    {
        if([self.results[[NSNumber numberWithInteger:i]] boolValue] == YES)
        {
            [values addObject:
             [NSString stringWithCString:choiceSetDataSource->GetChoices()[i]->GetValue().c_str()
                                encoding:NSUTF8StringEncoding]];

        }
    }
    dictionary[self.id] = [values componentsJoinedByString:@";"];
}

@end
