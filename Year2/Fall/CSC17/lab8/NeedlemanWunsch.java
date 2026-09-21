abstract public class NeedlemanWunsch {
    String seqA, seqB;
    

    
    public NeedlemanWunsch(String seqA, String seqB)
    {
        this. seqA = "." + seqA;
        this.seqB =  "." + seqB;
    }

    public int[][] D(int i, int k, String[][] traceback) {
        int[][] twod = new int[i + 1][k + 1];
    
        for (int a = 0; a <= i; a++) {
            twod[a][0] = a * penalty(true);
            traceback[a][0] = "T"; 
        }
        for (int b = 0; b <= k; b++) {
            twod[0][b] = b * penalty(true);
            traceback[0][b] = "L";
        }
    
        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= k; b++) {
                int gapA = twod[a][b - 1] + penalty(a == i); 
                int gapB = twod[a - 1][b] + penalty(b == k); 
                int match = twod[a - 1][b - 1] + score(a, b); 
    
                if (match >= gapA && match >= gapB) {
                    twod[a][b] = match;
                    traceback[a][b] = "D"; 
                } else if (gapA >= gapB) {
                    twod[a][b] = gapA;
                    traceback[a][b] = "L"; 
                } else {
                    twod[a][b] = gapB;
                    traceback[a][b] = "T"; 
                }
            }
        }
    
        return twod;
    }

    

    public String[] traceback(String[][] traceback) {
    String alignedA = "";
    String alignedB = "";

    int i = traceback.length - 1;
    int k = traceback[0].length - 1;

    while (i > 0 || k > 0) {
        String direction = traceback[i][k];
        if (direction.equals("D")) { 
            alignedA = seqA.charAt(i) + alignedA;
            alignedB = seqB.charAt(k) + alignedB;
            i--;
            k--;
        } else if (direction.equals("L")) { 
            alignedA = "-" + alignedA;
            alignedB = seqB.charAt(k) + alignedB;
            k--;
        } else if (direction.equals("T")) {
            alignedA = seqA.charAt(i) + alignedA;
            alignedB = "-" + alignedB;
            i--;
        }
    }

    return new String[] {alignedA, alignedB};
}

    abstract public int score(int i, int k);
    
    abstract public int penalty(boolean edge);
}
