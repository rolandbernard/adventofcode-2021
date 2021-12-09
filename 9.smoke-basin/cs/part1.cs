
using System;
using System.Linq;
using System.Collections;

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

    static void Main() {
        int[,] map = readInput();
        int count = 0;
        for (int i = 1; i < map.GetLength(0) - 1; i++) {
            for (int j = 1; j < map.GetLength(1) - 1; j++) {
                if (
                    map[i, j] < map[i - 1, j] && map[i, j] < map[i + 1, j]
                    && map[i, j] < map[i, j - 1] && map[i, j] < map[i, j + 1]
                ) {
                    count += map[i, j] + 1;
                }
            }
        }
        Console.WriteLine("Result: " + count);
    }
}

