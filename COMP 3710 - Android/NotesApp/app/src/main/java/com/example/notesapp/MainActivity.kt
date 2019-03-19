package com.example.notesapp

import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.RelativeLayout

class MainActivity : AppCompatActivity() {

    var entryBox: EditText? = null
    var notes: LinearLayout? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        notes = findViewById(R.id.notesTable)
        entryBox = findViewById(R.id.textView)
        var button: Button = findViewById(R.id.button)
        button.setOnClickListener {
            addNoteToNotes(entryBox!!.text.toString())
        }
    }

    fun addNoteToNotes(str: String) {
        val newNote = LinearLayout(this)
        newNote.orientation = LinearLayout.HORIZONTAL
        newNote.setBackgroundColor(Color.WHITE)
        newNote.setPadding(10,20,20,10)

        val text = EditText(this)
        newNote.addView(text)
        text.setText(entryBox!!.text)
        text.setBackgroundColor(Color.YELLOW)
        text.setTextColor(Color.BLACK)
        text.setPadding(5,5,5,5)
        text.layoutParams = LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT,3.5f)

        val delete = Button(this)
        delete.setText("Delete")
        delete.setOnClickListener {
            deleteNote(newNote)
        }
        delete.layoutParams = LinearLayout.LayoutParams(0,LinearLayout.LayoutParams.MATCH_PARENT,1.5f)
        newNote.addView(delete)

        notes!!.addView(newNote)

    }

    fun deleteNote(note: View) {
        notes!!.removeView(note)
    }
}
