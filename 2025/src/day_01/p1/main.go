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

		fmt.Println(r, dialPos)
		// goddamn, before I used "dialPos := ..." by accident
		// this lead the variable to be out of scope at the end of each for loop iteration
		dialPos = (dialPos + val) % 100
		fmt.Printf("Before %d\n", dialPos)
		if dialPos < 0 {
			dialPos += 100
		}
		fmt.Printf("After %d\n", dialPos)

		if dialPos == 0 {
			zeroCounter++
		}
	}

	fmt.Printf("Solution: %d\n", zeroCounter)
}
