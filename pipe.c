#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
int p1[2], p2[2];
int READ = 0;
int WRITE = 1;
pipe( p1 );
pipe( p2 );
int f1 = fork(); // Has to be at the end... Oops...

if( f1 ){
    close( p1[READ] ); // For parent to write to child
    close( p2[WRITE] ); // For child to read what parent wrote

    int num = 4;

    printf("[parent] sending %d\n", num);
    write( p1[WRITE], &num, sizeof(num));
    close ( p1[WRITE] ); // Done writing. So close it.

    int num2;
    read( p2[READ], &num2, sizeof(num2) ); // Read it
    close ( p2[READ] ); //Finished? Close it. 
    printf("[parent] received: %d\n", num2); // Parent gets the number back. 
}

else{
    close( p1[WRITE] ); // For parent to read
    close( p2[READ] ); // For child to write

    int num2;
    read( p1[READ], &num2, sizeof(num2) );
    printf("[child] received: %d\n", num2);

    num2 += 3;

    printf("[child] altered regular num to: %d\n", num2);
    write( p2[WRITE], &num2, sizeof(num2) ); // Write it. 
    close( p1[READ] ); 
    close( p2[WRITE] );

    }

    return 0;

}	