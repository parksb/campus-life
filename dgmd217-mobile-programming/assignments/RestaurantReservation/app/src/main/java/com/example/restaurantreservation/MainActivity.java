package com.example.restaurantreservation;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.CalendarView;
import android.widget.EditText;
import android.widget.TimePicker;
import android.widget.Toast;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;

public class MainActivity extends AppCompatActivity {
    LocalDateTime selectedDateTime = LocalDateTime.now();
    final DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("yyyy/M/d");
    final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("HH:mm");
    final DateTimeFormatter dateTimeFormatA = DateTimeFormatter.ofPattern("yyyy년 M월 d일 HH:mm");
    final DateTimeFormatter dateTimeFormatB = DateTimeFormatter.ofPattern("yyyy년 M월 d일 HH시 mm분");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        CalendarView cal = findViewById(R.id.calendarView);
        cal.setOnDateChangeListener((calendarView, year, month, dayOfMonth) -> {
            EditText date = findViewById(R.id.textDate);
            selectedDateTime = selectedDateTime.withYear(year).withMonth(month + 1).withDayOfMonth(dayOfMonth);
            date.setText(selectedDateTime.format(dateFormat));
        });

        TimePicker timePicker = findViewById(R.id.timePicker);
        timePicker.setOnTimeChangedListener((timePickerView, hourOfDay, minute) -> {
            EditText time = findViewById(R.id.textTime);
            selectedDateTime = selectedDateTime.withHour(hourOfDay).withMinute(minute);
            time.setText(selectedDateTime.format(timeFormat));
        });
    }

    public void onReserveButtonClick(View v) {
        new AlertDialog.Builder(MainActivity.this)
                .setTitle("예약")
                .setMessage(selectedDateTime.format(dateTimeFormatA) + "에 예약하시겠습니까?")
                .setPositiveButton("예약", (dialogInterface, i) ->
                        Toast.makeText(
                                getApplicationContext(),
                                selectedDateTime.format(dateTimeFormatB) + "에 예약되었습니다.",
                                Toast.LENGTH_SHORT
                        ).show()
                )
                .setNegativeButton("취소", (dialogInterface, i) ->
                        Toast.makeText(
                                getApplicationContext(),
                                "예약이 취소되었습니다.",
                                Toast.LENGTH_SHORT
                        ).show()
                )
                .create()
                .show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.reservmenu, menu);
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.clear) {
            selectedDateTime = LocalDateTime.now();

            EditText date = findViewById(R.id.textDate);
            date.setText(selectedDateTime.format(dateFormat));

            CalendarView calView = findViewById(R.id.calendarView);
            calView.setDate(selectedDateTime.atZone(ZoneId.systemDefault())
                    .toInstant().toEpochMilli());

            TimePicker timePicker = findViewById(R.id.timePicker);
            int hour = selectedDateTime.getHour();
            int min = selectedDateTime.getMinute();
            timePicker.setHour(hour);
            timePicker.setMinute(min);
        }

        return true;
    }
}
