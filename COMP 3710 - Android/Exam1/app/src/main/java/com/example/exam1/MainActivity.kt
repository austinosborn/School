package com.example.exam1

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.PersistableBundle
import android.widget.*
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    var balanceLabel: TextView? = null
    var dateInput: EditText? = null
    var priceInput: EditText? = null
    var descriptionInput: EditText? = null
    var addButton: Button? = null
    var spentButton: Button? = null
    var historyLabel: TextView? = null
    var log: LinearLayout? = null
    var items: ArrayList<String>? = ArrayList()
    var balance: Double = 0.0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        balanceLabel = findViewById(R.id.balance)
        dateInput = findViewById(R.id.date)
        priceInput = findViewById(R.id.cost)
        descriptionInput = findViewById(R.id.description)
        addButton = findViewById(R.id.add)
        spentButton = findViewById(R.id.remove)
        historyLabel = findViewById(R.id.history)
        log = findViewById(R.id.log)
        //Add listeners to added and spent button
        addButton!!.setOnClickListener {
            var item = "Added $${this.priceInput!!.text} on ${this.dateInput!!.text} from ${this.descriptionInput!!.text}"
            balance += this.priceInput!!.text.toString().toDouble()
            updateBalance()
            addNewRecord(item)
        }
        spentButton!!.setOnClickListener {
            var item = "Spent $${this.priceInput!!.text} on ${this.dateInput!!.text} from ${this.descriptionInput!!.text}"
            balance -= this.priceInput!!.text.toString().toDouble()
            updateBalance()
            addNewRecord(item)
        }
        //DEBUGGED: For some reason, savedInstanceState is null even though onSaveInstanceState is being called properly.
        restorePreviousRecords(savedInstanceState)
    }

    override fun onSaveInstanceState(outState: Bundle?) {
        super.onSaveInstanceState(outState)
        outState?.putStringArrayList("items",this.items)
        outState?.putDouble("balance",this.balance)
        //Debugged: NOT NULL WHILE GOING OUT OF APP
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle?) {
        super.onRestoreInstanceState(savedInstanceState)
        restorePreviousRecords(savedInstanceState)
    }

    fun restorePreviousRecords(bundle: Bundle?) {
        if (bundle != null) {
            //Restore all items in the log
            var items = bundle!!.getStringArrayList("items")
            for (item in items) {
                addNewRecord(item)
            }
            //Set the balance attributes
            this.balance = bundle!!.getDouble("balance")
            this.balanceLabel!!.text = "Current Balance: $${this.balance}"
        }
    }

    fun addNewRecord(item: String) {
        this.items?.add(item)
        val note = TextView(this)
        note.text = item
        log!!.addView(note)
    }

    fun updateBalance() {
        this.balanceLabel!!.text = "Current Balance: $${this.balance!!.toString()}"
    }
}
