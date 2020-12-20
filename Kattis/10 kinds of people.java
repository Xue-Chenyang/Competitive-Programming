import java.util.Arrays;
import java.util.Scanner;

public class Solution {

    private static int find(int coor, int[] tree) {
        while (coor != tree[coor]) {
            coor = tree[coor];
        }
        return coor;
    }

    private static void unite(int a, int b, int[] tree, int[] count) {
        a = find(a, tree);
        b = find(b, tree);
        if (count[a] < count[b]) {
            count[b] += count[a];
            tree[a] = b;
        } else {
            count[a] += count[b];
            tree[b] = a;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();
        int rows = Integer.parseInt(line.split(" ")[0]);
        int cols = Integer.parseInt(line.split(" ")[1]);
        int[] tree = new int[rows * cols];
        int[] count = new int[rows * cols];
        boolean[][] map = new boolean[rows][cols];
        for (int i = 0; i < rows; i ++) {
            line = scanner.nextLine();
            for (int j = 0; j < cols; j ++) {
                if (line.charAt(j) == '1') {
                    map[i][j] = true;
                } else {
                    map[i][j] = false;
                }
                tree[i * cols + j] = i * cols + j;
                count[i * cols + j] = 1;
            }
        }
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                if ((j < cols - 1) && (map[i][j + 1] == map[i][j])) {
                    unite(i * cols + j, i * cols + j + 1, tree, count);
                }
                if ((i < rows - 1) && (map[i + 1][j] == map[i][j])) {
                    unite(i * cols + j, (i + 1) * cols + j, tree, count);
                }
            }
        }
        line = scanner.nextLine();
        int num = Integer.parseInt(line);
        for (int i = 0; i < num; i ++) {
            line = scanner.nextLine();
            int[] data = Arrays.asList(line.split(" ")).stream().mapToInt((String s) -> (Integer.parseInt(s))).map((int k) -> (k -1)).toArray();
            if (find((data[0]) * cols + data[1], tree) == find((data[2]) * cols + data[3], tree)) {
                if (map[data[0]][data[1]]) {
                    System.out.println("decimal");
                } else {
                    System.out.println("binary");
                }
            } else {
                System.out.println("neither");
            }
        }
    }
}
