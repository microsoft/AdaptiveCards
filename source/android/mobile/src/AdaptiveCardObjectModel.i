/* File : AdaptiveCardObjectModel.i */

namespace std {
    template <class T> class enable_shared_from_this {
    public:
        shared_ptr<T> shared_from_this();
    protected:
        enable_shared_from_this();
        enable_shared_from_this(const enable_shared_from_this &);
        ~enable_shared_from_this();        
    };
}

%module AdaptiveCardObjectModel

%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_vector.i>

%{
#include "pch.h"
#include <memory>
#include "../../../shared/cpp/ObjectModel/Enums.h"
#include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
#include "../../../shared/cpp/ObjectModel/Container.h"
#include "../../../shared/cpp/ObjectModel/TextBlock.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCard.h"
%}

%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::Container)
%shared_ptr(AdaptiveCards::TextBlock)
%shared_ptr(AdaptiveCards::AdaptiveCard)

%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >; 
%template(EnableSharedFromThisContainer) std::enable_shared_from_this<AdaptiveCards::Container>;

%exception AdaptiveCards::Container::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Container {
    static AdaptiveCards::Container *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Container *>(baseCardElement);
    }
};

%exception AdaptiveCards::TextBlock::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::TextBlock {
    static AdaptiveCards::TextBlock *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::TextBlock *>(baseCardElement);
    }
};

#include "../../../shared/cpp/ObjectModel/pch.h"
%include "../../../shared/cpp/ObjectModel/Enums.h"
%include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
%include "../../../shared/cpp/ObjectModel/Container.h"
%include "../../../shared/cpp/ObjectModel/TextBlock.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCard.h"

