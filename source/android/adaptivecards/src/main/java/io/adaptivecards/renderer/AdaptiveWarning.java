package io.adaptivecards.renderer;

public class AdaptiveWarning {
    public static final int UNKNOWN_ELEMENT_TYPE = 1;
    public static final int UNABLE_TO_LOAD_IMAGE = 2;
    public static final int INTERACTIVITY_DISALLOWED = 3;
    public static final int MAX_ACTIONS_EXCEEDED = 4;
    public static final int TOGGLE_MISSING_VALUE = 5;

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
