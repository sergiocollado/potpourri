/*
Write a program which prompts the user to enter integers and stores the integers 
in a sorted slice. The program should be written as a loop. Before entering the loop,
 the program should create an empty integer slice of size (length) 3. During each pass
 through the loop, the program prompts the user to enter an integer to be added to the slice.
 The program adds the integer to the slice, sorts the slice, and prints the contents of
 the slice in sorted order. The slice must grow in size to accommodate any number of
 integers which the user decides to enter. The program should only quit (exiting the loop)
 when the user enters the character ‘X’ instead of an integer.
*/

/* reference: https://gobyexample.com/slices */

package main

import (
    "fmt"
    "log"
	"strings"
	"strconv"
    "sort"
)

func main() {

    sli := make([]int, 0, 3)
	var numString string
	
	fmt.Println("Hello")

    for  {	
	fmt.Println("... please, give me a number\n");
	var input string
	if    _, err := fmt.Scan(&input);    err != nil {
		log.Println("Scan for input failed, due to ", err)
		return
	}
	
	if strings.Compare(input, "X") == 0 {
		fmt.Println("\n>> " + numString)
		fmt.Println("Bye")
		return
	}
	
	value, err := strconv.Atoi(input) 
	 
	if err != nil {
		log.Println("Scan for input failed, due to ", err)
		continue
	}

    sli = append(sli, value) 
	sort.Ints (sli)
	
	numString = ""
	
    for _, v := range sli {
		numString = numString + strconv.Itoa(v) + " "
    }
	
	fmt.Println(numString)
		
	} //end of for-loop 

	return
}
