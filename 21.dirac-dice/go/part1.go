package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	player0, _ := reader.ReadString('\n')
	player1, _ := reader.ReadString('\n')
	var pos [2]int
	pos[0] = int(player0[len(player0)-2] - '0')
	pos[1] = int(player1[len(player1)-2] - '0')
	points := []int{0, 0}
	step := 0
	for points[0] < 1000 && points[1] < 1000 {
		new_pos := (pos[step%2]+9*step+5)%10 + 1
		pos[step%2] = new_pos
		points[step%2] += new_pos
		step += 1
	}
	var result int
	if points[0] > points[1] {
		result = 3 * step * points[1]
	} else {
		result = 3 * step * points[0]
	}
	fmt.Println("Result:", result)
}
