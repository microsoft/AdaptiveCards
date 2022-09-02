package io.adaptivecards.renderer;

import androidx.annotation.NonNull;

import java.util.List;

public interface IChoiceSetListener {
    public void updateChoices(String query, @NonNull List<String> updatedChoices);
}
