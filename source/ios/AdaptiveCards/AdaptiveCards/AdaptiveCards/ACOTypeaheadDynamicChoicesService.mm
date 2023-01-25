//
//  ACOTypeaheadDynamicChoicesService.mm
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRView.h"
#import "ACOTypeaheadDebouncer.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACOBaseCardElementPrivate.h"
#import "ChoiceSetInput.h"
#import "ChoicesData.h"

static NSString * const AdaptiveCardChoices = @"action";

@implementation ACOTypeaheadDynamicChoicesService {
    __weak ACRView *_rootView;
    ACOTypeaheadDebouncer *_debouncer;
    dispatch_queue_t _global_queue;
    ACOBaseCardElement *_inputElem;
    id<ACRTypeaheadSearchProtocol> _typeaheadSearchDelegate;
}

-(instancetype)initWithRootView:(ACRView *)rootView
                      inputElem:(ACOBaseCardElement *)inputElem
        typeaheadSearchDelegate:(id<ACRTypeaheadSearchProtocol>)typeaheadSearchDelegate
{
    self = [super init];
    if(self) {
        _rootView = rootView;
        _debouncer = [[ACOTypeaheadDebouncer alloc] initWithDelay:0.2];
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
                                                     withSkipValue:(NSNumber *)skipVal
                                                       AndTopValue:(NSNumber *)topVal
{
    std::shared_ptr<BaseCardElement> elem = [_inputElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    std::shared_ptr<ChoicesData> choicesData = choiceSet->GetChoicesData();
    NSString *type = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ChoicesDataType).c_str() encoding:NSUTF8StringEncoding];
    NSString *datasetKey = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Dataset).c_str() encoding:NSUTF8StringEncoding];
    NSString *value = [NSString stringWithCString:AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value).c_str() encoding:NSUTF8StringEncoding];
    NSString *dataset = [NSString stringWithCString:choicesData->GetDataset().c_str()
                                 encoding:NSUTF8StringEncoding];
    NSString *dataQuery = [NSString stringWithCString:choicesData->GetChoicesDataType().c_str()
                                 encoding:NSUTF8StringEncoding];

    NSMutableDictionary *requestPayload = [NSMutableDictionary new];
    [requestPayload setDictionary: @{
        type: dataQuery,
        datasetKey: dataset,
        value: queryText ?: @"",
        //used for pagination.Usage - retrieve top n records by skipping first x records.
        @"skip": skipVal,
        @"top": topVal
    }];
    return requestPayload;
}

#pragma mark - ACODebouncerDelegate Methods specifically for dynamic typeahead
- (void)debouncerDidSendOutput:(id)key
{
    if ([key isKindOfClass:NSString.class])
    {
        dispatch_async(_global_queue, ^{
            __weak typeof(self) weakSelf = self;
            if ([self->_rootView.acrActionDelegate
                 respondsToSelector:@selector(onChoiceSetQueryChange:acoElem:completion:)]) {
                NSDictionary *requestPayload = [self getRequestPayloadForTypeaheadSearchWithQueryText:key withSkipValue:[NSNumber numberWithInt:0] AndTopValue:[NSNumber numberWithInt:15]];
                [self->_rootView.acrActionDelegate onChoiceSetQueryChange:requestPayload acoElem:self->_inputElem completion:^(NSDictionary * response, NSError *error) {
                    __strong typeof(self) strongSelf = weakSelf;
                    dispatch_async(dispatch_get_main_queue(), ^{
                        NSDictionary *choices = [response objectForKey:@"value"];
                        [strongSelf->_typeaheadSearchDelegate updateTypeaheadUIWithSearchText:key dynamicChoices:choices withError:error];
                    });
                }];
            } else {
                [self->_typeaheadSearchDelegate updateTypeaheadUIWithSearchText:key dynamicChoices:nil withError:nil];
            }
        });
    }
}
@end
