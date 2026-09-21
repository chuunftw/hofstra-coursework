class Time
{
    protected int minutes;
    protected int seconds;
    public Time(int m, int s)
    {
        int extra_minutes = s/60;
        seconds = s%60;
        minutes = m+extra_minutes;
    }
    public Time(){
        minutes = seconds = 0;
    }
    public int total_seconds() {
        return minutes *60 +seconds;
    }
    public String toString() {
        return minutes + "min" + seconds + " sec";
    }
    public void tick() {
        seconds++;
        minutes+=seconds/60;
        seconds = seconds % 60;
    }
    public int compareTo(Time other) {
        int total1= this.total_seconds();
        int total2 = other.total_seconds();
        return total1-total2;
    }
    public Time add(Time other) {
        int other_seconds = other.total_seconds();
        int s = seconds + other_seconds;
        int m = minutes = s/60;
        s=s%60;
        return new Time(m,s);
    }
    
}


 class HTime extends Time {

    protected int hours;

    public HTime(int h, int m, int s) {  //:Time(m,s) ??
       super(m,s);
       int extra_hours = minutes/60;
           minutes = minutes%60;
           hours = h + extra_hours;
        }//subclass constructor

    public int total_seconds() { 
        return hours*3600 + minutes*60 + seconds; 
    } //new version total_seconds

    public String toString() {
        return hours + " hrs " + super.toString(); 
    }//toString

    public void tick() {
       super.tick();
       hours += minutes/60;
       minutes = minutes%60;
    } //tick

    public Time add(Time other) {
       int other_seconds = other.total_seconds();
       int s = seconds + other_seconds;
       int m = minutes + s/60;
       int h = hours + m/60;
       s = s%60;
       m = m%60;
       return new HTime(h,m,s);
    }//sum

 }


public class progname {
    public static void main2() {
        Time t1 = new Time(3,50);
        Time t2 = new HTime(1,2,30);
        System.out.println(t1.add(t2));
    
        Time times[] = new Time[4];
        times[0] = new Time(2,30);
        times[1] = new HTime(1,30,25);
        times[2] = new Time(5,45);
        times[3] = new HTime(2,0,0);
        Time sum = new HTime(0,0,0);
        for(Time t:times) {
                sum = sum.add(t);
            }
        System.out.println("total time: " + sum);
        System.out.println("can still compare HTimes: " + sum.compareTo(t2));
        System.out.println(new HTime(1,0,0).compareTo(new Time(60,0)));
     }
    public static void main(String[] args) {
        
        Time t1 = new Time(2, 15);
        t1.tick();
        Time t2 = new Time(1, 44);
        Time t3 = t1.add(t2);
        System.out.println("t1: " + t1);
        System.out.println("t2: " + t2);
        System.out.println("sum Time: " + t3);
        System.out.println("compare t1 and t2: " + t1.compareTo(t2));
        System.out.println("compare t1 with equivalent value: " + t1.compareTo(new Time(0, 136)));
        main2();
    }
}
