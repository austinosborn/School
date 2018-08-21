package A6;
import java.io.*;

import java.util.*;

/**
 * Doublets.java
 * Provides an implementation of the WordLadderGame interface. The lexicon
 * is stored as a TreeSet of Strings.
 *
 * @author Your Name (you@auburn.edu)
 * @author Dean Hendrix (dh@auburn.edu)
 * @version 2017-04-28
 */
public class Doublets implements WordLadderGame {

    ////////////////////////////////////////////
    // DON'T CHANGE THE FOLLOWING TWO FIELDS. //
    ////////////////////////////////////////////

    // A word ladder with no words. Used as the return value for the ladder methods
    // below when no ladder exists.
    List<String> EMPTY_LADDER = new ArrayList<>();

    // The word list used to validate words.
    // Must be instantiated and populated in the constructor.
    TreeSet<String> lexicon;


    /**
     * Instantiates a new instance of Doublets with the lexicon populated with
     * the strings in the provided InputStream. The InputStream can be formatted
     * in different ways as long as the first string on each line is a word to be
     * stored in the lexicon.
     */
    public Doublets(InputStream in) {
        try {
            lexicon = new TreeSet<String>();
            Scanner s =
                new Scanner(new BufferedReader(new InputStreamReader(in)));
            while (s.hasNext()) {
                String str = s.next();
                lexicon.add(str.toLowerCase());
                ////////////////////////////////////////////////
                // Add code here to store str in the lexicon. //
                ////////////////////////////////////////////////
                s.nextLine();
            }
            in.close();
        }
        catch (java.io.IOException e) {
            System.err.println("Error reading from InputStream.");
            System.exit(1);
        }
    }


    ///////////////////////////////////////////////////////////////////////////////
    // Fill in implementations of all the WordLadderGame interface methods here. //
    ///////////////////////////////////////////////////////////////////////////////
    @Override
    public int getHammingDistance(String str1, String str2) {
        int differences = 0;
        if (str1.length() != str2.length()) {
            return -1;
        }
        for (int i = 0; i < str1.length(); i++) {
            if (str1.charAt(i)!= str2.charAt(i)){
                differences++;
            }
        }
        return differences;
    }

    @Override
    public List<String> getMinLadder(String start, String end) {
        start = start.toLowerCase();
        end = end.toLowerCase();
        Queue<String> queue = new LinkedList<String>();
        Set<String> visited = new TreeSet<>();
        List<String> result = new ArrayList<>();
        HashMap<String,String> hashMap = new HashMap<>();
        hashMap.put(start, "");
        visited.add(start);
        queue.add(start);
        while(!queue.isEmpty()) {
            String currentWord = queue.remove();
            if (currentWord.equals(end)) {
                Stack<String> wordStack = new Stack<>();
                String lastWord = end;
                wordStack.push(lastWord);
                while (!lastWord.equals(start)) {
                    lastWord = hashMap.get(lastWord);
                    wordStack.push(lastWord);
                }
                while (!wordStack.isEmpty()) {
                    result.add(wordStack.pop());
                }
                break;
            }
            List<String> neighbors = getNeighbors((currentWord));
            for (String word : neighbors) {
                if (!visited.contains(word)) {
                    visited.add(word);
                    queue.add(word);
                    hashMap.put(word,currentWord);
                }
            }
        }
        return result;
    }

    @Override
    public List<String> getNeighbors(String word) {
        List<String> neighbors = new ArrayList<>();
        for (int i = 0; i < word.length(); i++) {
            char[] wordArray = word.toCharArray();
            for (char c = 'a'; c < 'z'; c++) {
                if (c != word.charAt(i)) {
                    wordArray[i] = c;
                    if (isWord(new String(wordArray))) {
                        neighbors.add(new String(wordArray));
                    }
                }
            }
        }
        return neighbors;
    }

    @Override
    public int getWordCount() {
        return lexicon.size();
    }

    @Override
    public boolean isWord(String str) {
        return lexicon.contains(str);
    }

    @Override
    public boolean isWordLadder(List<String> sequence) {
        if (sequence.size() == 0) {
            return false;
        }
        for (int i = 0; i < sequence.size() - 1; i++) {
            String str1 = sequence.get(i);
            String str2 = sequence.get(i+1);
        if ((getHammingDistance(str2,str1) != 1) || !isWord(str1) || !isWord(str2)) {
            return false;
        }
        }
        if (isWord(sequence.get(0))) {
            return true;
        }
        return false;
    }
    //////////////////////////////////////////////////////

    private void testing() {
        System.out.println(lexicon.first());
    }

    public static void main(String[] args) throws FileNotFoundException{
        Doublets n = new Doublets(new FileInputStream(new File("sowpods.txt")));
        System.out.println(n.lexicon.first());
    }
}

