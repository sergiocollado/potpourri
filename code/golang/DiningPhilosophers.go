/*
The classical Dining philosophers problem.
Implemented with chopsticks as mutexes.
*/

package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var wg sync.WaitGroup

type Chopstick struct{ sync.Mutex }

type Philosopher struct {
	id                  int
	leftChopstick, rightChopstick *Chopstick
}

func (p Philosopher) dine() {

    defer wg.Done()
	
	randomPause(1)

	p.leftChopstick.Lock()
	p.rightChopstick.Lock()

	say("eating", p.id)
	randomPause(3)
	say("finished eating", p.id)
	
	p.rightChopstick.Unlock()
	p.leftChopstick.Unlock()
}

func randomPause(max int) {
	time.Sleep(time.Millisecond * time.Duration(rand.Intn(max*1000)))
}

func say(action string, id int) {
	fmt.Printf("#%d is %s\n", id, action)
}

func init() {
	// Random seed
	rand.Seed(time.Now().UTC().UnixNano())
}

func min(x, y int) int {
    if x < y {
        return x
    }
    return y
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}

func main() {
	// How many philosophers and forks
	count := 5

	// Create chopsticks
	chopstick := make([]*Chopstick, count)
	for i := 0; i < count; i++ {
		chopstick[i] = new(Chopstick)
	}

    wg.Add(count)
	
	// Create philospoher, assign them 2 chopsticks
	philosophers := make([]*Philosopher, count)
	for i := 0; i < count; i++ {
		philosophers[i] = &Philosopher{
			id: i, leftChopstick: chopstick[min(i, (i+1)%count)], rightChopstick: chopstick[max(i, (i+1)%count)]}
			
	    // let's begin the dinner
		go philosophers[i].dine()
	}
	
	wg.Wait()

    fmt.Println("\nDiner finished\n")

}
