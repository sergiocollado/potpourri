/*
 Write a program which prompts the user to enter a string.
 The program searches through the entered string for the characters ‘i’, ‘a’, and ‘n’. 
 and should print “Found!” if the entered string starts with the character ‘i’,
 ends with the character ‘n’, and contains the character ‘a’. Otherwise, should 
 print “Not Found!”. 
 The program should not be case-sensitive, so it does not matter if the characters are upper-case or lower-case.
*/
/* The program should print “Found!” for the following example entered strings,
 “ian”, “Ian”, “iuiygaygn”, “I d skd a efju N”. The program should print “Not Found!”
 for the following strings, “ihhhhhn”, “ina”, “xian”
*/
/* reference: https://gobyexample.com/string-functions */
/* reference: https://blog.golang.org/strings */
/* reference: https://pkg.go.dev/strings */

package main

import (
    "fmt"
    "log"
	"strings"
)

var p = fmt.Println

func main() {

	fmt.Println("Hello, please, give me a string\n");
	var input string
	if    _, err := fmt.Scan(&input);    err != nil {
		log.Println("Scan for input failed, due to ", err)
		return
	}
	
	var inputTrimmed string = strings.TrimSpace(input)
 
    fmt.Println(">>" + inputTrimmed);
	
    if (strings.HasPrefix(strings.ToLower(inputTrimmed), "i")  && strings.HasSuffix (strings.ToLower(inputTrimmed), "n") && strings.Contains(strings.ToLower(inputTrimmed), "a")) {
		fmt.Println("Found")
	} else {
		fmt.Println("Not found!")
	}
	
}
