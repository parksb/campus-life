/**
 * Lab Practice 3
 * Department of Digital Media 201700000 박성범
 * 2018.3.13
 */

import java.util.Arrays;

public class IntArrayListTest {

    public static void main(String[] args) {
        IntArrayList list = new IntArrayList();

        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);

        System.out.println("get() TEST: " + list.get(3));
        //get() TEST: 4

        list.add(6);
        list.add(7);
        list.println();
        //1 2 3 4 5 6 7

        System.out.println("");

        list.insert(0, 0);
        list.insert(5, 55);
        list.println();
        //0 1 2 3 4 55 5 6 7

        System.out.println("");

        list.remove(3);
        list.println();
        //0 1 2 4 55 5 6 7

        System.out.println("");

        list.set(3, 33);
        list.println();
        //0 1 2 33 55 5 6 7

        System.out.println("");

        IntArrayList newList = (IntArrayList)list.clone();
        newList.add(8);
        System.out.print("New list: ");
        newList.println();
        //New list: 0 1 2 33 55 5 6 7 8

        System.out.println("");

        System.out.print("Old list: ");
        list.println();
        //Old list: 0 1 2 33 55 5 6 7

        System.out.println("");

        if (newList.contains(8)) {
            int tempIndex = newList.indexOf(8);
            newList.set(tempIndex, 9);
        }
        newList.println();
        //0 1 2 33 55 5 6 7 9

        System.out.println("");

        int[] newArray = newList.toArray();
        newArray[0] = 100;
        System.out.println(Arrays.toString(newArray));
        //[100, 1, 2, 33, 55, 5, 6, 7, 9]

        newList.println();
        //0 1 2 33 55 5 6 7 9
    }

}

