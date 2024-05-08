//
//  ACOTypeaheadDynamicChoicesService.mm
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOTypeaheadDebouncer.h"
#import "ACRView.h"
#import "ChoiceSetInput.h"
#import "ChoicesData.h"
#import <Foundation/Foundation.h>

static NSString *const AdaptiveCardChoices = @"action";
static NSTimeInterval delayTimeInSeconds = 0.25;

@implementation ACOTypeaheadDynamicChoicesService {
    __weak ACRView *_rootView;
    ACOTypeaheadDebouncer *_debouncer;
    dispatch_queue_t _global_queue;
    ACOBaseCardElement *_inputElem;
    id<ACRTypeaheadSearchProtocol> _typeaheadSearchDelegate;
}

- (instancetype)initWithRootView:(ACRView *)rootView
                       inputElem:(ACOBaseCardElement *)inputElem
         typeaheadSearchDelegate:(id<ACRTypeaheadSearchProtocol>)typeaheadSearchDelegate
{
    self = [super init];
    if (self) {
        _rootView = rootView;
        _debouncer = [[ACOTypeaheadDebouncer alloc] initWithDelay:delayTimeInSeconds];
        _debouncer.delegate = self;
        _global_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _inputElem = inputElem;
        _typeaheadSearchDelegate = typeaheadSearchDelegate;
    }

    return self;
}

- (void)fetchChoicesFromDynamicSourceWithSearchQuery:(NSString *)searchQuery
{
    [_debouncer postInput:searchQuery];
}

- (void)dealloc
{
    _debouncer.delegate = nil;
}

- (NSDictionary *)getRequestPayloadForTypeaheadSearchWithQueryText:(NSString *)queryText
                                                     withSkipValue:(int)skipVal
                                                       AndTopValue:(int)topVal
{
    std::shared_ptr<BaseCardElement> elem = [_inputElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    std::shared_ptr<ChoicesData> choicesData = choiceSet->GetChoicesData();
    NSString *choicesDataType = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ChoicesDataType).c_str() encoding:NSUTF8StringEncoding];
    NSString *datasetKey = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Dataset).c_str() encoding:NSUTF8StringEncoding];
    NSString *value = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value).c_str() encoding:NSUTF8StringEncoding];
    NSString *dataset = (choicesData == nil) ? @"" : [NSString stringWithCString:choicesData->GetDataset().c_str()
                                                                        encoding:NSUTF8StringEncoding];
    NSString *dataQuery = (choicesData == nil) ? @"" : [NSString stringWithCString:choicesData->GetChoicesDataType().c_str()
                                                                          encoding:NSUTF8StringEncoding];

    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary:@{
        choicesDataType : dataQuery,
        datasetKey : dataset,
        value : queryText ?: @"",
        @"skip" : [NSNumber numberWithInt:skipVal], // used for pagination.Usage - retrieve top n records by skipping first x records.
        @"top" : [NSNumber numberWithInt:topVal]
    }];
    return requestPayload;
}

#pragma mark - ACOTypeaheadDebouncerDelegate Methods specifically for dynamic typeahead

- (void)debouncerDidSendOutput:(id)key
{
    if ([key isKindOfClass:NSString.class]) {
        __weak __typeof(self) weakSelf = self;
        dispatch_async(_global_queue, ^{
            __strong __typeof(self) strongSelf = weakSelf;
            if ([strongSelf->_rootView.acrActionDelegate respondsToSelector:@selector(onChoiceSetQueryChange:acoElem:completion:)]) {
                NSDictionary *requestPayload = [strongSelf getRequestPayloadForTypeaheadSearchWithQueryText:key withSkipValue:0 AndTopValue:15];
                [strongSelf->_rootView.acrActionDelegate onChoiceSetQueryChange:requestPayload
                                                                        acoElem:strongSelf->_inputElem
                                                                     completion:^(NSDictionary *response, NSError *error) {
                                                                         NSDictionary *choices = [response objectForKey:@"value"];
                                                                         if ([strongSelf->_typeaheadSearchDelegate respondsToSelector:@selector(updateTypeaheadUIWithSearchText:dynamicChoices:withError:)]) {
                                                                             [strongSelf->_typeaheadSearchDelegate updateTypeaheadUIWithSearchText:key dynamicChoices:choices withError:error];
                                                                         }
                                                                     }];
            }
        });
    }
}

@end
