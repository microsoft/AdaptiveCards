export function sanitizeString(input: string): string {
    return input.toLowerCase().replace(".", "");
}

export function sanitizeName(input: string): string {
    let src = input.replace(".", " ");
    return src.replace("Set", " Set");
}
