
package main

/* reference: https://pkg.go.dev/std */

import (
    "fmt"
	"os"
	"bufio"
    "strings"	
)

type Animal struct {

   food       string
   locomotion string
   noise      string
}

func (a Animal) Eat() {
    fmt.Println(a.food)
}

func (a Animal) Move() {
    fmt.Println(a.locomotion)
}

func (a Animal) Speak() {
    fmt.Println(a.noise)
}


func main() {

	animalsMap:= make(map[string]Animal)
	
	var cow   Animal = Animal{ food: "grass", locomotion: "walk"   , noise: "moo" }
	var bird  Animal = Animal{ food: "worms", locomotion: "fly"    , noise: "peep"}	
	var snake Animal = Animal{ food: "mice" , locomotion: "slither", noise: "hsss"}

	animalsMap["cow"]   = cow
	animalsMap["bird"]  = bird
	animalsMap["snake"] = snake
	
	var animalName string
	var animalMethod string

	fmt.Printf("\nInput a wrong animal to end the program\n")	
	fmt.Printf("\nYou can request an animal (cow, bird, snake) and a method (eat, move, speak)\n\n")		
	for { 

		fmt.Printf("\nRequest the animal and method\n>")
		
		reader := bufio.NewReader(os.Stdin)
		answer1, _   := reader.ReadString(' ')
		answer2, _   := reader.ReadString('\n')
		animalName   =  strings.ToLower(strings.ReplaceAll(answer1, " ", ""))
		animalMethod =  strings.ToLower(strings.TrimRight(strings.TrimRight(answer2, "\n"), "\r"))
		
		//fmt.Printf(animalName)
		//fmt.Printf(animalMethod)
		fmt.Printf("\n")
		
		myAnimal, exists := animalsMap[animalName]	
		if exists == false {
			fmt.Println("The requested animal doesn't exist")
			return
		}
		
		if strings.Compare(animalMethod, "eat") == 0   { myAnimal.Eat()   }
		if strings.Compare(animalMethod, "move") == 0  { myAnimal.Move()  }		
		if strings.Compare(animalMethod, "speak") == 0 { myAnimal.Speak() }		
    }
}
	
