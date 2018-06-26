export function sanitizeString(input: string): string {
    return input.toLowerCase().replace(".", "");
}
