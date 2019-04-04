package com.example.exam2

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.SearchView
import android.database.sqlite.*
import android.content.ContentValues
import android.content.Context
import android.content.Intent
import android.database.Cursor
import android.util.Log
import android.widget.Button

class MainActivity : AppCompatActivity() {

    var db: SQLiteDatabase? = null
    var addButton: Button? = null
    var spendButton: Button? = null
    var historyButton: Button? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        addButton = findViewById(R.id.buttonAdd)
        spendButton = findViewById(R.id.buttonSpend)
        historyButton = findViewById(R.id.history)

        //Create database and table
        db = openOrCreateDatabase("expenseDB", Context.MODE_PRIVATE,null)
        try {
            db!!.execSQL("CREATE TABLE Expense(id INTEGER PRIMARY KEY AUTOINCREMENT, date VARCHAR(255), category VARCHAR(255), amount REAL)")
        }
        catch (e: Exception) {
            Log.i("Main Activity", "Table already exists")
        }
        //Make buttons go to their appopriate activities
        addButton!!.setOnClickListener {
            val intent = Intent(this,UpdateActivity::class.java).apply {
            }
            startActivity(intent)
        }
        spendButton!!.setOnClickListener {
            val intent = Intent(this,UpdateActivity::class.java).apply {
            }
            startActivity(intent)
        }
        historyButton!!.setOnClickListener {
            val intent = Intent(this,HistoryActivity::class.java).apply {
            }
            startActivity(intent)
        }

    }
}
