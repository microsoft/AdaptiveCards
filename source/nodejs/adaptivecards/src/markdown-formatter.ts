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

export interface IFormatterConfiguration {
    type: string
    styles: IFormatterStyleRule;
    patterns: string[];
    patternType: FormatterPatternType;
    groups: number;
    regexp?: RegExp;
}

export abstract class TextFormatter {
    abstract formatText(text: string): string;
}

export class MarkdownFormatter extends TextFormatter {

    // To match all special characters
    private static SPECIAL_CHAR_REGEX = new RegExp("[^|a-z\\\\s\\d]", 'gi');

    private configuration: IFormatterConfiguration[] = [
        {
            type: "orderedList",
            styles: {
                start: "<ol>",
                end: "</ol>"
            },
            patterns: ["\\d.", '\\r|\\n'],
            patternType: "list",
            groups: 1
        }, {
            type: "unorderedList",
            styles: {
                start: "<ul>",
                end: "</ul>"
            },
            patterns: ['-', '\\r|\\n'],
            patternType: 'list',
            groups: 1,
        }, {
            type: "bold",
            styles: {
                start: "<b>",
                end: "</b>"
            },
            patterns: ['**'],
            patternType: 'symmetric',
            groups: 1,
        }, {
            type: "italic",
            styles: {
                start: "<i>",
                end: "</i>"
            },
            patterns: ['_'],
            patternType: 'symmetric',
            groups: 1,
        }, {
            type: "hyperlink",
            styles: {
                html: "<a href='{1}'>{0}</a>"
            },
            patterns: ['[]()'],
            patternType: 'asymmetric',
            groups: 2,
        }
    ];

    constructor() {
        super();
        this.configuration.forEach(config => {
            this.initailize(config);
        });
    }

    /**
     * To add custom markdown rules. This will update the default markdown rule is the same type is passed.
     * 
     * @param configurations 
     */
    public setCustomRules(configurations: IFormatterConfiguration[]): void {
        for (let j = 0; j < configurations.length; j++) {
            let index = this.configuration.findIndex(config => config.type == configurations[j].type);
            if (index >= 0) {
                this.configuration[index] = configurations[j];
                this.initailize(configurations[j]);
                continue;
            }
            else {
                this.configuration.push(configurations[j]);
            }
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

    private initailize(configuration: IFormatterConfiguration): void {
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

    formatText(text: string): string {
        for (let i = 0; i < this.configuration.length; i++) {
            let first = true;
            let parsed,
                pattern = this.configuration[i].regexp,
                patternType = this.configuration[i].patternType,
                styles = this.configuration[i].styles;
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