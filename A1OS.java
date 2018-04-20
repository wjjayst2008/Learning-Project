/**
* A1OS.java - a class for implementing warm-up function
* @author Junjie Wu
* @sid  47503174
*/

public class A1OS {
    /* intToHex - a function converts an integer
    *  to its hexadecimal string
    */
    public static String intToHex (int i) {
        String outHexString = "";
        /** define char array hexDigits to represnts "10,11,12,13,14,15"
        *   in base 16.
        */
        char [] hexDigits = {'A','B','C','D','E','F'};
        while(i>=16) {
            int a = i%16;
            if(a>=10) {
                outHexString = String.valueOf(hexDigits[a-10]) +
                                          outHexString;
            }
            else {
                    outHexString = Integer.toString(a) + outHexString;
            }
            i = i/16;
        }
        if(i>=10) {
             outHexString = String.valueOf(hexDigits[i-10]) +
                                        outHexString;
        }
        else {
             outHexString = Integer.toString(i)+outHexString;
        }
        return outHexString;
    }
    /** intToBinary - a function converts an integer
    *   to its binary form string
    */
    public static String intToBinary (int i) {
        String outBinaryString = "";
        while(i>=2){
            int a = i%2;
            outBinaryString = Integer.toString(a) + outBinaryString;
            i= i/2;
        }
        outBinaryString = Integer.toString(i) + outBinaryString;
        /** if outBinaryString is less than 16-bits,
        *   fill with "0" to its left bits.
        */
        while(outBinaryString.length()<16) {
            outBinaryString = Integer.toString(0)+ outBinaryString;
        }
        return outBinaryString;
    }
    /** binaryToInt - a function converts a binary string to an int */
    public static int binaryToInt (String str) {
        int i = 0;
        int len = str.length();
        int outInt = 0;
        int digit;
        while (i<len) {
            digit = Character.digit(str.charAt(i++),2);
            outInt *= 2;
            outInt += digit;
        }
        return outInt;
    }

    public static void main(String[] args) {
        /** test intToHex funtion */
        int test1 = 175;
        String hexExpected = "AF";
        String hexActual = intToHex(test1);
        if(hexExpected.equals(hexActual)) {
            System.out.printf("intToHex: PASSED\n");
        }
        else {
            System.out.printf("intToHex: FAILED " +
                        "hexExpected = " + hexExpected +
                        " hexActual = " + hexActual +
                        " Parameter = " + Integer.toString(test1));
        }
        /** test intToBinary function */
        int test2 = 213;
        String binaryExpected = "0000000011010101";
        String binaryActual = intToBinary(test2);
        if(binaryExpected.equals(binaryActual)) {
            System.out.printf("intToBianry: PASSED\n");
        }
        else {
            System.out.printf("intToBinary: FAILED " +
                       "binaryExpected = " + binaryExpected +
                       " binaryActual = " + binaryActual +
                       " Parameter = " + Integer.toString(test2));
        }
        /** test binaryToInt function */
        String test3 = "1100101100111111";
        int expected = 52031;
        int actual = binaryToInt(test3);
        if(expected == actual) {
            System.out.printf("binaryToInt: PASSED\n");
        }
        else {
            System.out.printf("binaryToInt: FAILED " +
                       "expected = " + expected +
                       " actual = " + actual +
                       " Parameter = " + test3);
        }
    }
}
