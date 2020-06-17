/* Copyright (c) Microsoft Corporation. All rights reserved. */
/* Licensed under the MIT License. */
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


%module(directors="1") AdaptiveCardObjectModel;

%rename (CTime) tm;
struct tm {
    %rename (Sec) tm_sec;
    %rename (Min) tm_min;
    %rename (Hour) tm_hour;
    %rename (MDay) tm_mday;
    %rename (Mon) tm_mon;
    %rename (Year) tm_year;
    %rename (WDay) tm_wday;
    %rename (YDay) tm_yday;
    %rename (IsDst) tm_isdst;
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

%include <typemaps.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_vector.i>
%include <std_wstring.i>
%include "enums.swg"
%javaconst(1);

%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("adaptivecards-native-lib");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}

#define __ANDROID__ 1

%{
#include "pch.h"
#include <memory>
#include <time.h>
#include "../../../shared/cpp/ObjectModel/EnumMagic.h"
#include "../../../shared/cpp/ObjectModel/Enums.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveBase64Util.h"
#include "../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"
#include "../../../shared/cpp/ObjectModel/BaseElement.h"
#include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
#include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
#include "../../../shared/cpp/ObjectModel/BaseInputElement.h"
#include "../../../shared/cpp/ObjectModel/CollectionTypeElement.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCardParseWarning.h"
#include "../../../shared/cpp/ObjectModel/ActionParserRegistration.h"
#include "../../../shared/cpp/ObjectModel/ElementParserRegistration.h"
#include "../../../shared/cpp/ObjectModel/FeatureRegistration.h"
#include "../../../shared/cpp/ObjectModel/BackgroundImage.h"
#include "../../../shared/cpp/ObjectModel/Container.h"
#include "../../../shared/cpp/ObjectModel/Image.h"
#include "../../../shared/cpp/ObjectModel/ImageSet.h"
#include "../../../shared/cpp/ObjectModel/Column.h"
#include "../../../shared/cpp/ObjectModel/ColumnSet.h"
#include "../../../shared/cpp/ObjectModel/ChoiceInput.h"
#include "../../../shared/cpp/ObjectModel/ChoiceSetInput.h"
#include "../../../shared/cpp/ObjectModel/DateInput.h"
#include "../../../shared/cpp/ObjectModel/NumberInput.h"
#include "../../../shared/cpp/ObjectModel/TextInput.h"
#include "../../../shared/cpp/ObjectModel/TimeInput.h"
#include "../../../shared/cpp/ObjectModel/ToggleInput.h"
#include "../../../shared/cpp/ObjectModel/OpenUrlAction.h"
#include "../../../shared/cpp/ObjectModel/SemanticVersion.h"
#include "../../../shared/cpp/ObjectModel/ShowCardAction.h"
#include "../../../shared/cpp/ObjectModel/SubmitAction.h"
#include "../../../shared/cpp/ObjectModel/ParseContext.h"
#include "../../../shared/cpp/ObjectModel/ParseResult.h"
#include "../../../shared/cpp/ObjectModel/SharedAdaptiveCard.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
#include "../../../shared/cpp/ObjectModel/HostConfig.h"
#include "../../../shared/cpp/ObjectModel/MarkDownParser.h"
#include "../../../shared/cpp/ObjectModel/DateTimePreparsedToken.h"
#include "../../../shared/cpp/ObjectModel/DateTimePreparser.h"
#include "../../../shared/cpp/ObjectModel/Fact.h"
#include "../../../shared/cpp/ObjectModel/FactSet.h"
#include "../../../shared/cpp/ObjectModel/TextBlock.h"
#include "../../../shared/cpp/ObjectModel/ActionSet.h"
#include "../../../shared/cpp/ObjectModel/MediaSource.h"
#include "../../../shared/cpp/ObjectModel/Media.h"
#include "../../../shared/cpp/ObjectModel/ToggleVisibilityAction.h"
#include "../../../shared/cpp/ObjectModel/ToggleVisibilityTarget.h"
#include "../../../shared/cpp/ObjectModel/UnknownElement.h"
#include "../../../shared/cpp/ObjectModel/UnknownAction.h"
#include "../../../shared/cpp/ObjectModel/TextElementProperties.h"
#include "../../../shared/cpp/ObjectModel/Inline.h"
#include "../../../shared/cpp/ObjectModel/RichTextBlock.h"
#include "../../../shared/cpp/ObjectModel/TextRun.h"
#include "../../../shared/cpp/ObjectModel/RichTextElementProperties.h"
%}

%shared_ptr(AdaptiveCards::BaseElement)
%shared_ptr(AdaptiveCards::BaseActionElement)
%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::BaseInputElement)
%shared_ptr(AdaptiveCards::ActionElementParser)
%shared_ptr(AdaptiveCards::BaseCardElementParser)
%shared_ptr(AdaptiveCards::ActionElementParserWrapper)
%shared_ptr(AdaptiveCards::BaseCardElementParserWrapper)
%shared_ptr(AdaptiveCards::CollectionTypeElement)
%shared_ptr(AdaptiveCards::ElementParserRegistration)
%shared_ptr(AdaptiveCards::ActionParserRegistration)
%shared_ptr(AdaptiveCards::FeatureRegistration)
%shared_ptr(AdaptiveCards::BackgroundImage)
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
%shared_ptr(AdaptiveCards::AdaptiveCardParseWarning)
%shared_ptr(AdaptiveCards::ParseContext)
%shared_ptr(AdaptiveCards::ParseResult)
%shared_ptr(AdaptiveCards::RemoteResourceInformation)
%shared_ptr(AdaptiveCards::AdaptiveCard)
%shared_ptr(AdaptiveCards::ContainerParser)
%shared_ptr(AdaptiveCards::TextBlockParser)
%shared_ptr(AdaptiveCards::ImageParser)
%shared_ptr(AdaptiveCards::ColumnParser)
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
%shared_ptr(AdaptiveCards::MediaSource)
%shared_ptr(AdaptiveCards::Media)
%shared_ptr(AdaptiveCards::MediaParser)
%shared_ptr(AdaptiveCards::ToggleVisibilityTarget)
%shared_ptr(AdaptiveCards::ToggleVisibilityAction)
%shared_ptr(AdaptiveCards::ToggleVisibilityActionParser)
%shared_ptr(AdaptiveCards::ActionSet)
%shared_ptr(AdaptiveCards::ActionSetParser)
%shared_ptr(AdaptiveCards::UnknownElement)
%shared_ptr(AdaptiveCards::UnknownElementParser)
%shared_ptr(AdaptiveCards::UnknownAction)
%shared_ptr(AdaptiveCards::UnknownActionParser)
%shared_ptr(AdaptiveCards::Inline)
%shared_ptr(AdaptiveCards::RichTextBlock)
%shared_ptr(AdaptiveCards::RichTextBlockParser)
%shared_ptr(AdaptiveCards::TextRun)
%shared_ptr(AdaptiveCards::TextElementProperties)
%shared_ptr(AdaptiveCards::RichTextElementProperties)

%apply unsigned int& INOUT { unsigned int& };

namespace Json {
    %rename(JsonValue) Value;
    class Value { };

    %extend Value {
        std::string getString() {
            Json::StreamWriterBuilder builder;
            builder["commentStyle"] = "None";
            builder["indentation"] = "";
            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

            std::ostringstream outStream;
            writer->write(*self, &outStream);
            outStream << std::endl;
            return outStream.str();
        }
    }
}

%feature("director", assumeoverride=1) AdaptiveCards::BaseCardElementParser;
%feature("director", assumeoverride=1) AdaptiveCards::ActionElementParser;

%feature("director", assumeoverride=1) AdaptiveCards::BaseElement;

%typemap(in,numinputs=0) JNIEnv *jenv "$1 = jenv;"
%extend AdaptiveCards::BaseCardElement {
    // return the underlying Java object if this is a Director, or null otherwise
    jobject swigOriginalObject(JNIEnv *jenv) {
        Swig::Director *dir = dynamic_cast<Swig::Director*>($self);
        if (dir) {
            return dir->swig_get_self(jenv);
        }
        return NULL;
    }
}

%typemap(javacode) AdaptiveCards::BaseCardElement %{
  // check if the C++ code finds an object and just return ourselves if it doesn't
  public BaseCardElement findImplObj() {
     Object o = swigOriginalObject();
     return o != null ? ($javaclassname)o : this;
  }
%}

%feature("director") AdaptiveCards::BaseCardElement;

%typemap(in,numinputs=0) JNIEnv *jenv "$1 = jenv;"
%extend AdaptiveCards::BaseActionElement {
    // return the underlying Java object if this is a Director, or null otherwise
    jobject swigOriginalObject(JNIEnv *jenv) {
        Swig::Director *dir = dynamic_cast<Swig::Director*>($self);
        if (dir) {
            return dir->swig_get_self(jenv);
        }
        return NULL;
    }
}

%typemap(javacode) AdaptiveCards::BaseActionElement %{
  // check if the C++ code finds an object and just return ourselves if it doesn't
  public BaseActionElement findImplObj() {
     Object o = swigOriginalObject();
     return o != null ? ($javaclassname)o : this;
  }
%}

%feature("director") AdaptiveCards::BaseActionElement;


%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::ActionParserRegistration> "new $typemap(jstype, AdaptiveCards::ActionParserRegistration)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/ActionParserRegistration;") std::shared_ptr<AdaptiveCards::ActionParserRegistration> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::ActionParserRegistration> "$typemap(jstype, AdaptiveCards::ActionParserRegistration).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::ActionParserRegistration> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::BaseCardElement> "new $typemap(jstype, AdaptiveCards::BaseCardElement)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/BaseCardElement;") std::shared_ptr<AdaptiveCards::BaseCardElement> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::BaseCardElement> "$typemap(jstype, AdaptiveCards::BaseCardElement).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::BaseCardElement> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::BaseInputElement> "new $typemap(jstype, AdaptiveCards::BaseInputElement)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/BaseInputElement;") std::shared_ptr<AdaptiveCards::BaseInputElement> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::BaseInputElement> "$typemap(jstype, AdaptiveCards::BaseInputElement).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::BaseInputElement> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}


%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::BaseActionElement> "new $typemap(jstype, AdaptiveCards::BaseActionElement)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/BaseActionElement;") std::shared_ptr<AdaptiveCards::BaseActionElement> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::BaseActionElement> "$typemap(jstype, AdaptiveCards::BaseActionElement).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::BaseActionElement> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::ActionParserRegistration> "new $typemap(jstype, AdaptiveCards::ActionParserRegistration)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/ActionParserRegistration;") std::shared_ptr<AdaptiveCards::ActionParserRegistration> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::ActionParserRegistration> "$typemap(jstype, AdaptiveCards::ActionParserRegistration).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::ActionParserRegistration> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::ElementParserRegistration> "new $typemap(jstype, AdaptiveCards::ElementParserRegistration)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/ElementParserRegistration;") std::shared_ptr<AdaptiveCards::ElementParserRegistration> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::ElementParserRegistration> "$typemap(jstype, AdaptiveCards::ElementParserRegistration).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::ElementParserRegistration> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

%typemap(javadirectorin) std::shared_ptr<AdaptiveCards::FeatureRegistration> "new $typemap(jstype, AdaptiveCards::FeatureRegistration)($1,true)";
%typemap(directorin,descriptor="Lio/adaptivecards/objectmodel/FeatureRegistration;") std::shared_ptr<AdaptiveCards::FeatureRegistration> %{
  *($&1_type*)&j$1 = new $1_type($1);
%}

%typemap(javadirectorout) std::shared_ptr<AdaptiveCards::FeatureRegistration> "$typemap(jstype, AdaptiveCards::FeatureRegistration).getCPtr($javacall)";
%typemap(directorout) std::shared_ptr<AdaptiveCards::FeatureRegistration> %{
  $&1_type tmp = NULL;
  *($&1_type*)&tmp = *($&1_type*)&$input;
  if (!tmp) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null $1_type");
    return NULL;
  }
  $result = *tmp;
%}

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

%template(RemoteResourceInformationVector) std::vector<AdaptiveCards::RemoteResourceInformation>;
%template(AdaptiveCardParseWarningVector) std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning> >;
%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >;
%template(ImageVector) std::vector<std::shared_ptr<AdaptiveCards::Image> >;
%template(FactVector) std::vector<std::shared_ptr<AdaptiveCards::Fact> >;
%template(ColumnVector) std::vector<std::shared_ptr<AdaptiveCards::Column> >;
%template(ChoiceInputVector) std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput> >;
%template(MediaSourceVector) std::vector<std::shared_ptr<AdaptiveCards::MediaSource> >;
%template(BaseActionElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement> >;
%template(DateTimePreparsedTokenVector) std::vector<std::shared_ptr<AdaptiveCards::DateTimePreparsedToken> >;
%template(ToggleVisibilityTargetVector) std::vector<std::shared_ptr<AdaptiveCards::ToggleVisibilityTarget> >;
%template(StringVector) std::vector<std::string>;
%template(CharVector) std::vector<char>;
%template(InlineVector) std::vector<std::shared_ptr<AdaptiveCards::Inline>>;

%template(EnableSharedFromThisContainer) std::enable_shared_from_this<AdaptiveCards::Container>;

%exception AdaptiveCards::BaseCardElement::dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::BaseCardElement {
    static AdaptiveCards::BaseCardElement *dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
        return dynamic_cast<AdaptiveCards::BaseCardElement *>(baseElement);
    }
};

%exception AdaptiveCards::BaseInputElement::dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::BaseInputElement {
    static AdaptiveCards::BaseInputElement *dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
        return dynamic_cast<AdaptiveCards::BaseInputElement *>(baseElement);
    }
};

%exception AdaptiveCards::BaseActionElement::dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::BaseActionElement {
    static AdaptiveCards::BaseActionElement *dynamic_cast(AdaptiveCards::BaseElement *baseElement) {
        return dynamic_cast<AdaptiveCards::BaseActionElement *>(baseElement);
    }
};

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

%exception AdaptiveCards::Media::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Media {
    static AdaptiveCards::Media *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Media *>(baseCardElement);
    }
};

%exception AdaptiveCards::ToggleVisibilityAction::dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ToggleVisibilityAction {
    static AdaptiveCards::ToggleVisibilityAction *dynamic_cast(AdaptiveCards::BaseActionElement *baseActionElement) {
        return dynamic_cast<AdaptiveCards::ToggleVisibilityAction *>(baseActionElement);
    }
};

%exception AdaptiveCards::ActionSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ActionSet {
    static AdaptiveCards::ActionSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ActionSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::RichTextBlock::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::RichTextBlock {
    static AdaptiveCards::RichTextBlock *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::RichTextBlock *>(baseCardElement);
    }
};

%exception AdaptiveCards::TextRun::dynamic_cast(AdaptiveCards::Inline *inlineVar) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::TextRun {
    static AdaptiveCards::TextRun *dynamic_cast(AdaptiveCards::Inline *inlineVar) {
        return dynamic_cast<AdaptiveCards::TextRun *>(inlineVar);
    }
};

%include "../../../shared/cpp/ObjectModel/pch.h"
%include "../../../shared/cpp/ObjectModel/EnumMagic.h"
%include "../../../shared/cpp/ObjectModel/Enums.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveBase64Util.h"
%include "../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"
%include "../../../shared/cpp/ObjectModel/BaseElement.h"
%include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
%include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
%include "../../../shared/cpp/ObjectModel/BaseInputElement.h"
%include "../../../shared/cpp/ObjectModel/BackgroundImage.h"
%include "../../../shared/cpp/ObjectModel/CollectionTypeElement.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCardParseWarning.h"
%include "../../../shared/cpp/ObjectModel/ActionParserRegistration.h"
%include "../../../shared/cpp/ObjectModel/ElementParserRegistration.h"
%include "../../../shared/cpp/ObjectModel/FeatureRegistration.h"
%include "../../../shared/cpp/ObjectModel/SemanticVersion.h"
%include "../../../shared/cpp/ObjectModel/Container.h"
%include "../../../shared/cpp/ObjectModel/Image.h"
%include "../../../shared/cpp/ObjectModel/ImageSet.h"
%include "../../../shared/cpp/ObjectModel/Column.h"
%include "../../../shared/cpp/ObjectModel/ColumnSet.h"
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
%include "../../../shared/cpp/ObjectModel/ParseContext.h"
%include "../../../shared/cpp/ObjectModel/ParseResult.h"
%include "../../../shared/cpp/ObjectModel/SharedAdaptiveCard.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
%include "../../../shared/cpp/ObjectModel/HostConfig.h"
%include "../../../shared/cpp/ObjectModel/MarkDownParser.h"
%include "../../../shared/cpp/ObjectModel/DateTimePreparsedToken.h"
%include "../../../shared/cpp/ObjectModel/DateTimePreparser.h"
%include "../../../shared/cpp/ObjectModel/Fact.h"
%include "../../../shared/cpp/ObjectModel/FactSet.h"
%include "../../../shared/cpp/ObjectModel/TextBlock.h"
%include "../../../shared/cpp/ObjectModel/MediaSource.h"
%include "../../../shared/cpp/ObjectModel/Media.h"
%include "../../../shared/cpp/ObjectModel/ToggleVisibilityTarget.h"
%include "../../../shared/cpp/ObjectModel/ToggleVisibilityAction.h"
%include "../../../shared/cpp/ObjectModel/ActionSet.h"
%include "../../../shared/cpp/ObjectModel/UnknownElement.h"
%include "../../../shared/cpp/ObjectModel/UnknownAction.h"
%include "../../../shared/cpp/ObjectModel/TextElementProperties.h"
%include "../../../shared/cpp/ObjectModel/Inline.h"
%include "../../../shared/cpp/ObjectModel/RichTextBlock.h"
%include "../../../shared/cpp/ObjectModel/TextRun.h"
%include "../../../shared/cpp/ObjectModel/RichTextElementProperties.h"
