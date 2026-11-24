import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();

        int[] freq = new int[26];

        for (char ch : s.toCharArray()) {
            if (ch >= 'A' && ch <= 'Z') {
                freq[ch - 'A']++;
            } else if (ch >= 'a' && ch <= 'z') {
                freq[ch - 'a']++;
            }
        }

        int maxFreq = 0;
        char answer = 'a';

        for (int i = 0; i < 26; i++) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                answer = (char) ('a' + i);
            }
        }

        System.out.println(answer);
    }
}