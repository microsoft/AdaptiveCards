package io.adaptivecards.uitestapp.ui.rendered_card;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ParseResult;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.uitestapp.R;
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput;
import io.adaptivecards.uitestapp.ui.test_cases.TestCasesViewModel;

public class RenderedCardFragment extends Fragment implements ICardActionHandler
{
    private RenderedCardViewModel mRenderedCardViewModel;
    private TestCasesViewModel mTestCasesViewModel;
    private LinearLayout mCardContainer;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState)
    {
        mRenderedCardViewModel = new ViewModelProvider(requireActivity()).get(RenderedCardViewModel.class);

        mTestCasesViewModel = new ViewModelProvider(requireActivity()).get(TestCasesViewModel.class);

        View root = inflater.inflate(R.layout.fragment_rendered_card, container, false);

        mCardContainer = root.findViewById(R.id.layout_cardContainer);

        mTestCasesViewModel.getLastClickedItem().observe(getViewLifecycleOwner(),
                                                        new TestCaseObserver(this));

        return root;
    }

    @Override
    public void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard)
    {
        ActionType actionType = actionElement.GetElementType();
        if (actionType == ActionType.Submit)
        {
            Map<String, String> keyValueMap = renderedAdaptiveCard.getInputs();

            List<RetrievedInput> retrievedInputList = new ArrayList<RetrievedInput>();
            for (Map.Entry<String, String> entry : keyValueMap.entrySet())
            {
                retrievedInputList.add(new RetrievedInput(entry.getKey(), entry.getValue()));
            }
            mRenderedCardViewModel.getInputs().setValue(retrievedInputList);
        }
    }

    @Override
    public void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard) {

    }

    @Override
    public void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard) {

    }

    private class TestCaseObserver implements Observer<String>
    {
        ICardActionHandler m_cardActionHandler;

        public TestCaseObserver(ICardActionHandler cardActionHandler)
        {
            m_cardActionHandler = cardActionHandler;
        }

        @Override
        public void onChanged(String testCase)
        {
            getActivity().setTitle(testCase);
            String adaptiveCardContents = readAdaptiveCardJson(testCase);
            renderCard(adaptiveCardContents);
        }

        private void renderCard(String adaptiveCardContents)
        {
            try
            {
                ParseResult parseResult = AdaptiveCard.DeserializeFromString(adaptiveCardContents,
                                                                             AdaptiveCardRenderer.VERSION);

                mCardContainer.removeAllViews();
                RenderedAdaptiveCard renderedCard = AdaptiveCardRenderer.getInstance().render(getContext(),
                                                                                              getActivity().getSupportFragmentManager(),
                                                                                              parseResult.GetAdaptiveCard(),
                                                                                              m_cardActionHandler,
                                                                                              new HostConfig());
                mCardContainer.addView(renderedCard.getView());
            }
            catch (Exception ex)
            {
            }
        }

        private String readAdaptiveCardJson(String testCase)
        {
            try
            {
                AssetManager assetManager = getActivity().getAssets();
                BufferedReader reader = new BufferedReader(new InputStreamReader(assetManager.open(testCase)));
                StringBuilder total = new StringBuilder();

                String line;
                while ((line = reader.readLine()) != null)
                {
                    total.append(line + "\n");
                }

                return total.toString();
            }
            catch (IOException ioExcep)
            {

            }

            return null;
        }
    }
}
