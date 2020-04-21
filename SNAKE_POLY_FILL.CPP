// Flood-Fill (Forest Fire) Polygon Filling Implementation
typedef struct queue Queue;

struct queue{
	int x, y;
	Queue *next;
};

void enQueue(Queue **head, int x, int y){
	//cout << "\nIn EnQueue";
	Queue *n = new Queue;
	n->x = x, n->y = y;
	n->next = NULL;
	if(!(*head))
		*head = n;
	else{

		Queue *temp = *head;
		while(temp->next)
			temp = temp->next;
		temp->next = n;

		//n->next = *head;
		//*head = n;
	}
}

Queue *deQueue(Queue **head){
	Queue *n = *head;
	(*head) = (*head)->next;
	return n;
}

int inQueue(Queue *root, int x, int y){
	Queue *head = root;
	while(head){
		 if(x == head->x && y == head->y)
			return 1;
		 head = head->next;
	}
	return 0;
}

void fillPoly(int xc, int yc, int colorToAdd, int colorToRemove){
	int currColor, colorBool;
	Queue *head = NULL, *r;
	enQueue(&head, xc, yc);
	// Queue Not Empty
	while(head){
		r = deQueue(&head);
		colorBool = getpixel(r->x, r->y) == colorToRemove;

		if(r){ // i.e Not Null
			putpixel(r->x, r->y, colorToAdd);
		}
		if(colorBool){
			if(!inQueue(head, r->x+1, r->y))
				enQueue(&head, r->x+1, r->y);
			if(!inQueue(head, r->x-1, r->y))
				enQueue(&head, r->x-1, r->y);
			if(!inQueue(head, r->x, r->y+1))
				enQueue(&head, r->x, r->y+1);
			if(!inQueue(head, r->x, r->y-1))
				enQueue(&head, r->x, r->y-1);
		}
		delete r;
	}
}

void drawSquare(int xc, int yc, int color, int box_size){
	int bs = box_size/2;
	dda(xc-bs, yc-bs, xc+bs, yc-bs, color);
	dda(xc+bs, yc-bs, xc+bs, yc+bs, color);
	dda(xc+bs, yc+bs, xc-bs, yc+bs, color);
	dda(xc-bs, yc+bs, xc-bs, yc-bs, color);
}