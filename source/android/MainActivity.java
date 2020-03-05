package com.example.testapplication;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;
import android.graphics.drawable.shapes.Shape;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.constraintlayout.solver.widgets.Rectangle;

import android.view.KeyEvent;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;

import java.util.ArrayList;
import java.util.List;

class BackgroundColorDrawable extends ShapeDrawable
{
    private final int failColor = Color.RED;
    private final int neutralColor = Color.GREEN;

    public BackgroundColorDrawable()
    {
        super(new RectShape());
        getPaint().setStrokeWidth(8);
        getPaint().setStyle(Paint.Style.STROKE);
        setNeutralBorder();
    }

    private void setBorderColor(int color)
    {
        getPaint().setColor(color);
        this.invalidateSelf();
    }

    public void setFailBorder()
    {
        setBorderColor(failColor);
    }

    public void setNeutralBorder()
    {
        setBorderColor(neutralColor);
    }
}

class ButtonClickListener implements View.OnClickListener
{

    public ButtonClickListener(View ... views)
    {
        for (View v : views)
        {
            inputs.add(v);
        }
    }

    @Override
    public void onClick(View v)
    {
        for (View input : inputs)
        {
            if (!toggleFlag)
            {
                ((BackgroundColorDrawable) input.getBackground()).setFailBorder();
            }
            else
            {
                ((BackgroundColorDrawable) input.getBackground()).setNeutralBorder();
            }

        }

        toggleFlag = !toggleFlag;
    }

    private List<View> inputs = new ArrayList<>();
    private boolean toggleFlag = false;
}

interface IInputValidator
{
    boolean isValid(String inputValue);

    boolean compliesRequired(View ... views);
}

class TextInputInputValidator implements IInputValidator
{
    @Override
    public boolean isValid(String inputValue)
    {
        return ((inputValue.length() % 2) == 0);
    }

    @Override
    public boolean compliesRequired(View... views) {
        EditText textInput = (EditText) views[0];
        return (textInput.getText().length() > 0);
    }
}

class OnKeyListener implements View.OnKeyListener
{
    public OnKeyListener(IInputValidator inputValidator)
    {
        m_inputValidator = inputValidator;
    }

    @Override
    public boolean onKey(View v, int keyCode, KeyEvent event) {
        EditText et = (EditText)v;
        if (m_inputValidator.isValid(et.getText().toString()))
        {
            ((BackgroundColorDrawable) et.getBackground()).setFailBorder();
        }
        else
        {
            ((BackgroundColorDrawable) et.getBackground()).setNeutralBorder();
        }
        return false;
    }

    private IInputValidator m_inputValidator = null;
}

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        m_testEditText = findViewById(R.id.testEditText);
        m_testEditText.setBackground(new BackgroundColorDrawable());
        m_testEditText.setOnKeyListener(new OnKeyListener(new TextInputInputValidator()));

        m_testLinearLayout = findViewById(R.id.testLinearLayout);
        m_testLinearLayout.setBackground(new BackgroundColorDrawable());

        m_testButton = findViewById(R.id.testButton);
        m_testButton.setOnClickListener(new ButtonClickListener(m_testEditText, m_testLinearLayout));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private EditText m_testEditText = null;
    private LinearLayout m_testLinearLayout = null;
    private Button m_testButton = null;
}
