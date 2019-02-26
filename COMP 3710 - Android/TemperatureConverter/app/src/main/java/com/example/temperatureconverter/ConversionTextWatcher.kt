package com.example.temperatureconverter

import android.text.Editable
import android.text.TextWatcher
import android.util.Log
import android.widget.EditText
import java.text.SimpleDateFormat
import java.util.*

class ConversionTextWatcher: TextWatcher {
    val source: EditText
    val target: EditText
    val function: (Double) -> Double
    val sourceName: String
    val targetName: String

    constructor(src: EditText, tgt: EditText, srcID: String, tgtID:String, func: (Double) -> Double) {
        this.source =  src
        this.target = tgt
        this.function = func
        this.sourceName = srcID
        this.targetName = tgtID
    }

    override fun afterTextChanged(s: Editable?) {
        if (source.tag != null) {
        }
        target.setTag("")
    }

    override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {

    }

    override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
        target.setTag(null)
        if (source.tag != null) {
            val string = s.toString()
            if (!string.isNullOrEmpty() && string != "-") {
                val value = string.toDouble()
                val rounded = String.format("%.2f", function(value))
                target.setText(rounded)
                Log.i("Conversion","${this.sourceName} changed to ${this.source.text} -> ${this.targetName} changed to ${this.target.text} at time ${getReadableTime(System.currentTimeMillis())}")
            } else {
                target.setText("")
                if (string != "-") {
                    Log.i("Conversion","${this.sourceName} & ${this.targetName} cleared at time ${getReadableTime(System.currentTimeMillis())}")
                }
            }
        }
    }

    fun getReadableTime(time: Long): String {
        val date = Date(time)
        val format = SimpleDateFormat("yyyy.MM.dd HH:mm:ss")
        return format.format(date)
    }
}