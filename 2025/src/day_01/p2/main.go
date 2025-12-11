package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strconv"
)

func main() {
	path := filepath.Join("./input.txt")

	f, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	// 0 defines that no empty string is initialized
	// otherwise an empty string will be initialized and will be appended
	// which leads to structures like " L58", " R395" etc.
	rotations := make([]string, 0, 4059)
	for scanner.Scan() {
		rotations = append(rotations, scanner.Text())
	}

	err = scanner.Err()
	if err != nil {
		log.Fatal(err)
	}

	dialPos := 50
	zeroCounter := 0
	for _, r := range rotations {
		direction := r[0]
		val, err := strconv.Atoi(r[1:])
		if err != nil {
			log.Fatal(err)
		}

		if direction == 'L' {
			val = -val
		}

		newPos := dialPos + val


		// if val < 0 {
		// 	div := val / -100
		// 	rem := val % -100
		// 	zeroCounter += div
		// 	if dialPos+rem <= 0 && (dialPos+rem)%100 != 0 {
		// 		zeroCounter += 1
		// 	}
		// } else {
		// 	div := val / 100
		// 	rem := val % 100
		// 	zeroCounter += div
		// 	if dialPos+rem >= 100 && (dialPos+rem)%100 != 0 {
		// 		zeroCounter += 1
		// 	}
		// }

		// if val < 0 {
		// 	div := val / -100
		// 	rem := val % -100
		// 	zeroCounter += div
		// 	if dialPos != 0 && dialPos+rem < 0 {
		// 		zeroCounter += 1
		// 	}
		// } else {
		// 	div := val / 100
		// 	rem := val % 100
		// 	zeroCounter += div
		// 	if dialPos+rem >= 100 {
		// 		zeroCounter += 1
		// 	}
		// }

		dialPos = newPos % 100
		if dialPos < 0 {
			dialPos += 100
		}

		if dialPos == 0 {
			zeroCounter++
		}
	}

	fmt.Printf("Solution: %d\n", zeroCounter)
}
