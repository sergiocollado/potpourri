package main

import (
    "time"
    "fmt"	
)

var count int

func raceIncr() {
    count++
}

func raceDecr() {
    count--
}

func main() {
	
	for a := 0; a < 1000; a++ {
      go raceIncr() 
	  go raceDecr()
    }
	
    time.Sleep(1 * time.Second)
	
	/* the exepected output would be count = 0
	   but that doen't always happen
	   
	   A race condition occurs when multiple threads/processes/routines try to access
	   and modify the same data. So one overwrites the value of other, resulting in
	   an incorrect value. 
	   Race conditions arise, in the knwons in software as Critical-Sections witch 
	   are code that fits to RUW: read-update-write. For example: i = i+1. 
	   
	   routine1         routine2
	   read i = 0   
	                    read i = 0
	   increm i+1 = 1
	                    imcrem i+1 = 1
	   write 1 
	                    write 1 // this overwrites the resulting
	
	   we would be expecting 2 as a result, but we got 1, because the order of the routines.
	*/
	fmt.Println("count: ", count)
}
