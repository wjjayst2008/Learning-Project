package junjie;

import junjie.RandomGeometricGraph;
import junjie.Vertex;
import processing.core.PApplet;
import processing.core.PShape;

public class Main extends PApplet {
    public static void main(String[] args) {
        PApplet.main("junjie.Main");
    }
    public void settings() {
	size(1100,700);
    }
    PShape point;
    PShape pointMaxDegree;
    PShape pointMinDegree;
    PShape line;
    RandomGeometricGraph rgg;
    GraphColoring gc;
    int[] colorArray;
    long start;

    public void setup() {
        start = System.currentTimeMillis();
	stroke(255,255,0);
	background(0,0,0);
	point = createShape(ELLIPSE,0,0,5,5);
	point.setFill(color(255,255,0));
	pointMaxDegree = createShape(ELLIPSE, 0, 0, 30, 30);
	pointMaxDegree.setFill(color(0,255,0));
	pointMinDegree = createShape(ELLIPSE, 0, 0, 10, 10);
	pointMinDegree.setFill(color(0,0,255));
	line = createShape(LINE,0,0,0,0);
	line.setStrokeWeight(1);
	colorArray = new int[50];

	colorArray[0] = color(255,0,0);
	colorArray[1] = color(0,255,0);
	colorArray[2] = color(0,0,255);
	colorArray[3] = color(255,255,0);
	colorArray[4] = color(0,255,255);
	colorArray[5] = color(255,0,255);
	colorArray[6] = color(255,127,127);
	colorArray[7] = color(127,255,127);
	colorArray[8] = color(127,127,255);
	colorArray[9] = color(127,127,127);
	colorArray[10] = color(255,0,0);
	colorArray[11] = color(0,255,0);
	colorArray[12] = color(0,0,255);
	colorArray[13] = color(255,255,0);
	colorArray[14] = color(0,255,255);
	colorArray[15] = color(255,0,255);
	colorArray[16] = color(255,127,127);
	colorArray[17] = color(127,255,127);
	colorArray[18] = color(127,127,255);
	colorArray[19] = color(127,127,127);
	colorArray[20] = color(255,0,0);
	colorArray[21] = color(0,255,0);
	colorArray[22] = color(0,0,255);
	colorArray[23] = color(255,255,0);
	colorArray[24] = color(0,255,255);
	colorArray[25] = color(255,0,255);
	colorArray[26] = color(255,127,127);
	colorArray[27] = color(127,255,127);
	colorArray[28] = color(127,127,255);
	colorArray[29] = color(127,127,127);
	colorArray[30] = color(255,0,0);

	rgg = new RandomGeometricGraph(8000,64,"disk");
	gc = new GraphColoring(rgg.getAdjacentList(), rgg.getMaxDegVertex().initDegree);
	String radius = String.format("%.2f",rgg.getRadius());
	textSize(20);
	fill(255,0,0);
	textAlign(LEFT);
	text("BenthMark #1",750,150);
	text("Estimated radius = " + radius,750,200);
	text("Number of Edges = " + rgg.getNumEdges(),750,250);
	text("Avg.Deg. = " + rgg.getAvgDegree(),750,300);
	text("MaxDegree = " + rgg.getMaxDegVertex().initDegree,750,350);
	text("MinDegree = " + rgg.getMinDegVertex().initDegree,750,400);
	text("Num of colors = " + gc.getColorNums(),750,450);
	text("Max degree-when-delete = " + gc.getMaxDegWhenDelete(),750,500);
	text("Max color set = " + gc.getMaxColorSet(), 750,550);
	long end1 = System.currentTimeMillis();
	System.out.println("Point generation time: " + (end1 - start));

	for(int i: gc.getColorList().keySet()) {
		System.out.println("color i = " + i + "  Vertices= " + gc.getColorList().get(i).size());
	}
    }

    public void draw() {
	translate(300,300);
	noLoop();
        for(Vertex v: rgg.getList()) {
            if(v.initDegree == rgg.getMaxDegVertex().initDegree) {
		shape(pointMaxDegree,(float)v.x*300, (float)v.y*300);
	    }		
	    else if (v.initDegree == rgg.getMinDegVertex().initDegree) {
		 shape(pointMinDegree, (float)v.x*300, (float)v.y*300);
	    }
            else {
		 //point.setFill(colorArray[v.color]);
	         shape(point,(float)v.x*300,(float)v.y*300);
	    }
	}
	long end2 = System.currentTimeMillis();
	System.out.println("Point generation time: " + (end2 - start));
    }
}
