package A4;
import java.util.NoSuchElementException;
import java.util.Random;
import java.util.Iterator;

/**
 * Created by Austin on 3/4/2017.
 */
public class RandomizedListImplements<T> implements RandomizedList<T> {
   Random rng = new Random();
   int size; g
   
   T[] array;
   int[] indexes;

   public RandomizedListImplements() {
      size = 0;
      array = (T[]) new Object[100];
   }

   @Override
   public void add(T element) {
      if (element == null) {
         throw new IllegalArgumentException();
      }
      if (size > array.length / 2) {
         resize(2);
         add(element);
      }
      array[size] = element;
      size++;

   }

   @Override
   public T remove() {
      if (isEmpty()) {
         return null;
      }
      if (size() == 1) {
         T temp = array[0];
         array[0] = null;
         size--;
         return temp;
      }
      int random = rng.nextInt(size());
      T returnValue = array[random];
      array[random] = array[size() - 1];
      array[size() - 1] = null;
      size--;
      return returnValue;
   }

   @Override
   public T sample() {
      if (isEmpty()) {
         return null;
      }
      return array[rng.nextInt(size())];
   }

   @Override
   public int size() {
      return size;
   }

   @Override
   public boolean isEmpty() {
      return size() == 0;
   }

   @Override
   public Iterator iterator() {
      return new Iterator() {
         T[] dupe = (T[]) new Object[size];
         int dupeSize = size();
         boolean initalized = false;
         @Override
         public boolean hasNext() {
            if (!initalized) {
               for (int i = 0; i < size(); i++) {
                  dupe[i] = array[i];
               }
               initalized = true;
            }
            return (!isEmpty() && dupeSize != 0);

         }

         @Override
         public Object next() {
            if (!hasNext()) {
               throw new NoSuchElementException();
            }
            int random = rng.nextInt(dupeSize);
            T returnValue = dupe[random];
            dupe[random] = dupe[dupeSize - 1];
            dupe[dupeSize - 1] = null;
            dupeSize--;
            if (returnValue == null) {
               throw new NoSuchElementException();
            }
            return returnValue;
         }
      };
   }

   private void resize(int multiplier) {
      int newSize = array.length * multiplier;
      T[] temp = (T[]) new Object[newSize];
      for (int i = 0; i < size(); i++) {
         temp[i] = array[i];
      }
      array = temp;

   }
}
