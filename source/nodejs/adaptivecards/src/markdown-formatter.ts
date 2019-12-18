// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
/**
 *  Markdown Formatter that supports bold, italic, hyperlinks, number lists and bullet lists.
 *  It also gives user an option to add their own pattern to format.
 */
export type FormatterPatternType = "list" | "symmetric" | "asymmetric";

export interface IFormatterStyleRule {
    start?: string;
    end?: string;
    html?: string;
}

export interface IFormatterRule {
    styles: IFormatterStyleRule;
    patterns: string[];
    patternType: FormatterPatternType;
    groups: number;
    regexp?: RegExp;
}

export interface IFormatterConfiguration {
    orderedList: IFormatterRule;
    unorderedList: IFormatterRule;
    bold: IFormatterRule;
    italic: IFormatterRule;
    hyperlink: IFormatterRule;
    [name: string]: IFormatterRule;
}

export abstract class TextFormatter {
    abstract formatText(text: string): string;
}

export class MarkdownFormatter extends TextFormatter {

    // To match all special characters
    private static SPECIAL_CHAR_REGEX = new RegExp("[^|a-z\\\\s\\d]", 'gi');

    private _configuration: IFormatterConfiguration;

    /**
     * Returns the default configuration for the Markdownformatter. 
     * Add or change on top this.
     */
    static getDefaultConfiguration(): IFormatterConfiguration {
        return {
            orderedList: {
                styles: {
                    start: "<ol>",
                    end: "</ol>"
                },
                patterns: ["\\d.", '\\r|\\n'],
                patternType: "list",
                groups: 1
            },
            unorderedList: {
                styles: {
                    start: "<ul>",
                    end: "</ul>"
                },
                patterns: ['-', '\\r|\\n'],
                patternType: 'list',
                groups: 1,
            },
            bold: {
                styles: {
                    start: "<b>",
                    end: "</b>"
                },
                patterns: ['**'],
                patternType: 'symmetric',
                groups: 1,
            },
            italic: {
                styles: {
                    start: "<i>",
                    end: "</i>"
                },
                patterns: ['_'],
                patternType: 'symmetric',
                groups: 1,
            },
            hyperlink: {
                styles: {
                    html: "<a href='{1}'>{0}</a>"
                },
                patterns: ['[]()'],
                patternType: 'asymmetric',
                groups: 2,
            }
        };
    }

    /**
     * @param configuration : optional custom configuration
     */
    constructor(configuration?: IFormatterConfiguration) {
        super();
        this._configuration = configuration ? configuration : MarkdownFormatter.getDefaultConfiguration();

        for (let type in this._configuration) {
            this.initailize(this._configuration[type]);
        }
    }

    /**
     * To add '\' before all the special characters in the regex. In a regex to match a special charater you need to add \ before it.
     * Example: ** will become \*\*
     * 
     * @param pattern 
     */
    private encodeSpecialCharacters(pattern: string): string {
        return pattern.replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&");
    }

    /**
     * To initialize the regexp for the rule passed.
     * 
     * @param configuration 
     */
    private initailize(configuration: IFormatterRule): void {
        let patternArray = configuration.patterns,
            patternType = configuration.patternType,
            pattern = patternArray[0],
            groups = configuration.groups,
            pattern_0 = this.encodeSpecialCharacters(patternArray[0]),
            pattern_1 = patternArray[1] ? this.encodeSpecialCharacters(patternArray[1]) : "";

        if (patternType === "list") {
            pattern = pattern_0 + '[\\s]+((.*?)[' + pattern_1 + "](?=" + pattern_1 + "[\\s]+)|(.*?)$)";
        }
        else if (patternType === "symmetric") {
            pattern = pattern_0 + '(.*?)' + pattern_0;
        }
        else if (patternType === "asymmetric") {
            let regexForm = pattern_0;
            let part = regexForm.length / groups;
            let regex = "";

            for (let j = 0; j < groups; j++) {
                let group = regexForm.substring(part * j, part * (j + 1)),
                    firstHalf = group.substring(0, group.length / 2),
                    secondHalf = group.substring(group.length / 2, group.length),
                    middle = (j < groups / 2) ? group.substring(0, group.length / 2) : group.substring(group.length / 2, group.length);

                regex = regex + firstHalf + '([^' + middle + ']+)' + secondHalf;
            }
            pattern = regex;
        }
        configuration.regexp = new RegExp(pattern, 'gim');
    }

    /**
     * The main function that formats the text based on the rules initalized.
     * 
     * @param text : text to parse 
     */
    formatText(text: string): string {
        for (let type in this._configuration) {
            this.initailize(this._configuration[type]);
            let first = true;
            let parsed,
                pattern = this._configuration[type].regexp,
                patternType = this._configuration[type].patternType,
                styles = this._configuration[type].styles;

            while (pattern && (parsed = pattern.exec(text)) !== null) {
                if (parsed[1] === undefined) {
                    continue;
                }

                //For lists.
                if (patternType === "list" && styles.start && styles.end) {
                    //If it is the first element of the list then add the list start tag(<ol> / <ul>) 
                    if (first) {
                        text = text.replace(parsed[0], styles.start + "<li>" + parsed[1] + "</li>" + styles.end);
                        first = false;
                    }
                    else {
                        //Remove the end tag and add the list item.
                        let indexOL = text.lastIndexOf(styles.end);
                        text = text.replace(text.substring(indexOL, indexOL + styles.end.length), "");
                        text = text.replace(parsed[0], "<li>" + parsed[1] + "</li>" + styles.end);
                    }
                }
                //for bold, italic.
                else if (patternType === "symmetric") {
                    text = text.replace(parsed[0], styles.start + parsed[1] + styles.end);
                }
                //for hyperlinks.
                else if (patternType === "asymmetric" && styles.html) {
                    styles.html = styles.html.replace("{0}", parsed[1]);
                    styles.html = styles.html.replace("{1}", parsed[2]);
                    text = text.replace(parsed[0], styles.html);
                }
            }
        }
        return text;
    }
}