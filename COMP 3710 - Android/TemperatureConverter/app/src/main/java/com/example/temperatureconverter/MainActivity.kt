package com.example.temperatureconverter

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.util.Log
import android.widget.EditText

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Link text views to immutable variables
        val celsius = findViewById<EditText>(R.id.celcius)
        val fahrenheit = findViewById<EditText>(R.id.fahrenheit)
        val kilometers = findViewById<EditText>(R.id.kilometers)
        val miles = findViewById<EditText>(R.id.miles)
        val kilograms = findViewById<EditText>(R.id.kilograms)
        val pounds = findViewById<EditText>(R.id.pounds)
        val liters = findViewById<EditText>(R.id.liters)
        val gallons = findViewById<EditText>(R.id.gallons)

        //Add listeners to those text views
        celsius.addTextChangedListener(ConversionTextWatcher(celsius, fahrenheit, "Celsius", "Fahrenheit", ::celsiusToFahrenheit))
        fahrenheit.addTextChangedListener(ConversionTextWatcher(fahrenheit, celsius,"Fahrenheit", "Celsius", ::fahrenheitToCelcius))
        kilometers.addTextChangedListener(ConversionTextWatcher(kilometers, miles,"Kilometers", "Miles", ::kilometersToMiles))
        miles.addTextChangedListener(ConversionTextWatcher(miles, kilometers,"Miles", "Kilometers", ::milesToKilometers))
        kilograms.addTextChangedListener(ConversionTextWatcher(kilograms, pounds,"Kilograms", "Pounds", ::kilogramsToPounds))
        pounds.addTextChangedListener(ConversionTextWatcher(pounds, kilograms,"Pounds", "Kilograms", ::poundsToKilograms))
        liters.addTextChangedListener(ConversionTextWatcher(liters,gallons,"Liters", "Gallons", ::litersToGallons))
        gallons.addTextChangedListener(ConversionTextWatcher(gallons,liters,"Gallons", "Liters", ::gallonsToLiters))
    }

    // Calculation functions conform to (Double) -> Double
    fun celsiusToFahrenheit(c: Double): Double {
        return (c * 9.0) / 5.0 + 32.0
    }

    fun fahrenheitToCelcius(f: Double): Double {
        return (f - 32.0) * (5.0/9.0)
    }

    fun kilometersToMiles(km: Double): Double {
        return km * 0.621371
    }

    fun milesToKilometers(mi: Double): Double {
        return mi * 1.60934
    }

    fun kilogramsToPounds(kg: Double): Double {
        return kg * 2.20462
    }

    fun poundsToKilograms(lb: Double): Double {
        return lb * 0.453592
    }

    fun litersToGallons(L: Double): Double {
        return L * 0.264172
    }

    fun gallonsToLiters(gal: Double): Double {
        return gal * 3.78541
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle?) {
        super.onRestoreInstanceState(savedInstanceState)
        
    }



}