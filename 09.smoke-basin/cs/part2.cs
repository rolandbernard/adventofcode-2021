
using System;
using System.Linq;
using System.Collections.Generic;

class part1 {

    static int[,] readInput() {
        string raw = Console.In.ReadToEnd();
        int[][] map = raw.Split('\n')
            .Where(line => line.Trim().Length != 0)
            .Select(line => line.ToCharArray().Select(val => val - '0').ToArray())
            .ToArray();
        int[,] padded = new int[map.Length + 2, map[0].Length + 2];
        for (int i = 0; i < map.Length; i++) {
            for (int j = 0; j < map[i].Length; j++) {
                padded[i + 1, j + 1] = map[i][j];
            }
        }
        for (int i = 0; i < padded.GetLength(0); i++) {
            padded[i, 0] = 9;
            padded[i, padded.GetLength(1) - 1] = 9;
        }
        for (int i = 0; i < padded.GetLength(1); i++) {
            padded[0, i] = 9;
            padded[padded.GetLength(0) - 1, i] = 9;
        }
        return padded;
    }

    static int measureBasin(int[,] map, int x, int y) {
        Queue<Tuple<int, int>> queue = new Queue<Tuple<int, int>>();
        queue.Enqueue(new Tuple<int, int>(x, y));
        int size = 0;
        while (queue.Count != 0) {
            Tuple<int, int> p = queue.Dequeue();
            if (map[p.Item1, p.Item2] != 9) {
                size++;
                map[p.Item1, p.Item2] = 9;
                queue.Enqueue(new Tuple<int, int>(p.Item1 - 1, p.Item2));
                queue.Enqueue(new Tuple<int, int>(p.Item1 + 1, p.Item2));
                queue.Enqueue(new Tuple<int, int>(p.Item1, p.Item2 - 1));
                queue.Enqueue(new Tuple<int, int>(p.Item1, p.Item2 + 1));
            }
        }
        return size;
    }

    static void Main() {
        int[,] map = readInput();
        List<int> basins = new List<int>();
        for (int i = 1; i < map.GetLength(0) - 1; i++) {
            for (int j = 1; j < map.GetLength(1) - 1; j++) {
                if (
                    map[i, j] < map[i - 1, j] && map[i, j] < map[i + 1, j]
                    && map[i, j] < map[i, j - 1] && map[i, j] < map[i, j + 1]
                ) {
                    basins.Add(measureBasin(map, i, j));
                }
            }
        }
        basins.Sort((a, b) => b - a);
        Console.WriteLine("Result: " + (basins[0] * basins[1] * basins[2]));
    }
}

