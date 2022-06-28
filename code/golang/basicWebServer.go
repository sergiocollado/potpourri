// basic web server in golang
// in Go, with the basic language we can implement a basic web server
// if we do: curl localhost:8080/hello, we should receive the answer Hello World!. 
// in the web browser it should work also.

package main

import (
     "net/http"
)

func main() {
    http.HandleFunc("/hello", func(writer http.ResponseWriter, request *http.Request) { 
	    writer.Write([]byte("hello World!"))
	})
	
	if err := http.ListenAndServe(":8080", nil); err != nil {
	    panic(err)
	}
}
