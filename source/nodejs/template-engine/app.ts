function tokenizeExpression() {
    let tokenizer = new Tokenizer();
    tokenizer.parse((<HTMLInputElement>document.getElementById("expression")).value);

    let outputDiv = document.getElementById("output");
    outputDiv.innerHTML = "";

    let table = document.createElement("table");

    for (let token of tokenizer.tokens) {
        let tr = document.createElement("tr");

        let td = document.createElement("td");
        td.innerText = TokenType[token.type];

        tr.appendChild(td);

        td = document.createElement("td");
        td.innerText = token.value;

        tr.appendChild(td);

        table.appendChild(tr);
    }

    outputDiv.appendChild(table);

    let serializedExpression = document.getElementById("serializedExpression");

    let parser = new ExpressionParser(tokenizer.tokens);

    try {
        let parsedExpression = parser.parse();
        
        serializedExpression.innerText = parsedExpression.print();
    }
    catch (e) {
        serializedExpression.innerText = e.message;
    }
}

window.onload = function()
{
    document.getElementById("btnTokenize").onclick = function(e: MouseEvent)
    {
        tokenizeExpression();
    }
}