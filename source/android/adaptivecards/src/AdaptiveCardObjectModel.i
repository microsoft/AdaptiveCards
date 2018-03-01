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
%include <std_wstring.i>

#define __ANDROID__ 1

%{
#include "pch.h"
#include <memory>
#include "../../../shared/cpp/ObjectModel/Enums.h"
#include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
#include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
#include "../../../shared/cpp/ObjectModel/BaseInputElement.h"
#include "../../../shared/cpp/ObjectModel/ActionParserRegistration.h"
#include "../../../shared/cpp/ObjectModel/ElementParserRegistration.h"
#include "../../../shared/cpp/ObjectModel/Container.h"
#include "../../../shared/cpp/ObjectModel/Image.h"
#include "../../../shared/cpp/ObjectModel/ImageSet.h"
#include "../../../shared/cpp/ObjectModel/Column.h"
#include "../../../shared/cpp/ObjectModel/ColumnSet.h"
#include "../../../shared/cpp/ObjectModel/Fact.h"
#include "../../../shared/cpp/ObjectModel/FactSet.h"
#include "../../../shared/cpp/ObjectModel/ChoiceInput.h"
#include "../../../shared/cpp/ObjectModel/ChoiceSetInput.h"
#include "../../../shared/cpp/ObjectModel/DateInput.h"
#include "../../../shared/cpp/ObjectModel/NumberInput.h"
#include "../../../shared/cpp/ObjectModel/TextInput.h"
#include "../../../shared/cpp/ObjectModel/TimeInput.h"
#include "../../../shared/cpp/ObjectModel/ToggleInput.h"
#include "../../../shared/cpp/ObjectModel/OpenUrlAction.h"
#include "../../../shared/cpp/ObjectModel/ShowCardAction.h"
#include "../../../shared/cpp/ObjectModel/SubmitAction.h"
#include "../../../shared/cpp/ObjectModel/SharedAdaptiveCard.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
#include "../../../shared/cpp/ObjectModel/HostConfig.h"
#include "../../../shared/cpp/ObjectModel/MarkDownParser.h"
#include "../../../shared/cpp/ObjectModel/DateTimePreparsedToken.h"
#include "../../../shared/cpp/ObjectModel/DateTimePreparser.h"
#include "../../../shared/cpp/ObjectModel/TextBlock.h"
%}

%shared_ptr(AdaptiveCards::BaseActionElement)
%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::BaseInputElement)
%shared_ptr(AdaptiveCards::IActionElementParser)
%shared_ptr(AdaptiveCards::IBaseCardElementParser)
%shared_ptr(AdaptiveCards::ElementParserRegistration)
%shared_ptr(AdaptiveCards::ActionParserRegistration)
%shared_ptr(AdaptiveCards::Container)
%shared_ptr(AdaptiveCards::TextBlock)
%shared_ptr(AdaptiveCards::Image)
%shared_ptr(AdaptiveCards::ImageSet)
%shared_ptr(AdaptiveCards::Column)
%shared_ptr(AdaptiveCards::ColumnSet)
%shared_ptr(AdaptiveCards::Fact)
%shared_ptr(AdaptiveCards::FactSet)
%shared_ptr(AdaptiveCards::ChoiceInput)
%shared_ptr(AdaptiveCards::ChoiceSetInput)
%shared_ptr(AdaptiveCards::DateInput)
%shared_ptr(AdaptiveCards::NumberInput)
%shared_ptr(AdaptiveCards::TextInput)
%shared_ptr(AdaptiveCards::TimeInput)
%shared_ptr(AdaptiveCards::ToggleInput)
%shared_ptr(AdaptiveCards::OpenUrlAction)
%shared_ptr(AdaptiveCards::ShowCardAction)
%shared_ptr(AdaptiveCards::SubmitAction)
%shared_ptr(AdaptiveCards::AdaptiveCard)
%shared_ptr(AdaptiveCards::ContainerParser)
%shared_ptr(AdaptiveCards::TextBlockParser)
%shared_ptr(AdaptiveCards::ImageParser)
%shared_ptr(AdaptiveCards::ColumnSetParser)
%shared_ptr(AdaptiveCards::FactSetParser)
%shared_ptr(AdaptiveCards::ChoiceSetInputParser)
%shared_ptr(AdaptiveCards::NumberInputParser)
%shared_ptr(AdaptiveCards::TextInputParser)
%shared_ptr(AdaptiveCards::TimeInputParser)
%shared_ptr(AdaptiveCards::ToggleInputParser)
%shared_ptr(AdaptiveCards::OpenUrlActionParser)
%shared_ptr(AdaptiveCards::ShowCardActionParser)
%shared_ptr(AdaptiveCards::SubmitActionParser)
%shared_ptr(AdaptiveCards::ImageSetParser)
%shared_ptr(AdaptiveCards::DateInputParser)
%shared_ptr(AdaptiveCards::DateTimePreparsedToken)

// Allow C++ exceptions to be handled in Java
%typemap(throws, throws="java.io.IOException") AdaptiveCards::AdaptiveCardParseException {
  jclass excep = jenv->FindClass("java/io/IOException");
  if (excep)
    jenv->ThrowNew(excep, $1.what());
  return $null;
}

// Force the CustomException Java class to extend java.lang.Exception
%typemap(javabase) AdaptiveCards::AdaptiveCardParseException "java.lang.Exception";

// Override getMessage()
%typemap(javacode) AdaptiveCards::AdaptiveCardParseException %{
  public String getMessage() {
    return what();
  }
%}

%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >; 
%template(ImageVector) std::vector<std::shared_ptr<AdaptiveCards::Image> >; 
%template(FactVector) std::vector<std::shared_ptr<AdaptiveCards::Fact> >; 
%template(ColumnVector) std::vector<std::shared_ptr<AdaptiveCards::Column> >; 
%template(ChoiceInputVector) std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput> >; 
%template(BaseActionElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement> >; 
%template(DateTimePreparsedTokenVector) std::vector<std::shared_ptr<AdaptiveCards::DateTimePreparsedToken> >;

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

%exception AdaptiveCards::Image::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Image {
    static AdaptiveCards::Image *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Image *>(baseCardElement);
    }
};

%exception AdaptiveCards::ImageSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ImageSet {
    static AdaptiveCards::ImageSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ImageSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::Column::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Column {
    static AdaptiveCards::Column *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Column *>(baseCardElement);
    }
};

%exception AdaptiveCards::ColumnSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ColumnSet {
    static AdaptiveCards::ColumnSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ColumnSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::FactSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::FactSet {
    static AdaptiveCards::FactSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::FactSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::ChoiceInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ChoiceInput {
    static AdaptiveCards::ChoiceInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ChoiceInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::ChoiceSetInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ChoiceSetInput {
    static AdaptiveCards::ChoiceSetInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ChoiceSetInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::DateInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::DateInput {
    static AdaptiveCards::DateInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::DateInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::NumberInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::NumberInput {
    static AdaptiveCards::NumberInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::NumberInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::TextInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::TextInput {
    static AdaptiveCards::TextInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::TextInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::TimeInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::TimeInput {
    static AdaptiveCards::TimeInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::TimeInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::ToggleInput::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ToggleInput {
    static AdaptiveCards::ToggleInput *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ToggleInput *>(baseCardElement);
    }
};

%exception AdaptiveCards::OpenUrlAction::dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::OpenUrlAction {
    static AdaptiveCards::OpenUrlAction *dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
        return dynamic_cast<AdaptiveCards::OpenUrlAction *>(baseActionElement);
    }
};

%exception AdaptiveCards::ShowCardAction::dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ShowCardAction {
    static AdaptiveCards::ShowCardAction *dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
        return dynamic_cast<AdaptiveCards::ShowCardAction *>(baseActionElement);
    }
};

%exception AdaptiveCards::SubmitAction::dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::SubmitAction {
    static AdaptiveCards::SubmitAction *dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
        return dynamic_cast<AdaptiveCards::SubmitAction *>(baseActionElement);
    }
};

%include "../../../shared/cpp/ObjectModel/pch.h"
%include "../../../shared/cpp/ObjectModel/Enums.h"
%include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
%include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
%include "../../../shared/cpp/ObjectModel/BaseInputElement.h"
%include "../../../shared/cpp/ObjectModel/ActionParserRegistration.h"
%include "../../../shared/cpp/ObjectModel/ElementParserRegistration.h"
%include "../../../shared/cpp/ObjectModel/Container.h"
%include "../../../shared/cpp/ObjectModel/Image.h"
%include "../../../shared/cpp/ObjectModel/ImageSet.h"
%include "../../../shared/cpp/ObjectModel/Column.h"
%include "../../../shared/cpp/ObjectModel/ColumnSet.h"
%include "../../../shared/cpp/ObjectModel/Fact.h"
%include "../../../shared/cpp/ObjectModel/FactSet.h"
%include "../../../shared/cpp/ObjectModel/ChoiceInput.h"
%include "../../../shared/cpp/ObjectModel/ChoiceSetInput.h"
%include "../../../shared/cpp/ObjectModel/DateInput.h"
%include "../../../shared/cpp/ObjectModel/NumberInput.h"
%include "../../../shared/cpp/ObjectModel/TextInput.h"
%include "../../../shared/cpp/ObjectModel/TimeInput.h"
%include "../../../shared/cpp/ObjectModel/ToggleInput.h"
%include "../../../shared/cpp/ObjectModel/OpenUrlAction.h"
%include "../../../shared/cpp/ObjectModel/ShowCardAction.h"
%include "../../../shared/cpp/ObjectModel/SubmitAction.h"
%include "../../../shared/cpp/ObjectModel/SharedAdaptiveCard.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
%include "../../../shared/cpp/ObjectModel/HostConfig.h"
%include "../../../shared/cpp/ObjectModel/MarkDownParser.h"
%include "../../../shared/cpp/ObjectModel/DateTimePreparsedToken.h"
%include "../../../shared/cpp/ObjectModel/DateTimePreparser.h"
%include "../../../shared/cpp/ObjectModel/TextBlock.h"
