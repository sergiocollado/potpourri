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
	
	/* the exepected output would be count = 0, but that doesn't always happen.
     A race condition occurs when two goroutines access the same variable at same time and try to write it
	*/
	fmt.Println("count: ", count)
}
