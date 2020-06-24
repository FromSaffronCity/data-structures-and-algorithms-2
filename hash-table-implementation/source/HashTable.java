package myPackage;

import java.util.List;
import java.util.ArrayList;

public class HashTable {
    private int length;
    private int methodOpt;
    private boolean isOne;
    private List<KeyValuePair>[] array;

    public HashTable(int length, int methodOpt, boolean isOne) {
        this.length = length;
        this.methodOpt = methodOpt;
        this.isOne = isOne;

        array = new List[this.length];

        for(int i=0; i<this.length; i++) {
            array[i] = new ArrayList<>(2);  // NOTICE
        }
    }


    /* auxiliary functionality */
    private long hashFunction1(String key) {
        /* source: https://cp-algorithms.com/string/string-hashing.html (Polynomial Rolling Hash Function) */
        int p = 31;
        long hash = 0;
        long pow = 1;

        for(int i=0; i<key.length(); i++) {
            hash = (hash + (key.charAt(i)-'a'+1)*pow) % length;
            pow = (pow*p) % length;
        }

        return hash;
    }

    private long hashFunction2(String key) {
        /* source: https://stackoverflow.com/questions/7666509/hash-function-for-string */
        long hash = 5381;

        for(int i=0; i<key.length(); i++) {
            hash = ((hash<<5) + hash) + Character.getNumericValue(key.charAt(i));
        }

        return (hash % length);
    }

    private long auxHashFunction(String key) {
        long hash = 97;

        for(int i=0; i<key.length(); i++) {
            hash = ((hash<<3) + i*hash + (int) key.charAt(i));
        }

        return (hash % length);
    }

    private long doubleHashFunction(String key, int i) {
        if(isOne == true) {
            return (hashFunction1(key) + i*auxHashFunction(key)) % length;
        } else {
            return (hashFunction2(key) + i*auxHashFunction(key)) % length;
        }
    }

    private long customHashFunction(String key, int i) {
        long C1 = 509;  // NOTICE: C1 and C2 are tow randomly chosen auxiliary constant
        long C2 = 91;

        if(isOne == true) {
            return (hashFunction1(key) + C1*i*auxHashFunction(key) + C2*i*i) % length;
        } else {
            return (hashFunction2(key) + C1*i*auxHashFunction(key) + C2*i*i) % length;
        }
    }


    /* main functionality */

    /* insertion */
    private int insertOpen(String key, int value) {
        /* separate chaining (Open Hashing) is considered */
        int collisionNumber;
        int index;

        if(isOne == true) {
            index = (int) hashFunction1(key);
        } else {
            index = (int) hashFunction2(key);
        }

        if(array[index].isEmpty() == true) {
            collisionNumber = 0;  // NOTICE
        } else {
            collisionNumber = 1;
        }

        array[index].add(new KeyValuePair(key, value));

        return collisionNumber;
    }

    private int insertClosedDouble(String key, int value) {
        /* double hashing (closed hashing, open addressing) is considered */
        int index, idx;

        for(idx=0; idx<length; idx++) {
            index = (int) doubleHashFunction(key, idx);

            if(array[index].isEmpty() == true) {
                array[index].add(new KeyValuePair(key, value));
                break;
            }

            if(array[index].get(0).getKey().equals("") == true) {
                array[index].remove(0);  // NOTICE
                array[index].add(new KeyValuePair(key, value));
                break;
            }
        }

        if(idx == length) {
            // System.out.println(key + " insertion failed");
        }

        return idx; // as collisionNumber
    }

    private int insertClosedCustom(String key, int value) {
        /* custom hashing (closed hashing, open addressing) is considered */
        int index, idx;

        for(idx=0; idx<length; idx++) {
            index = (int) customHashFunction(key, idx);

            if(array[index].isEmpty() == true) {
                array[index].add(new KeyValuePair(key, value));
                break;
            }

            if(array[index].get(0).getKey().equals("") == true) {
                array[index].remove(0);  // NOTICE
                array[index].add(new KeyValuePair(key, value));
                break;
            }
        }

        if(idx == length) {
            // System.out.println(key + " insertion failed");
        }

        return idx; // as collisionNumber
    }

    /* search operation */
    private int searchOpen(String key) {
        int idx;
        int index;

        if(isOne == true) {
            index = (int) hashFunction1(key);
        } else {
            index = (int) hashFunction2(key);
        }

        for(idx=0; idx<array[index].size(); idx++) {
            if(array[index].get(idx).getKey().equals(key) == true) {
                break;
            }
        }

        if(idx == array[index].size() || array[index].isEmpty() == true) {
            // System.out.println(key + " not found");
        }

        return (idx + 1);  // as hitNumber (for empty index, still need to access to hash table to check emptiness)
    }

    private int searchClosedDouble(String key) {
        int index, idx;

        for(idx=0; idx<length; idx++) {
            index = (int) doubleHashFunction(key, idx);

            if(array[index].isEmpty() == true) {
                System.out.println(key + " not found");
                break;
            }

            if(array[index].get(0).getKey().equals(key) == true) {
                break;
            }
        }

        if(idx == length) {
            // System.out.println(key + " not found");
            return idx;  // as hitNumber
        }

        return (idx + 1);  // as hitNumber
    }

    private int searchClosedCustom(String key) {
        int index, idx;

        for(idx=0; idx<length; idx++) {
            index = (int) customHashFunction(key, idx);

            if(array[index].isEmpty() == true) {
                System.out.println(key + " not found");
                break;
            }

            if(array[index].get(0).getKey().equals(key) == true) {
                break;
            }
        }

        if(idx == length) {
            // System.out.println(key + " not found");
            return idx;  // as hitNumber
        }

        return (idx + 1);  // as hitNumber
    }

    /* deletion */
    private void deleteOpen(String key) {
        int index, idx;

        if(isOne == true) {
            index = (int) hashFunction1(key);
        } else {
            index = (int) hashFunction2(key);
        }

        for(idx=0; idx<array[index].size(); idx++) {
            if(array[index].get(idx).getKey().equals(key) == true) {
                break;
            }
        }

        if(idx < array[index].size()) {
            array[index].remove(idx);
        } else {
            System.out.println("deletion failed");
        }

        return ;
    }

    private void deleteClosedDouble(String key) {
        int index = -1;  // NOTICE
        boolean found = false;

        for(int i=0; i<length; i++) {
            index = (int) doubleHashFunction(key, i);

            if(array[index].isEmpty() == true) {
                break;
            }

            if(array[index].get(0).getKey().equals(key) == true) {
                found = true;
                break;
            }
        }

        if(found == false) {
            System.out.println("deletion failed");
            return ;
        }

        array[index].remove(0);
        array[index].add(new KeyValuePair("", -1));  // NOTICE - dummy node

        return ;
    }

    private void deleteClosedCustom(String key) {
        int index = -1;
        boolean found = false;

        for(int i=0; i<length; i++) {
            index = (int) customHashFunction(key, i);

            if(array[index].isEmpty() == true) {
                break;
            }

            if(array[index].get(0).getKey().equals(key) == true) {
                found = true;
                break;
            }
        }

        if(found == false) {
            System.out.println("deletion failed");
            return ;
        }

        array[index].remove(0);
        array[index].add(new KeyValuePair("", -1));  // NOTICE - dummy node

        return ;
    }


    /* public methods */
    public int insert(String key, int value) {
        if(methodOpt%3 == 0) {
            return insertOpen(key, value);
        }

        if(methodOpt%3 == 1) {
            return insertClosedDouble(key, value);
        }

        if(methodOpt%3 == 2) {
            return insertClosedCustom(key, value);
        }

        return -1;  // unlikely case
    }

    public int search(String key) {
        if(methodOpt%3 == 0) {
            return searchOpen(key);
        }

        if(methodOpt%3 == 1) {
            return searchClosedDouble(key);
        }

        if(methodOpt%3 == 2) {
            return searchClosedCustom(key);
        }

        return -1;  // unlikely case
    }

    public void delete(String key) {
        if(methodOpt%3 == 0) {
            deleteOpen(key);
        }

        if(methodOpt%3 == 1) {
            deleteClosedDouble(key);
        }

        if(methodOpt%3 == 2) {
            deleteClosedCustom(key);
        }

        return ;
    }
}
