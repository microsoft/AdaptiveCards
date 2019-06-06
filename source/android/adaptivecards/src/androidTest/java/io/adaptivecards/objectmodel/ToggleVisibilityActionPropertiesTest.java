package io.adaptivecards.objectmodel;

import static org.junit.Assert.*;

public class ToggleVisibilityActionPropertiesTest
{

    public static ToggleVisibilityTarget createTarget(String id, Boolean visibility)
    {
        ToggleVisibilityTarget target = new ToggleVisibilityTarget();
        target.SetElementId(id);

        if (visibility == null)
        {
            target.SetIsVisible(IsVisible.IsVisibleToggle);
        }
        else if (visibility == true)
        {
            target.SetIsVisible(IsVisible.IsVisibleTrue);
        }
        else
        {
            target.SetIsVisible(IsVisible.IsVisibleFalse);
        }

        return target;
    }

    public static ToggleVisibilityAction createMockToggleVisibilityAction()
    {
        ToggleVisibilityAction toggleVisibilityAction = new ToggleVisibilityAction();
        ToggleVisibilityTargetVector targets = toggleVisibilityAction.GetTargetElements();
        targets.add(createTarget("id1", null));
        targets.add(createTarget("id2", true));
        targets.add(createTarget("id3", false));

        return toggleVisibilityAction;
    }

}
