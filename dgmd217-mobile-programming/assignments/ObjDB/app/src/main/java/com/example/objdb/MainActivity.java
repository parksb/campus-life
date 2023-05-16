package com.example.objdb;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

class DBHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "spheregeom.db";
    private static final int DATABASE_VERSION = 1;

    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE vertices (_id integer PRIMARY KEY AUTOINCREMENT, x float, y float, z float);");
        db.execSQL("CREATE TABLE triangles (_id integer PRIMARY KEY AUTOINCREMENT, v0 integer, v1 integer, v2 integer);");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS vertices");
        db.execSQL("DROP TABLE IF EXISTS trinagles");
    }
}

public class MainActivity extends AppCompatActivity {
    private SQLiteDatabase db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        DBHelper helper = new DBHelper(this);
        try {
            db = helper.getWritableDatabase();
        } catch (SQLException e) {
            db = helper.getReadableDatabase();
        }
    }

    public void readSphere(View view) {
        db.execSQL("DELETE FROM vertices");
        db.execSQL("DELETE FROM triangles");

        InputStream inputStream = this.getResources().openRawResource(R.raw.sphere);
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

        String line;

        try {
            while ((line = bufferedReader.readLine()) != null) {
                String[] tokens = line.split(" ");
                if (tokens[0].equals("v")) {
                    db.execSQL("INSERT INTO vertices VALUES (null, '" + tokens[1] + "', '" + tokens[2] + "', '" + tokens[3] + "');");
                } else if (tokens[0].equals("f")) {
                    db.execSQL("INSERT INTO triangles VALUES (null, '" + tokens[1] + "', '" + tokens[2] + "', '" + tokens[3] + "');");
                }
            }
        } catch (IOException e) {
            // Do nothing
        }
    }

    public void queryDatabase(View view) {
        Cursor cursor;

        cursor = db.rawQuery("SELECT x, y, z FROM vertices WHERE x < -6;", null);
        while (cursor.moveToNext()) {
            String x = cursor.getString(0);
            String y = cursor.getString(1);
            String z = cursor.getString(2);
            Log.v("OUT", "vertex pos (" + x + ", " + y + ", " + z + ")");
        }
    }
}
