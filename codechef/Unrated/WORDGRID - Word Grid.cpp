import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;

            do {
                c = read();
            } while (c <= ' ' && c != -1);

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    static class WordClass {
        String word;
        String rev;

        WordClass(String word) {
            this.word = word;
            this.rev = reverse(word);
        }
    }

    static List<WordClass> words;

    // lineWord[i] = class assigned to line i
    // lineOrientation[i] = 0 => word, 1 => reverse
    static int[] lineWord;
    static int[] lineOrientation;
    static boolean[] usedLine;

    static char[][] best;
    static boolean found;

    static String reverse(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    /*
     * line numbers:
     *
     * 0 1 2 3 -> rows
     * 4 5 6 7 -> columns
     */
    static boolean compatible(int line, int classId, int orientation) {

        String s = orientation == 0
                ? words.get(classId).word
                : words.get(classId).rev;

        // If this is a row, compare against already assigned columns.
        if (line < 4) {
            int r = line;

            for (int c = 0; c < 4; c++) {
                int colLine = 4 + c;

                if (lineWord[colLine] == -1)
                    continue;

                int otherId = lineWord[colLine];
                int otherOri = lineOrientation[colLine];

                String col = otherOri == 0
                        ? words.get(otherId).word
                        : words.get(otherId).rev;

                if (s.charAt(c) != col.charAt(r))
                    return false;
            }
        }

        // If this is a column, compare against already assigned rows.
        else {
            int c = line - 4;

            for (int r = 0; r < 4; r++) {
                int rowLine = r;

                if (lineWord[rowLine] == -1)
                    continue;

                int otherId = lineWord[rowLine];
                int otherOri = lineOrientation[rowLine];

                String row = otherOri == 0
                        ? words.get(otherId).word
                        : words.get(otherId).rev;

                if (row.charAt(c) != s.charAt(r))
                    return false;
            }
        }

        return true;
    }

    static char[][] buildGrid() {
        char[][] grid = new char[4][4];

        // Initially all cells are A.
        for (int r = 0; r < 4; r++) {
            Arrays.fill(grid[r], 'A');
        }

        // Put assigned rows.
        for (int r = 0; r < 4; r++) {
            if (lineWord[r] == -1)
                continue;

            String s = lineOrientation[r] == 0
                    ? words.get(lineWord[r]).word
                    : words.get(lineWord[r]).rev;

            for (int c = 0; c < 4; c++) {
                grid[r][c] = s.charAt(c);
            }
        }

        // Put assigned columns.
        for (int c = 0; c < 4; c++) {
            int line = 4 + c;

            if (lineWord[line] == -1)
                continue;

            String s = lineOrientation[line] == 0
                    ? words.get(lineWord[line]).word
                    : words.get(lineWord[line]).rev;

            for (int r = 0; r < 4; r++) {
                grid[r][c] = s.charAt(r);
            }
        }

        return grid;
    }

    static boolean lexicographicallySmaller(char[][] a, char[][] b) {
        if (b == null)
            return true;

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (a[r][c] < b[r][c])
                    return true;

                if (a[r][c] > b[r][c])
                    return false;
            }
        }

        return false;
    }

    static boolean containsRequiredWord(char[][] grid, String word) {

        // Rows
        for (int r = 0; r < 4; r++) {
            StringBuilder sb = new StringBuilder();

            for (int c = 0; c < 4; c++)
                sb.append(grid[r][c]);

            String row = sb.toString();

            if (row.equals(word) || reverse(row).equals(word))
                return true;
        }

        // Columns
        for (int c = 0; c < 4; c++) {
            StringBuilder sb = new StringBuilder();

            for (int r = 0; r < 4; r++)
                sb.append(grid[r][c]);

            String col = sb.toString();

            if (col.equals(word) || reverse(col).equals(word))
                return true;
        }

        return false;
    }

    static boolean validGrid(char[][] grid) {
        for (WordClass wc : words) {
            if (!containsRequiredWord(grid, wc.word))
                return false;
        }

        return true;
    }

    /*
     * Assign classes to lines.
     *
     * We process the lines in this order:
     *
     * row 0, row 1, row 2, row 3,
     * col 0, col 1, col 2, col 3
     *
     * Every required word-class must occupy one unique line.
     */
    static void dfs(int classIndex) {

        if (classIndex == words.size()) {

            char[][] grid = buildGrid();

            if (validGrid(grid)) {
                if (lexicographicallySmaller(grid, best)) {
                    best = grid;
                    found = true;
                }
            }

            return;
        }

        /*
         * Try putting the current word-class on every unused line.
         */
        for (int line = 0; line < 8; line++) {

            if (usedLine[line])
                continue;

            /*
             * Try both directions.
             */
            for (int orientation = 0; orientation < 2; orientation++) {

                if (!compatible(line, classIndex, orientation))
                    continue;

                lineWord[line] = classIndex;
                lineOrientation[line] = orientation;
                usedLine[line] = true;

                dfs(classIndex + 1);

                usedLine[line] = false;
                lineWord[line] = -1;
                lineOrientation[line] = -1;
            }
        }
    }

    /*
     * A more useful ordering:
     *
     * Put lexicographically smaller words first.
     * This improves pruning/comparison in practice.
     */
    static void sortWords() {
        words.sort((a, b) -> {
            int cmp = a.word.compareTo(b.word);

            if (cmp != 0)
                return cmp;

            return a.rev.compareTo(b.rev);
        });
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            /*
             * Remove duplicate words and words which are simply
             * reverses of one another.
             */
            Map<String, String> unique = new HashMap<>();

            for (int i = 0; i < n; i++) {
                String s = fs.next();

                String rev = reverse(s);
                String canonical = s.compareTo(rev) <= 0 ? s : rev;

                unique.put(canonical, canonical);
            }

            words = new ArrayList<>();

            for (String s : unique.keySet()) {
                words.add(new WordClass(s));
            }

            /*
             * More than 8 distinct word/reverse classes cannot fit
             * into the 8 lines of a 4x4 grid.
             */
            if (words.size() > 8) {

                out.append("grid\n");
                out.append("snot\n");
                out.append("poss\n");
                out.append("ible\n\n");

                continue;
            }

            sortWords();

            lineWord = new int[8];
            lineOrientation = new int[8];
            usedLine = new boolean[8];

            Arrays.fill(lineWord, -1);
            Arrays.fill(lineOrientation, -1);

            best = null;
            found = false;

            dfs(0);

            if (!found) {
                out.append("grid\n");
                out.append("snot\n");
                out.append("poss\n");
                out.append("ible\n\n");
            } else {
                for (int r = 0; r < 4; r++) {
                    out.append(best[r]);
                    out.append('\n');
                }

                out.append('\n');
            }
        }

        System.out.print(out);
    }
}