function expand(jsonTemplate, jsonData) {
    var template = new ACData.Template(JSON.parse(jsonTemplate));

    var context = new ACData.EvaluationContext();
    context.$root = JSON.parse(jsonData);

    var expanded = template.expand(context);
    return JSON.stringify(expanded);
}
