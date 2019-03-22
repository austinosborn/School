package A5;
/**
 * Provides a factory method for creating word search games. 
 *
 * @author YOUR NAME HERE
 * @author Dean Hendrix (dh@auburn.edu)
 * @version 2017-03-23
 */
public class WordSearchGameFactory {

   /**
    * Returns an instance of a class that implements the WordSearchGame
    * interface.
    */
   public static Game2 createGame() {
      // You must return an instance of your solution class here instead of null.
      return new Game2();
   }
}

