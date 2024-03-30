/**
 * Lab Practice 3
 * Department of Digital Media 201700000 박성범
 * 2018.3.13
 */

public class IntArrayList {
    private int size = 0; // 배열이 실제 사용중인 길이
    private int limit = 1024; // 배열의 최대 길이
    private int[] data = new int[limit];

    public void add(int val) {
        if ((size + 1) >= limit) {
            // 배열의 길이를 두배로 늘린다.
            limit *= 2;

            int[] tempData = new int[limit];
            System.arraycopy(data, 0, tempData, 0, (size + 1));

            data = new int[tempData.length];
            System.arraycopy(tempData, 0, data, 0, tempData.length);
        }

        data[size] = val;
        size += 1;
    }

    public void insert(int index, int val) {
        if ((size + 1) >= limit) {
            // 배열의 길이를 두배로 늘린다.
            limit *= 2;

            int[] tempData = new int[limit];
            System.arraycopy(data, 0, tempData, 0, (size + 1));

            data = new int[tempData.length];
            System.arraycopy(tempData, 0, data, 0, tempData.length);
        }

        // 요소를 밀어낸다.
        for (int i = (size + 1); i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = val;
        size += 1;
    }

    public void remove(int index) {
        // 요소를 당긴다.
        for (int i = index; i < size; i++) {
            data[i] = data[i + 1];
        }

        size -= 1;
    }

    public int get(int index) {
        return data[index];
    }

    public boolean set(int index, int val) {
        data[index] = val;
        return true;
    }

    public boolean contains(int val) {
        for (int i = 0; i < size; i++) {
            if (data[i] == val) {
                return true;
            }
        }

        return false;
    }

    public int indexOf(int val) {
        for (int i = 0; i < size; i++) {
            if (data[i] == val) {
                return i;
            }
        }

        return -1;
    }

    public int size() {
        return size;
    }


    public Object clone() {
        IntArrayList temp = new IntArrayList();

        for (int i = 0; i < size; i++) {
            temp.add(data[i]);
        }

        return temp;
    }

    public int[] toArray() {
        int[] newData = new int[size];
        System.arraycopy(data, 0, newData, 0, size);

        return newData;
    }


    public void println() {
        for (int i = 0; i < size; i++) {
            System.out.print(data[i] + " ");
        }
    }

}

