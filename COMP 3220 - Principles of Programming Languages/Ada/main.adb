with Binary; use Binary;
with Ada.Text_IO; use Ada.Text_IO;
procedure Main is
   myArray : BINARY_ARRAY;
   secondArray: BINARY_ARRAY;
   thirdArray: BINARY_ARRAY;
   fourthArray: BINARY_ARRAY;
begin
   --Call the Initialization implemented in Section 1.
   Put_Line("Printing Random Array My_Array");
   myArray := Random_Array;
   Print_Bin_Arr(myArray);
   New_Line;
   --Call your Bin_To_Int function from Section2a and display the result on the console
   Put_Line("Printing integer value of My_Array");
   Put_Line(String(Integer'Image(Bin_To_Int(myArray))));
   New_Line;
   --Call your Int_To_Bin function Section2b and save the return value into a second BINARY_ARRAY.
   Put_Line("Printing array from function call Int_To_Bin(55)");
   secondArray := Int_To_Bin(Integer(55));
   --Call your Print_Bin_Arr procedure from Section 3b to display the newly created binary array.
   Print_Bin_Arr(secondArray);
   New_Line;
   --Use the overloaded "+: function on arrays 1 and 2, and save the return value into a thrid BINARY_ARRAY.
   --Print this as well using your print procedure.
   thirdArray := myArray + secondArray;
   Put("Printing value of My_Array + Another_Array");
   New_Line;
   Put("Int value of My_Array: ");
   Put(String(Integer'Image(Bin_To_Int(myArray))));
   New_Line;
   Put("Int value of Another_Array: ");
   Put_Line(String(Integer'Image(Bin_To_Int(secondArray))));
   New_Line;
   Put("Int value of Array3: ");
   Put_Line(String(Integer'Image(Bin_To_Int(thirdArray))));
   Put("Current binary value of Array3: ");
   Print_Bin_Arr(thirdArray);
   New_Line;

   --Print this as well.
   fourthArray := myArray - secondArray;
   Put("Printing value of My_Array - Another_Array");
   New_Line;
   Put("Int value of My_Array: ");
   Put(String(Integer'Image(Bin_To_Int(myArray))));
   New_Line;
   Put("Int value of Another_Array: ");
   Put_Line(String(Integer'Image(Bin_To_Int(secondArray))));
   New_Line;
   Put("Int value of Array4: ");
   Put_Line(String(Integer'Image(Bin_To_Int(fourthArray))));
   Put("Current binary value of Array4: ");
   Print_Bin_Arr(fourthArray);
   New_Line;
   --Finally, reverse the fourth BINARY_ARRAY using your Reverse_Bin_Arr procedure from Section 3a, and print the result.
   Put("Printing reverse of Array4: ");
   Reverse_Bin_Arr(fourthArray);

end Main;




