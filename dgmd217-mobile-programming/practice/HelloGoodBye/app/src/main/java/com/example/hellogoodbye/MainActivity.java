package com.example.hellogoodbye;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClick1(View v) {
        ConstraintLayout container = (ConstraintLayout) findViewById(R.id.container);
        container.setBackgroundResource(R.drawable.exclamationbtn);
    }

    public void onClick2(View v) {
        ConstraintLayout container = (ConstraintLayout) findViewById(R.id.container);
        container.setBackgroundResource(R.drawable.greetimage);
    }

}