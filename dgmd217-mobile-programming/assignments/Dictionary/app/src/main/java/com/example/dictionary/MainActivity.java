package com.example.dictionary;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity implements  WordFragment.OnWordSelectedListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (findViewById(R.id.fragment_container) != null) {
            WordFragment wordFragment = new WordFragment();
            FragmentManager fm = getSupportFragmentManager();
            fm.beginTransaction().replace(R.id.fragment_container, wordFragment).commit();
        }
    }

    public void onWordSelected(int position) {
        if (findViewById(R.id.fragment_container) != null) {
            DefinitionFragment newFragment = new DefinitionFragment();
            Bundle args = new Bundle();
            args.putInt("position", position);
            newFragment.setArguments(args);

            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.replace(R.id.fragment_container, newFragment);
            transaction.addToBackStack(null);
            transaction.commit();
        } else {
            FragmentManager fm = getSupportFragmentManager();
            DefinitionFragment definitionFragment =
                    (DefinitionFragment) fm.findFragmentById(R.id.definition_fragment);
            if (definitionFragment != null) {
                definitionFragment.updateDefinitionView(position);
            }
        }
    }
}
