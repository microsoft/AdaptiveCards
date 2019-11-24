/**
 *  Markdown Formatter that supports bold, italic, hyperlinks, number lists and bullet lists.
 *  It also gives user an option to add their own regex to format.
 */

class MarkdownFormatter {
    text:string;
    patterns:any[] = [];
    styles:any[] = [];
    patternTypes:any[] = [];
    styleTypes:any[] = [];

    static regexArray:any[];
    static SPECIAL_CHAR_REGEX = new RegExp("[^|a-z\\\\s\\d]", 'gi');
    
	static MD_FORMATTER_CONFIG=[
        {
            type: 'numbered',
            styles:{
                start: "<ol>",
                end: "</ol>"},
            pattern: ["\\d.", '\\r|\\n'],
            patternType: 'start-end',
            groups: 1,
        },  
        {
            type: 'bullet',
            styles:{
                start: "<ul>",
                end: "</ul>"},
            pattern: ['-', '\\r|\\n'],
            patternType: 'start-end',
            groups: 1,
        },  
		{
			type: 'bold',
            styles:{
            start: "<b>",
            end: "</b>"},
			pattern: ['**'],
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'italic',
            styles:{
                start: "<i>",
                end: "</i>"},
			pattern: ['_'],
			patternType: 'symmetric',
			groups: 1,
		},
		{
			type: 'hyperlink',
            styles: {
                html:"<a href='{1}'>{0}</a>"
            },
			pattern: ['[]()'],
			patternType: 'asymmetric',
			groups: 2,
		},
    ];

    //combines default config and user config.
    static setCustomMarkdownRegex(regexArray: any[]){
        MarkdownFormatter.regexArray = regexArray;

		// prefer user configs
		for(var i = 0; i < MarkdownFormatter.MD_FORMATTER_CONFIG.length; i++){
			for(var j =0; j < MarkdownFormatter.regexArray.length; j++){
				if(MarkdownFormatter.MD_FORMATTER_CONFIG[i].type == MarkdownFormatter.regexArray[j].type){
					MarkdownFormatter.MD_FORMATTER_CONFIG[i] = MarkdownFormatter.regexArray[j];
					MarkdownFormatter.regexArray.splice(j, 1);
					continue;					
				}
			}
		}
        MarkdownFormatter.regexArray = MarkdownFormatter.MD_FORMATTER_CONFIG.concat(MarkdownFormatter.regexArray);
        
    }
    

	constructor(text:string) {
        this.text = text;
       
		for (var i = 0; i < MarkdownFormatter.MD_FORMATTER_CONFIG.length; i++) {
			let patternArray = MarkdownFormatter.MD_FORMATTER_CONFIG[i].pattern;
			let patternType = MarkdownFormatter.MD_FORMATTER_CONFIG[i].patternType;
            let groups = MarkdownFormatter.MD_FORMATTER_CONFIG[i].groups;
            let pattern = patternArray[0];
            
            if(patternType === "custom"){                
                pattern = patternArray[0];
            }
            if(patternType === "start-end"){ 
                pattern = patternArray[0].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&") + '[\\s]+((.*?)[' + patternArray[1].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&")+ "](?="+patternArray[1].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, '\\$&')+"[\\s]+)|(.*?)$)";
            }else if(patternType == "symmetric"){
                pattern = patternArray[0].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&") + '(.*?)' + patternArray[0].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&");    
            }else if(patternType == "asymmetric"){                
                pattern = patternArray[0].replace(MarkdownFormatter.SPECIAL_CHAR_REGEX, "\\$&");    
                let regexForm = '';
                let p = MarkdownFormatter.MD_FORMATTER_CONFIG[i].pattern[0];
                for (var j = 0; j < p.length; j++) {
                    regexForm = regexForm + "\\" + p[j];
                }
                // create all group regex
				let part = regexForm.length / groups;
				let regex = "";
				for (var j = 0; j < groups; j++) {
					let group = regexForm.substring(part * j, part * (j + 1));
					let firstHalf = group.substring(0, group.length / 2);
					let secondHalf = group.substring(group.length / 2, group.length);
					let middle = (j < groups / 2) ? group.substring(0, group.length / 2) : group.substring(group.length / 2, group.length);
					regex = regex + firstHalf + '([^' + middle + ']+)' + secondHalf;
				}  
				pattern = regex;
			}
            this.patterns[i] = new RegExp(pattern, 'gim');
			this.styles[i] = MarkdownFormatter.MD_FORMATTER_CONFIG[i].styles;
			this.styleTypes[i] = MarkdownFormatter.MD_FORMATTER_CONFIG[i].type;
			this.patternTypes[i] = patternType;
		}
	}

	render() {
        
		for (var i = 0; i <= this.styleTypes.length - 1; i++) {		
			this.text = this.parseText(this.text, this.styleTypes[i], this.styles[i], this.patterns[i], this.patternTypes[i]);
		}

		return this.text;
	}

	parseText = (text, type, styles, pattern, patternType) => {
        let first=true;
        let parsed;
		while ((parsed = pattern.exec(text)) !== null) {
			if(parsed[1] === undefined){
				continue;
            } 

            //For lists.
            if(patternType === "start-end"){
                //If it is the first element of the list then add the list start tag(<ol> / <ul>) 
                if(first){
                    text = text.replace(parsed[0], styles.start+ "<li>" + parsed[1] + "</li>" + styles.end);
                    first=false;
                } else {
                    //Remove the end tag and add the list item.
                    let indexOL = text.lastIndexOf(styles.end);
                    text = text.replace(text.substring(indexOL, indexOL + styles.end.length), "");
                    text = text.replace(parsed[0], "<li>" + parsed[1] + "</li>" + styles.end);
                }
            }
            //for bold, italic.
            else if(patternType == "symmetric"){
                text = text.replace(parsed[0], styles.start + parsed[1] + styles.end);
            }
            //for hyperlinks.
            else if(patternType == "asymmetric"){ 
                styles.html = styles.html.replace("{0}",parsed[1]);
                styles.html = styles.html.replace("{1}",parsed[2]);
                text = text.replace(parsed[0], styles.html);
            }

		}
		return text;
    }
    
}

//formats the markdown in the text passed.
export function formatText(text: string): string {
    let mdformatter = new MarkdownFormatter(text);
    return mdformatter.render();
}

//adds custom regex to the format config.
export function setCustomMarkdownRegex(regexArray: any[]): void {
    MarkdownFormatter.setCustomMarkdownRegex(regexArray);
    return;
}