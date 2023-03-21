package com.example.simpledrawing;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onColorButtonClick(View v) {
        SingleTouchView singleTouch = findViewById(R.id.singleTouchView);
        switch (v.getId()) {
            case R.id.btn_black:
                singleTouch.setColor(Color.BLACK);
                break;
            case R.id.btn_red:
                singleTouch.setColor(Color.RED);
                break;
            case R.id.btn_green:
                singleTouch.setColor(Color.GREEN);
                break;
            case R.id.btn_clear:
                singleTouch.clearPath();
                break;
        }
    }
}