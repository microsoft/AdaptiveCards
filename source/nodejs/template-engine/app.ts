var context = new ExpressionContext();
context.registerFunction(
    "my.function",
    (params: any[]) => {
        return "Tada";
    }
);

var dataEdit: HTMLTextAreaElement;
var inputEdit: HTMLTextAreaElement;
var outputEdit: HTMLTextAreaElement;

window.onload = function()
{
    dataEdit = <HTMLTextAreaElement>document.getElementById("data");
    inputEdit = <HTMLTextAreaElement>document.getElementById("input");
    outputEdit = <HTMLTextAreaElement>document.getElementById("output");

    document.getElementById("btnExpandTemplate").onclick = function(e: MouseEvent)
    {
        try {
            let template = new Template(JSON.parse(inputEdit.value));

            context.$root = JSON.parse(dataEdit.value);
            outputEdit.value = JSON.stringify(template.expand(context), null, 4);
        }
        catch (e) {
            alert(e.message);
        }
    }
}