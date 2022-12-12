# Shared Model Feature Implementation

In order to add a new element or a new property for a element for the UWP, iOS or Android renderers you will need to modify the shared model first. You can work on the Shared Model changes by using the following Visual Studio solutions:
* `source\shared\cpp\AdaptiveCardsSharedModel\AdaptiveCardsSharedModel.sln`
* `source\uwp\AdaptiveCards.sln`

For the following example we will implement a simple star rating element as defined in the sample feature proposal you can find [here](TODO_Add_a_sample_feature_proposal):

## Adding a new element

The steps to add a new element are:

1. Create the header and cpp files for your element under `source\shared\cpp\ObjectModel`. In this example you would create 2 new files `Tutorial_StarRatingInput.h` and `Tutorial_StarRatingInput.cpp`. As we are creating a new input element we are adding the suffix Input to keep consistency with other elements

2. The object model is in charge of parsing, storing the logical structure as defined in the json and serializing the structure again if requested, as such, every element is comprised of at least two classes, a class named the same as your element (`Tutorial_StarRatingInput`) which stores the properties defined in the json schema for the element and a parser class (`Tutorial_StarRatingInputParser`) which as its name suggests parses the json to transform it into the aforementioned class.

The basic skeleton for our `Tutorial_StarRatingInput` shared model class would look like this:

```c++
namespace AdaptiveCards
{
class Tutorial_StarRatingInput : public BaseInputElement
{
    friend class Tutorial_StarRatingInputParser;

public:
    Tutorial_StarRatingInput();
    Tutorial_StarRatingInput(const Tutorial_StarRatingInput&) = default;
    Tutorial_StarRatingInput(Tutorial_StarRatingInput&&) = default;
    Tutorial_StarRatingInput operator=(const Tutorial_StarRatingInput&) = default;
    Tutorial_StarRatingInput& operator=(Tutorial_StarRatingInput&&) = default;
    ~Tutorial_StarRatingInput() = default;

    Json::Value SerializeToJsonValue() const override;

private:
    void PopulateKnownPropertiesSet();
};
} // namespace AdaptiveCards

```

As our class is an input, it can inherit from the `BaseInputElement` class. The `BaseInputElement` contains properties that are part of every input element, for example, label, errorMessage and isRequired. The `BaseInputElement`inherits itself from the `BaseCardElement` which in turn already defines properties such as id, spacing and separator which are part of all card elements.

The skeleton for our `Tutorial_StarRatingInput` class looks like this:

``` c++
namespace AdaptiveCards
{
class Tutorial_StarRatingInputParser : public BaseCardElementParser
{
public:
    Tutorial_StarRatingInputParser() = default;
    Tutorial_StarRatingInputParser(const Tutorial_StarRatingInputParser&) = default;
    Tutorial_StarRatingInputParser(Tutorial_StarRatingInputParser&&) = default;
    Tutorial_StarRatingInputParser& operator=(const Tutorial_StarRatingInputParser&) = default;
    Tutorial_StarRatingInputParser& operator=(Tutorial_StarRatingInputParser&&) = default;
    virtual ~Tutorial_StarRatingInputParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
```

This class inherits from the BaseCardElementParser class which declares two virtual deserializing methods to be implemented by you:
* `std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value); `
* `std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value); `

3. The next step is adding all public properties for your element as defined in the schema. This are the properties that will have to be serialized and deserialized from the json. In this step let's also implement the class constructor to initialize all properties and the `PopulateKnownPropertiesSet` method.

#### Tutorial_StarRatingInput.h

```c++
class Tutorial_StarRatingInput : public BaseInputElement
{
public:
    bool GetHas5StarLimit() const;
    void SetHas5StarLimit(bool value);

private:
    bool m_has5StarLimit;
};
```

#### Tutorial_StarRatingInput.cpp

```c++
Tutorial_StarRatingInput::Tutorial_StarRatingInput() :
    BaseInputElement(CardElementType::StarRatingInput), m_has5StarLimit(true)
{
    PopulateKnownPropertiesSet();
}

bool Tutorial_StarRatingInput::GetHas5StarLimit() const
{
    return m_has5StarLimit;
}

void Tutorial_StarRatingInput::SetHas5StarLimit(bool value)
{
    m_has5StarLimit = value;
}

void Tutorial_StarRatingInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert(
        {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Has5StarLimit)});
}
```

4. Once we know what information needs to be stored in the shared model we can implement the shared model serializing and deserializing. The serializing is performed in the `SerializeToJsonValue` method, as the `StarRatingInput` element is an input we can use the `BaseInputElement::SerializeToJsonValue` to serialize common input properties. For performing deserialization you will have to implement the `Deserialize` method defined in the parser class from step 2. To ease the parsing of common properties you can use the `BaseInputElement::Deserialize` method to parse them. The `ParseUtil` class also defines helper methods to parse native types such as integers, booleans or strings.  

```c++
#include "ParseUtil.h"
#include "Util.h"

Json::Value Tutorial_StarRatingInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Has5StarLimit)] = m_has5StarLimit;
    
    return root;
}

std::shared_ptr<BaseCardElement> Tutorial_StarRatingInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::StarRatingInput);

    std::shared_ptr<Tutorial_StarRatingInput> starRatingInput = BaseInputElement::Deserialize<Tutorial_StarRatingInput>(context, json);
    starRatingInput->SetHas5StarLimit(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Has5StarLimit, true));

    return starRatingInput;
}

std::shared_ptr<BaseCardElement> Tutorial_StarRatingInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return Tutorial_StarRatingInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
```

As of this moment only the logical structure of the element has been defined, the next step to be performed will be registering the element in the internal dictionaries which will be described in the next section.

### Registering the new element

In order to register the new element:
1. add the element name to the CardElementType enum located in the `shared\cpp\ObjectModel\Enums.h` file. The enumeration is sorted alphabetically.
2. add the element name to the AdaptiveCardSchemaKey enum located in the `shared\cpp\ObjectModel\Enums.h` file. The enumeration is sorted alphabetically.
3. add all new property names to the AdaptiveCardSchemaKey enum located in the `shared\cpp\ObjectModel\Enums.h` file. The enumeration is sorted alphabetically.
4. add an entry for every new property and element name to the `DEFINE_ADAPTIVECARD_ENUM(AdaptiveCardSchemaKey, {...})` macro in the `shared\cpp\ObjectModel\Enums.cpp` file. The string value to be added is the same as the enum value starting with a lower case letter. The enumeration is sorted alphabetically.
5. add an entry for every new element name to the `DEFINE_ADAPTIVECARD_ENUM(CardElementType, {...})` macro in the `shared\cpp\ObjectModel\Enums.cpp` file. The string value to be added is the same as the element will appear in the json, in the case of inputs they have to be prefixed with `Input.`. The enumeration is sorted alphabetically.
6. add an entry for the element in the `m_knownElements` and the `m_cardElementParsers` maps under the `ElementParserRegistration` constructor in the `shared\cpp\ObjectModel\ElementParserRegistration.cpp` file. 

## Adding a new native type property

To add a new property into an already existing element you need to:

1. Locate the element or object to modify, to exemplify we will use the `TextBlock` element 
2. Add the private properties in the class and declare the public getter and setters

```c++
class TextBlock : public BaseCardElement
{
public:
    const std::string GetSampleProperty() const;
    void SetSampleProperty(const std::string& value);

private:
    std::string m_sampleProperty;
};
```

3. If needed, initialize the value in the class constructor
4. Add the property to the list of know properties in the `PopulateKnownPropertiesSet` method.
5. Update the `SerializeToJsonValue` and `Deserialize` methods 

```c++
Json::Value TextBlock::SerializeToJsonValue() const
{
    ... 
    if (!m_sampleProperty.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SampleProperty)] = m_sampleProperty;
    }
    ...
}

std::shared_ptr<BaseCardElement> TextBlockParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ...
    textBlock->SetSampleProperty(ParseUtil::GetString(json, AdaptiveCardSchemaKey::SampleProperty, false));
    ...
}
```

6. Add an entry to the `DEFINE_ADAPTIVECARD_ENUM(AdaptiveCardSchemaKey)` macro in the `shared\cpp\ObjectModel\Enums.cpp` file for each property added.   

## Adding an enum type property

Adding a new enumeration property is the same as adding a new native type property, please follow the same steps as outlined in that process but add the following steps:

1. Add the enumeration in the `shared\cpp\ObjectModel\Enums.h` file. Do not forget to add the `DECLARE_ADAPTIVECARD_ENUM` macro call as it implements the `EnumToString` and `EnumFromString` methods.

```c++
enum class SampleEnumProperty
{
    SampleEnumValue1 = 0,
    SampleEnumValue2,
};
DECLARE_ADAPTIVECARD_ENUM(SampleEnumProperty);
```

2. Add the mapping between the enum value and the json string value.

```c++
DEFINE_ADAPTIVECARD_ENUM(TextInputStyle, {
    {SampleEnumProperty::SampleEnumValue1, "SampleEnumValue1"},
    {SampleEnumProperty::SampleEnumValue2, "SampleEnumValue2"}});
```

3. Update the Deserialize and DeserializeToJson methods of the shared object model of the element to modify like this:

```c++
Json::Value SerializeToJsonValue() const
{
    ...
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SampleEnumProperty)] = SampleEnumPropertyToString(m_sampleEnumProperty);
    ...
}

std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& json)
{
    ...
    const auto sampleEnumProperty =
        ParseUtil::GetEnumValue<SampleEnumProperty>(json, AdaptiveCardSchemaKey::SampleEnumProperty, SampleEnumProperty::SampleEnumValue1, SampleEnumPropertyFromString);
    myElement->SetSampleEnumProperty(sampleEnumProperty);
    ...
}
```

## Adding a new object property

The process to create a property is very similar to creating a new element as you have to manually add serializing and deserializing methods for it. An example of an object property is the `BackgroundImage` property in the `StyledCollectionElement` class. To add an object property to an element:

1. Create your object property class, i.e. `SampleObjectProperty`.
2. Add the `Deserialize`, `DeserializeFromString`, `Serialize` and `SerializeToJsonValue` methods to the class you just added.

```c++
class BackgroundImage
{
public:
    std::string Serialize() const;
    Json::Value SerializeToJsonValue() const;

    static std::shared_ptr<BackgroundImage> Deserialize(const Json::Value& json);
    static std::shared_ptr<BackgroundImage> DeserializeFromString(const std::string& jsonString);
```

3. Add the private property and the public getter and setters to the element class. Please remember to return a `shared_ptr<>`.

```c++
class SampleElement
{
public:
    std::shared_ptr<SampleObjectProperty> GetSampleObjectProperty() const;
    void SetSampleObjectProperty(const std::shared_ptr<SampleObjectProperty> value);

private:
    std::shared_ptr<SampleObjectProperty> m_backgroundImage;
};
```

4. Add the class and the properties to the enum maps as described in the [Registering the new element](#Registering-the-new-element) section, except for step 6.