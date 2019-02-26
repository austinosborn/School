with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;
with Ada.Numerics.Discrete_Random;

package body binary is 
   
   --FUNCTION: Int_To_Bin
   --INPUT: n - an integer of WORD size
   --RETURN: A BINARY_ARRAY representation of n
   function Int_To_Bin(n : Integer) return BINARY_ARRAY is
      returnArray: BINARY_ARRAY;
      quotient: Integer := n;
      remainder: Integer;
   begin
      for i in reverse returnArray'range loop  
         if quotient = 0 then
            remainder := 0;
         else
            remainder := quotient mod 2;
            quotient := quotient / 2;
         end if;
         returnArray(i) := BINARY_NUMBER(remainder);
      end loop;
      return returnArray;
   end Int_To_Bin; 
   
   --FUNCTION: Bin_To_Int
   --INPUT: binaryArray - A BINARY_ARAY
   --RETURN: Integer representation of binaryArray
   function Bin_To_Int(binaryArray : BINARY_ARRAY) return Integer is
      current: Integer;
      sum: Integer := 0;
      binary_factor: Integer := 1;
   begin
      for index in reverse binaryArray'range loop 
         current := Integer(binaryArray(index)) * binary_factor;
         sum := sum + current;
         binary_factor := binary_factor * 2;
      end loop;
      return sum;
   end Bin_To_Int;
   
   --FUNCTION: Random_Array
   --RETURN: A binary array of length 16
   function Random_Array return BINARY_ARRAY is 
   package random_bin is new Ada.Numerics.Discrete_Random (BINARY_NUMBER);
   use random_bin;
   rng : Generator;
   myArray : BINARY_ARRAY;  
   begin
      Reset(rng);
      for index in myArray'range loop 
         myArray(index) := Random(rng);        
      end loop;        
      return myArray;
   end Random_Array;
   
   --FUNCTION: Plus (unary overload)
   --INPUTS: left - left hand side BINARY_ARRAY, right - right hand side BINARY_ARRAY
   --Adds two binary arrays
   function "+"(left: BINARY_ARRAY; right: BINARY_ARRAY) return BINARY_ARRAY is
      returnArray: BINARY_ARRAY;
      carry: Integer := 0;
   begin
      for i in reverse left'range loop
         if Carry <= 0 then   
            if left(i) = 1 and right(i) = 1 then 
               returnArray(i) := BINARY_NUMBER(0);
               carry := carry + 1;
            elsif left(i) = 0 and right(i) = 0 then  
               returnArray(i) := BINARY_NUMBER(0);
            else
               returnArray(i) := BINARY_NUMBER(1);
            end if;       
         elsif Carry > 0 then
            if left(i) = 1 and right(i) = 1 then 
               returnArray(i) := BINARY_NUMBER(1);
            elsif left(i) = 0 and right(i) = 0 then  
               returnArray(i) := BINARY_NUMBER(1);
               carry := carry - 1;
            else
               returnArray(i) := BINARY_NUMBER(0);
            end if;
         end if;
      end loop;
      return returnArray;     
   end "+";
   
   
   --FUNCTION: Subtract (unary overload)
   --INPUTS: left - left hand side BINARY_ARRAY, right - right hand side BINARY_ARRAY
   --RETURN: difference of left minus right  
   function "-"(left: BINARY_ARRAY; right: BINARY_ARRAY) return BINARY_ARRAY is
      returnArray: BINARY_ARRAY;
      borrow: Integer := 0;
   begin
      for i in reverse Left'range loop
         if borrow <= 0 then          
            if left(i) = 0 and right(i) = 1 then 
               returnArray(i) := BINARY_NUMBER(1);
               borrow := borrow + 1;
            elsif left(i) = 1 and right(i) = 0 then  
               returnArray(i) := BINARY_NUMBER(1);
            else
               returnArray(i) := BINARY_NUMBER(0);
            end if;      
         elsif borrow > 0 then
            if left(i) = 1 and right(i) = 1 then 
               returnArray(i) := BINARY_NUMBER(1);
            elsif left(i) = 0 and right(i) = 0 then  
               returnArray(i) := BINARY_NUMBER(1);
            elsif left(i) = 1 and right(i) = 0 then  
               returnArray(i) := BINARY_NUMBER(0);
               borrow := borrow - 1;               
            else
               returnArray(i) := BINARY_NUMBER(0);

            end if;
         end if;   
      end loop;    
      return returnArray;       
   end "-";
   
   --PROCEDURE: Reverse_Bin_Arr
   --INPUT: binaryArray - A BINARY_ARRAY
   --Reverses the order of binaryArray
   procedure Reverse_Bin_Arr(binaryArray : BINARY_ARRAY) is 
   begin
      for index in reverse binaryArray'range loop 
         Put(String(Integer'Image(Integer(binaryArray(index)))));         
      end loop; 
      New_Line;
   end Reverse_Bin_Arr;
   
   
   --PROCEDURE: Print_Bin_Arr
   --INPUT: binaryArray - A BINARY_ARRAY
   --Prints a binary array to the console
   procedure Print_Bin_Arr(binaryArray : BINARY_ARRAY) is 
   begin
      for i in binaryArray'range loop 
         Put(String(Integer'Image(Integer(binaryArray(i)))));         
      end loop; 
      New_Line;
   end Print_Bin_Arr;
      
end Binary;
