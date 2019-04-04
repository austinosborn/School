package com.example.exam2

import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.graphics.Color
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.View
import android.view.ViewGroup
import android.widget.*
import org.w3c.dom.Text

class HistoryActivity : AppCompatActivity() {
    var db: SQLiteDatabase? = null
    var cursor: Cursor? = null
    var tl: TableLayout? = null
    var balance: TextView? = null


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_history)
        db = openOrCreateDatabase("expenseDB", Context.MODE_PRIVATE,null)
        tl = findViewById(R.id.tl)
        balance = findViewById(R.id.balance)
        showTransactionsTotal()
        addRowToTable("DATE",0.0,"CATEGORY")
        addExpensesToTable()
    }

    fun showTransactionsTotal() {
        cursor = db!!.query("Expense", null,null,null,null,null,null)
        var total: Double = 0.0
        while (cursor!!.moveToNext()) {
            total += cursor!!.getDouble(3)
        }
        balance!!.text = "Current balance: $${total}"

    }

    fun addExpensesToTable() {
        cursor = db!!.query("Expense", null,null,null,null,null,null)
        while (cursor!!.moveToNext()) {
            var date: String = cursor!!.getString(1)
            var category = cursor!!.getString(2)
            var amount: Double = cursor!!.getDouble(3)
            addRowToTable(date,amount,category)
        }
    }

    fun addRowToTable(date: String, amount: Double, category: String) {
        val tableRow = TableRow(this)
        tableRow.layoutParams = TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT,TableRow.LayoutParams.WRAP_CONTENT)

        val newNote = LinearLayout(this)
        newNote.orientation = LinearLayout.HORIZONTAL
        newNote.setBackgroundColor(Color.WHITE)
        newNote.setPadding(10,20,20,10)

        val dateView = EditText(this)
        newNote.addView(dateView)
        dateView.setText(date)
        if (date != "DATE") {
            dateView.setBackgroundColor(Color.WHITE)
            dateView.setTextColor(Color.BLACK)
        }
        else {
            dateView.setBackgroundColor(Color.BLUE)
            dateView.setTextColor(Color.WHITE)
        }
        dateView.setPadding(5,5,5,5)
        dateView.layoutParams = LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT,1.0f)

        val amountView = EditText(this)
        newNote.addView(amountView)
        if (amount == 0.0) {
            amountView.setText("AMOUNT")
            amountView.setBackgroundColor(Color.BLUE)
            amountView.setTextColor(Color.WHITE)
        }
        else {
            amountView.setText(amount.toString())
            amountView.setTextColor(Color.BLACK)
            amountView.setBackgroundColor(Color.WHITE)
        }
        amountView.setPadding(5,5,5,5)
        amountView.layoutParams = LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT,1.0f)

        val categoryView = EditText(this)
        newNote.addView(categoryView)
        categoryView.setText(category)
        if (category == "CATEGORY") {
            categoryView.setBackgroundColor(Color.BLUE)
            categoryView.setTextColor(Color.WHITE)
        }
        else {
            categoryView.setBackgroundColor(Color.WHITE)
            categoryView.setTextColor(Color.BLACK)
        }
        categoryView.setPadding(5,5,5,5)
        categoryView.layoutParams = LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT,1.0f)

        tableRow.addView(newNote)
        tl!!.addView(tableRow)

    }
}