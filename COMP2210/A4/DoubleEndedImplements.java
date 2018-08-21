package A4;

import java.util.Iterator;
import java.util.NoSuchElementException;


public class DoubleEndedImplements<T> implements DoubleEndedList<T> {
   Node<T> front, rear;
   int size;

   public DoubleEndedImplements() {
      front = null;
      rear = null;
   }
   @Override
   public void addFirst(T element) {
      if (element == null) {
         throw new IllegalArgumentException();
      }
      if (front != null) {
         Node<T> newNode = new Node<>(element);
         newNode.right = front;
         front.left = newNode;
         front = newNode;
         size++;
      }
      else {
         Node<T> newNode = new Node<>(element);
         rear = newNode;
         front= newNode;
         size++;
      }

   }

   @Override
   public void addLast(T element) {
      if (front == null && rear == null) {
         Node<T> newNode = new Node<>(element);
         front = newNode;
         rear = newNode;
         size++;
      }
      else {
         Node<T> newNode = new Node<>(element);
         newNode.left = rear;
         rear.right = newNode;
         rear = newNode;
         size++;
      }
   }

   @Override
   public T removeFirst() {
      if (size() > 1) {
         Node<T> returnValue = front;
         front = front.getRight();
         front.left = null;
         size--;
         return returnValue.content();
      }
      else if (size() == 1) {
         T returnValue = front.content();
         front = null;
         rear = null;
         size--;
         return returnValue;

      }
      else {
         return null;
      }

   }

   @Override
   public T removeLast() {
      if (size() > 1) {
         T returnValue = rear.content();
         rear = rear.getLeft();
         rear.right = null;
         size--;
         return returnValue;
      }
      if (size() == 1) {
         T returnValue = front.content();
         front = null;
         rear = null;
         size--;
         return returnValue;
      }
      return null;
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
   public Iterator<T> iterator() {
      return new Iterator<T>() {
         Node<T> index = front;
         @Override
         public boolean hasNext() {
            return index != null && index.getRight() != null;
         }

         @Override
         public T next() {
            if (hasNext()) {
               Node<T> temp = index;
               index = index.getRight();
               return temp.content();
            }
            throw new NoSuchElementException();
         }

         @Override
         public void remove() {
            throw new UnsupportedOperationException();
         }
      };
   }

   class Node<T> {
      Node<T> left, right;
      private T data;
      public Node (T input) {
         data = input;
         left = null;
         right = null;
      }
      public Node<T> getLeft() {
         return left;
      }
      public Node<T> getRight() {
         return right;
      }
      public T content() {
         return data;
      }

   }
}
