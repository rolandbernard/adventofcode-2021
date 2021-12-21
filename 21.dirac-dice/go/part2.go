package main

import (
	"bufio"
	"fmt"
	"os"
)

func universes(mem [][11][21][21][2][2]int64, pos [2]int, points [2]int, step int) [2]int64 {
	if points[0] >= 21 {
		return [2]int64{1, 0}
	} else if points[1] >= 21 {
		return [2]int64{0, 1}
	} else {
		cached := mem[pos[0]][pos[1]][points[0]][points[1]][step%2]
		if cached[0] == 0 && cached[1] == 0 {
			res := [2]int64{0, 0}
			for i := 1; i <= 3; i++ {
				for j := 1; j <= 3; j++ {
					for k := 1; k <= 3; k++ {
						var spl [2]int64
						new_pos := (pos[step%2]+i+j+k-1)%10 + 1
						if step%2 == 0 {
							spl = universes(mem, [2]int{new_pos, pos[1]}, [2]int{points[0] + new_pos, points[1]}, step+1)
						} else {
							spl = universes(mem, [2]int{pos[0], new_pos}, [2]int{points[0], points[1] + new_pos}, step+1)
						}
						res[0] += spl[0]
						res[1] += spl[1]
					}
				}
			}
			mem[pos[0]][pos[1]][points[0]][points[1]][step%2] = res
			return res
		} else {
			return cached
		}
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	player0, _ := reader.ReadString('\n')
	player1, _ := reader.ReadString('\n')
	var pos [2]int
	pos[0] = int(player0[len(player0)-2] - '0')
	pos[1] = int(player1[len(player1)-2] - '0')
	var mem [11][11][21][21][2][2]int64
	result := universes(mem[:], pos, [2]int{0, 0}, 0)
	if result[0] > result[1] {
		fmt.Println("Result:", result[0])
	} else {
		fmt.Println("Result:", result[1])
	}
}
