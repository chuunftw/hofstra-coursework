public class Main{
    //#1
        public static boolean inarray(String s, String[] SA)
      {
            for(int i = 0; i< SA.length;i++)
            {
                if(s.equals(SA[i]))
                {
                    return true;
                }
            }  
            return false;
        }
    //#2
         public static int sum(int[] A)
        {
          int sum1 =0;
          for(int i =0;i<A.length;i++)
            {
              sum1 = sum1 + A[i];
            }
          return sum1;
        }
    //#2b
        public static String smallest(String[] SA)
        {
          String first = SA[0]; 
          if(SA.length == 0)
            {
              return null;
            }
          
          for(int i =1;i<SA.length;i++)
            {
              if((SA[i].compareTo(first))<first.length())
              {
                first = SA[i];
              }
            }
            return first;
        }
    //#3
        public static String reverse(String s)
        {
          String rev = "";
          for(int i =s.length()-1;i>=0;i--)
            {
              rev+=s.charAt(i); 
            }
          return rev;
        }
    //#3b
        public static boolean palindrome(String s)
        {
          String hi = reverse(s);
          return hi.equals(s);
        }
    //#4
        public static boolean duplicate(String[] str)
        {
          for(int i =0;i<str.length;i++)
            {
              for(int j=1;j<str.length;j++)
                {
                  if(!str[i].equals(str[j]))
                  {
                    return true;
                  }
                }
              
            }
          return false;
        }
    
        public static void main(String[] args){
            String[] SA = {"ab", "cd" , "fg"};
            String s = "cd";
            int[] A = {1,2,3,4,5}; 
            String[] AB = {"fdattb", "cfvdd" , "fg"};
            String small = smallest(AB);
            String rev = "Apple";
            boolean result = inarray(s, SA); 
            String pali = "racecar";
            String[] SB = {"ab", "cd" , "fg", "cd"};
            System.out.println(result);
            System.out.println(sum(A));
            System.out.println(small);
            System.out.println(reverse(rev));
            System.out.println(palindrome(pali));
            System.out.println(duplicate(SB));
      }
    }
    
    