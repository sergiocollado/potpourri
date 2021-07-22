/**
 * Write a program which prompts the user to enter a floating point number and prints the integer which is a truncated version of the floating 
 * point number that was entered. Truncation is the process of removing the digits to the right of the decimal place.
**/

package main

import (
    "fmt"
    "log"
	"math"
)

func main() {
	fmt.Println("Hello, please, give me a floating number\n");
	var i float64 = 0
	if    _, err := fmt.Scan(&i);    err != nil {
		log.Print("  Scan for i failed, due to ", err)
		return
	}
	fmt.Println("The floating number trucated is:", math.Round(i))
}
	
