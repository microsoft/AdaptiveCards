var context = new ExpressionContext();
context.$root = {
    firstName: "David",
    lastName: "Claux",
    age: 45,
    address: {
        city: "Redmond",
        state: "WA"
    },
    children: [
        { name: "Alexandre", age: 13 },
        { name: "Thomas", age: 9 }
    ]
};
context.registerFunction(
    "my.function",
    (params: any[]) => {
        return "Tada";
    }
);

window.onload = function()
{
    document.getElementById("btnExpandTemplate").onclick = function(e: MouseEvent)
    {
        let expression = (<HTMLTextAreaElement>document.getElementById("input")).value;

        let template = new Template(JSON.parse(expression));

        (<HTMLTextAreaElement>document.getElementById("output")).value = JSON.stringify(template.expand(context), null, 4);
    }
}