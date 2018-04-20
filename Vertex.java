package junjie;

public class Vertex {
   public double x;
   public double y;
   public double z;
   public int curDegree;
   public int initDegree;
   public int color;
   public int id;
   
   public Vertex(double x, double y) {
	   this.x = x;
	   this.y = y;
	   curDegree = 0;
	   initDegree = 0;
	   color = 0;
	   id = 0;
   }
   
   public Vertex(double x, double y, double z) {
	   this.x = x;
	   this.y = y;
	   this.z = z;
	   curDegree = 0;
	   initDegree = 0;
	   color = 0;
	   id = 0;
   }
}
