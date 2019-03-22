package A3;
import A3.Point;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Extractor.java. Implements feature extraction for collinear points in
 * two dimensional data.
 *
 * @author  Dean Hendrix (dh@auburn.edu)
 * @version 2017-02-08
 *
 */
public class Extractor {
   
   /** raw data: all (x,y) points from source data. */
   private Point[] points;
   
   /** lines identified from raw data. */
   private SortedSet<Line> lines;
  
   /**
    * Builds an extractor based on the points in the file named by filename. 
    */
   public Extractor(String filename) throws FileNotFoundException {
      int x, y;
      Scanner input = new Scanner(new File(filename));
      if (input.hasNext()) {
         int length = input.nextInt();
         points = new Point[length];
         for (int i = 0; i < length; i++) {
            points[i] = new Point(input.nextInt(), input.nextInt());
         }
      }
   }
  
   /**
    * Builds an extractor based on the points in the Collection named by pcoll. 
    *
    * THIS METHOD IS PROVIDED FOR YOU AND MUST NOT BE CHANGED.
    */
   public Extractor(Collection<Point> pcoll) {
      points = pcoll.toArray(new Point[]{});
   }
  
   /**
    * Returns a sorted set of all line segments of exactly four collinear
    * points. Uses a brute-force combinatorial strategy. Returns an empty set
    * if there are no qualifying line segments.
    */
   public SortedSet<Line> getLinesBrute() {
      lines = new TreeSet<Line>();
      for (int a = 0; a < points.length; a++) {
         for (int b = a + 1; b < points.length; b++) {
            for (int c = b + 1; c < points.length; c++) {
               for (int d = c + 1; d < points.length; d++) {
                  Line line = new Line(Arrays.asList(points[a],points[b],points[c],points[d]));
                  if (line.length() == 4) {
                     lines.add(line);
                  }
               }
            }
         }
      }
      return lines;
   }
  
   /**
    * Returns a sorted set of all line segments of at least four collinear
    * points. The line segments are maximal; that is, no sub-segments are
    * identified separately. A sort-and-scan strategy is used. Returns an empty
    * set if there are no qualifying line segments.
    */
   public SortedSet<Line> getLinesFast() { //Taking array points
      lines = new TreeSet<>();
      ArrayList<Line> lineData = new ArrayList<>();
      ArrayList<Point> pointData = new ArrayList<>(Arrays.asList(points));
      while (!pointData.isEmpty()) {
         HashMap<Double, SortedSet<Point>> slopeMap = new HashMap<>();
         Set<Double> slopes = new HashSet<>();
         Point p = pointData.get(0);
         for (Point i : pointData) {
            if (!i.equals(p)) {
               if (slopeMap.containsKey(i.slopeTo(p))) {
                  slopeMap.get(i.slopeTo(p)).add(i); //get(key) retrieves value, add point to value
               }
               else {
                  SortedSet<Point> tempSet = new TreeSet<>();
                  tempSet.add(i);
                  tempSet.add(p);
                  slopes.add(i.slopeTo(p));
                  slopeMap.put(i.slopeTo(p), tempSet);
               }
            }
         }
         for (Double slope : slopes) {
            boolean uniqueSet;
            if (slopeMap.get(slope).size() > 3) {
               uniqueSet = true;
               for (Line l : lines) {
                  if (l.line.containsAll(slopeMap.get(slope))) {
                     uniqueSet = false;
                     break;
                  }
               }
               if (uniqueSet) {
                  lines.add(new Line(slopeMap.get(slope)));
               }
            }

         }
         pointData.remove(p);
      }
      return lines;
   }
   
}

