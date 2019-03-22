import java.io.*;
import static java.lang.Math.max;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;


//Austin Osborn
//COMP 3270-001
//Programming Homework

public class PHW {
    //Enter directory of commna delimited txt file containing numbers (including the "phw_input.txt" part) HERE
    //Ex: "C:\\Users\\Austin\\IdeaProjects\\test\\src\\phw_input.txt" on Windows machines
    //Ex: "/home/austin/IdeaProjects/COMP3270ProgrammingAssignment/out/production/COMP3270ProgrammingAssignment/phw_input.txt" on Linux machines
    private static final String filename = "phw_input.txt";


    public static void main(String[] args) throws IOException {
        //Creates array from phw_input.txt
        int[] A = new int[10];
        try {
            //Parse int array from input
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            String s = scanner.next();
            String[] numbers = s.split(",");
            for (int i = 0; i < numbers.length; i++) {
                A[i] = Integer.parseInt(numbers[i]);
            }

        } catch (Exception e) {
            //Error message. If this occurs, please check the above final String filename to ensure you are pointing it to the correct directory
            System.out.println("Error parsing file. Please change private static\nstring filename to the full directory of phw_input.txt");
        }
        //Runs each Algorithm on file input and prints answer to console
        System.out.println("algorithm-1: " + (Algorithm_1(A)));
        System.out.println("algorithm-2: " + Algorithm_2(A));
        System.out.println("algorithm-3: " + maxSum(A, 0, A.length - 1));
        System.out.println("algorithm-4: " + Algorithm_4(A));


        //Creates other 19 arrays of length 10, 15, 20, ..., 100
        ArrayList<int[]> randomArrays = new ArrayList<>();
        Random rng = new Random();
        for (int i = 0; i < 19; i++) {
            int[] temp = new int[5 * i + 10];
            for (int j = 0; j < (5 * i + 10); j++) {
                temp[j] = rng.nextInt();
            }
            randomArrays.add(temp);
        }

        //Run each array on each algorithm 1000 times.
        long[][] matrix = new long[19][8];
        long t1, t2, average; int answer;
        for (int array = 0; array < 19; array++) {
            int[] X = randomArrays.get(array);
            for (int algorithm = 0; algorithm < 4; algorithm++) {
                t1 = System.nanoTime();
                for (int i = 0; i < 1000; i++) {
                    //Calls upon the appropriate algorithm
                    switch (algorithm) {
                        case 0:
                            answer = Algorithm_1(X);
                            break;
                        case 1:
                            answer = Algorithm_2(X);
                            break;
                        case 2:
                            answer = maxSum(X,0,X.length - 1);
                            break;
                        case 3:
                            answer = Algorithm_4(X);
                            break;
                        default:
                            System.out.println("Error. No algorithm being called upon");
                    }
                }
                t2 = System.nanoTime();
                average = (t2 - t1) / 1000;
                matrix[array][algorithm] = average;

                //Add appropriate T(n) theoretical computations
                //Calculate array size
                int n = (array*5) + 10;
                switch (algorithm) {
                    //Use specific T(n) calculation for each algorithm found in calculation documents
                    case 0:
                        matrix[array][algorithm+4] = (n*n*n) + (13/2)*(n*n) + (13/2)*(n) + 6; // T1(n) = n^3 + (13/2)n^2 +(13/2)n + 6
                        break;
                    case 1:
                        matrix[array][algorithm+4] = 6*(n*n) + 8*n + 4; //T2(n) = 6n^2 + 8n + 4
                        break;
                    case 2:
                        double log = (double) Math.log(n);
                        try {
                            matrix[array][algorithm + 4] = (long) ((12 * n) * log + 12 * n + 11); //T3(n) = 12nlgn +12n + 11
                        }
                        catch (Exception e) {
                            System.out.print("Lossy conversion");
                        }
                        break;
                    case 3:
                        matrix[array][algorithm+4] = 14*n + 4;
                }
            }
        }

        //Print out results in phw_output.txt file
        try {
            File file = new File("AustinOsborn_phw_output.txt");
            file.createNewFile();
        }
        catch (Exception e) {
            System.out.print("Error creating output file.");
        }
        FileOutputStream output = new FileOutputStream("AustinOsborn_phw_output.txt",false);
        String header = "Algorithm-1,Algorithm-2,Algorithm-3,Algorithm-4,T1(n),T2(n),T3(n),T4(n)\n";
        output.write(header.getBytes());
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 8; j++) {
                char endChar;
                switch (j) {
                    case (7):
                        endChar = '\n';
                        break;
                    default:
                        endChar = ',';
                }
                String value = Long.toString(matrix[i][j]);
                value += endChar;
                output.write(value.getBytes());
            }
        }
    }

    //Implementation of given algorithms
    public static int Algorithm_1(int[] X) {
        int P = 0;
        int Q = X.length;
        int maxSoFar = 0;
        for (int L = P; L < Q; L++) {
            for (int U = L; U < Q; U++) {
                int sum = 0;
                for (int I = L; I <= U; I++) {
                    sum += X[I];
                    //Sum now contains the sum of X[L..U]
                }
                maxSoFar = max(maxSoFar, sum);
            }
        }
        return maxSoFar;
    }

    public static int Algorithm_2(int[] X) {
        int P = 0;
        int Q = X.length;
        int maxSoFar = 0;
        for (int L = P; L < Q; L++) {
            int sum = 0;
            for (int U = L; U < Q; U++) {
                sum += X[U];
                maxSoFar = max(maxSoFar, sum);
            }
        }
        return maxSoFar;
    }

    public static int maxSum(int[] X, int L, int U) {
        if (L > U) {
            return 0;
        }
        if (L == U) {
            return max(0,X[L]);
        }
        int M = (L+U) / 2;
        //Find max crossing to left
        int sum = 0; int maxToLeft = 0;
        for (int I = M; I >= L; I--) {
            sum += X[I];
            maxToLeft = max(maxToLeft, sum);
        }
        //Find max crossing to right
        sum = 0; int maxToRight = 0;
        for (int I = M+1; I <= U; I++) {
            sum += X[I];
            maxToRight = max(maxToRight, sum);
        }
        int maxCrossing = maxToLeft + maxToRight;

        int maxInA = maxSum(X,L,M);
        int maxInB = maxSum(X,M+1,U);
        //Return max of maxCrossing, maxInA, maxInB
        int returnValue = max(maxInA,maxInB);
        returnValue = max(returnValue, maxCrossing);
        return returnValue;


    }

    public static int Algorithm_4(int[] X) {
        int P = 0;
        int Q = X.length;
        int maxSoFar = 0;
        int maxEndingHere = 0;
        for (int I = P; I < Q; I++) {
            maxEndingHere = max(0,(maxEndingHere + X[I]));
            maxSoFar = max (maxSoFar, maxEndingHere);
        }
        return maxSoFar;
    }


}
