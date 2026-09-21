
import java.util.Stack;
public class maze extends mazebase
{
    // default constructor suffices and is equivalent to
    // public maze() { super(); }

 @Override
 public void digout(int y, int x)   // modify this function
 {

     

     // We always dig out two spaces at a time: we look two spaces ahead
     // in the direction we're trying to dig out, and if that space has
     // not already been dug out, we dig out that space as well as the
     // intermediate space.  This makes sure that there's always a wall
     // separating adjacent corridors.

    //random permutation algorithm 
     
    
     M[y][x] = 1;  // digout maze at coordinate y,x
     drawblock(y,x);  // change graphical display to reflect space dug out
     //nextframe(40); // show next animation frame after 40ms delay

    //int dir = (int)(Math.random()*4);
    int[] DX = {0,1,0,-1};
    int[] DY = {-1,0,1,0};
    

    
    int[] P = {0,1,2,3};
            for(int i =0;i<P.length-1;i++)
            {
                int r =i+(int)(Math.random()*(P.length-i));
                int temp = P[i];
                P[i] = P[r];
                P[r] = temp;
            }

    for(int i=0;i<4;i++)
    {
            
        int d = P[i];
        int nx = x + DX[d]*2;
        int ny = y + DY[d]*2;


        
        if(nx>=0 && nx<mwidth && ny>=0 && ny<mheight && M[ny][nx]==0)
        {
            M[y+DY[d]][x+DX[d]]=1;
            drawblock(y+DY[d],x+DX[d]);
            digout(ny,nx);
        }
        
    }
 }

    //black = 1 
    //green = 0
    @Override
    public void solve() {

       int[] DX = {0, 1, 0, -1};
       int[] DY = {-1, 0, 1, 0};
       int x = 1;
       int y = 1;
       int targetY = mheight - 2;
       int targetX = mwidth - 1;
       M[targetY][targetX] = 1;
       drawblock(targetY, targetX);
       
       while (x != targetX || y != targetY) {
           drawdot(y, x);
           drawblock(y, x);
           int dir = -1;
           int best = 0x7fffffff;
           for (int i = 0; i < 4; i++) {
               int nx = x + DX[i];
               int ny = y + DY[i];
   
               if (nx >= 0 && nx < mwidth && ny >= 0 && ny < mheight && M[ny][nx] >= 1) {
                   if (M[ny][nx] < best) {
                       best = M[ny][nx];
                       dir = i;
                   }
               }
           }
   
           if (dir != -1) {
               
   
               x += DX[dir];
               y += DY[dir];
   
               M[y][x]++;
               
               drawdot(y, x);
               nextframe(10); 
           } 
       }
   }

record coord(int y,int x){}
protected coord[][] PATH = new coord[mheight][mwidth];


@Override
public void trace() {
    
    int[] DX = {0, 1, 0, -1};
    int[] DY = {-1, 0, 1, 0};
    int x = 1;
    int y = 1;
    int currentY = mheight - 2;
    int currentX = mwidth - 1;

    drawdot(currentY, currentX);
    M[currentY][currentX] = 0; 

    while (currentY != y || currentX != x) {
        int bestValue = 0x7fffffff; 
        int bestDirection = -1;

        
        for (int i = 0; i < 4; i++) {
            int nx = currentX + DX[i];
            int ny = currentY + DY[i];

            if (nx >= 0 && nx < mwidth && ny >= 0 && ny < mheight) 
            {
                if (M[ny][nx] > 1 && M[ny][nx] < bestValue) 
                {
                    bestValue = M[ny][nx];
                    bestDirection = i;
                }
            }
        }

        
        if (bestDirection != -1) 
        {
            currentX += DX[bestDirection];
            currentY += DY[bestDirection];
            drawdot(currentY, currentX);
            M[currentY][currentX] = 0; 
            nextframe(10);
        } 
    }
    drawdot(1,1);
}

   

 

    public static void main(String[] av)
    {

	new maze(); // constructor of superclass will initiate everything
    }

    // other hints:  override customize to change maze parameters:
    @Override
    public void customize()
    {
        wallcolor = java.awt.Color.pink;
	// ... can change mwidth, mheight, bw,bh, colors here
    }

}//maze subclass