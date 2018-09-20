function determineDecimalSeparator() {
    var n = 1.1;

    // var result = n.toLocaleString().substring(1, 2);
    var result = /^1(.+)1$/.exec(n.toLocaleString())[1];

    return n;
}