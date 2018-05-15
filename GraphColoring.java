package junjie;
import java.util.*;

public class GraphColoring {
        // define the maxDegree that a vertex has
	private int maxDegree;
	private int maxColor;
	private final int capacity;
       	private int maxDelete;
	private List<Vertex> vertex;
        // use a stack to store the vertices that will be coloring
	private Stack<Vertex> stack;
	private Map<Integer, List<Vertex>> colorList;
	private Map<Vertex, List<Vertex>> adjacentList;
	private Map<Integer, LinkedList<Vertex>> degreeList;
	private Map<Integer, LinkedList<Vertex>> originalDegreeList;
	
	public GraphColoring(Map<Vertex, List<Vertex>> map, int maxDegree) {
		this.maxDegree = maxDegree;
		maxColor = 0;
		capacity = map.size();
		maxDelete = 0;
		
		vertex = new ArrayList<Vertex>(); 
		stack = new Stack<Vertex>();
		colorList = new HashMap<Integer, List<Vertex>>();
		adjacentList = new HashMap<Vertex, List<Vertex>>();
		degreeList = new HashMap<Integer, LinkedList<Vertex>>();
		originalDegreeList = new HashMap<Integer, LinkedList<Vertex>>();
		
		
		for (Map.Entry<Vertex, List<Vertex>> entry : map.entrySet()) {
			adjacentList.put(entry.getKey(), new ArrayList<Vertex>(entry.getValue()));
		}
		
		for(int i = 0; i <= maxDegree; i++) {
			degreeList.put(i, new LinkedList<Vertex>());
		}
	    
		for(Vertex v: adjacentList.keySet()) {
			degreeList.get(v.initDegree).addLast(v);
		}
		for(int i: degreeList.keySet()) {
			System.out.println("degree i = " + i + " Vertices = " + degreeList.get(i).size());
		}
		smallestLastOrdering();
		smallestLastColoring(map);
	}
	
	private void smallestLastOrdering () {
		int count = 1;
		while (stack.size() != capacity) {
			for (int i = 0; i <= maxDegree; i++ ) {
				if(degreeList.get(i).size() != 0 && degreeList.get(i).getFirst()!=null) {
					Vertex v = degreeList.get(i).getFirst();
					if (i != 0) {
						for (Vertex m: adjacentList.get(v)) {
							adjacentList.get(m).remove(v);
							degreeList.get(m.curDegree).remove(m);
							m.curDegree--;
							degreeList.get(m.curDegree).addLast(m);
						}
					}
					
					adjacentList.remove(v);
					degreeList.get(i).remove(v);
					stack.push(v);
					if (v.initDegree == this.maxDegree) {
						maxDelete = count;
					}
					break;
				}
			}
			count++;
		}
	}
	private void smallestLastColoring(Map<Vertex, List<Vertex>> map) {
	
			while (!stack.isEmpty()) {
				Vertex v = stack.pop();
			        vertex.add(v);
				int colorNum = 1;
				boolean  find = true;
				while (find) {
					for(Vertex m: map.get(v)) {
						if(m.color == colorNum) {
							colorNum++;
							find = false;
							break;
						}
					}
					if (find == true) {
						v.color = colorNum;
						maxColor = Math.max(colorNum, maxColor);
						colorList.putIfAbsent(colorNum, new ArrayList<Vertex>());
						colorList.get(v.color).add(v);
						find = false;
					}
					else {
						find = true;
					}
				}
				
		}
	}
	
	public Map<Integer, List<Vertex>> getColorList() {
		return colorList;
	}
	
	public Map<Integer, LinkedList<Vertex>> getDegreeList() {
		return degreeList;
	}
	public int getColorNums() {
		return maxColor;
	}
	
	public int getMaxColorSet() {
		int max = 0;
		for(int i: colorList.keySet()) {
			if(max < (colorList.get(i).size())) {
				max = colorList.get(i).size();
			}
		}
		return max;
	}
	
	public int getMaxDegWhenDelete() {
		return maxDelete;
	}
}
