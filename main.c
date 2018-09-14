//
//  main.c
//  CSE-6010 Assignment1
//
//  Created by Karl Gemayel on 8/17/17.
//  Copyright © 2017 Karl Gemayel. All rights reserved.
//
//  Student name: Haoli Sun
//  Student username: hsun325/ID：903316698

#include <stdio.h>
#include <stdlib.h>     // for rand, srand
#include <time.h>       // for time, clock
#include <string.h>     // for strncmp

// Use these variables for simplicity of code
#define RED 'R'
#define GREEN 'G'
#define VACANT ' '

// Function Prototypes: generic
void usage(const char *programName);

// Function Prototypes: matrix specific
char**      malloc_matrix   (int n1, int n2);
void        free_matrix     (int n1, int n2, char **a);
void        init_matrix     (int n1, int n2, char **a);
int         simulate        (int n1, int n2, char **a, double f);
void        print_matrix    (int n1, int n2, char **a);
char        check_satisf    (int n1, int n2, char **a, double f, int i, int j);
char        check_satisf_2  (int n1, int n2, char **a, double f, int i1, int j1,int i,int j);
void	        move_to_satisf  (int n1, int n2, char **a, double f,int i, int j) ;
void 		save_to_file    (int n1, int n2, char *name, char **a);


// Main function
int main() {

    // Start by reading the input from the command line prompt.
    // Note: when no additional arguments are passed through the
    // the command prompt, argc equals 1, and argv[0] is the 
    // name of our executable file.

    // In this case, the program takes in 3 addition arguments:
    // (1) number of rows, (2) number of columns, (3) number of
    // times to run 'simulate', and (4) value of f
	/*char argv[]="schelling'model 40 40 100 0.3";
    if (argv != 5) {
        usage(argv[0]);
        return 1;
    }


    int n1 = (int) strtol(argv[1], NULL, 10);                   // number of rows
    int n2 = (int) strtol(argv[2], NULL, 10);                   // number of columns
    int numSimulations = (int) strtol(argv[3], NULL, 10);       // number of times to run 'simulate'
    double f = strtol(argv[4], NULL);                           // the satisfiability fraction
*/

    // TODO: Your code here.
    // This part should actually run the simulate function over and over
    // and print the final result.

	int n1=100;
	int n2=100;

	double f=0.8;
    int x;
	char **mat = malloc_matrix(n1, n2);



	init_matrix(n1, n2, mat);
	printf("initial complete\n");
	print_matrix(n1, n2, mat);
	save_to_file(n1,n2,"f0.8_initial",mat);
	printf("print complete\n");
	//free(n1,n2,mat);
	printf("%s", "------");
	//at most 100 times
	for(int i=0;i<100;i++){
		printf("--------%d time step begin\n",i+1);
		x = simulate ( n1,  n2,  mat,f);
		printf("result:%d\n",x);
		//print_matrix(n1,n2,mat);
		if (x==0){break;}
		if(i==99){printf("100 time steps are not enough");}//if all cells are satisfied
	}
	print_matrix(n1,n2,mat);
	save_to_file(n1,n2,"f0.8_final",mat);

    //printf("result:%d\n",x);
	printf("--------------final matrix above----end");
	free_matrix(n1,n2,mat);
	//print_matrix(n1, n2, mat);
    return 0;
}

/**
 * Print out the usage message.
 *
 * @param programName the name of the executable file.
 */
void usage(const char *programName) {
    printf("usage: %s  n1 n2 s f\n", programName);
    printf("where:\n");
    printf("    n1      : number of rows\n");
    printf("    n2      : number of columns\n");
    printf("    s       : number of simulation iterations\n");
    printf("    f       : minimum fraction for satisfiability\n");
    printf("\nExample: %s 10 10 100 0.3\n", programName);
}

/****** Matrix Specific Functions ******\
 *                                     *
 * These functions define what matrix  *
 * operations can be performed.        *
 *                                     *
\***************************************/


/**
 * Allocate memory for a 2D matrix
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @return a pointer to the matrix
 */
char** malloc_matrix(int n1, int n2) {
    
    char** mat = NULL;       // pointer to the matrix
    // TODO: Your code here. Don't forget to:
    //Haoli's code...
    int i;
    //printf("malloc start");
    if(n1<=0||n2<=0){printf("%s\n","matrix size must be lager than 0*0");}
    mat=(char**)malloc(sizeof(char*)*n1);

    for (i=0;i<n1;i++){
    	mat[i]=(char*)malloc(sizeof(char)*n2);
    }

    // - check for invalid inputs!
    // - update the 'mat' variable
    //printf("malloc success");
    return mat;
}


/**
 * Free the space allocated for the matrix.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void free_matrix(int n1, int n2, char **a) {
    // TODO: Your code here. Don't forget to:
	//Haoli's code
	int i;

    if(n1<=0||n2<=0){printf("%s\n","matrix size must be lager than 0*0");}


	for (i=0; i<n1; i++){
		free(a[i]);
	}

	free(a);
    // - check for invalid inputs!
}


/**
 * Initialize the matrix.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void init_matrix(int n1, int n2, char **a) {

    // TODO: Your code here. Don't forget to:
	//Haoli's code
	int i,j,r;
    if(n1<=0||n2<=0){printf("%s\n","matrix size must be lager than 0*0");}


	for (i=0; i<n1; i++){
		for (j=0; j<n2; j++){
			 r=rand()%100;
			//get random digits range from 0-99.
			 //R-40%,G-40%, V-20%
			 if ((r>=0)&&(r<40)){*(*(a+i)+j)='R';}

			 if ((r>=40)&&(r<80)){*(*(a+i)+j)='G';}

			 if ((r>=80)&&(r<100)){*(*(a+i)+j)=' ';}
		}

	}
    
    // - check for invalid inputs!
}

/**
 * Print the matrix to standard output
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void print_matrix(int n1, int n2, char **a) {
	//Haoli's code
    // TODO: Your code here. Don't forget to:
	int i,j;
	if(n1<=0||n2<=0||a==NULL)
			{
				printf("input unvalid");
				return ;
		}
	for  (i=0; i<n1; i++){
		for (j=0; j<n2; j++){
			//if(a[i][j] != NULL){
			printf("%c ",*(*(a+i)+j));

			//else {printf("%d row %d col miss",i,j);
					//break;
		}//check invalid input
		printf("\n");
	}
	}

	//printf("\n");
    // - check for invalid inputs!




/**
 * Simulate one time-step using matrix 'a', where f determines
 * the minimum number of desired neighbors similar to the occupant.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 * @param f the fraction indicating the minimum number of desired similar neighbours
 * @return the number of citizens that moved or left the game in this time-step; -1 if
 * function failed.
 */
int simulate(int n1, int n2, char **a, double f) {
    //Haoli's code
    // TODO: Your code here. Don't forget to:
	int sum=0;
	if(n1<=0||n2<=0||a==NULL||f<0)
			{
				printf("input unvalid");
				return 0;
		}
    printf("simulate success start\n");
	int location_unsatif[n1][n2];//mark location of unsatisfied
	for(int i =0; i<n1; i++){
    		for( int j=0; j<n2; j++){
    			location_unsatif[i][j]=0;
    			}
    		}

	for(int i =0; i<n1; i++){
    		for( int j=0; j<n2; j++){
    			if(a[i][j]!=' '){
    			a[i][j]=check_satisf(n1,n2, a, f, i,j);// whether a[i][j] is satisfied .
    			if(a[i][j]!='R'&&a[i][j]!=' '&&a[i][j]!='G') {location_unsatif[i][j]=1;} //if unsatisfied, mark 1
    			}
    		}
	}
/*	for(int i =0; i<n1; i++){
    		for( int j=0; j<n2; j++){
    			printf("%d",location_unsatif[i][j]);
    		}
    		printf("\n");
    		}
*///to see position of unsatisfied cells

	for(int i =0; i<n1; i++){
    		for( int j=0; j<n2; j++){
    			//move unsatisfied cell
    			if(location_unsatif[i][j]==1){
    				move_to_satisf(n1,n2,a,f,i,j);
    				//print_matrix(n1,n2,a)	;//use to check matrix
    			}

    		}
	}

	//print_matrix(n1,n1,a);

	for(int i =0; i<n1; i++){
	    		for( int j=0; j<n2; j++){
	    			sum=sum+location_unsatif[i][j];//number of citizens that moved in one time step
	    		}

	    		}

    			return sum;
}
	//for(int i=0; i<100; i++){

//	}
    // - check for invalid inputs
    // - update the return value based on success/failure
    
  //  return 1;
//}

char check_satisf(int n1, int n2, char **a, double f, int i, int j){
	int total_neigh=0;//total number of neighbor, at most 8
	int same_neigh=0;//number of neighbor with same color
	if(n1<=0||n2<=0||a==NULL||f<0)
			{
				printf("input unvalid");
				return ' ';
		}
	for ( int x=i-1; x<i+2;x++ ){
		if ((x<0)||(x>n1-1)){continue;}//cells locate edge or corner do not have 8 neighbors

		for( int y=j-1; y<j+2; y++){
			if ((y<0)||(y>n2-1)||((i==x)&&(j==y))){continue;}

			if(a[x][y]!=' '){total_neigh=total_neigh+1;}// all neighbor cells which are not vacant count to total number of neighbor
			if(a[i][j]=='R'){
				if(a[x][y]=='R'||a[x][y]=='Z'){same_neigh=same_neigh+1;}//R and Z are both Red cells
			}
			if(a[i][j]=='G'){
							if(a[x][y]=='G'||a[x][y]=='X'){same_neigh=same_neigh+1;}//G and X are both green cells
			}

		}
	}

	if((total_neigh*f>same_neigh)&&(a[i][j]=='R')) return 'Z';//color:R and not satisf
	if((total_neigh*f>same_neigh)&&(a[i][j]=='G')) return 'X';//color:G and not satisf
	else return a[i][j];

}


void	  move_to_satisf(int n1, int n2, char **a,double f, int i, int j){
	int i1,j1;
	i1=rand()%n1;
	j1=rand()%n2;//randomly select a cell as starting
	if(n1<=0||n2<=0||a==NULL||f<0)
			{
				printf("input unvalid");
				return ;
		}
	//printf("------------%s:%d %d\n","start location:",i1,j1);//print start position
	for (int i2=i1; i2<n1; i2++){//start from a[i1][j1] to the last cell a[n1][n2]
		for(int j2=0; j2<n2; j2++){
			if(j2<j1&&i2==i1){continue;}// start from j1
			if (a[i2][j2]==' '){
				a[i2][j2]=check_satisf_2(n1,n2,a, f, i2, j2, i, j);//if "v", check if satisfy
				 //printf("%c\n",a[i2][j2]);
				if (a[i2][j2]!=' '){
					a[i][j]=' ';//if a[i2][j2]!=V means cells move to a[i2][j2], its original position should change to 'V'
					break;
				}
			}
		}
		if (a[i][j]==' '){break;}
	}
	if(a[i][j]!=' '){
		for (int i2=0; i2<i1; i2++){//start from first cell a[0][0] to the start position
			for(int j2=0; j2<n2; j2++){
				if(i2==i1&&j2==j1){break;}
				if (a[i2][j2]==' '){
					a[i2][j2]=check_satisf_2(n1,n2,a, f, i2, j2, i, j);//if vacant, check whether satisfy after puting a R or G cell
					//printf("%c\n",a[i2][j2]);
					if (a[i2][j2]!=' '){
						a[i][j]=' ';
						break;
					}
				}
			}
			if (a[i][j]==' '){break;}
		}
	}
	if(a[i][j]!=' '){a[i][j]=' '; //After scan all vacant position, if there is no position satisfied it, this cell out
		//printf("a[%d][%d] remove\n",i,j);
	}

}

//check if a vacant cell can be satisfied for R or G
char check_satisf_2(int n1, int n2, char **a, double f, int i2, int j2,int i, int j){
	if(n1<=0||n2<=0||a==NULL||f<0)
			{
				printf("input unvalid");
				return ' ';
		}
	int total_neigh=0;
	int same_neigh=0;

	for ( int x=i2-1; x<i2+2;x++ ){
		if ((x<0)||(x>n1-1)){continue;}// for special position like corner and edge

		for( int y=j2-1; y<j2+2; y++){
			if ((y<0)||(y>n2-1)||((i2==x)&&(j2==y))){continue;}// for special position like corner and edge

			if(a[x][y]!=' '){total_neigh=total_neigh+1;}
			if(a[i][j]=='Z'){
				if(a[x][y]=='R'||a[x][y]=='Z'){same_neigh=same_neigh+1;}
			}
			if(a[i][j]=='X'){
							if(a[x][y]=='G'||a[x][y]=='X'){same_neigh=same_neigh+1;}
			}

		}
	}
	//
	if((i>=i2-1)&&(i<=i2+1)&&(j<=j2+1)&&(j>=j2-1)){// if a[i][j] is neighbor of a[i2][j2], it should not be counted, since it now move to a[i2][j2]
		same_neigh=same_neigh-1;
		total_neigh=total_neigh-1;}
	//printf("%d %d\n",total_neigh,same_neigh);
	if((total_neigh*f<=same_neigh)&&(a[i][j]=='Z')) return 'R';//color:R and  satisf
	if((total_neigh*f<=same_neigh)&&(a[i][j]=='X')) return 'G';//color:G and  satisf
	else return ' ';

}

void save_to_file(int n1, int n2, char *name, char **a){
	if(n1<=0||n2<=0||a==NULL)
			{
				printf("input unvalid");
				return ;
		}
	FILE* doc=fopen(name,"w");
	for(int i=0; i<n1;i++){
		for(int j=0; j<n2; j++){
			fprintf(doc,"%c",a[i][j]);
			fprintf(doc,"%c",',');
		}
		fprintf(doc,"\n");
	}
	fclose(doc);

}










