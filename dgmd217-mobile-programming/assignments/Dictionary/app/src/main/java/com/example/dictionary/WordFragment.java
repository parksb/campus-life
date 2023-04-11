package com.example.dictionary;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class WordFragment extends Fragment {

    public interface OnWordSelectedListener {
        public void onWordSelected(int position);
    }

    OnWordSelectedListener mWordSelListener;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_word, container, false);
        ListView listView = view.findViewById(R.id.word_list);
        listView.setAdapter(new ArrayAdapter<>(getActivity(), android.R.layout.simple_list_item_1, Data.words));
        mWordSelListener = (MainActivity) getActivity();
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                mWordSelListener.onWordSelected(position);
            }
        });
        return view;
    }
}
