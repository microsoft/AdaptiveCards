package io.adaptivecards.renderer;

public class AdaptiveWarning {
    private int code;
    private String message;

    public AdaptiveWarning(int code, String message)
    {
        this.code = code;
        this.message = message;
    }

    public int getCode() {
        return code;
    }

    public String getMessage() {
        return message;
    }
}
