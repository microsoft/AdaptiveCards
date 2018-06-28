//
//  ACRToggleInputDataSource.mm
//  ACRToggleInputDataSource
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRToggleInputDataSource.h"
#import "ACRIBaseCardElementRenderer.h"
#import "HostConfig.h"
#import "ACRUILabel.h"
#import "ACRColumnSetView.h"

using namespace AdaptiveCards;

@implementation ACRToggleInputDataSource
{
    std::shared_ptr<ToggleInput> _toggleInputDataSource;
    std::shared_ptr<HostConfig> _config;
    UISwitch *_toggleSwitch;
    NSString *_title;
}

- (instancetype)initWithInputToggle:(std::shared_ptr<ToggleInput> const&)toggleInput
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
{
    self = [super init];
    
    if(self) {
        _title = [NSString stringWithCString:toggleInput->GetTitle().c_str()
                                    encoding:NSUTF8StringEncoding];
        _toggleSwitch = [[UISwitch alloc] init];
        _toggleInputDataSource = toggleInput;
        _config = hostConfig;
        self.id = [[NSString alloc]initWithCString:_toggleInputDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        if(_toggleInputDataSource->GetValue() == _toggleInputDataSource->GetValueOn()) {
            _toggleSwitch.on = YES;
        }

        self.valueOn  = [[NSString alloc]initWithCString:_toggleInputDataSource->GetValueOn().c_str()
                                           encoding:NSUTF8StringEncoding];
        self.valueOff = [[NSString alloc]initWithCString:_toggleInputDataSource->GetValueOff().c_str()
                                           encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"cellForCompactMode";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(!cell)
    {
        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        [tableView registerNib:[UINib nibWithNibName:@"ACRCellForCompactMode" bundle:bundle] forCellReuseIdentifier:identifier];
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        cell.textLabel.text = _title;
        cell.accessoryView = _toggleSwitch;
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

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = _toggleSwitch.on? self.valueOn : self.valueOff;
}

@end
