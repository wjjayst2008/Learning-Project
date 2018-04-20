/* SID: 47503174  Junjie Wu
   This testing code is for homework of course 7103.
   The findDuplicates fuction receives an ArrayList parameter
   and return all the values in the list or return the elements that appear more than once.
*/


import java.util.ArrayList;

public class DuplicatesTest
{ 
  private ArrayList<Integer> outputList; // define the outputList to store the output results.
  private boolean  findFlag=false;       // define a boolean variable which gives us what values to output
  public static void main(String[] args)
  {
     DuplicatesTest test= new DuplicatesTest();
     ArrayList<Integer> inputList= new ArrayList<Integer>();// add the initial values to the inputList
     inputList.add(1);
     inputList.add(3);
     inputList.add(4);
     inputList.add(5);
     inputList.add(5);   // in the second test,  delete the duplicates in inputList
     inputList.add(3);   // in the second test,  delete the duplicates in inputList
     inputList.add(8);
     inputList.add(9); 
     inputList.add(11);  // in the second test,  delete the duplicates in inputList
     inputList.add(11);  // in the second test,  delete the duplicates in inputList
     inputList.add(11);
     /*  calling the findDuplicates function  */
     test.outputList=test.findDuplicates(inputList); 
     System.out.println(test.outputList); // print the results
  }
  
  public ArrayList<Integer> findDuplicates(ArrayList<Integer> someList)
  {
    ArrayList<Integer> newList= new ArrayList<Integer>();
    for(int i=0;i<someList.size();i++)
       for(int j=i+1;j<someList.size();j++)
       {  /* if someList has duplicates and newList doesn't contain that value,
             add the value to the newList. */
          if(someList.get(i)==someList.get(j)&&!newList.contains(someList.get(i))) 
          {
            newList.add(someList.get(i));
            findFlag=true;   // set flag
          }
       }
    if(findFlag)
       return newList; // find duplicates in someList, return the newList that contains the duplicates
    else 
    return someList; // no duplicates found, return the original values in the array.
   }
}   

