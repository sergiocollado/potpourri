/* 
Write a program which reads information from a file and represents it in a 
slice of structs. Assume that there is a text file which contains a series of names.
Each line of the text file has a first name and a last name, in that order, 
separated by a single space on the line. 
 
The program should prompt the user for the name of the text file. The program will
 successively read each line of the text file and create a struct which contains the
 first and last names found in the file. Each struct created will be added to a slice,
 and after all lines have been read from the file, your program will have a slice
 containing one struct for each line in the file. After reading all lines from the file,
 your program should iterate through your slice of structs and print the first and
 last names found in each struct.
*/

package main

import (
    "fmt"
    "log"
	  "strings"
	  "io/ioutil"
	  "bufio"
	  "os"
	  "io"
)

var p = fmt.Println

func main() {

    const maxLength int = 20
	type person struct {
		fname string
		lname string	
	}

    //hardcoded file writting 
	dataSlice := []byte("Dumitru Margareta\n Corneliu Leopold\n Blanca Karol\n Aeon Ignatius\n Raphael Maria\n Niketas Ἄγγελος\n Shilage Mihaly\n Сергей Злата\n Καλλιόπη Λεωνίδας")
    err := ioutil.WriteFile("names.txt", dataSlice, 0644)
	if err != nil {
        panic(err)
    }

	fmt.Println("Hello, please, the name of the file (ie: names.txt):\n");
	var fileName string
	
	if  _, err := fmt.Scan(&fileName);    err != nil {
		log.Println("failed for file: " + fileName, err)
		return
	}
	
	fileName = "names.txt"
	fileHandler, err := os.Open(fileName)
	if err != nil {
		fmt.Printf("error opening file: " + fileName + "%v\n",err)
		os.Exit(1)
	} else {
	    fmt.Printf("opened file: " + fileName);
	}
	defer fileHandler.Close()
	
	
	reader := bufio.NewReader(fileHandler)
	var fname string //first name
	var lname string //last name
	sli := make([]person, 0, 3)
		
	// reading file loop
	for {
	
		line, err := reader.ReadString(10) // 0x0A separator (10) = newline
		
		for i,v := range strings.Fields(line)  {
			if i==0 { fname=v }
			if i==1 { lname=v }
		}
		
		// limit the string length to 20 runes
		if len(fname) > maxLength { lname = lname[:maxLength] }
		if len(lname) > maxLength { lname = fname[:maxLength] }
		
		sli = append(sli, person{fname:fname, lname:(lname)})
		
		if err == io.EOF {
		  // do something here
		  break
		} else if err != nil {
		  fmt.Println(err)
		  return
		}
		
	} //end reading for-loop
	
	
	fmt.Printf("\n...\n")
	
	// print the contents of the file
	for _, v := range sli {
		fmt.Println(v)
    }
	
	fmt.Printf("\n")
	return
}
