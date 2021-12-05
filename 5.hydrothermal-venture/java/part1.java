
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class part1 {

    private static final int N = 1000;

    private static int sign(int n) {
        return n > 0 ? 1 : n < 0 ? -1 : 0;
    }

    private static boolean before(int n, int e, int dx) {
        return dx < 0 ? n >= e : n <= e;
    }

    private static record Point(int x, int y) { }

    private static record Line(Point start, Point end) {

        public boolean isOrthogonal() {
            return start.x == end.x || start.y == end.y;
        }

        public List<Point> getPoints() {
            List<Point> list = new ArrayList<>();
            int dx = sign(end.x - start.x);
            int dy = sign(end.y - start.y);
            for (int x = start.x, y = start.y; before(x, end.x, dx) && before(y, end.y, dy); x += dx, y += dy) {
                list.add(new Point(x, y));
            }
            return list;
        }
    }

    public static void main(String[] args) {
        List<Line> lines = new ArrayList<>();
        Scanner scan = new Scanner(System.in);
        while (scan.hasNextLine()) {
            String line = scan.nextLine();
            String[] split = line.split(" -> ");
            String[] start = split[0].split(",");
            String[] end = split[1].split(",");
            lines.add(new Line(
                new Point(Integer.parseInt(start[0]), Integer.parseInt(start[1])),
                new Point(Integer.parseInt(end[0]), Integer.parseInt(end[1]))
            ));
        }
        scan.close();
        int[][] map = new int[N][N];
        for (Line l : lines) {
            if (l.isOrthogonal()) {
                for (Point p : l.getPoints()) {
                    map[p.x][p.y] += 1;
                }
            }
        }
        long danger = Arrays.stream(map)
            .flatMapToInt(Arrays::stream)
            .filter(i -> i >= 2)
            .count();
        System.out.println("Result: " + danger);
    }
}

