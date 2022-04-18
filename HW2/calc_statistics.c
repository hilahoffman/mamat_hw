#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {PASS_GRADE=55, MAT_ROWS=10, MAT_COLS=10, MAX_GRADE=100};

/**
 * @brief read from a file and calculate the statistic of a course
 * @return: none
 * @note: prints the statistic into a text in a new directory
*/

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
	
	/*open new file :course_statistics.txt*/
	FILE *stat;
	stat=fopen(argv[1], "w+");/*pointer to course_statistics.txt*/ 
	FILE *fp;
	fp=fopen(argv[2], "r");/*pointer to grades.txt*/
	
	/*define variants*/
	int students_num=0, mid, max, min,sum=0;
	double avg, pass_per;
	char c;
	
	/*computing the num of students*/
	while((c=fgetc(fp)) != EOF ) {
		if(c == '\n')
			students_num++;
	}
	fseek(fp,0,SEEK_SET);/*return to the beginning of the file*/
	
	/*make and sort the grades array to calculate the results*/
	int *grades_arr = malloc(sizeof(int)*students_num);
	if(grades_arr == NULL) {
		fprintf(stat, "Malloc Error");
	}
	else {
		for (int i=0; i<students_num; i++) {
			fscanf(fp,"%d", &grades_arr[i]);
			sum += grades_arr[i];
		}
		avg= (double)sum/students_num; /*calculate the avg*/
		for (int i=0; i<students_num; i++) {
			for (int j=1; j<students_num; j++)
				if(grades_arr[j]<grades_arr[j-1]) {
					/*swap*/
					int temp = grades_arr[j];
					grades_arr[j]= grades_arr[j-1];
					grades_arr[j-1]=temp;
				}
		}
		mid = grades_arr[((students_num+1)/2)-1];
		min = grades_arr[0];
		max = grades_arr[students_num-1];
		
		int i=0; 
		while(grades_arr[i]<PASS_GRADE && i<students_num){
			i++;
		}
		int num_of_pass = students_num - i;
		pass_per = ( (double)num_of_pass / students_num ) * 100;
		
		int mat[MAT_ROWS][MAT_COLS]={0};
		for (i=0; i<students_num; i++){
			int row=grades_arr[i]/10;
			int col=grades_arr[i]%10;
			if(grades_arr[i] == MAX_GRADE)
				mat[MAT_ROWS-1][MAT_COLS-1]++; 
			else{
				if(col== 0) {
						col= 10;
						row--;
				}
				mat[row][col-1]++;
			}
		}

		/*printing the results*/
		fprintf(stat, "num of students = %d\n", students_num);
		fprintf(stat, "avg = %.3lf\n", avg);
		fprintf(stat, "the median is - %d\n", mid);
		fprintf(stat, "max grade = %d, min grade = %d\n", max, min);
		fprintf(stat, "pass rate = %.2lf%\n", pass_per);
		
		/*printing the matrix*/
		for(int i=0; i<MAT_ROWS; i++){
			for(int j=0; j<MAT_COLS; j++){
				if(j!=MAT_COLS-1){
					fprintf(stat, "%d ", mat[i][j]);
				}
				else{
					fprintf(stat, "%d", mat[i][j]);
				}
			}
			fprintf(stat, "\n");
		}
		free(grades_arr);
	}
	fclose(stat);
	fclose(fp);
	
    return 0;
}
