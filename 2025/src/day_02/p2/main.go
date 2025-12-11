package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/dlclark/regexp2"
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
		ranges = append(ranges, Range{start, end})
	}

	// \d keep capturing digits -> capture group
	// \1 possible to match capture group 1 many possible times
	// sadly the standard library regexp does not support back references
	var pattern *regexp2.Regexp = regexp2.MustCompile(`^(\d+)\1+$`, regexp2.None)

	var invalidIds []int
	for _, r := range ranges {
		for id := r.start; id <= r.end; id++ {
			var c string = strconv.Itoa(id)

			if isMatch, _ := pattern.MatchString(c); isMatch {
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
