package com.example.notesapp

import android.content.Context
import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.ViewGroup
import android.widget.*

class MainActivity : AppCompatActivity() {

    var entryBox: EditText? = null
    var notes: LinearLayout? = null
    var search: SearchView? = null
    var notesDictionary = HashMap<String,View>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        notes = findViewById(R.id.notesTable)
        entryBox = findViewById(R.id.textView)
        search = findViewById(R.id.searchBar)
        var button: Button = findViewById(R.id.button)
        button.setOnClickListener {
            addNoteToNotes(entryBox!!.text.toString())
        }
        search!!.setOnQueryTextListener(object : SearchView.OnQueryTextListener {
            override fun onQueryTextChange(newText: String?): Boolean {
                val str = newText ?: return false
                filterNotes(str)
                return true
                //To change body of created functions use File | Settings | File Templates.
            }

            override fun onQueryTextSubmit(query: String?): Boolean {
                return false
            }
        })
        loadSavedNotes()
    }

    fun addNoteToNotes(str: String, fromRestore: Boolean = false) {
        val newNote = LinearLayout(this)
        newNote.orientation = LinearLayout.HORIZONTAL
        newNote.setBackgroundColor(Color.WHITE)
        newNote.setPadding(10,20,20,10)

        val text = EditText(this)
        newNote.addView(text)
        text.setText(str)
        text.setBackgroundColor(Color.YELLOW)
        text.setTextColor(Color.BLACK)
        text.setPadding(5,5,5,5)
        text.layoutParams = LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT,3.5f)

        val delete = Button(this)
        delete.setText("Delete")
        delete.setOnClickListener {
            deleteNote(newNote,str)
        }
        delete.layoutParams = LinearLayout.LayoutParams(0,LinearLayout.LayoutParams.MATCH_PARENT,1.5f)
        newNote.addView(delete)

        notes!!.addView(newNote)
        notesDictionary[str] = newNote
        if (!fromRestore) {
            saveToPreferences(str)
        }
    }

    fun deleteNote(note: View, str: String) {
        notes!!.removeView(note)
        removeFromPreferences(str)

    }

    fun filterNotes(str: String) {
        for (item in notesDictionary) {
            if (item.key.toLowerCase().contains(str.toLowerCase())) {
                item.value.visibility = View.VISIBLE
            }
            else {
                item.value.visibility = View.GONE
            }
        }
    }

    fun modifyPreferences(note: String, operation: String) {
        val sharedPref = getPreferences(Context.MODE_PRIVATE) ?: return
        val editor = sharedPref.edit()

        //Get current set
        var currentSet = sharedPref.getStringSet("Notes",null)
        if (currentSet == null) {
            Log.d("Main Activity","Shared preferences null")
            currentSet = mutableSetOf<String>()
        }
        //Remove current set in order to overwrite later
        editor.remove("Notes")
        editor.apply()

        //Make a new set object containing all previously existing elements
        val newSet = mutableSetOf<String>()
        newSet.addAll(currentSet)

        //Add or remove from it
        if (operation == "add")
            newSet.add(note)
        else if (operation == "remove")
            newSet.remove(note)

        //Write it to shared preferences
        editor.putStringSet("Notes",newSet)
        editor.apply()
    }

    fun saveToPreferences(note: String) {
        modifyPreferences(note, "add")
    }

    fun removeFromPreferences(note: String) {
        modifyPreferences(note, "remove")
    }

    fun loadSavedNotes() {
        val prefs = getPreferences(Context.MODE_PRIVATE) ?: return
        val notes = prefs.getStringSet("Notes",null) ?: return
        for (note in notes.sorted()) {
            addNoteToNotes(note, true)
        }
    }


}
