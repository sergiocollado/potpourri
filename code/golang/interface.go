package main

import (
    "fmt"
)

type Animal interface {
    Eat () 
    Move() 
    Speak()
}

type cow struct { name string }
func (v cow) Eat()   { fmt.Println("grass")  }
func (v cow) Move()  { fmt.Println("walk")   }
func (v cow) Speak() { fmt.Println("move")   }

type bird struct { name string }
func (v bird) Eat()   { fmt.Println("worms") }
func (v bird) Move()  { fmt.Println("fly")   }
func (v bird) Speak() { fmt.Println("peep")  }

type snake struct {name string }
func (v snake) Eat()   { fmt.Println("mice")    }
func (v snake) Move()  { fmt.Println("slither") }
func (v snake) Speak() { fmt.Println("hsss")    }

func main() {

	animalsMap:= make(map[string]Animal)
	
	for {
		fmt.Print(">")

		str1 := "0"
		str2 := "0"
		str3 := "0" 
		fmt.Scan(&str1, &str2, &str3)
	
		if (str1 == "newanimal") {
			switch str3 {
			case "cow": 
			    animalsMap[str2] = cow{ name:str2}
			    fmt.Println("Cow ", str2, "-Created it!\n")
			case "bird":
			    animalsMap[str2] = bird{ name:str2}
			    fmt.Println("Bird ", str2, "-Created it!\n")			
			case "snake":
			    animalsMap[str2] = snake{ name:str2}
				fmt.Println("Snake ", str2, "-Created it!\n")
			default: 
			    fmt.Println("unknwon animal type\n")
				return
			}
		} else if (str1 == "query") {
			switch str3 {
			case "eat": 
			    animalsMap[str2].Eat()
			case "move":
			    animalsMap[str2].Move()	
			case "speak":
			    animalsMap[str2].Speak()
			default: 
			    fmt.Println("unknwon animal name\n")
				return
			}
		} else {
		    fmt.Println("Unknown command\n")
		}

	}
}
