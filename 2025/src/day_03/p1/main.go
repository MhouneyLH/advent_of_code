package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
)

func main() {
	path := filepath.Join("../input.txt")

	f, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	var highestJoltages []int
	for scanner.Scan() {
		var bank string = scanner.Text()

		var bankInt []int
		for _, cStr := range bank {
			c, _ := strconv.Atoi(string(cStr))
			bankInt = append(bankInt, c)
		}

		maxJoltage := 0
		for i := 0; i < len(bankInt); i++ {
			for j := i + 1; j < len(bankInt); j++ {
				joltageStr := strconv.Itoa(bankInt[i]) + strconv.Itoa(bankInt[j])
				joltage, _ := strconv.Atoi(joltageStr)

				if joltage > maxJoltage {
					maxJoltage = joltage
				}
			}
		}

		highestJoltages = append(highestJoltages, maxJoltage)
	}

	fmt.Println(highestJoltages)

	var sum int = 0
	for _, id := range highestJoltages {
		sum += id
	}

	fmt.Printf("Joltage sum: %d\n", sum)
}
