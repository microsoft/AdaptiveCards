//
//  ACRToggleInputView.mm
//  ACRToggleInputView
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRToggleInputView.h"
#import "ToggleInput.h"

using namespace AdaptiveCards;

@implementation ACRToggleInputView
{
    std::shared_ptr<ToggleInput> toggleInputDataSource;
    std::shared_ptr<HostConfig> config;
}

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
{
    self = [super initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) style:style];
    if(self)
    {
        self.dataSource = self;
        self.delegate = self;
        self.backgroundColor = UIColor.clearColor;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        super.isSelected = NO;
        super.results = nil;
    }
    return self;
}

- (instancetype)initWithInputToggle:(std::shared_ptr<ToggleInput> const&)toggleInput
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
       WithSuperview:(UIView *)view
{
    self = [self initWithFrame:view.frame style:UITableViewStylePlain];
    if(self)
    {
        toggleInputDataSource = toggleInput;
        config = hostConfig;
        self.id = [[NSString alloc]initWithCString:toggleInputDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        if(toggleInputDataSource->GetValue() == toggleInputDataSource->GetValueOn())
        {
            self.isSelected = YES;
        }
        self.valueOn  = [[NSString alloc]initWithCString:toggleInputDataSource->GetValueOn().c_str()
                                           encoding:NSUTF8StringEncoding];
        self.valueOff = [[NSString alloc]initWithCString:toggleInputDataSource->GetValueOff().c_str()
                                           encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return nil;
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

    title = [NSString stringWithCString:toggleInputDataSource->GetTitle().c_str()
                       encoding:NSUTF8StringEncoding];
    if(self.isSelected)
    {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }

    cell.textLabel.text = title;

    return cell;
}

- (CGSize)intrinsicContentSize
{
    [self layoutIfNeeded];
    return self.contentSize;
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = self.isSelected? self.valueOn : self.valueOff;
}

@end
