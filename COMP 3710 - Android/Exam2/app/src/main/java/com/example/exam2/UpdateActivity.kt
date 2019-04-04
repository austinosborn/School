package com.example.exam2

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.Button
import android.widget.EditText

class UpdateActivity: AppCompatActivity() {
    var db: SQLiteDatabase? = null


    var amount: EditText? = null
    var date: EditText? = null
    var category: EditText? = null

    var add: Button? = null
    var spend: Button? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_update)
        db = openOrCreateDatabase("expenseDB", Context.MODE_PRIVATE,null)
        amount = findViewById(R.id.amount)
        date = findViewById(R.id.date)
        category = findViewById(R.id.category)
        add = findViewById(R.id.addButton)
        spend = findViewById(R.id.spendButton)

        add!!.setOnClickListener {
            addExpense("add")
        }

        spend!!.setOnClickListener {
            addExpense("spend")
        }

    }

    fun addExpense(type: String) {
        var dateEntry = date!!.text.toString()
        var categoryEntry = category!!.text.toString()
        var amountEntry = amount!!.text.toString()
        var amountDouble = amountEntry.toDouble()
        if (type == "spend") {
            amountDouble = 0 - amountDouble
        }
        var tuple = ContentValues()
        tuple.put("date",dateEntry)
        tuple.put("category",categoryEntry)
        tuple.put("amount",amountDouble)
        db!!.insert("Expense",null,tuple)
    }

}