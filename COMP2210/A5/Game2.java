package A5;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.SortedSet;
import java.util.Stack;
import java.util.TreeSet;

/**
 * Created by Austin on 3/28/2017.
 */
public class Game2 implements WordSearchGame {

   private String[][] board;
   private Trie lexicon;
   private boolean initialized = false;
   public int total = 0;
   //OK

   @Override
   public void loadLexicon(String fileName) { //ok
      if (fileName == null) {
         throw new IllegalArgumentException();
      }
      try {
         URL directory = Game2.class.getResource(fileName);
         File file = new File(directory.getFile());
         FileReader fReader = new FileReader(file);
         BufferedReader reader = new BufferedReader(fReader);
         String in;
         while ((in = reader.readLine()) != null) {
            if (lexicon == null) {
               lexicon = new Trie();
            }
            if (in.contains(" ")) {
               in = in.substring(0, in.indexOf(" "));
            }
            in = in.replace(" ", "");
            lexicon.add(in.toUpperCase());
            total++;
         }
      }
      catch (Exception e) {
         throw new IllegalArgumentException();
      }
      initialized = true;
   }
   //OK

   @Override
   public void setBoard(String[] letterArray) {
      if (letterArray == null) {
         throw new IllegalArgumentException();
      }
      double n = Math.sqrt(letterArray.length);
      if (n != Math.floor(n)) {
         throw new IllegalArgumentException();
      }
      int intN = (int) Math.floor(n);
      board = new String[intN][intN];
      int index = 0;
      for (int i = 0; i < intN; i++) {
         for (int j = 0; j < intN; j++) {
            board[i][j] = letterArray[index];
            index++;
         }
      }
   }
   //OK

   @Override
   public String getBoard() { //ok
      String result = "";
      int horizontal = board.length + 2;
      int vertical = board.length * 2 + 3;
      for (int i = 0, k = -1; i < horizontal; i++) {
         for (int j = 0, l = -1; j < vertical; j++) {
            if (i == 0 || i == horizontal - 1) {
               if (j == 0 || j == vertical - 1) {
                  if (i > 0 && i != horizontal - 1) {
                     result = result + "|";
                  }
                  else {
                     result = result + " ";
                  }
               }
               if (j > 0 && j < vertical - 1) {
                  result = result + "-";
               }
            }
            else if (i > 0 && (j == 0) || j == vertical - 1) {
               result = result + "|";
            }
            else if ((j + 1) % 2 == 0) {
               result = result + " ";
               l += (l + 1 != board.length) ? 1 : 2 - board.length;
               if (l == 0) {
                  k++;
               }
            }
            else {
               result += board[k][l];
            }
         }
         result = result + "\n";
      }
      return result;
   }
   //OK

   @Override
   public SortedSet<String> getAllValidWords(int minimumWordLength) {
      if (minimumWordLength < 1) {
         throw new IllegalArgumentException();
      }
      if (!initialized) {
         throw new IllegalStateException();
      }
      SortedSet<String> all = new TreeSet<>();
      for (int i = 0; i < board.length; i++) {
         for (int j = 0; j < board.length; j++) {
            Crawler crawler = new Crawler(lexicon.getNode(board[i][j]), board, new Coordinate(i,j), minimumWordLength);
            Stack<Node> stackOfNodes = new Stack<>();
            stackOfNodes.push(crawler.getParent());
            crawler.crawl(crawler.getCoordinate(), stackOfNodes, "", new Stack<>()); //getCoordinate ->getCoordinate
            all.addAll(crawler.getAllWords()); //getAllWords ->getAllWords
         }
      }
      return all;
   }
   //OK

   @Override
   public int getScoreForWords(SortedSet<String> words, int minimumWordLength) {
      if (minimumWordLength < 1) {
         throw new IllegalArgumentException();
      }
      if (!initialized) {
         throw new IllegalStateException();
      }
      int total = 0;
      for (String s : words) {
         if (s.length() > minimumWordLength) {
            total = total + s.length() - minimumWordLength;
         }
      }
      return total;
   }
   //OK

   @Override
   public boolean isValidWord(String wordToCheck) {
      return lexicon.contains(wordToCheck);
   }
   //OK

   @Override
   public boolean isValidPrefix(String prefixToCheck) {
      return lexicon.containsPrefix(prefixToCheck);
   }
   //OK

   @Override
   public List<Integer> isOnBoard(String wordToCheck) {
      if (wordToCheck == null) {
         throw new IllegalArgumentException();
      }
      if (! initialized) {
         throw new IllegalStateException();
      }
      Crawler crawler = new Crawler(lexicon.getParentNode(wordToCheck), board, wordToCheck);
      Stack<Coordinate> locations = crawler.getRes();
      List<Integer> result = new ArrayList<>();
      for (Coordinate c : locations) {
         result.add(c.returnX() * board.length + c.returnY());
      }
      return result;
   }
   //CRAWLER CLASS OK

   private class Crawler {

      private final Node parent;
      private final Coordinate coordinate;
      private  int minLen;
      private String target;
      private String[][] board;
      private SortedSet<String> allWords;
      private Stack<Node> net;
      private Stack<Coordinate> result;
      //OK

      Crawler(Node parent, String[][] board, String target) {
         this.parent = parent;
         allWords  = new TreeSet<>();
         this.board = board;
         this.minLen = 0;
         this.target = target;
         result = new Stack<>();
         this.net = new Stack<>();
         this.net.add(parent);
         Coordinate firstLocation = new Coordinate(- 1, - 1);
         for (Coordinate location : getLocations(parent)) {
            if (location != null) {
               firstLocation = location;
            }
            this.crawl(location, net, "", new Stack<>());
         }
         this.coordinate = firstLocation;
      }
      //OK

      Crawler(Node parent, String[][] board, Coordinate coordinate, int minimumLength) {
         this.parent = parent;
         allWords  = new TreeSet<>();
         this.board = board;
         this.coordinate = coordinate;
         this.minLen = minimumLength;
      }
      //OK

      void crawl(Coordinate pos, Stack<Node> stackOfNodes, String s, Stack<Coordinate> alreadyBeen) {
         int[][] allPositions = {{0, 1}, {0, - 1}, {1, 0}, {- 1, 0}, {1, 1}, {- 1, - 1}, {- 1, 1}, {1, - 1}};
         int x = pos.returnX();
         int y = pos.returnY();
         if (x < 0 || y < 0 ) {
            throw new IllegalArgumentException();
         }
         s = s + board[x][y];
         alreadyBeen.push(new Coordinate(x,y));
         if (result != null && (! result.isEmpty())) {
            return;
         }
         if (target != null && s.equals(target)) {
            if (result == null) {
               result = new Stack<>();
            }
            result.addAll(alreadyBeen);
         }
         addWord(stackOfNodes.peek(), s);
         for (int [] positions : allPositions) {
            while (stackOfNodes.size() > s.length()) {
               stackOfNodes.pop();
            }
            while (alreadyBeen.size() > s.length()) {
               alreadyBeen.pop();
            }
            int xOffset = positions[0];
            int yOffset = positions[1];
            if (moveIsValid((x + xOffset), y + yOffset, board.length, board.length)
                  && lexicon.containsPrefix(s + board[x + xOffset][y + yOffset])
                  && ! alreadyBeen.contains(new Coordinate(x + xOffset,y + yOffset))) {
               Node n = lexicon.getNode(s + board[x + xOffset][y + yOffset]);
               stackOfNodes.push(n);
               crawl(new Coordinate(x + xOffset, y + yOffset), stackOfNodes, s, alreadyBeen);
            }
         }
      }
      //OK
      private ArrayList<Coordinate> getLocations(Node parent) {
         ArrayList<Coordinate> locs = new ArrayList<>();
         if (parent == null) {
            return locs;
         }
         for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board.length; j++) {
               if (board[i][j].equals(parent.returnValue())) {
                  locs.add(new Coordinate(i,j));
               }
            }
         }
         return locs;
      }
      //OK
      boolean moveIsValid(int x, int y, int maxX, int maxY) {
         boolean belowMax = x < maxX && y < maxY;
         boolean aboveMin = x >= 0 && y >= 0;
         return belowMax && aboveMin;
      }
      //OK

      Node getParent() {
         return parent;
      }

      //OK
      Coordinate getCoordinate() {
         return coordinate;
      }

      //OK
      private void addWord(Node n, String s) {
         if (n != null && n.isWord() && s.length() >= minLen) {
            allWords.add(s);
         }
      }

      //OK
      private SortedSet<String>getAllWords() {
         return allWords ;
      }
      //OK

      Stack<Coordinate> getRes() {
         return result;
      }
   }

   //COORDINATE CLASS OK

   private class Coordinate {
      private int x;
      private int y;

      Coordinate(int x, int y) {
         this.x = x;
         this.y = y;
      }

      int returnX() {
         return x;
      }

      int returnY() {
         return y;
      }

      @Override
      public boolean equals(Object other) {
         return ! (other == null || ! (other instanceof Coordinate)) && (this.x == ((Coordinate) other).returnX() && this.y == ((Coordinate) other).returnY());
      }
   }
   //TRIE CLASS OK

   private class Trie {
      private ArrayList<Node> web;
      private String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      public Trie() {
         web = new ArrayList<>();
         for (String s : alphabet.split("")) {
            web.add(new Node(s));
         }
      }
      //OK

      boolean containsPrefix(String prefix) {
         prefix = prefix.toUpperCase();
         Node parent = getParentNode(prefix);
         return containsPrefix(parent, new ArrayList<>(Arrays.asList(prefix.split(""))));
      }
      //OK

      private boolean containsPrefix(Node parent, ArrayList<String> rem) {
         if (parent == null) {
            return false;
         }
         rem.remove(0);
         return rem.size() == 0 || containsPrefix(parent.getChild(rem.get(0)), rem);
      }
      //OK

      boolean contains(String s) {
         s = s.toUpperCase();
         Node n = getParentNode(s);
         return contains(n, new ArrayList<>(Arrays.asList(s.split(""))));
      }
      //OK

      private boolean contains(Node parent, ArrayList<String> remainingLetters) {
         if (parent == null) {
            return false;
         }
         remainingLetters.remove(0);
         if (remainingLetters.size() == 0) {
            return parent.isWord();
         }
         return contains(parent.getChild(remainingLetters.get(0)), remainingLetters);
      }
      //OK
      
      boolean add(String word) {
         word = word.toUpperCase();
         Node parent = getParentNode(word);
         return add(parent, new ArrayList<>(Arrays.asList(word.split(""))));
      }
      //OK

      private boolean add(Node parent, ArrayList<String> remainingLetters) {
         remainingLetters.remove(0);
         if (remainingLetters.size() == 0) {
            parent.setAsWord();
            return true;
         }
         return add(parent.makeChild(remainingLetters.get(0)), remainingLetters);
      }
      //OK

      Node getParentNode(String s) {
         if (s == null) {
            throw new IllegalArgumentException();
         }
         return web.get(alphabet.indexOf(s.charAt(0) + ""));
      }
      //OK

      Node getNode(String s) {
         if (s == null) {
            throw new IllegalArgumentException();
         }
         Node n = getParentNode(s);
         s = s.substring(1, s.length());
         while (s.length() > 0) {
            if (n.getChild(s.charAt(0) + "") == null) {
               return n;
            }
            n = n.getChild(s.charAt(0) + "");
            s = s.substring(1, s.length());
         }
         return n;
      }
   }
   //REMOVED GENERICS

   private class Node {
      String value;
      private Node parent;
      private HashMap <String , Node> children;
      boolean word;
      //OK

      public Node(String value) {
         this.value = value;
         this.children = new HashMap<>();
      }
      //OK

      Node(String value, Node parent) {
         this.value = value;
         this.parent = parent;
         this.children = new HashMap<>();
         word = false;
      }
      //OK

      Node makeChild(String s) {
         Node child = new Node(s, this);
         children.putIfAbsent(s, child);
         return children.get(s);
      }
      //OK

      Node getChild(String s) {
         return children.get(s);
      }
      //OK

      Node setAsWord() {
         word = true;
         return this;
      }
      //OK

      boolean isWord() {
         return word;
      }
      //OK

      @Override
      public boolean equals(Object object) {
         if (object == null) {
            return false;
         }
         if (! (object instanceof Node)) {
            return false;
         }
         Node other = (Node) object;
         return value == other.value && parent == other.parent;
      }

      public String returnValue() {
         return value;
      }
   }
}


