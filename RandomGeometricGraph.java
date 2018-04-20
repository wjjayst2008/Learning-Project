/* Genereate Random Geometricm Graphs in different topology with uniform
   distribution.
** @author Junjie Wu
** @ID  47503174
*/

package junjie;


import java.util.Random;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;

public class RandomGeometricGraph {
    private int num;
    private double radius;
    private int totalDegrees;
    private Vertex maxDegVertex;
    private Vertex minDegVertex;
    private List<Vertex> list;
    private Map<Integer, List<Vertex>> cell;
    private Map<Vertex, List<Vertex>> adjacentList;

    /* Construction function */
    public RandomGeometricGraph(int num, int avg, String shape) {
        this.num = num;
        totalDegrees = 0;
        maxDegVertex = null;
        minDegVertex = null;

        /* list stores the whole vertices */
        list = new ArrayList<Vertex>();
        /* split the shape to uniform cells and give each cell an ID */
        cell = new HashMap<Integer, List<Vertex>>();
	adjacentList = new HashMap<Vertex,List<Vertex>>();
        if(shape.toLowerCase().equals("square")) {
	    // avg/(PI*r*r) = N/area
	    radius = Math.sqrt((float)avg / (num*Math.PI));
	    squarePointGeneration();
	    addEdge(shape);
        }
        else if (shape.toLowerCase().equals("disk")) {
	    radius = Math.sqrt((float)avg / num);
	    diskPointGeneration();
	    addEdge(shape);
	}
        else if (shape.toLowerCase().equals("sphere")) {
	    radius = Math.sqrt(4*(float)avg / num);
	    spherePointGeneration();
	    addEdge(shape);
        }
    }

    /* Calculate the total degree of the graph */
    private final void calculateDegree() {
        int min = Integer.MAX_VALUE;
        int max = 0;
	int total = 0;
        for (Vertex v: adjacentList.keySet()) {
            v.curDegree = adjacentList.get(v).size() -1;
	    v.initDegree = v.curDegree;
	    if(v.initDegree != 0) {
	        total += v.initDegree;
	        if (v.initDegree < min) {
	            min = v.initDegree;
		    minDegVertex = v;
	        }
	        if (v.initDegree > max) {
	            max = v.initDegree;
		    maxDegVertex = v;
	        }
	     }
          }
	  totalDegrees = total;
    }

    /* Generate nodes in the square topology */
    private void squarePointGeneration() {
        Random rand = new Random();
    	for (int i = 1; i <= num; i++) {
    		     double x = rand.nextDouble();
    		     double y = rand.nextDouble();
    		     Vertex v = new Vertex(x,y);
    		     v.id = i;
    		     list.add(v);
    		     adjacentList.put(v, new ArrayList<Vertex>());
    	  }
    }

    private void diskPointGeneration() {
    	  Random rand = new Random();
    	  for (int i = 1; i <= num; i++) {
    	      double theta = rand.nextDouble()*2*Math.PI;
    	      double R = rand.nextDouble();
    	      double x = Math.sin(theta)*Math.sqrt(R);
    	      double y = Math.cos(theta)*Math.sqrt(R);
    	      Vertex v = new Vertex(x,y);
    	      v.id = i;
    	      list.add(v);
    	      adjacentList.put(v, new ArrayList<Vertex>());
	  }
    }

    private void spherePointGeneration() {
        Random rand = new Random();
    	while(list.size() != num) {
    	    double x1 = rand.nextDouble()*2-1;
    	    double x2 = rand.nextDouble()*2-1;
    	    if((x1*x1 + x2*x2) < 1) {
    	        double x = 2*x1*Math.sqrt(1-x1*x1-x2*x2);
    	        double y = 2*x2*Math.sqrt(1-x1*x1-x2*x2);
                double z = 1 - 2*(x1*x1 + x2*x2);
    	        Vertex v = new Vertex(x,y,z);
    	        v.id = list.size() + 1;
    		list.add(v);
    	        adjacentList.put(v, new ArrayList<Vertex>());
     	     }
    	}
    }

    private void addEdge(String shape) {
        int splitLength = 0;
    	int cellSize = 0;
    	if(shape.toLowerCase().equals("square")) {
            splitLength = (int) Math.ceil(1 / radius);
    	    cellSize = (int)Math.pow(splitLength, 2);
    	    for (Vertex v: list) {
    	        int cellIndex = 0;
    		cellIndex = (int)(Math.ceil(v.x/radius)) + (int)((Math.ceil(v.y / radius-1))*splitLength);
    		cell.putIfAbsent(cellIndex,new ArrayList<Vertex>());
    		cell.get(cellIndex).add(v);
             }
      	}
 	if(shape.toLowerCase().equals("disk")) {
            splitLength = (int)Math.ceil(2 / radius);
    	    cellSize = (int)Math.pow(splitLength, 2);
    	    for (Vertex v: list) {
                int cellIndex = 0;
    		cellIndex = (int)(Math.ceil(v.x/radius)) + (int)((Math.ceil(v.y / radius -1))*splitLength);
    		cell.putIfAbsent(cellIndex,new ArrayList<Vertex>());
    		cell.get(cellIndex).add(v);
             }
    	  }
    	  if(shape.toLowerCase().equals("sphere")) {
              splitLength = (int)Math.ceil(2 / radius);
    	      cellSize = (int)Math.pow(splitLength, 3);
    	      for (Vertex v: list) {
    	          int cellIndex = 0;
    		  cellIndex = (int)(Math.ceil(v.x/radius)) + (int)((Math.ceil(v.y / radius -1))*splitLength) +
    		    	      (int)((Math.ceil(v.z / radius -1))*splitLength);
    		  cell.putIfAbsent(cellIndex,new ArrayList<Vertex>());
    		  cell.get(cellIndex).add(v);
    	      }
    	  }

    	  for (int i = 0; i < cellSize; i++) {
              if(cell.get(i) == null) {
    	          continue;
    	      }
    	      for(int j = 0; j < cell.get(i).size(); j++) {
    	          Vertex v = cell.get(i).get(j);
      	          addEdgeWithNeighborCell(v,i);
      	          if(i % splitLength != 0) {
    	              addEdgeWithNeighborCell(v,i + 1);
    	          }
    	          if(i <=splitLength*(splitLength-1)) {
    	              addEdgeWithNeighborCell(v,i + splitLength);
    	          }
    	          if((i <= splitLength*(splitLength-1)) && (i % splitLength != 0)) {
    		      addEdgeWithNeighborCell(v,i + splitLength + 1);
    	          }
    	          if((i > splitLength) && (i % splitLength != 0)) {
    		      addEdgeWithNeighborCell(v, i- splitLength + 1);
    		  }
    	      }
    	  }
    	  calculateDegree();
    }

    private void addEdgeWithNeighborCell(Vertex v, int i) {
        if(cell.get(i) == null) {
            return;
        }
	for(int j = 0; j < cell.get(i).size(); j++) {
            Vertex m = cell.get(i).get(j);
    	    if(Math.sqrt(Math.pow((v.x - m.x),2) + Math.pow(v.y - m.y, 2)) <= radius) {
    	        if(m != v) {
    		    if(!adjacentList.get(v).contains(m)) {
                        adjacentList.get(v).add(m);
    	            }
    		    if(!adjacentList.get(m).contains(v)) {
    		        adjacentList.get(m).add(v);
    		    }
    	         }
    	      }
        }
    }

    public int getNumVertices() {
        return num;
    }

    public int getNumEdges() {
        return totalDegrees / 2;
    }

    public double getRadius() {
        return radius;
    }

    public double getAvgDegree() {
        return totalDegrees / num;
    }
    public Vertex getMaxDegVertex() {
    	return maxDegVertex;
    }

    public Vertex getMinDegVertex() {
        return minDegVertex;
    }

    public List<Vertex> getList() {
        return list;
    }

    public Map<Vertex, List<Vertex>> getAdjacentList() {
        return adjacentList;
    }
}
