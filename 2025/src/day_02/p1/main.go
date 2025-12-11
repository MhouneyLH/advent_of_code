package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

func main() {
	path := filepath.Join("../input.txt")

	f, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	scanner.Scan()
	line := scanner.Text()

	type Range struct {
		start int
		end   int
	}

	idRanges := strings.Split(line, ",")
	var ranges []Range
	for _, r := range idRanges {
		temp := strings.Split(r, "-")
		start, _ := strconv.Atoi(temp[0])
		end, _ := strconv.Atoi(temp[1])
		var ran Range = Range{
			start: start,
			end:   end,
		}
		ranges = append(ranges, ran)
	}

	fmt.Println(ranges)

	var invalidIds []int
	for _, r := range ranges {
		for id := r.start; id <= r.end; id++ {
			var c string = strconv.Itoa(id)
			mid := len(c) / 2
			// number of digits must be even so that we can split nicely
			if len(c)%2 != 0 {
				continue
			}

			var invalid bool = true
			for i := 0; i < mid; i++ {
				e1 := c[i]
				e2 := c[i+mid]
				if e1 != e2 {
					invalid = false
				}
			}

			if invalid {
				invalidIds = append(invalidIds, id)
			}
		}
	}

	fmt.Println("Invalid ids")
	fmt.Println(invalidIds)

	var sum int = 0
	for _, id := range invalidIds {
		sum += id
	}

	fmt.Printf("Sum of invalid ids: %d\n", sum)
}
