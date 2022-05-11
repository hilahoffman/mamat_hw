#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"

enum {FAIL=-1, SUCCESS=0};

int element_clone_student(void *element, void **output);
void element_destroy_student(void *element);
void element_destroy_course(void *element);
int element_clone_course(void *element, void **output);



struct grades{
	struct list *students_list;
};

struct student{
	char *name; /* the students_list will contain objects of student type*/
	int id;
	struct list *courses_list;
};

struct course{
	char *course_name; // the courses_list will contain objects of course type
	int grade;
};

int search_student(struct grades *grades, int id);
struct iterator* find_student(struct grades *grades, int id);

struct grades* grades_init(){ // initialise the grades struct
	struct list *students_list;
	struct grades *grades;
	grades=(struct grades*)malloc(sizeof(*grades));
	if (!grades){ // malloc check
		//free(grades);
		return NULL;
	}
	students_list=list_init(&element_clone_student, &element_destroy_student);
	grades->students_list=students_list;
	return grades;
}

void grades_destroy(struct grades *grades){/*destroy the main struct "grades"*/
	if (!grades){ // if grades illigal
		return;
	}
	list_destroy(grades->students_list);
	free (grades);
}

//need to check if alloud to use string.h
int grades_add_student(struct grades *grades, const char *name, int id){
	if (!grades){ // if grades illigal
		return FAIL;
	}
	if(search_student(grades,id) == FAIL)/*returns FAIL if the student exists*/
		return FAIL;
	struct student *new_student;
	new_student=(struct student*)malloc(sizeof(*new_student));
	if (!new_student) {
		/* Out of memory... */
		return FAIL;
	}
	char *student_name = (char*)malloc((sizeof(char))*(strlen(name)+1));
	if (!student_name) {
		/* Out of memory... */
		free(new_student);
		return FAIL;
	}
	strcpy(student_name,name);
	new_student->name = student_name;
	new_student->id = id;
	new_student->courses_list = list_init(&element_clone_course,
								&element_destroy_course);
	if(!(list_push_back(grades->students_list, new_student))){
		/*adding the new_student to the end of the list*/
		 free(student_name);
		 free(new_student);
		 return SUCCESS;
	}
	free(student_name);
    free(new_student);
	return FAIL;
}


 int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
	if (!grades){ // if grades illigal
		return FAIL;
	}
	struct iterator* cursor = (struct iterator*)find_student(grades,id);
	if(!cursor){
		return FAIL;
		/*because if cursor equal to NULL it means that
		the student doesnt exists*/
	}
	struct student* current_student=(struct student*)list_get(cursor);
	/*after breaking the while, current_student is a pointer to the student
	that we want to add a new course for him*/
	
	struct list *courses = current_student->courses_list;
	/*courses is a pointer to the coursrs list*/
	cursor = list_begin(courses);
	/*iterator is going to the beginning of the courses list*/
	while(cursor){
		struct course *current_course = (struct course*)list_get(cursor);
		/*current_course is a pointer to a course*/
		if(!strcmp(current_course->course_name,name)){
			return FAIL;//the course is already exists
		}
		cursor=list_next(cursor);
	}
	if(0<=grade && grade<=100){
		struct course *new_course;
		new_course=(struct course*)malloc(sizeof(*new_course));
		if (!new_course) {
			/* Out of memory... */
			return FAIL;
		}
		char *new_course_name = (char*)malloc((sizeof(char))*(strlen(name)+1));
		if (!new_course_name) {
			/* Out of memory... */
			free(new_course);
			return FAIL;
		}
		strcpy(new_course_name,name);
		new_course->course_name = new_course_name;
		new_course->grade = grade;
		/*now we have a new course with a course_name and a grade and now we
		are going to push this course in the end of the courses list*/
		if(!(list_push_back(courses, new_course))){
		/*now the new item enterd to the end of the list*/
			free(new_course_name);
			free(new_course);
			return SUCCESS;
		}
		free(new_course_name);
		free(new_course);
		return FAIL;
	}
	return FAIL;
}


float grades_calc_avg(struct grades *grades, int id, char **out){
	if (!grades){ // if grades illigal
		*out = NULL;
		return FAIL;
	}
	struct iterator* cursor = find_student(grades,id);
	if(!cursor){
		*out=NULL;
		return FAIL;/*because if cursor equal to NULL it means that the
		student doesnt exists*/
	}
	struct student* current_student=(struct student*)list_get(cursor);
	/*after breaking the while, current_student is a pointer to the student
	that we want to calc his avrege*/
	int num_of_courses=0;
	float avg;
	int sum=0;//to sum all grades
	*out=(char*)malloc(sizeof(*out)); /*memory allocation*/
	if (!*out) {
			/* Out of memory... */
			return FAIL;
		}
	strcpy(*out,current_student->name);
	/*now we want to go over the courses and calculate the avrege*/
	cursor=list_begin(current_student->courses_list);/*cursor is an itrator
	placed at the beginnig of the list*/
	while(cursor){
		struct course *current_course=(struct course*)list_get(cursor);
		/*current_course is a pointer to a course in the list courses*/
		sum+=current_course->grade;
		num_of_courses++;
		cursor=list_next(cursor);
		/*cursor is now an iterator to the next element*/
	}
	if(sum==0){
		return 0;
	}
	avg=((float)sum)/((float)num_of_courses);
	return avg;
}


int grades_print_student(struct grades *grades, int id){
	if (!grades){ // if grades illigal
		return FAIL;
	}
	struct iterator* cursor = find_student(grades,id);
	if(!cursor){
		return FAIL;/*because if cursor equal to NULL it means that the
					student doesnt exists*/
	}
	struct student* current_student=(struct student*)list_get(cursor);
	/*after breaking the while, current_student is a pointer to the student
	that we want to calc his avrege now we want to go over the courses and
	print the courses*/
	printf("%s %d:", current_student->name, current_student->id );
	struct iterator *it=list_begin(current_student->courses_list);
	/*cursor is an itrator placed at the beginnig of the list*/
	while(it){
		struct course *current_course=(struct course*)list_get(it);
		/*current_course is a pointer to a course in the list courses*/
		printf(" %s %d", current_course->course_name, current_course->grade );
		it=list_next(it);/*cursor is now an iterator to the next element*/
		if(it){
			printf(",");
		}
	}
	printf("\n");
	return SUCCESS;
}


int grades_print_all(struct grades *grades){
	if (!grades){ /*if grades illigal*/
		return FAIL;
	}
	struct iterator *cursor = list_begin(grades->students_list);
	/*iterator at the beginning of the list*/
	while(cursor){
		struct student *current_student = (struct student*)list_get(cursor);
		/*current_student is a pointer to a student*/
		if(current_student){
			grades_print_student(grades, current_student->id);
		}
		cursor=list_next(cursor);
	}
	return SUCCESS;
}

/*user functions for student*/
int element_clone_student(void *element, void **output) {
	struct student *student;
	student=(struct student*)element;
	struct student *new_student;
	new_student=(struct student*)malloc(sizeof(*new_student));
	if (!new_student){
		return FAIL;
	}
	new_student->id = student->id;
	char* name=(char*)malloc(sizeof(char)*(strlen(student->name)+1));
	if(!name) {
		return FAIL;
	}
	strcpy(name, student->name);
	new_student->name=name;
	new_student->courses_list=student->courses_list;
	*output=new_student;
	return SUCCESS;

}

void element_destroy_student(void *element){
	if (!element) {
		return;
	}
	struct student *student = (struct student*) element;
	free(student->name);
	list_destroy(student->courses_list);
	free(student);
	return;
}

/*user functions for course*/
int element_clone_course(void *element, void **output) {
	struct course *course;
	course=(struct course*)element;
	struct course *new_course;
	new_course=(struct course*)malloc(sizeof(*new_course));
	if (!new_course){
		return FAIL;
	}
	new_course->grade = course->grade;
	char* course_name = (char*)malloc(sizeof(char)*
						(strlen(course->course_name)+1));
	if(!course_name) {
		return FAIL;
	}
	strcpy(course_name, course->course_name);
	new_course->course_name=course_name;
	*output=new_course;
	return SUCCESS;
}

void element_destroy_course(void *element){
	if (!element) {
		return;
	}
	struct course *course = (struct course*) element;
	free(course->course_name);
	free(course);
	return;
}

/**
 * @brief Returns FAIL if the student exist and SUCCESS otherwise
 * @param struct grades* and the requsted int id
 */

int search_student(struct grades *grades, int id){
	struct iterator *cursor = list_begin(grades->students_list);
	/*iterator at the beginning of the list*/
	struct student *current_student;
	while(cursor){
		current_student = (struct student*)list_get(cursor);
		/*current_student = a pointer to the first student*/
		if(current_student->id == id){
		/*check if there is other student with same id*/
			return FAIL;
		}
		cursor=list_next(cursor);
	}
	return SUCCESS;
}

/**
 * @brief Returns "cursor" an iterator to the student with id
 * @param struct grades* and the requsted int id
 * @note Returns NULL if cursor is NULL
 */

struct iterator* find_student(struct grades *grades, int id){
	struct iterator *cursor = list_begin(grades->students_list);
	/*iterator at the beginning of the list*/
	struct student *current_student;
	while(cursor){
		current_student = (struct student*)list_get(cursor);
		if(current_student->id == id){
		/*found the student who need to have another course*/
			return cursor;
		}
		cursor=list_next(cursor);
	}
	return cursor; /*if not found*/
}
