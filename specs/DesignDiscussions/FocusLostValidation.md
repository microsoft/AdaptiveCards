# Focus Lost Input Validation

In version 1.3 of the Adaptive Cards schema we introduced input validation in Adaptive Cards. For that initial version we validated inputs only when the user presses the submit button. In order to improve the user experience, and to allow more control to the hosts, this spec covers the introduction of additional options for validation.


## Table of Contents
- [Schema Changes](#schema-changes)
- [Behavior](#Behavior)
    - [First Validation](#First-validation)
        -  [onFocusLost](#onFocusLost)
        - [onFocusLostWithInput](#onFocusLostWithInput)
        - [onSubmit](#onSubmit)
    - [Subsequent Validations](#Subsequent-Validations)
- [Motivation](#Motivation)
    - [Research](#Research)
    - [WinUI Consistency](#WinUI-Consistency)
    - [Survey Data](#Survey-Data)

## Schema Changes

This feature does not introduce any changes to the Adaptive Cards schema, but does add properties to the Host Config schema. Specifically, the `validationBehavior` property is added to `InputsConfig` as described below:

```json
{
    "InputsConfig": {
        "properties": {
            "validationBehavior":{
                "type":"string",
                "description":"Controls when inputs are validated",
                "default":"onFocusLost",
                "enum":[
                    "onFocusLost",
                    "onFocusLostWithInput",
                    "onSubmit"
                ]
            }
        }
    }
},
```

These values allow hosts to determine the behavior of input validation as described below.

## Behavior

### First validation
The host config values above determine when the first validation of the property takes place.

#### onFocusLost
The input is validated when it loses focus for the first time. If a user tabs past a required input, or enters an invalid value in field, the error message will show once focus leaves that field.

#### onFocusLostWithInput
The input is validated when it loses focus only if the user has entered a value into the input field. If this value is set we will not validate for the `isRequired` property on focus lost unless the user has typed something and subsequently removed it. 

#### onSubmit
This is the behavior that shipped with the 1.3 schema update. The inputs are validated when the submit button is pressed. No validation takes place before submit is pressed.

### Subsequent Validations
Once the field has been validated for the first time based on the behavior specified by the host config, all host config settings have the same subsequent behavior. Once the field has been marked as invalid, from that point forward it will be validated on each keystroke. This allows users to correct their errors and see when they have successfully met the validation criteria. Validation will continue to be run on each keystroke even after the error has been corrected, in order to allow users to continue to see if their new value is correct.


## Motivation

There are several reasons to introduce earlier validation to Adaptive Cards. This section covers the data that supports this feature.

### Research
In issue [#3081](https://github.com/microsoft/AdaptiveCards/issues/3081) research was done on best practices for input validation. The following sources were found to support validating on focus lost as a best practice:

 - [A List Apart](https://alistapart.com/about/) study on [Inline Validation in Web Forms](https://alistapart.com/article/inline-validation-in-web-forms/):

    >When compared to our control version [validated input only when someone clicked its “create account” button], the inline validation form with the best performance showed compelling improvements across all the data we measured. Specifically, we saw:
    > - a 22% increase in success rates,
    > - a 22% decrease in errors made,
    > - a 31% increase in satisfaction rating,
    > - a 42% decrease in completion times, and
    > - a 47% decrease in the number of eye fixations.
    >
    > Participant comments highlighted their strong preference for getting real-time feedback from our form:
    >
    >“You’d rather know about your mistakes as you go along.”
    >
    >“It’s much better than getting all the way down and hitting ‘submit,’ only to find out that it doesn’t like your username. It’s much better when it tells you as you go along.”

- [Baymard Institute](https://baymard.com/about) Study on [Inline Form Validation](https://baymard.com/blog/inline-form-validation):

    >Our latest eye-tracking and usability testing shows that in order to perfect the user’s recovery experience, live inline validation must be used.
    >
    >Now, our checkout benchmarks reveal that live inline validation has seen an explosive growth in adoption: in 2012, just 13% of checkouts had live inline validation, whereas in 2016, 60% had implemented it. This makes good sense since the general importance of live inline validation is well documented. 

    They also list the following benefits that would apply to Adaptive Cards:
    > - Locating errors is easier.
    > - Field context is fresh in mind.
    > - Less likely to unintentionally skip required fields.

 - Prototypr.io UX Design 101: [UX best practices of Form Validation](https://blog.prototypr.io/ux-best-practices-of-form-validation-ddb8a0df14fd):
    
    >Users dislike when they go through the entire process of filling up the forms and have to wait for clicking the submit button to understand what went wrong.

 - [UX Planet](https://uxplanet.org/): Guidance on [Designing More Efficient Forms: Assistance and Validation](https://uxplanet.org/designing-more-efficient-forms-assistance-and-validation-f26a5241199d):
    >The right time to inform about the success/failure of provided data is right after the user has provided the information. And the solution for this is real-time inline validation because it immediately informs users about the correctness of provided data. This approach allows users to correct the errors they make faster without having to wait until they press the submit button to see the errors.

 - [The UX Blog](https://medium.theuxblog.com/about) Article: [Best Practices for Designing User Friendly Forms](https://medium.theuxblog.com/10-best-practices-for-designing-user-friendly-forms-fa0ba7c3e01f):
    >**Best practice 5. Validate errors as you go.**
    >The last thing you want is for your user to realise they’ve made an error just after they’ve finished filling out a form and must now go back and correct them. Instead, check and reveal their errors in real time. 

### WinUI Consistency
WinUI 3.0 introduces input validation for XAML. The behavior introduced there is that all inputs are validated when focus is lost for the first time. Subsequently inputs are validated on each key stroke. Introducing a similar behavior to Adaptive Cards will provide consistent behavior for users of XAML.

### Survey data
In February of 2020, a survey was sent to Adaptive Cards users who had expressed interest in Input Validation via our Product Board portal. The survey was also sent to out to our TAP audience. The question asked on this topic was:

**When do you expect validation errors to be shown to the user for a text input? (38 responses)**
|| |
|---|---|
| When the input loses focus (via tabbing through the form) | 37% |
| When the input loses focus, but only if the user has typed something in the text box | 32% |
| Only when the user hits the associated submit button | 24% |
| Other | 8% |

This data shows that a plurality of respondents prefer that the input is always validated on focus lost, and a majority expects validation before submit in some cases.

We also asked hosts how important it was for them to be able to control this behavior on a scale of 1 to 5.

**If you render Adaptive Cards authored by others in your own app, how important to you is the ability to control when validation takes place? (33 responses)**
||||||
|---|---|---|---|---|
|I'm fine with a reasonable default behavior <br><center> 1 | <br><br><center>2 | <br><br><center>3 | <br><br><center>4 |I must be able to configure this for consistency with other UI in my app <br><center> 5 |
|<center>21%|<center>6%|<center>24%|<center>15%|<center>33%|

The average response was 3.33. This ranks this feature higher than controlling required indicators (3.18) and slightly lower than controlling label styling (3.40).


