package Binary is

   type BINARY_NUMBER is range 0..1;
   type BINARY_ARRAY is array(0..15) of BINARY_NUMBER;
   function Int_To_Bin(n : Integer) return BINARY_ARRAY;
   function Bin_To_Int(binaryArray : BINARY_ARRAY) return Integer;
   function Random_Array return BINARY_ARRAY;
   function "+"(left: BINARY_ARRAY; right: BINARY_ARRAY) return BINARY_ARRAY;
   function "-"(left: BINARY_ARRAY; right: BINARY_ARRAY) return BINARY_ARRAY;
   procedure Reverse_Bin_Arr(binaryArray : BINARY_ARRAY);
   procedure Print_Bin_Arr(binaryArray : BINARY_ARRAY);
end Binary;
