// Fatih Baskın
// 150210710

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Recursive function for left process.
void left_process(int);

// Recursive function for right process.
void right_process(int, int);

int main()
{
    // This program creates process tree in preorder traversal.
    // First prints the root, then left subtree then right subtree.

    // Get n value. (n >= 0)
    int n;
    do
    {
        printf("Please provide a n value which is greater than or equal to zero: ");
        scanf("%d", &n);
    } while (n < 0);

    // Get m value. (m >= 0)
    int m;
    do
    {
        printf("Please provide a m value which is greater than or equal to zero: ");
        scanf("%d", &m);
    } while (m < 0);

    // Print root (main) process.
    printf("This is the root process, pid:%d.\n", (int)getpid());

    // Fork value, this will be the return value of fork() system call.
    int fork_val;

    // If m > 0, proceed for left process. Otherwise skip left process.
    if (m > 0)
    {
        fork_val = (int)fork();
        if (fork_val < 0)
        {
            // Print an error message if process can't be created.
            fprintf(stderr, "There was an error while forking left process for pid:%d.\n", (int)getpid());
        }
        else if (fork_val > 0)
        {
            // If this is the parent process, then wait for child process to end.
            wait(NULL);
        }
        else
        {
            // If this the child process, continue as a left child then terminate.
            left_process(m);
            exit(EXIT_SUCCESS);
        }
    }

    // If n > 0, proceed for right process. Otherwise terminate the program. (return EXIT_SUCCESS)
    if (n == 0)
        return EXIT_SUCCESS;

    // Since we are moving below in the tree, we need to fork a child process for right process and make current process wait.
    fork_val = (int)fork();

    if (fork_val < 0)
    {
        // Print an error message if process can't be created.
        fprintf(stderr, "There was an error while forking a right process for pid:%d.\n", (int)getpid());
    }
    else if (fork_val > 0)
    {
        // If this is the parent process, then wait for child process to end.
        wait(NULL);
    }
    else
    {
        // If this the child process, continue as a right process then terminate.
        right_process(n, m);
        exit(EXIT_SUCCESS);
    }
    // At the end of the program, terminate. (return EXIT_SUCCESS)
    return EXIT_SUCCESS;
}

void left_process(int m)
{
    // First, print details of the current process.
    printf("This is a left child process, m:%d, pid:%d, ppid:%d.\n", m, (int)getpid(), (int)getppid());

    // Decrement m, since this tree is reducible into subtrees, m value for the below left process is m-1.
    m = m - 1;

    // If the decremented m is 0, there is no need to proceed further, terminate the current process.
    if (m == 0)
        exit(EXIT_SUCCESS);

    int fork_val = (int)fork();
    if (fork_val < 0)
    {
        // Print an error message if process can't be created.
        fprintf(stderr, "There was an error while forking left process for pid:%d.\n", (int)getpid());
    }
    else if (fork_val > 0)
    {
        // If this is the parent process, then wait for child process to end.
        wait(NULL);
    }
    else
    {
        // If this the child process, continue as a left child then terminate.
        left_process(m);
        exit(EXIT_SUCCESS);
    }
    // At the end of the function, terminate the current process.
    exit(EXIT_SUCCESS);
}

void right_process(int n, int m)
{
    // First, print some dashes to seperate current right processes from its parent.
    printf("---\n");

    // Then print details of the current process.
    printf("This is a right child process, n:%d, pid:%d, ppid:%d.\n", n, (int)getpid(), (int)getppid());

    // Fork value, this will be the return value of fork() system call.
    int fork_val;

    // If m > 0, proceed for left process. Otherwise skip left process.
    if (m > 0)
    {
        fork_val = (int)fork();
        if (fork_val < 0)
        {
            // Print an error message if process can't be created.
            fprintf(stderr, "There was an error while forking left process for pid:%d.\n", (int)getpid());
        }
        else if (fork_val > 0)
        {
            // If this is the parent process, then wait for child process to end.
            wait(NULL);
        }
        else
        {
            // If this the child process, continue as a left child then terminate.
            left_process(m);
            exit(EXIT_SUCCESS);
        }
    }

    // Decrement n, since this tree is reducible into subtrees, n value for the below right process is n-1.
    n = n - 1;

    // If the decremented n is 0, there is no need to proceed further, terminate the current process.
    if (n == 0)
        exit(EXIT_SUCCESS);

    // Since we are moving below in the tree, we need to fork a child process for right process and make current process wait.
    fork_val = (int)fork();

    if (fork_val < 0)
    {
        // Print an error message if process can't be created.
        fprintf(stderr, "There was an error while forking right process for pid:%d.\n", (int)getpid());
    }
    else if (fork_val > 0)
    {
        // If this is the parent process, then wait for child process to end.
        wait(NULL);
    }
    else
    {
        // If this the child process, continue as a right process then terminate.
        right_process(n, m);
        exit(EXIT_SUCCESS);
    }
    // At the end of the function, terminate the current process.
    exit(EXIT_SUCCESS);
}