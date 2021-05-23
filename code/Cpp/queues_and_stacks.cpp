#include <iostream>
#include <stack>
#include <queue>

std::stack<int> reverse_stack(std::stack<int> s) {
  std::stack<int> reversed_s;
  int size = s.size();
  for( size_t i = 0; i < size; ++i) {
    reversed_s.push(s.top());
    s.pop();
  }
  // write code here that returns a stack whose elements are
  // in reverse order from those in stack s
  
  return reversed_s;
}

std::queue<int> reverse_queue(std::queue<int> q) {
  std::queue<int> reversed_q;
  
  // write code here that returns a queue whose elements are
  // in reverse order from those in queue q
  int size = q.size();
  std::stack<int> s; 
  for(size_t i = 0; i < size; ++i) {
    s.push(q.front());
    q.pop();
  }
  for(size_t i=0; i < size; ++i) {
    reversed_q.push(s.top());
    s.pop();
  }
  return reversed_q;
}

void print_stack(std::string name, std::stack<int> s) {
  std::cout << "stack " << name << ": ";
  while (!s.empty()) {
    std::cout << s.top() << " ";
    s.pop();
  }
  std::cout << std::endl;
}

void print_queue(std::string name, std::queue<int> q) {
  std::cout << "queue " << name << ": ";
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main() {
  std::stack<int> s, rs;
  std::queue<int> q, rq;
  
  s.push(1); s.push(2); s.push(3); s.push(4); s.push(5);

  print_stack("s",s);

  rs = reverse_stack(s);

  print_stack("reversed s",rs);
  
  q.push(1); q.push(2); q.push(3); q.push(4); q.push(5);
  
  print_queue("q",q);
  
  rq = reverse_queue(q);
  
  print_queue("reversed q",rq);

  return 0;
}

/*
stack s: 5 4 3 2 1 
stack reversed s: 1 2 3 4 5 
queue q: 1 2 3 4 5 
queue reversed q: 5 4 3 2 1 
*/
