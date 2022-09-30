/**
 * CSC A48 - Intro to Computer Science II, Summer 2020
 * 
 * This is the program file where you will implement your solution for
 * assignment 1. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will need to have read the handout carefully. Parts where you have to 
 * implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive and will
 * check that your solution is *correct*, not only that it provides 
 * functionality.
 * 
 * Developed by Mustafa Quraish for CSCA48
 * (c) Mustafa Quraish 2020
 */
#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 *
 *  - loop_head  : A pointer to a struct of the same type. This will be the head
 *              of the linked list of commands that are in the loop. It
 *              should be set to NULL for commands of any other type.
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode {
    
    char cmd[10];
    int val;
    struct cmdnode *loop_head;
    struct cmdnode *next;
    
} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */
    
    if (strcmp("backward", cmd) == 0 || strcmp("forward", cmd) == 0 || strcmp("pendown", cmd) == 0 || strcmp("colour", cmd) == 0 || strcmp("penup", cmd) == 0 || strcmp("right", cmd) == 0 || strcmp("left", cmd) == 0 || strcmp("loop", cmd) == 0) {
        
        CmdNode *new_node = NULL;
        new_node = (CmdNode *)calloc(1, sizeof(CmdNode));
        
        strcpy(new_node->cmd, cmd);
        new_node->val = val;
        new_node->loop_head = NULL;
        new_node->next = NULL;

        return new_node;
    }
    
    printf("Invalid command.\n");
    return NULL;
    
}

/*---------------------------------------------------------------------------*/

void insertCommandLoop(CmdNode *loop_node, CmdNode *new_node)  {
    /**
     * This function will be used to insert a command at the end of the linked list
     * for a 'loop' node. It will take in 2 parameters, the first will be a pointer to
     * the loop node, and the second will be a pointer to the new command node
     * that you have to insert into the loop. This function should not return anything,
     * but just update the linked list at the loop node.
     *
     * TODO: Implement this function
     */
    
    if (loop_node == NULL) {
        return;
    }
    
    // Inserting at head of loop
    if (loop_node->loop_head == NULL) {
        loop_node->loop_head = new_node;
        return;
    }
    
    // New node has invalid command
    if (new_node == NULL) {
        return;
    }
    
    
    CmdNode *ptr = NULL;
    ptr = loop_node->loop_head;
    
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    
    ptr->next = new_node;
    new_node->next = NULL;
    
    return;
}


void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */
    
    int c = 0;
    CmdNode *ptr = NULL;
    CmdNode *loop_ptr = NULL;
    ptr = head;
    
    while (ptr != NULL) {
        if (strcmp(ptr->cmd, "forward") == 0 || strcmp(ptr->cmd, "backward") == 0 || strcmp(ptr->cmd, "colour") == 0 || strcmp(ptr->cmd, "loop") == 0) {
            printf("%d: %s %d\n", c, ptr->cmd, ptr->val);
        } else {
            printf("%d: %s\n", c, ptr->cmd);
        }
        
        c++;
        
        if (ptr->loop_head != NULL) {
            loop_ptr = ptr->loop_head;
            
            while (loop_ptr != NULL) {
                if (strcmp(loop_ptr->cmd, "forward") == 0 || strcmp(loop_ptr->cmd, "backward") == 0 || strcmp(loop_ptr->cmd, "colour") == 0 || strcmp(loop_ptr->cmd, "loop") == 0) {
                    printf("%d:   %s %d\n", c, loop_ptr->cmd, loop_ptr->val);
                } else {
                    printf("%d:   %s\n", c, loop_ptr->cmd);
                }

                c++;
                loop_ptr = loop_ptr->next;
            }
            
        }
        
        ptr = ptr->next;

    }
    
    return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */
    
    int c = 0;
    CmdNode *ptr = NULL;
    CmdNode *loop_ptr = NULL;
    ptr = head;
    
    while (ptr != NULL) {
        
        if (strcmp(ptr->cmd, cmd) == 0) {
            printf("%d: %s %d\n", c, ptr->cmd, ptr->val);
        }
        
        c++;
        
        if (ptr->loop_head != NULL) {
            loop_ptr = ptr->loop_head;
            
            while (loop_ptr != NULL) {
                if (strcmp(loop_ptr->cmd, cmd) == 0) {
                    printf("%d:   %s %d\n", c, loop_ptr->cmd, loop_ptr->val);
                }
                
                c++;
                loop_ptr = loop_ptr->next;
            }
        }
        
        ptr = ptr->next;

    }
    
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */
    
    int c = 0;
    CmdNode *ptr = NULL;
    ptr = head;
    CmdNode *loop_ptr = NULL;
    
    while (ptr != NULL) {
        if (ptr->loop_head != NULL) {
            loop_ptr = ptr->loop_head;
            
            while (loop_ptr != NULL) {
                c++;
                loop_ptr = loop_ptr->next;
            }
        }
        
        c++;
        ptr = ptr->next;
    }
    
  return c;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */
    
    if (head == NULL) {
        head = new_CmdNode;
        return head;
    }
    
    // New node has invalid command
    if (new_CmdNode == NULL) {
        return head;
    }
    
    CmdNode *ptr = NULL;
    ptr = head;
    
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    
    ptr->next = new_CmdNode;
    new_CmdNode->next = NULL;
    
    return head;
}

/*---------------------------------------------------------------------------*/

CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */
    
    CmdNode *cur = head;
    CmdNode *next;
    
    if (head == NULL) {
        return NULL;
    }
    
    while (cur != NULL)
    {
        if (cur->loop_head != NULL) {
            CmdNode *loop_cur = cur->loop_head;
            CmdNode *loop_next;
            
            loop_next = loop_cur->next;
            free(loop_cur);
            loop_cur = loop_next;
        }
        
        next = cur->next;
        free(cur);
        cur = next;
    }
    
    head = NULL;
    
    return head;
}

/*---------------------------------------------------------------------------*/

void updateDirection(char *ptr, char direction[6]) {
    if (*ptr == 'R') {
        if (strcmp("left", direction) == 0) {
            *ptr = 'U';
        } else if (strcmp("right", direction) == 0) {
            *ptr = 'D';
        }
    }
    
    else if (*ptr == 'L') {
        if (strcmp("left", direction) == 0) {
            *ptr = 'D';
        } else if (strcmp("right", direction) == 0) {
            *ptr = 'U';
        }
    }
    
    else if (*ptr == 'U') {
        if (strcmp("left", direction) == 0) {
            *ptr = 'L';
        } else if (strcmp("right", direction) == 0) {
            *ptr = 'R';
        }
    }
    
    else if (*ptr == 'D') {
        if (strcmp("left", direction) == 0) {
            *ptr = 'R';
        } else if (strcmp("right", direction) == 0) {
            *ptr = 'L';
        }
    }
    
}

/*---------------------------------------------------------------------------*/

void run_helper(Image *im, CmdNode *ptr, int *endX, int *endY, int *pen, int *colour, char *direction, int coordinates[2]) {
    
    if (strcmp("penup", ptr->cmd) == 0) {
        *pen = 1;
    }
    
    else if (strcmp("pendown", ptr->cmd) == 0) {
        *pen = 0;
    }
    
    else if (strcmp("colour", ptr->cmd) == 0) {
        if (ptr->val < 0) {
            *colour = 0;
        }

        else if (ptr->val > 255) {
            *colour = 255;
        }

        else {
        *colour = ptr->val;
        }
    }
    
    else if (strcmp("right", ptr->cmd) == 0) {
        updateDirection(direction, "right");
    }
    
    else if (strcmp("left", ptr->cmd) == 0) {
        updateDirection(direction, "left");
    }
    
    else if (strcmp("forward", ptr->cmd) == 0) {
        if (*direction == 'R') {
            
            *endX = coordinates[0] + ptr->val;
            if (*endX >= SIZEX) {
                *endX = SIZEX - 1;
            }
            else if (*endX < 0) {
                *endX = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[0] = *endX;
        }
        
        else if (*direction == 'L') {
            
            *endX = coordinates[0] - ptr->val;
            if (*endX >= SIZEX){
                *endX = SIZEX - 1;
            }
            else if (*endX < 0) {
                *endX = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[0] = *endX;
        }
        
        else if (*direction == 'U') {
            
            *endY = coordinates[1] - ptr->val;
            if (*endY >= SIZEY) {
                *endY = SIZEY - 1;
            }
            else if (*endY < 0) {
                *endY = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[1] = *endY;
        }
        
        else if (*direction == 'D') {
            
            *endY = coordinates[1] + ptr->val;
            if (*endY >= SIZEY) {
                *endY = SIZEY - 1;
            }
            else if (*endY < 0) {
                *endY = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[1] = *endY;
        }
    }
    
    else if (strcmp("backward", ptr->cmd) == 0) {
        if (*direction == 'L') {
            
            *endX = coordinates[0] + ptr->val;
            if (*endX >= SIZEX){
                *endX = SIZEX - 1;
            }
            else if (*endX < 0) {
                *endX = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[0] = *endX;
        }
        
        else if (*direction == 'R') {
            
            *endX = coordinates[0] - ptr->val;
            if (*endX >= SIZEX){
                *endX = SIZEX - 1;
            }
            else if (*endX < 0) {
                *endX = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[0] = *endX;
        }
        
        else if (*direction == 'D') {
            
            *endY = coordinates[1] - ptr->val;
            if (*endY >= SIZEY) {
                *endY = SIZEY - 1;
            }
            else if (*endY < 0) {
                *endY = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[1] = *endY;
        }
        
        else if (*direction == 'U') {
            
            *endY = coordinates[1] + ptr->val;
            if (*endY >= SIZEY) {
                *endY = SIZEY - 1;
            }
            else if (*endY < 0) {
                *endY = 0;
            }
            
            if (*pen == 0) {
                drawLine(im, coordinates[0], coordinates[1], *endX, *endY, *colour);
            }
            coordinates[1] = *endY;
        }
        
    }
}

/*---------------------------------------------------------------------------*/

void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   * 
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   *
   * We have already implemented a drawLine() function (in imgUtils.c) which
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */
    
    if (im == NULL) {
        return;
    }
    
    CmdNode *ptr = NULL;
    CmdNode *loop_ptr = NULL;
    ptr = head;
    
    int pen = 0; // 0: pendown, 1: penup
    
    int colour = 0; // same as ptr->val;
    
    char direction = 'R'; // 'R': right, 'L': left, 'U': up, 'D': down
    // use updateDirection(&direction, 'left'/'right');

    int coordinates[2] = {0, 0}; // [x, y]
    
    while (ptr != NULL) {
        run_helper(im, ptr, endX, endY, &pen, &colour, &direction, coordinates);
        
        if (ptr->loop_head != NULL) {
            
            for (int i = 1; i <= ptr->val; i++) {
                loop_ptr = ptr->loop_head;
                while (loop_ptr != NULL) {
                    run_helper(im, loop_ptr, endX, endY, &pen, &colour, &direction, coordinates);
                    loop_ptr = loop_ptr->next;
                }
            }
        }
        
        ptr = ptr->next;
    }

  return;
}

/*---------------------------------------------------------------------------*/
// All done!
