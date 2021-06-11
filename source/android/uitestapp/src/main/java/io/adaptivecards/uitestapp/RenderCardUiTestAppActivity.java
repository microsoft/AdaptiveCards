package io.adaptivecards.uitestapp;

import android.os.Bundle;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import io.adaptivecards.uitestapp.ui.inputs.InputsFragment;
import io.adaptivecards.uitestapp.ui.rendered_card.RenderedCardFragment;
import io.adaptivecards.uitestapp.ui.test_cases.TestCasesFragment;

public class RenderCardUiTestAppActivity extends AppCompatActivity
{

    public static class PagerAdapter extends FragmentPagerAdapter
    {
        private static int NUM_FRAGMENTS = 3;

        public PagerAdapter(FragmentManager fragmentManager)
        {
            super(fragmentManager, BEHAVIOR_RESUME_ONLY_CURRENT_FRAGMENT);
        }

        @NonNull
        @Override
        public Fragment getItem(int position)
        {
            switch(position)
            {
                case 0:
                    return new TestCasesFragment();
                case 1:
                    return new RenderedCardFragment();
                case 2:
                    return new InputsFragment();
            }
            return null;
        }

        @Override
        public int getCount()
        {
            return NUM_FRAGMENTS;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_render_card_ui_test_app);
        BottomNavigationView navView = findViewById(R.id.nav_view);
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        AppBarConfiguration appBarConfiguration = new AppBarConfiguration.Builder(
            R.id.navigation_home, R.id.navigation_dashboard, R.id.navigation_notifications)
            .build();
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        NavigationUI.setupActionBarWithNavController(this, navController, appBarConfiguration);
        NavigationUI.setupWithNavController(navView, navController);
    }

}
