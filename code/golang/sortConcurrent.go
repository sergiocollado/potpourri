/* reference: https://yourbasic.org/golang/how-to-sort-in-go/ */

/*
Write a program to sort an array of integers. The program should partition the array into 4 parts,
each of which is sorted by a different goroutine. Each partition should be of approximately equal size.
Then the main goroutine should merge the 4 sorted subarrays into one large sorted array. 
Each goroutine which sorts 1/4 of the array should print the subarray that it will sort.
*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"sort"
	"sync"
)

var wg sync.WaitGroup
	
func routine(arr []int) {
    defer wg.Done()
	sort.Ints(arr)
	fmt.Println(arr)
	return
}

func main() {

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Print("Enter numbers seperated by space ")
	scanner.Scan()
	numbers := strings.Split(scanner.Text(), " ")

	array := make([]int, 0, len(numbers))
	for _, numStr := range numbers {
		num, _ := strconv.ParseInt(numStr, 10, 64)
		array = append(array, int(num))
	}
	
	
    var array_size int = len(numbers) / 4 
	
	arr1 := make([]int, array_size)	
	arr2 := make([]int, array_size)	
	arr3 := make([]int, array_size)	
	arr4 := make([]int, array_size + len(numbers)%4)
	
	arr1 = array[0:array_size]
	arr2 = array[array_size:2*array_size]	
	arr3 = array[2*array_size: 3*array_size]
	arr4 = array[3*array_size: len(numbers)]

	wg.Add(4)
	
	go routine(arr1)	
	go routine(arr2)	
	go routine(arr3)	
	go routine(arr4)

	wg.Wait()

	fmt.Println("\n")
	sort.Ints(array)
	
	fmt.Println(array)
}
