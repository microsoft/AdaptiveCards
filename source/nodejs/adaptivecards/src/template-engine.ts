// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AEL from "adaptive-expressions";
import { GlobalSettings, PropertyBag } from "./shared";

function internalTryEvaluateExpression(expression: AEL.Expression, context: EvaluationContext, allowSubstitutions: boolean): { value: any; error?: string } {
    let memory = new TemplateObjectMemory();
    memory.$root = context.$root;
    memory.$data = context.$data;
    memory.$index = context.$index;

    let options: AEL.Options | undefined = undefined;

    if (allowSubstitutions) {
        options = new AEL.Options();
        options.nullSubstitution = (path: string) => {
            let substitutionValue: string | undefined = undefined;

            if (GlobalSettings.getUndefinedFieldValueSubstitutionString) {
                substitutionValue = GlobalSettings.getUndefinedFieldValueSubstitutionString(path);    
            }
    
            return substitutionValue ? substitutionValue : "${" + path + "}";
        }
    }

    // The root of an expression coming from an interpolated string is of type Concat.
    // In that case, and if the caller allows it, we're doing our own concatenation
    // in order to catch each individual expression evaluation error and substitute in
    // the final string
    if (expression.type === AEL.ExpressionType.Concat && allowSubstitutions) {
        let result = "";

        for (let childExpression of expression.children) {
            let evaluationResult: { value: any; error: string };
            
            try {
                evaluationResult = childExpression.tryEvaluate(memory, options);
            }
            catch (ex) {
                // We'll swallow all exceptions here
                evaluationResult = {
                    value: undefined,
                    error: ex
                };
            }

            if (evaluationResult.error) {
                evaluationResult.value = "${" + childExpression.toString() + "}";
            }

            result += evaluationResult.value.toString();
        }

        return { value: result, error: undefined };
    }
    
    return expression.tryEvaluate(memory, options);
}

/**
 * Parses an interpolated string into an Expression object ready to evaluate.
 * 
 * @param interpolatedString The interpolated string to parse. Example: "Hello ${name}"
 * @returns An Expression object if the provided interpolated string contained at least one expression (e.g. "${expression}"); the original string otherwise.
 */
export function parseInterpolatedString(interpolatedString: string): AEL.Expression | string {
    let regExp = /\${([^{}}]+)}/g;
    let matches: RegExpExecArray | null = null;
    let lastMatch: RegExpExecArray | null = null;
    let matchCount = 0;

    // Determine if the string contains any ${<expression>}
    while (matchCount <= 1 && (matches = regExp.exec(interpolatedString)) != null) {
        lastMatch = matches;

        matchCount++;
    };

    let lookup: AEL.EvaluatorLookup = (type: string) => {
        let standardFunction = AEL.ExpressionFunctions.standardFunctions.get(type);

        if (standardFunction) {
            return standardFunction;
        }
        else {
            return new AEL.ExpressionEvaluator(
                type,
                (expression: AEL.Expression, state: AEL.MemoryInterface, options: AEL.Options) => { throw new Error("Unknown function " + type); },
                AEL.ReturnType.String);
        }
    }

    // If there are none, it's just a string
    if (matchCount === 0) {
        return interpolatedString;
    }
    // If the entire string is enclosed in a single ${}, extract the enclosed expression
    else if (matchCount === 1 && lastMatch && lastMatch[0].length === interpolatedString.length) {
        return AEL.Expression.parse(lastMatch[1], lookup);
    }

    // Otherwise, it's an interpolated string with multiple embedded expressions
    return AEL.Expression.parse("`" + interpolatedString + "`", lookup);
}

/**
 * Tries to evaluate the provided expression using the provided context.
 * 
 * @param expression The expression to evaluate.
 * @param context The context (data) used to evaluate the expression.
 * @param allowSubstitutions Indicates if the expression evaluator should substitute undefined value with a default
 *   string or the value returned by the GlobalSettings.getUndefinedFieldValueSubstitutionString callback.
 * @returns An object representing the result of the evaluation. If the evaluation succeeded, the value property
 *   contains the actual evaluation result, and the error property is undefined. If the evaluation fails, the error
 *   property contains a message detailing the error that occurred.
 */
export function tryEvaluateExpression(expression: AEL.Expression, context: IEvaluationContext, allowSubstitutions: boolean): { value: any; error?: string } {
    return internalTryEvaluateExpression(expression, new EvaluationContext(context), allowSubstitutions);
}

class EvaluationContext {
    private static readonly _reservedFields = ["$data", "$root", "$index"];

    private _stateStack: Array<{ $data: any, $index: any }> = [];
    private _$data: any;

    $root: any;
    $index: number;

    constructor(context?: IEvaluationContext) {
        if (context !== undefined) {
            this.$root = context.$root;
        }
    }

    isReservedField(name: string): boolean {
        return EvaluationContext._reservedFields.indexOf(name) >= 0;
    }

    saveState() {
        this._stateStack.push(
            {
                $data: this.$data,
                $index: this.$index
            });
    }

    restoreLastState() {
        if (this._stateStack.length === 0) {
            throw new Error("There is no evaluation context state to restore.");
        }

        let savedContext = this._stateStack.pop();

        if (savedContext) {
            this.$data = savedContext.$data;
            this.$index = savedContext.$index;
        }
    }

    get $data(): any {
        return this._$data !== undefined ? this._$data : this.$root;
    }

    set $data(value: any) {
        this._$data = value;
    }
}

class TemplateObjectMemory implements AEL.MemoryInterface {
    private _memory: AEL.MemoryInterface;

    $root: any;
    $data: any;
    $index: any;

    constructor() {
        this._memory = new AEL.SimpleObjectMemory(this);
    }

    getValue(path: string): any {
        let actualPath = (path.length > 0 && path[0] !== "$") ? "$data." + path : path;

        return this._memory.getValue(actualPath);
    }

    setValue(path: string, input: any) {
        this._memory.setValue(path, input);
    }

    version(): string {
        return this._memory.version();
    }
}

/**
 * Holds the context used to expand a template.
 */
export interface IEvaluationContext {
    /**
     * The root data object the template will bind to. Expressions that refer to $root in the template payload
     * map to this field. Initially, $data also maps to $root.
     */
    $root: any
}

/**
 * Represents a template that can be bound to data.
 */
export class Template {
    private static prepare(node: any): any {
        if (typeof node === "string") {
            return parseInterpolatedString(node);
        }
        else if (typeof node === "object" && node !== null) {
            if (Array.isArray(node)) {
                let result: any[] = [];

                for (let item of node) {
                    result.push(Template.prepare(item));
                }

                return result;
            }
            else {
                let keys = Object.keys(node);
                let result: PropertyBag = {};

                for (let key of keys) {
                    result[key] = Template.prepare(node[key]);
                }

                return result;
            }
        }
        else {
            return node;
        }
    }

    private _context: EvaluationContext;
    private _preparedPayload: any;

    private expandSingleObject(node: PropertyBag): any {
        let result: PropertyBag = {};
        let keys = Object.keys(node);

        for (let key of keys) {
            if (!this._context.isReservedField(key)) {
                let value = this.internalExpand(node[key]);

                if (value !== undefined) {
                    result[key] = value;
                }
            }
        }

        return result;
    }

    private internalExpand(node: any): any {
        let result: any;

        this._context.saveState();

        if (Array.isArray(node)) {
            let itemArray: any[] = [];

            for (let item of node) {
                let expandedItem = this.internalExpand(item);

                if (expandedItem !== null) {
                    if (Array.isArray(expandedItem)) {
                        itemArray = itemArray.concat(expandedItem);
                    }
                    else {
                        itemArray.push(expandedItem);
                    }
                }
            }

            result = itemArray;
        }
        else if (node instanceof AEL.Expression) {
            let evaluationResult = internalTryEvaluateExpression(node, this._context, true);

            if (!evaluationResult.error) {
                result = evaluationResult.value;
            }
            else {
                throw new Error(evaluationResult.error);
            }
        }
        else if (typeof node === "object" && node !== null) {
            let when = node["$when"];
            let dataContext = node["$data"];
            let dataContextIsArray: boolean = false;
            let dataContexts: any[];

            if (dataContext === undefined) {
                dataContexts = [ undefined ];
            }
            else {
                if (dataContext instanceof AEL.Expression) {
                    let evaluationResult = internalTryEvaluateExpression(dataContext, this._context, true);

                    if (!evaluationResult.error) {
                        dataContext = evaluationResult.value;
                    }
                    else {
                        throw new Error(evaluationResult.error);
                    }
                }

                if (Array.isArray(dataContext)) {
                    dataContexts = dataContext;
                    dataContextIsArray = true;
                }
                else {
                    dataContexts = [ dataContext ];
                }
            }

            result = [];

            for (let i = 0; i < dataContexts.length; i++) {
                if (dataContextIsArray) {
                    this._context.$index = i;
                }

                if (dataContexts[i] !== undefined) {
                    this._context.$data = dataContexts[i];
                }

                let dropObject = false;

                if (when instanceof AEL.Expression) {
                    let evaluationResult = internalTryEvaluateExpression(when, this._context, false);
                    let whenValue: boolean = false;
                    
                    // If $when fails to evaluate or evaluates to anything but a boolean, consider it is false
                    if (!evaluationResult.error) {
                        whenValue = typeof evaluationResult.value === "boolean" && evaluationResult.value;
                    }

                    dropObject = !whenValue;
                }

                if (!dropObject) {
                    let expandedObject = this.expandSingleObject(node);

                    if (expandedObject !== null) {
                        result.push(expandedObject);
                    }
                }
            }

            if (result.length === 0) {
                result = null;
            }
            else if (result.length === 1) {
                result = result[0];
            }
        }
        else {
            result = node;
        }

        this._context.restoreLastState();

        return result;
    }

    /**
     * Initializes a new Template instance based on the provided payload.
     * Once created, the instance can be bound to different data objects
     * in a loop.
     * 
     * @param payload The template payload.  
     */
    constructor(payload: any) {
        this._preparedPayload = Template.prepare(payload);
    }

    /**
     * Expands the template using the provided context. Template expansion involves
     * evaluating the expressions used in the original template payload, as well as
     * repeating (expanding) parts of that payload that are bound to arrays.
     * 
     * Example:
     * 
     * ```typescript
     * let context = {
     *     $root: {
     *         firstName: "John",
     *         lastName: "Doe",
     *         children: [
     *             { fullName: "Jane Doe", age: 9 },
     *             { fullName: "Alex Doe", age: 12 }
     *         ]
     *     }
     * }
     * 
     * let templatePayload = {
     *     type: "AdaptiveCard",
     *     version: "1.2",
     *     body: [
     *         {
     *             type: "TextBlock",
     *             text: "${firstName} ${lastName}"
     *         },
     *         {
     *             type: "TextBlock",
     *             $data: "${children}",
     *             text: "${fullName} (${age})"
     *         }
     *     ]
     * }
     * 
     * let template = new Template(templatePayload);
     * 
     * let expandedTemplate = template.expand(context);
     * ```
     * 
     * With the above code, the value of `expandedTemplate` will be
     * 
     * ```json
     * {
     *     type: "AdaptiveCard",
     *     version: "1.2",
     *     body: [
     *         {
     *             type: "TextBlock",
     *             text: "John Doe"
     *         },
     *         {
     *             type: "TextBlock",
     *             text: "Jane Doe (9)"
     *         },
     *         {
     *             type: "TextBlock",
     *             text: "Alex Doe (12)"
     *         }
     *     ]
     * }
     * ```
     * 
     * @param context The context to bind the template to.
     * @returns A value representing the expanded template. The type of that value
     *   is dependent on the type of the original template payload passed to the constructor.
     */
    expand(context: IEvaluationContext): any {
        this._context = new EvaluationContext(context);

        return this.internalExpand(this._preparedPayload);
    }
}