<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Authentication

**Introduced in version 1.4**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **text** | `string` | No | Text that can be displayed to the end user when prompting them to authenticate. | 1.4 |
| **connectionName** | `string` | No | The identifier for registered OAuth connection setting information. | 1.4 |
| **tokenExchangeResource** | `TokenExchangeResource` | No | Provides information required to enable on-behalf-of single sign-on user authentication. | 1.4 |
| **buttons** | `AuthCardButton[]` | No | Buttons that should be displayed to the user when prompting for authentication. The array MUST contain one button of type "signin". Other button types are not currently supported. | 1.4 |


## tokenExchangeResource

Provides information required to enable on-behalf-of single sign-on user authentication.

* **Type**: `TokenExchangeResource`
* **Required**: No
* **Allowed values**:
  * `TokenExchangeResource`


## buttons

Buttons that should be displayed to the user when prompting for authentication. The array MUST contain one button of type "signin". Other button types are not currently supported.

* **Type**: `AuthCardButton[]`
* **Required**: No
* **Allowed values**:
  * `AuthCardButton`
<!-- END AUTO-GENERATED -->

## Rendering