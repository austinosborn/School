package A4;
import java.util.Iterator;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
/**
 * Created by Austin on 3/4/2017.
 */
public class DoubleEndedListTest {

   /** Fixture initialization (common initialization
    *  for all tests). **/
   @Before public void setUp() {
   }



   @Test public void AddLastTest() {
      DoubleEndedList<String> g = new DoubleEndedImplements<>();
      g.addFirst("A");
      g.addLast("B");
      g.addFirst("C");
      String output = g.removeLast();
      assert output.equals("B");
      output = g.removeLast();
      assert output.equals("A");
      output = g.removeLast();
      assert output.equals("C");
      output = g.removeLast();
      assert output == null;
      int outInt = g.size();
      assert outInt == 0;
      g.addFirst("A");
      g.addLast("B");
      g.addFirst("C");
      output = g.removeFirst();
      assert output.equals("C");
      output = g.removeFirst();
      assert output.equals("A");
      output = g.removeFirst();
      assert output.equals("B");



   }

   @Test public void addFirstTest() {
      DoubleEndedList g = new DoubleEndedImplements<>();
      g.addLast("eezzzzs");
      g.addLast("eews");
      g.addLast("ttt");
      g.addLast("sf");
      g.addLast("ze342");
      g.addLast("2525");
      g.removeFirst();
      g.removeFirst();
      g.removeFirst();
      g.removeFirst();
      g.removeFirst();
      g.removeFirst();
      g.removeFirst();

   }
}
