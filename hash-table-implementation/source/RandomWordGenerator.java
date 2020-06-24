package myPackage;

import java.util.Random;
import java.util.List;
import java.util.ArrayList;

public class RandomWordGenerator {
    private Random random;
    private List<String> wordsList;

    public RandomWordGenerator() {
        random = new Random();
        wordsList = new ArrayList<>();
    }

    private boolean addWord(String string) {
        return wordsList.add(string);
    }

    public String getWord() {
        String string = null;

        while(true) {
            string = new String("");

            for(int i=0; i<7; i++) {
                string += (char) (97 + random.nextInt(26));
            }

            if(wordsList.contains(string) == false) {
                addWord(string);
                break;
            }
        }

        return string;
    }

    public boolean removeWord(String string) {
        return wordsList.remove(string);
    }
}
