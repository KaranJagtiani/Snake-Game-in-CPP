# Snake Game in C++
Snake Game created using graphics.h library

![](images/menu.jpg)

![](images/in_game.png)

## Snake's body created using Doubly Linked List
![](images/snake_body.JPG)

i)	Traverse the list till the end using next pointer.

ii)	From the last node, traverse back to the head by using previous pointer, while copying
    
    head->x = head->prev->x
    head->y = head->prev->y
    
iii)	Now, we are back to the head node, display the squares by traversing back to the last node through next pointer.

iv)	Repeat the process till game is over, or game is complete, or ESC is pressed.

## Forest Fire Algorithm for polygon filling using Queue(Linked List)
![](images/flood_fill_working.jpg)
